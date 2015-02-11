Version 4
SymbolType BLOCK
TEXT 32 32 LEFT 4 half_band_decim
RECTANGLE Normal 32 32 1024 608
LINE Normal 0 80 32 80
PIN 0 80 LEFT 36
PINATTR PinName s_axis_data_tvalid
PINATTR Polarity IN
LINE Normal 0 112 32 112
PIN 0 112 LEFT 36
PINATTR PinName s_axis_data_tready
PINATTR Polarity OUT
LINE Wide 0 208 32 208
PIN 0 208 LEFT 36
PINATTR PinName s_axis_data_tdata[31:0]
PINATTR Polarity IN
LINE Normal 0 496 32 496
PIN 0 496 LEFT 36
PINATTR PinName aclk
PINATTR Polarity IN
LINE Normal 1056 80 1024 80
PIN 1056 80 RIGHT 36
PINATTR PinName m_axis_data_tvalid
PINATTR Polarity OUT
LINE Normal 1056 112 1024 112
PIN 1056 112 RIGHT 36
PINATTR PinName m_axis_data_tready
PINATTR Polarity IN
LINE Wide 1056 208 1024 208
PIN 1056 208 RIGHT 36
PINATTR PinName m_axis_data_tdata[31:0]
PINATTR Polarity OUT

