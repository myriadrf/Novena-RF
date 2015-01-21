------------------------------------------------------------------------
-- TWBW Framer - ADC sample data framer with time and burst controls
--
-- Control port documentation:
--
-- Each control bus message consists of four 32-bit transactions.
-- The last 32-bit transaction in each message has a tlast asserted.
-- The message contains flags, a frame size, a burst size, and a time.
-- The tag is forwarded to the status port to help identify status responses.
-- The burst and time fields are only applicable when the burst and time
-- flags are set respectively; but must always be present in the message.
--
-- Control bus format:
--   ctrl0[31] - time stamp flag
--   ctrl0[28] - finite burst flag
--   ctrl0[27] - continuous flag
--   ctrl0[23:16] - identifying tag (forwarded to status port)
--   ctrl0[15:0] - frame size (number of transfers in a frame)
--   ctrl1[31:0] - burst size (only used with finite burst flag)
--   ctrl2[31:0] - 64 bit time high in clock ticks (used with time flag)
--   ctrl3[31:0] - 64 bit time low in clock ticks (used with time flag)
--
-- Status port documentation:
--
-- Each status bus message consists of four 32-bit transactions.
-- The last 32-bit transaction in each message has a tlast asserted.
-- Each message contains a status indicator and the event time.
-- A status message is reported upon burst completion,
-- invalid time specification, overflow condition,
-- and cessation of continuous streaming.
--
-- Status bus format:
--   stat0[31] - time stamp flag indicates valid time
--   stat0[30] - time error event occurred
--   stat0[29] - overflow event occurred
--   stat0[28] - finite burst ended
--   stat0[27] - continuous streaming stopped
--   stat0[23:16] - identifying tag (forwarded from control port)
--   stat1[31:0] - unused
--   stat2[31:0] - 64 bit time high in clock ticks (used with time flag)
--   stat3[31:0] - 64 bit time low in clock ticks (used with time flag)
--
-- Output port documentation:
--
-- The output port contains framed sample data with 4 header lines.
-- The last transaction in each frame has a tlast asserted.
-- The output port data width may be larger than 32 bits,
-- but only the first 32 bits of each header line are used.
--
-- Output bus format:
--   out0[31] - time stamp flag indicates valid time
--   out0[28] - finite burst flag (forwarded from control port)
--   out0[27] - continuous flag (forwarded from control port)
--   out0[23:16] - identifying tag (forwarded from control port)
--   out0[15:0] - frame size (forwarded from control port)
--   out1[31:0] - current burst size counting down to zero
--   out2[31:0] - 64 bit time high in clock ticks (used with time flag)
--   out3[31:0] - 64 bit time low in clock ticks (used with time flag)
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity twbw_framer is
    generic(
        -- the width of the ADC bus
        DATA_WIDTH : positive := 32;

        -- the width of the time bus
        -- the time bus can be no wider than 64 bits
        TIME_WIDTH : positive := 48;

        -- the size of the output fifo containing the framed data
        -- either use a small number and provide external buffering
        -- or set this to a reasonable size for your application
        FIFO_DEPTH : positive := 1024;

        -- the depth of the control and status fifos
        CTRL_DEPTH : positive := 16
    );
    port(
        -- The ADC clock domain used for all interfaces.
        clk : in std_logic;

        -- synchronous reset
        rst : in std_logic;

        -- The current time in clock ticks.
        in_time : in unsigned(TIME_WIDTH-1 downto 0);

        -- Input ADC interface:
        -- There is no ready signal, a valid signal with no space => overflow.
        -- To allow for frame overhead, this bus cannot be valid every cycle.
        -- Many interfaces do not produce receive data at every clock cycle,
        -- If this is not the case, we recommend doubling the ADC data width.
        adc_tdata : in std_logic_vector(DATA_WIDTH-1 downto 0);
        adc_tvalid : in std_logic;

        -- Output stream interface:
        -- The tuser signal indicates metadata and not sample data.
        out_tdata : out std_logic_vector(DATA_WIDTH-1 downto 0);
        out_tuser : out std_logic_vector(0 downto 0);
        out_tlast : out std_logic;
        out_tvalid : out std_logic;
        out_tready : in std_logic;

        -- control bus interface
        ctrl_tdata : in std_logic_vector(31 downto 0);
        ctrl_tlast : in std_logic;
        ctrl_tvalid : in std_logic;
        ctrl_tready : out std_logic;

        -- status bus interface
        stat_tdata : out std_logic_vector(31 downto 0);
        stat_tlast : out std_logic;
        stat_tvalid : out std_logic;
        stat_tready : in std_logic;

        -- Receive activity indicator based on internal state.
        -- Example: use this signal to drive external switches and LEDs.
        adc_active : out boolean
    );
