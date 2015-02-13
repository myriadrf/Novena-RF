object frmTop: TfrmTop
  Left = 0
  Top = 0
  Width = 777
  Height = 363
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  ParentFont = False
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
    TabOrder = 1
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 192
    Width = 153
    Height = 113
    Caption = ' Power Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object chbPwrTopMods: TCheckBox
      Left = 8
      Top = 16
      Width = 121
      Height = 17
      Caption = 'Top Modules Enable'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 0
      OnClick = chbPwrTopModsClick
    end
    object chbPwrSoftTx: TCheckBox
      Left = 8
      Top = 32
      Width = 121
      Height = 17
      Caption = 'Soft Tx Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chbPwrSoftTxClick
    end
    object chbPwrSoftRx: TCheckBox
      Left = 8
      Top = 48
      Width = 121
      Height = 17
      Caption = 'Soft Rx Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chbPwrSoftRxClick
    end
    object chbPwrLpfCal: TCheckBox
      Left = 8
      Top = 64
      Width = 143
      Height = 17
      Caption = 'DCOREF LPFCAL Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = chbPwrLpfCalClick
    end
    object chbPwrRfLbsw: TCheckBox
      Left = 8
      Top = 80
      Width = 113
      Height = 17
      Caption = 'RF LBSW Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = chbPwrRfLbswClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 328
    Top = 176
    Width = 249
    Height = 185
    Caption = ' TRX LPF Calibration '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Label1: TLabel
      Left = 144
      Top = 56
      Width = 70
      Height = 13
      Caption = 'LPFCAL Code:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 144
      Top = 96
      Width = 75
      Height = 13
      Caption = 'LPF Bandwidth:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object chkLpfCalRst: TCheckBox
      Left = 152
      Top = 32
      Width = 89
      Height = 17
      Caption = 'Reset LPFCAL'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chkLpfCalRstClick
    end
    object chkLpfCalEnEnf: TCheckBox
      Left = 8
      Top = 32
      Width = 121
      Height = 17
      Caption = 'Enable Enforce Mode'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chkLpfCalEnEnfClick
    end
    object chkLpfCalEn: TCheckBox
      Left = 8
      Top = 48
      Width = 97
      Height = 17
      Caption = 'Enable LPFCAL'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chkLpfCalEnClick
    end
    object cmbLpfCalCode: TComboBox
      Left = 144
      Top = 72
      Width = 97
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
      OnChange = cmbLpfCalCodeChange
      Items.Strings = (
        '000'
        '001'
        '010'
        '011'
        '100'
        '101'
        '110'
        '111')
    end
    object cmbLpfCalBw: TComboBox
      Left = 144
      Top = 112
      Width = 97
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 4
      OnChange = cmbLpfCalBwChange
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
    object chbPD_CLKLPFCAL: TCheckBox
      Left = 8
      Top = 16
      Width = 169
      Height = 17
      Caption = 'DIV8 for LPF Tuning Clock PD'
      TabOrder = 5
      OnClick = chbPD_CLKLPFCALClick
    end
    object rgrCLKSEL_LPFCAL: TRadioGroup
      Left = 8
      Top = 144
      Width = 233
      Height = 33
      Caption = ' LPF Tuning Clock '
      Columns = 2
      ItemIndex = 1
      Items.Strings = (
        'From TxPLL'
        'PLL Reference')
      TabOrder = 6
      OnClick = rgrCLKSEL_LPFCALClick
    end
    object GroupBox5: TGroupBox
      Left = 8
      Top = 64
      Width = 129
      Height = 73
      Caption = 'RCCAL LPFCAL Value '
      TabOrder = 7
      object Label9: TLabel
        Left = 6
        Top = 20
        Width = 83
        Height = 13
        Caption = 'RCCAL_LPFCAL:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object lblRCCAL_LPFCAL: TLabel
        Left = 95
        Top = 20
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
      object btnReadRCCALVal: TButton
        Left = 6
        Top = 40
        Width = 115
        Height = 25
        Caption = 'Read Value'
        TabOrder = 0
        OnClick = btnReadRCCALValClick
      end
    end
  end
  object rgrDecode: TRadioGroup
    Left = 584
    Top = 0
    Width = 105
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
    TabOrder = 4
    OnClick = rgrDecodeClick
  end
  object rgrSpiMode: TRadioGroup
    Left = 584
    Top = 64
    Width = 105
    Height = 57
    Caption = ' SPI Port Mode '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 1
    Items.Strings = (
      '3 Wire'
      '4 Wire')
    ParentFont = False
    TabOrder = 5
    OnClick = rgrSpiModeClick
  end
  object rgrDsmRst: TRadioGroup
    Left = 584
    Top = 192
    Width = 105
    Height = 57
    Caption = ' DSM Soft Reset '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 1
    Items.Strings = (
      'Reset State'
      'Inactive')
    ParentFont = False
    TabOrder = 6
    OnClick = rgrDsmRstClick
  end
  object GroupBox4: TGroupBox
    Left = 584
    Top = 128
    Width = 105
    Height = 57
    Caption = ' Rx Bypass Mode '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    object Label8: TLabel
      Left = 16
      Top = 32
      Width = 71
      Height = 13
      Caption = 'To Output Pins'
    end
    object chbRxTestModeEn: TCheckBox
      Left = 8
      Top = 16
      Width = 89
      Height = 17
      Caption = 'TIA Shorted'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chbRxTestModeEnClick
    end
  end
  object rgrRFLB: TRadioGroup
    Left = 8
    Top = 96
    Width = 169
    Height = 89
    Caption = ' RF Loopback Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      'Disabled'
      'TxMIX to LNA1 Path'
      'TxMIX to LNA2 Path'
      'TxMIX to LNA3 (GSM) Path')
    ParentFont = False
    TabOrder = 8
    OnClick = rgrRFLBClick
  end
  object GroupBox7: TGroupBox
    Left = 328
    Top = 96
    Width = 249
    Height = 75
    Caption = ' Clock Buffers '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
  end
  object chbSpiClkBuf: TCheckListBox
    Left = 336
    Top = 112
    Width = 233
    Height = 57
    BorderStyle = bsNone
    Color = clBtnFace
    Columns = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 13
    Items.Strings = (
      'Tx DSM SPI'
      'Tx LPF'
      'Rx DSM SPI'
      'Rx LPF'
      'Rx VGA2'
      'LPF CALCORE'
      'PLLCLKOUT')
    ParentFont = False
    TabOrder = 10
    OnClick = chbSpiClkBufClick
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 312
    Width = 313
    Height = 49
    Caption = ' XCO Buffer '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    object chbPDXCOBUF: TCheckBox
      Left = 8
      Top = 16
      Width = 82
      Height = 17
      Caption = 'Power Down'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chbPDXCOBUFClick
    end
    object chbSLFBXCOBUF: TCheckBox
      Left = 104
      Top = 16
      Width = 82
      Height = 17
      Caption = 'Self Biasing'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 1
      OnClick = chbSLFBXCOBUFClick
    end
    object chbBYPXCOBUF: TCheckBox
      Left = 208
      Top = 16
      Width = 82
      Height = 17
      Caption = 'Bypass'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chbBYPXCOBUFClick
    end
  end
  object GroupBox8: TGroupBox
    Left = 584
    Top = 256
    Width = 105
    Height = 105
    Caption = ' Global Reset '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object swReset: TRxSwitch
      Left = 24
      Top = 24
      Width = 50
      Height = 60
      Caption = 'swReset'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnOn = swResetOn
      OnOff = swResetOff
    end
  end
  object rgrBBLB: TRadioGroup
    Left = 184
    Top = 96
    Width = 137
    Height = 89
    Caption = 'BB Loopback Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      'Disabled'
      'loopb to LPF Input'
      'loopb to VGA2 Input'
      'loopb to Rx Out Pins')
    ParentFont = False
    TabOrder = 12
    OnClick = rgrBBLBClick
  end
  object rgrRXOUTSW: TRadioGroup
    Left = 168
    Top = 192
    Width = 153
    Height = 33
    Caption = ' RX Out/ADC In Switch '
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      'Open (off)'
      'Closed (on)')
    TabOrder = 13
    OnClick = rgrRXOUTSWClick
  end
  object rgrFDDTDD: TRadioGroup
    Left = 168
    Top = 272
    Width = 153
    Height = 33
    Caption = ' FDD/TDD Selection '
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      'FDD'
      'TDD')
    TabOrder = 14
    OnClick = rgrFDDTDDClick
  end
  object rgrTDDMOD: TRadioGroup
    Left = 168
    Top = 232
    Width = 153
    Height = 33
    Caption = ' TDD Mode Selection '
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      'Transmit'
      'Receive')
    TabOrder = 15
    OnClick = rgrTDDMODClick
  end
end
