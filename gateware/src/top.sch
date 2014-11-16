<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan6" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="RESETBMCU" />
        <signal name="cpu_mosi" />
        <signal name="cpu_sclk" />
        <signal name="cpu_sen" />
        <signal name="APOPTOSIS" />
        <signal name="lms_miso" />
        <signal name="lms_sclk" />
        <signal name="lms_mosi" />
        <signal name="lms_sen" />
        <signal name="clk_in" />
        <signal name="cpu_clk" />
        <signal name="txdds_fcw_upd" />
        <signal name="txdds_fcw(26:0)" />
        <signal name="measburst(15:0)" />
        <signal name="lms_txen" />
        <signal name="lms_rxen" />
        <signal name="lms_lmsrst" />
        <signal name="mrf_gpio0" />
        <signal name="mrf_gpio1" />
        <signal name="mrf_gpio2" />
        <signal name="XLXN_30(2:0)" />
        <signal name="actid" />
        <signal name="FPGA_LED2" />
        <signal name="cpu_miso" />
        <signal name="TXIQSEL" />
        <signal name="TXD(11:0)" />
        <port polarity="Input" name="RESETBMCU" />
        <port polarity="Input" name="cpu_mosi" />
        <port polarity="Input" name="cpu_sclk" />
        <port polarity="Input" name="cpu_sen" />
        <port polarity="Output" name="APOPTOSIS" />
        <port polarity="Input" name="lms_miso" />
        <port polarity="Output" name="lms_sclk" />
        <port polarity="Output" name="lms_mosi" />
        <port polarity="Output" name="lms_sen" />
        <port polarity="Input" name="clk_in" />
        <port polarity="Input" name="cpu_clk" />
        <port polarity="Output" name="lms_txen" />
        <port polarity="Output" name="lms_rxen" />
        <port polarity="Output" name="lms_lmsrst" />
        <port polarity="Output" name="mrf_gpio0" />
        <port polarity="Output" name="mrf_gpio1" />
        <port polarity="Output" name="mrf_gpio2" />
        <port polarity="Output" name="FPGA_LED2" />
        <port polarity="Output" name="cpu_miso" />
        <port polarity="Output" name="TXIQSEL" />
        <port polarity="Output" name="TXD(11:0)" />
        <blockdef name="alive">
            <timestamp>2014-7-10T7:47:9</timestamp>
            <line x2="0" y1="32" y2="32" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
            <rect width="256" x="64" y="-128" height="192" />
        </blockdef>
        <blockdef name="spi_bypass">
            <timestamp>2014-7-10T12:59:24</timestamp>
            <rect width="256" x="64" y="-448" height="264" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
        </blockdef>
        <blockdef name="spi_mod">
            <timestamp>2014-7-22T8:26:58</timestamp>
            <line x2="0" y1="0" y2="0" x1="64" />
            <rect width="64" x="0" y="-76" height="24" />
            <line x2="0" y1="-64" y2="-64" x1="64" />
            <line x2="384" y1="-192" y2="-192" x1="320" />
            <rect width="64" x="320" y="-140" height="24" />
            <line x2="384" y1="-128" y2="-128" x1="320" />
            <line x2="0" y1="-704" y2="-704" x1="64" />
            <line x2="0" y1="-592" y2="-592" x1="64" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-368" y2="-368" x1="64" />
            <rect width="64" x="0" y="-268" height="24" />
            <line x2="0" y1="-256" y2="-256" x1="64" />
            <line x2="384" y1="-704" y2="-704" x1="320" />
            <line x2="384" y1="-640" y2="-640" x1="320" />
            <line x2="384" y1="-576" y2="-576" x1="320" />
            <line x2="384" y1="-512" y2="-512" x1="320" />
            <line x2="384" y1="-448" y2="-448" x1="320" />
            <line x2="384" y1="-384" y2="-384" x1="320" />
            <line x2="384" y1="-320" y2="-320" x1="320" />
            <line x2="384" y1="-256" y2="-256" x1="320" />
            <rect width="256" x="64" y="-736" height="760" />
        </blockdef>
        <blockdef name="constant">
            <timestamp>2006-1-1T10:10:10</timestamp>
            <rect width="112" x="0" y="0" height="64" />
            <line x2="112" y1="32" y2="32" x1="144" />
        </blockdef>
        <blockdef name="dds_top">
            <timestamp>2014-7-11T12:49:41</timestamp>
            <rect width="256" x="64" y="-256" height="256" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <rect width="64" x="320" y="-44" height="24" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <block symbolname="spi_mod" name="XLXI_4">
            <blockpin signalname="cpu_mosi" name="sadin" />
            <blockpin signalname="cpu_sclk" name="saclk" />
            <blockpin signalname="cpu_sen" name="saen" />
            <blockpin signalname="RESETBMCU" name="hreset" />
            <blockpin signalname="XLXN_30(2:0)" name="maddress(2:0)" />
            <blockpin signalname="measburst(15:0)" name="measburst(15:0)" />
            <blockpin name="sadout" />
            <blockpin signalname="mrf_gpio0" name="gpio0" />
            <blockpin signalname="mrf_gpio1" name="gpio1" />
            <blockpin signalname="mrf_gpio2" name="gpio2" />
            <blockpin signalname="lms_txen" name="txen" />
            <blockpin signalname="lms_rxen" name="rxen" />
            <blockpin signalname="lms_lmsrst" name="reset" />
            <blockpin signalname="txdds_fcw_upd" name="txdds_fcw_upd" />
            <blockpin name="oen" />
            <blockpin signalname="txdds_fcw(26:0)" name="txdds_fcw(26:0)" />
            <blockpin signalname="actid" name="actid" />
        </block>
        <block symbolname="alive" name="XLXI_1">
            <blockpin signalname="clk_in" name="clk" />
            <blockpin signalname="FPGA_LED2" name="beat" />
            <blockpin signalname="APOPTOSIS" name="APOPTOSIS" />
            <blockpin signalname="RESETBMCU" name="rst" />
        </block>
        <block symbolname="spi_bypass" name="XLXI_2">
            <blockpin signalname="cpu_sclk" name="cpu_sclk" />
            <blockpin signalname="cpu_mosi" name="cpu_mosi" />
            <blockpin signalname="lms_miso" name="lms_miso" />
            <blockpin signalname="cpu_sen" name="cpu_sen" />
            <blockpin signalname="lms_sclk" name="lms_sclk" />
            <blockpin signalname="lms_mosi" name="lms_mosi" />
            <blockpin signalname="cpu_miso" name="cpu_miso" />
            <blockpin signalname="lms_sen" name="lms_sen" />
        </block>
        <block symbolname="alive" name="XLXI_3">
            <blockpin signalname="cpu_clk" name="clk" />
            <blockpin name="beat" />
            <blockpin name="APOPTOSIS" />
            <blockpin signalname="RESETBMCU" name="rst" />
        </block>
        <block symbolname="dds_top" name="XLXI_13">
            <blockpin signalname="clk_in" name="clk" />
            <blockpin signalname="RESETBMCU" name="nrst" />
            <blockpin signalname="txdds_fcw_upd" name="wrfcw" />
            <blockpin signalname="txdds_fcw(26:0)" name="fcw(26:0)" />
            <blockpin signalname="TXIQSEL" name="iqsel" />
            <blockpin signalname="TXD(11:0)" name="diq(11:0)" />
        </block>
        <block symbolname="constant" name="XLXI_6">
            <attr value="3" name="CValue">
                <trait delete="all:1 sym:0" />
                <trait editname="all:1 sch:0" />
                <trait valuetype="BitVector 32 Hexadecimal" />
            </attr>
            <blockpin signalname="XLXN_30(2:0)" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1120" y="1424" name="XLXI_1" orien="R0">
        </instance>
        <branch name="APOPTOSIS">
            <wire x2="1776" y1="1392" y2="1392" x1="1504" />
        </branch>
        <instance x="1120" y="2080" name="XLXI_2" orien="R0">
        </instance>
        <branch name="cpu_sclk">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="993" y="1664" type="branch" />
            <wire x2="992" y1="1664" y2="1664" x1="896" />
            <wire x2="1120" y1="1664" y2="1664" x1="992" />
        </branch>
        <branch name="cpu_mosi">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="989" y="1728" type="branch" />
            <wire x2="992" y1="1728" y2="1728" x1="896" />
            <wire x2="1120" y1="1728" y2="1728" x1="992" />
        </branch>
        <branch name="lms_miso">
            <wire x2="1120" y1="1792" y2="1792" x1="896" />
        </branch>
        <branch name="cpu_sen">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="989" y="1856" type="branch" />
            <wire x2="992" y1="1856" y2="1856" x1="896" />
            <wire x2="1120" y1="1856" y2="1856" x1="992" />
        </branch>
        <branch name="lms_sclk">
            <wire x2="1696" y1="1664" y2="1664" x1="1504" />
        </branch>
        <branch name="lms_mosi">
            <wire x2="1696" y1="1728" y2="1728" x1="1504" />
        </branch>
        <branch name="lms_sen">
            <wire x2="1696" y1="1856" y2="1856" x1="1504" />
        </branch>
        <branch name="RESETBMCU">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="1002" y="1456" type="branch" />
            <wire x2="1008" y1="1456" y2="1456" x1="896" />
            <wire x2="1120" y1="1456" y2="1456" x1="1008" />
        </branch>
        <branch name="clk_in">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="992" y="1328" type="branch" />
            <wire x2="992" y1="1328" y2="1328" x1="896" />
            <wire x2="1120" y1="1328" y2="1328" x1="992" />
        </branch>
        <instance x="1136" y="1104" name="XLXI_3" orien="R0">
        </instance>
        <branch name="RESETBMCU">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1056" y="1136" type="branch" />
            <wire x2="1056" y1="1136" y2="1136" x1="896" />
            <wire x2="1136" y1="1136" y2="1136" x1="1056" />
        </branch>
        <branch name="cpu_clk">
            <wire x2="1136" y1="1008" y2="1008" x1="896" />
        </branch>
        <iomarker fontsize="28" x="1776" y="1392" name="APOPTOSIS" orien="R0" />
        <iomarker fontsize="28" x="896" y="1664" name="cpu_sclk" orien="R180" />
        <iomarker fontsize="28" x="896" y="1728" name="cpu_mosi" orien="R180" />
        <iomarker fontsize="28" x="896" y="1792" name="lms_miso" orien="R180" />
        <iomarker fontsize="28" x="896" y="1856" name="cpu_sen" orien="R180" />
        <iomarker fontsize="28" x="1696" y="1664" name="lms_sclk" orien="R0" />
        <iomarker fontsize="28" x="1696" y="1728" name="lms_mosi" orien="R0" />
        <iomarker fontsize="28" x="1696" y="1856" name="lms_sen" orien="R0" />
        <iomarker fontsize="28" x="896" y="1456" name="RESETBMCU" orien="R180" />
        <iomarker fontsize="28" x="896" y="1328" name="clk_in" orien="R180" />
        <iomarker fontsize="28" x="896" y="1008" name="cpu_clk" orien="R180" />
        <instance x="1136" y="816" name="XLXI_4" orien="R0">
        </instance>
        <branch name="txdds_fcw_upd">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1664" y="624" type="branch" />
            <wire x2="1664" y1="624" y2="624" x1="1520" />
            <wire x2="1808" y1="624" y2="624" x1="1664" />
        </branch>
        <branch name="txdds_fcw(26:0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1680" y="688" type="branch" />
            <wire x2="1680" y1="688" y2="688" x1="1520" />
            <wire x2="1808" y1="688" y2="688" x1="1680" />
        </branch>
        <branch name="lms_txen">
            <wire x2="1792" y1="368" y2="368" x1="1520" />
            <wire x2="1808" y1="368" y2="368" x1="1792" />
        </branch>
        <branch name="lms_rxen">
            <wire x2="1792" y1="432" y2="432" x1="1520" />
            <wire x2="1808" y1="432" y2="432" x1="1792" />
        </branch>
        <branch name="lms_lmsrst">
            <wire x2="1792" y1="496" y2="496" x1="1520" />
            <wire x2="1808" y1="496" y2="496" x1="1792" />
        </branch>
        <branch name="mrf_gpio0">
            <wire x2="1792" y1="176" y2="176" x1="1520" />
            <wire x2="1808" y1="176" y2="176" x1="1792" />
        </branch>
        <branch name="mrf_gpio1">
            <wire x2="1792" y1="240" y2="240" x1="1520" />
            <wire x2="1808" y1="240" y2="240" x1="1792" />
        </branch>
        <branch name="mrf_gpio2">
            <wire x2="1792" y1="304" y2="304" x1="1520" />
            <wire x2="1808" y1="304" y2="304" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1808" y="368" name="lms_txen" orien="R0" />
        <iomarker fontsize="28" x="1808" y="432" name="lms_rxen" orien="R0" />
        <iomarker fontsize="28" x="1808" y="176" name="mrf_gpio0" orien="R0" />
        <iomarker fontsize="28" x="1808" y="240" name="mrf_gpio1" orien="R0" />
        <iomarker fontsize="28" x="1808" y="304" name="mrf_gpio2" orien="R0" />
        <iomarker fontsize="28" x="1808" y="496" name="lms_lmsrst" orien="R0" />
        <branch name="cpu_mosi">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1024" y="112" type="branch" />
            <wire x2="1024" y1="112" y2="112" x1="896" />
            <wire x2="1136" y1="112" y2="112" x1="1024" />
        </branch>
        <branch name="cpu_sclk">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="989" y="224" type="branch" />
            <wire x2="992" y1="224" y2="224" x1="896" />
            <wire x2="1136" y1="224" y2="224" x1="992" />
        </branch>
        <branch name="cpu_sen">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="989" y="336" type="branch" />
            <wire x2="992" y1="336" y2="336" x1="896" />
            <wire x2="1136" y1="336" y2="336" x1="992" />
        </branch>
        <branch name="RESETBMCU">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1056" y="448" type="branch" />
            <wire x2="1056" y1="448" y2="448" x1="896" />
            <wire x2="1136" y1="448" y2="448" x1="1056" />
        </branch>
        <branch name="XLXN_30(2:0)">
            <wire x2="1136" y1="560" y2="560" x1="1024" />
        </branch>
        <instance x="880" y="528" name="XLXI_6" orien="R0">
        </instance>
        <branch name="measburst(15:0)">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="816" y="752" type="branch" />
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="843" y="752" type="branch" />
            <wire x2="848" y1="752" y2="752" x1="816" />
            <wire x2="1136" y1="752" y2="752" x1="848" />
        </branch>
        <branch name="actid">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="927" y="816" type="branch" />
            <wire x2="928" y1="816" y2="816" x1="816" />
            <wire x2="1136" y1="816" y2="816" x1="928" />
        </branch>
        <branch name="FPGA_LED2">
            <wire x2="1776" y1="1328" y2="1328" x1="1504" />
        </branch>
        <iomarker fontsize="28" x="1776" y="1328" name="FPGA_LED2" orien="R0" />
        <instance x="2368" y="1040" name="XLXI_13" orien="R0">
        </instance>
        <branch name="txdds_fcw(26:0)">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2160" y="1008" type="branch" />
            <wire x2="2160" y1="1008" y2="1008" x1="2064" />
            <wire x2="2192" y1="1008" y2="1008" x1="2160" />
            <wire x2="2368" y1="1008" y2="1008" x1="2192" />
        </branch>
        <branch name="txdds_fcw_upd">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2173" y="944" type="branch" />
            <wire x2="2176" y1="944" y2="944" x1="2064" />
            <wire x2="2192" y1="944" y2="944" x1="2176" />
            <wire x2="2240" y1="944" y2="944" x1="2192" />
            <wire x2="2368" y1="944" y2="944" x1="2240" />
        </branch>
        <branch name="RESETBMCU">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2165" y="880" type="branch" />
            <wire x2="2160" y1="880" y2="880" x1="2064" />
            <wire x2="2176" y1="880" y2="880" x1="2160" />
            <wire x2="2208" y1="880" y2="880" x1="2176" />
            <wire x2="2368" y1="880" y2="880" x1="2208" />
        </branch>
        <branch name="clk_in">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="2168" y="816" type="branch" />
            <wire x2="2176" y1="816" y2="816" x1="2064" />
            <wire x2="2192" y1="816" y2="816" x1="2176" />
            <wire x2="2368" y1="816" y2="816" x1="2192" />
        </branch>
        <branch name="cpu_miso">
            <wire x2="1696" y1="1792" y2="1792" x1="1504" />
        </branch>
        <iomarker fontsize="28" x="1696" y="1792" name="cpu_miso" orien="R0" />
        <branch name="TXIQSEL">
            <wire x2="2784" y1="816" y2="816" x1="2752" />
        </branch>
        <iomarker fontsize="28" x="2784" y="816" name="TXIQSEL" orien="R0" />
        <branch name="TXD(11:0)">
            <wire x2="2784" y1="1008" y2="1008" x1="2752" />
        </branch>
        <iomarker fontsize="28" x="2784" y="1008" name="TXD(11:0)" orien="R0" />
    </sheet>
</drawing>