end entity twbw_framer;

architecture rtl of twbw_framer is

    -- state machine inspects the ADC from these signals
    signal adc_fifo_in_ready : std_logic;
    signal adc_fifo_out_data : std_logic_vector(DATA_WIDTH-1 downto 0);
    signal adc_fifo_out_valid : std_logic;
    signal adc_fifo_out_ready : std_logic;

    -- state machine inspects the control messages from these signals
    signal ctrl_fifo_out_data : std_logic_vector(127 downto 0);
    signal ctrl_fifo_out_valid : std_logic;
    signal ctrl_fifo_out_ready : std_logic;

    -- state machine controls the outgoing status bus signals
    signal stat_fifo_in_data : std_logic_vector(127 downto 0);
    signal stat_fifo_in_valid : std_logic;
    signal stat_fifo_in_ready : std_logic;

    -- state machine controls the outgoing framed bus signals
    signal framed_fifo_out_full : std_logic_vector(2+DATA_WIDTH-1 downto 0);
    signal framed_fifo_in_full : std_logic_vector(2+DATA_WIDTH-1 downto 0);
    signal framed_fifo_in_data : std_logic_vector(DATA_WIDTH-1 downto 0);
    signal framed_fifo_in_hdr : std_logic_vector(DATA_WIDTH-1 downto 0) := (others => '0');
    signal framed_fifo_in_user : std_logic_vector(0 downto 0);
    signal framed_fifo_in_last : std_logic;
    signal framed_fifo_in_valid : std_logic;
    signal framed_fifo_in_ready : std_logic;

    -- internal adc active indicator
    signal adc_active_i : boolean;

    -- state machine enumerations
    type state_type is (
        STATE_CTRL_IDLE,
        STATE_CTRL_READ,
        STATE_WAIT_TIME,
        STATE_HDR0_OUT,
        STATE_HDR1_OUT,
        STATE_HDR2_OUT,
        STATE_HDR3_OUT,
        STATE_SAMPS_OUT,
        STATE_STAT_OUT);
    signal state : state_type;

    -- state variables set by the state machine
    signal time_flag : std_logic := '0';
    signal burst_flag : std_logic := '0';
    signal continuous_flag : std_logic := '0';
    signal ctrl_tag : std_logic_vector(7 downto 0) := (others => '0');
    signal burst_size : unsigned(31 downto 0) := to_unsigned(0, 32);
    signal frame_size : unsigned(15 downto 0) := to_unsigned(0, 16);
    signal frame_count : unsigned(15 downto 0) := to_unsigned(0, 16);
    signal stream_time : unsigned(TIME_WIDTH-1 downto 0) := to_unsigned(0, TIME_WIDTH);
    signal frame_done : boolean := false;
    signal burst_done : boolean := false;
    signal overflow : boolean := false;

