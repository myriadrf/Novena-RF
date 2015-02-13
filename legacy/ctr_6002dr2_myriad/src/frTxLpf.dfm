object frmTxLpf: TfrmTxLpf
  Left = 0
  Top = 0
  Width = 777
  Height = 356
  TabOrder = 0
  object GroupBox6: TGroupBox
    Left = 8
    Top = 0
    Width = 569
    Height = 89
    Caption = ' DC Calibration '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label6: TLabel
      Left = 8
      Top = 40
      Width = 102
      Height = 13
      Caption = 'CAL Module Address:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 328
      Top = 24
      Width = 82
      Height = 13
      Caption = 'Calibration Value:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lbDC_REGVAL: TLabel
      Left = 424
      Top = 24
      Width = 36
      Height = 13
      Caption = '??????'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lblDC_LOCK: TLabel
      Left = 424
      Top = 40
      Width = 18
      Height = 13
      Caption = '???'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 328
      Top = 40
      Width = 64
      Height = 13
      Caption = 'Lock Pattern:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label13: TLabel
      Left = 328
      Top = 56
      Width = 85
      Height = 13
      Caption = 'Calibration Status:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lblDC_CLBR_DONE: TLabel
      Left = 424
      Top = 56
      Width = 6
      Height = 13
      Caption = '?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 328
      Top = 72
      Width = 87
      Height = 13
      Caption = 'Comparator Value:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object lblDC_UD: TLabel
      Left = 424
      Top = 72
      Width = 6
      Height = 13
      Caption = '?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label17: TLabel
      Left = 128
      Top = 40
      Width = 82
      Height = 13
      Caption = 'Calibration Value:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnDCStartClbr: TButton
      Left = 216
      Top = 12
      Width = 97
      Height = 25
      Caption = 'Start Calibration'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnDCStartClbrClick
    end
    object btnDCLoadVal: TButton
      Left = 112
      Top = 12
      Width = 97
      Height = 25
      Caption = 'Load Cnt Value'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnDCLoadValClick
    end
    object btnDCRstClbr: TButton
      Left = 8
      Top = 12
      Width = 97
      Height = 25
      Caption = 'Reset Calibration'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnDCRstClbrClick
    end
    object cmbDCCalAddr: TComboBox
      Left = 8
      Top = 59
      Width = 105
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 3
      OnChange = cmbDCCalAddrChange
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4')
    end
    object btnDCReadVal: TButton
      Left = 216
      Top = 56
      Width = 97
      Height = 25
      Caption = 'Read Values'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btnDCReadValClick
    end
    object cmbCalVal: TComboBox
      Left = 128
      Top = 59
      Width = 81
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 5
      OnChange = cmbCalValChange
    end
  end
  object rgrDecode: TRadioGroup
    Left = 584
    Top = 0
    Width = 113
    Height = 57
    Caption = ' Decoding '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      'Decode Signals'
      'Direct Signals')
    ParentFont = False
    TabOrder = 1
    OnClick = rgrDecodeClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 96
    Width = 177
    Height = 129
    Caption = ' Power Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object chbPwrLpfMods: TCheckBox
      Left = 8
      Top = 24
      Width = 121
      Height = 17
      Caption = 'LPF Modules Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chbPwrLpfModsClick
    end
    object chbPwrLpf: TCheckBox
      Left = 8
      Top = 40
      Width = 161
      Height = 17
      Caption = 'LPF Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chbPwrLpfClick
    end
    object chbPwrDCDac: TCheckBox
      Left = 8
      Top = 56
      Width = 161
      Height = 17
      Caption = 'DC Offset DAC Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chbPwrDCDacClick
    end
    object chbPwrDCRef: TCheckBox
      Left = 8
      Top = 72
      Width = 153
      Height = 17
      Caption = 'dc_ref_con3 Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = chbPwrDCRefClick
    end
    object chbPwrDCCmpr: TCheckBox
      Left = 8
      Top = 88
      Width = 161
      Height = 17
      Caption = 'DC Offset Comparator Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = chbPwrDCCmprClick
    end
    object chbTX_DACBUF_EN: TCheckBox
      Left = 8
      Top = 104
      Width = 161
      Height = 17
      Caption = 'DAC Buffer Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = chbTX_DACBUF_ENClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 192
    Top = 160
    Width = 241
    Height = 65
    Caption = ' Process Calibration Values '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Label3: TLabel
      Left = 8
      Top = 16
      Width = 90
      Height = 13
      Caption = 'DC Offset Resistor:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 120
      Top = 16
      Width = 102
      Height = 13
      Caption = 'From TRX_LPF_CAL:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbDCOffset: TComboBox
      Left = 8
      Top = 32
      Width = 105
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 0
      OnChange = cmbDCOffsetChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbRcCal: TComboBox
      Left = 120
      Top = 32
      Width = 105
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 1
      OnChange = cmbRcCalChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
  end
  object GroupBox2: TGroupBox
    Left = 192
    Top = 96
    Width = 105
    Height = 57
    Caption = ' LPF Bandwidth '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object cmbLpfBw: TComboBox
      Left = 8
      Top = 20
      Width = 89
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 0
      OnChange = cmbLpfBwChange
      Items.Strings = (
        '14'
        '10'
        '7'
        '6'
        '5'
        '4.375'
        '3.5'
        '3'
        '2.75'
        '2.5'
        '1.92'
        '1.5'
        '1.375'
        '1.25'
        '0.875'
        '0.75')
    end
  end
  object rgrLpfByp: TRadioGroup
    Left = 304
    Top = 96
    Width = 129
    Height = 57
    Caption = ' Test '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      'Normal Operation'
      'Bypass LPF')
    ParentFont = False
    TabOrder = 5
    OnClick = rgrLpfBypClick
  end
end