begin
    assert (TIME_WIDTH <= 64) report "twbw_framer: time width too large" severity failure;
    assert (DATA_WIDTH >= 32) report "twbw_framer: data width too small" severity failure;

    --boolean condition tracking
    adc_active <= adc_active_i;
    frame_done <= frame_count = to_unsigned(0, frame_count'length);
    burst_done <= burst_size = to_unsigned(0, burst_size'length);

    --------------------------------------------------------------------
    -- short fifo between adc out and state machine
    -- this fifo ensures a continuous streaming despite framing overhead
    -- the input time is associated with each adc data in this fifo
    --------------------------------------------------------------------
    adc_fifo: entity work.StreamFifo
    generic map (
        --configure a small distributed ram
        MEM_SIZE => 16, --must be greater than the number of header and wait states
        SYNC_READ => false
    )
    port map (
        clk => clk,
        rst => rst,
        in_data => adc_tdata,
        in_valid => adc_tvalid,
        in_ready => adc_fifo_in_ready,
        out_data => adc_fifo_out_data,
        out_valid => adc_fifo_out_valid,
        out_ready => adc_fifo_out_ready
    );

    adc_fifo_out_ready <=
        '1' when not adc_active_i else --always draining the fifo when inactive
        '0' when state /= STATE_SAMPS_OUT else framed_fifo_in_ready; --otherwise plugged unless forwarding samples

    --------------------------------------------------------------------
    -- short fifo between ctrl bus and state machine
    -- this fifo gives us a small command storage space
    --------------------------------------------------------------------
    ctrl_fifo: entity work.ctrl_msg_fifo128
    generic map (
        MEM_SIZE => CTRL_DEPTH
    )
    port map (
        clk => clk,
        rst => rst,
        in_tdata => ctrl_tdata,
        in_tlast => ctrl_tlast,
        in_tvalid => ctrl_tvalid,
        in_tready => ctrl_tready,
        out_tdata => ctrl_fifo_out_data,
        out_tvalid => ctrl_fifo_out_valid,
        out_tready => ctrl_fifo_out_ready
    );

    ctrl_fifo_out_ready <= '1' when (state = STATE_CTRL_READ) else '0';

    --------------------------------------------------------------------
    -- short fifo between state machine and stat bus
    -- this fifo gives us a small status storage space
    --------------------------------------------------------------------
    stat_fifo: entity work.stat_msg_fifo128
    generic map (
        MEM_SIZE => CTRL_DEPTH
    )
    port map (
        clk => clk,
        rst => rst,
        in_tdata => stat_fifo_in_data,
        in_tvalid => stat_fifo_in_valid,
        in_tready => stat_fifo_in_ready,
        out_tdata => stat_tdata,
        out_tlast => stat_tlast,
        out_tvalid => stat_tvalid,
        out_tready => stat_tready
    );

    stat_fifo_in_valid <= '1' when (state = STATE_STAT_OUT) else '0';

    --------------------------------------------------------------------
    -- short fifo between state machine and output stream
    --------------------------------------------------------------------
    framed_fifo : entity work.StreamFifo
    generic map (
        MEM_SIZE => FIFO_DEPTH,
        SYNC_READ => FIFO_DEPTH > 16
    )
    port map (
        clk => clk,
        rst => rst,
        in_data => framed_fifo_in_full,
        in_valid => framed_fifo_in_valid,
        in_ready => framed_fifo_in_ready,
        out_data => framed_fifo_out_full,
        out_valid => out_tvalid,
        out_ready => out_tready
    );

    framed_fifo_in_data <= adc_fifo_out_data when (state = STATE_SAMPS_OUT) else framed_fifo_in_hdr;
    framed_fifo_in_user <= "1" when (
        state = STATE_HDR0_OUT or
        state = STATE_HDR1_OUT or
        state = STATE_HDR2_OUT or
        state = STATE_HDR3_OUT) else "0";

    framed_fifo_in_last <= '1' when (state = STATE_SAMPS_OUT and (
        overflow or -- an overflow event
        frame_done or -- the frame ended
        (burst_flag = '1' and burst_done) or -- burst mode and counted last sample in burst
        (continuous_flag = '1' and ctrl_fifo_out_valid = '1') -- continuous mode and a new control message has arrived
    )) else '0';

    framed_fifo_in_full <= framed_fifo_in_user & framed_fifo_in_last & framed_fifo_in_data;
    framed_fifo_in_valid <=
        adc_fifo_out_valid when (state = STATE_SAMPS_OUT) else framed_fifo_in_user(0);

    out_tdata <= framed_fifo_out_full(DATA_WIDTH-1 downto 0);
    out_tlast <= framed_fifo_out_full(DATA_WIDTH);
    out_tuser <= framed_fifo_out_full(DATA_WIDTH+1 downto DATA_WIDTH+1);

    --------------------------------------------------------------------
    -- framer state machine
    --------------------------------------------------------------------
    process (clk) begin

    framed_fifo_in_hdr <= (others => '0');
    if (state = STATE_HDR0_OUT) then
        framed_fifo_in_hdr(31) <= time_flag;
        framed_fifo_in_hdr(28) <= burst_flag;
        framed_fifo_in_hdr(27) <= continuous_flag;
        framed_fifo_in_hdr(23 downto 16) <= ctrl_tag;
        framed_fifo_in_hdr(15 downto 0) <= std_logic_vector(frame_size);
    elsif (state = STATE_HDR1_OUT) then
        framed_fifo_in_hdr(31 downto 0) <= std_logic_vector(burst_size);
    elsif (state = STATE_HDR2_OUT) then
        framed_fifo_in_hdr(TIME_WIDTH-32-1 downto 0) <= std_logic_vector(stream_time(TIME_WIDTH-1 downto 32));
    elsif (state = STATE_HDR3_OUT) then
        framed_fifo_in_hdr(31 downto 0) <= std_logic_vector(stream_time(31 downto 0));
    end if;

    --always load up the next status message
    if (state /= STATE_STAT_OUT) then
        stat_fifo_in_data(TIME_WIDTH-1 downto 0) <= std_logic_vector(in_time);
        stat_fifo_in_data(127) <= '1'; --always has time flag for status
        stat_fifo_in_data(119 downto 112) <= ctrl_tag;
    end if;

    if (rising_edge(clk)) then
        if (rst = '1') then
            adc_active_i <= false;
            state <= STATE_CTRL_IDLE;
            time_flag <= '0';
            burst_flag <= '0';
            continuous_flag <= '0';
            ctrl_tag <= (others => '0');
            burst_size <= to_unsigned(0, burst_size'length);
            frame_size <= to_unsigned(0, frame_size'length);
            frame_count <= to_unsigned(0, frame_count'length);
            stream_time <= to_unsigned(0, stream_time'length);
            stat_fifo_in_data <= (others => '0');
            overflow <= false;
        else case state is

        when STATE_CTRL_IDLE =>
            -- state idle always returns to inactive
            -- remain inactive until a command begins
            stat_fifo_in_data <= (others => '0');
            adc_active_i <= false;
            state <= STATE_CTRL_READ;
            overflow <= false;

        when STATE_CTRL_READ =>
            if (ctrl_fifo_out_ready = '1' and ctrl_fifo_out_valid = '1') then
                --register all relevant fields from the control message
                time_flag <= ctrl_fifo_out_data(127);
                burst_flag <= ctrl_fifo_out_data(124);
                continuous_flag <= ctrl_fifo_out_data(123);
                ctrl_tag <= ctrl_fifo_out_data(119 downto 112);
                frame_size <= unsigned(ctrl_fifo_out_data(111 downto 96));
                burst_size <= unsigned(ctrl_fifo_out_data(95 downto 64));
                stream_time <= unsigned(ctrl_fifo_out_data(TIME_WIDTH-1 downto 0));
                state <= STATE_WAIT_TIME;
            end if;

        when STATE_WAIT_TIME =>
            --wait for the specified time to occur
            --if no time was specified, leave asap
            frame_count <= frame_size;
            if (time_flag = '0') then
                adc_active_i <= true;
                state <= STATE_HDR0_OUT;
                stream_time <= in_time;
            elsif (in_time > stream_time) then
                stat_fifo_in_data(126) <= '1';
                state <= STATE_STAT_OUT;
            elsif (in_time = stream_time) then
                adc_active_i <= true;
                state <= STATE_HDR0_OUT;
            end if;

        when STATE_HDR0_OUT =>
            --wait for the output fifo to accept a transfer
            if (framed_fifo_in_valid = '1' and framed_fifo_in_ready = '1') then
                state <= STATE_HDR1_OUT;
            end if;

        when STATE_HDR1_OUT =>
            --wait for the output fifo to accept a transfer
            if (framed_fifo_in_valid = '1' and framed_fifo_in_ready = '1') then
                state <= STATE_HDR2_OUT;
            end if;

        when STATE_HDR2_OUT =>
            --wait for the output fifo to accept a transfer
            if (framed_fifo_in_valid = '1' and framed_fifo_in_ready = '1') then
                state <= STATE_HDR3_OUT;
            end if;

        when STATE_HDR3_OUT =>
            --wait for the output fifo to accept a transfer
            if (framed_fifo_in_valid = '1' and framed_fifo_in_ready = '1') then
                state <= STATE_SAMPS_OUT;
            end if;

        when STATE_SAMPS_OUT =>
            --overflow indicator is sticky, only cleared by idle state
            if (not overflow) then
                overflow <= adc_tvalid = '1' and adc_fifo_in_ready = '0';
            end if;

            --wait for the output fifo to accept a transfer
            if (framed_fifo_in_valid = '1' and framed_fifo_in_ready = '1') then
                frame_count <= frame_count - 1;
                burst_size <= burst_size - 1;
            end if;

            --end this state under the various conditions below
            if (framed_fifo_in_valid = '1' and framed_fifo_in_ready = '1' and framed_fifo_in_last = '1') then
                time_flag <= '0'; -- dont wait on time again
                if (overflow) then
                    stat_fifo_in_data(125) <= '1';
                    state <= STATE_STAT_OUT;
                elsif (burst_flag = '1' and burst_done) then
                    stat_fifo_in_data(124) <= '1';
                    state <= STATE_STAT_OUT;
                elsif (continuous_flag = '1' and ctrl_fifo_out_valid = '1') then
                    state <= STATE_CTRL_READ;
                elsif (frame_done) then
                    state <= STATE_WAIT_TIME;
                else
                    stat_fifo_in_data(123) <= '1';
                    state <= STATE_STAT_OUT;
                end if;
            end if;

        when STATE_STAT_OUT =>
            --wait for the status fifo to accept the transfer
            if (stat_fifo_in_valid = '1' and stat_fifo_in_ready = '1') then
                state <= STATE_CTRL_IDLE;
            end if;

        end case;
        end if;
    end if;

    end process;

end architecture rtl;
