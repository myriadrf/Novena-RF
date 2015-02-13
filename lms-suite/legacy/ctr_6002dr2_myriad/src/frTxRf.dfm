object frmTxRf: TfrmTxRf
  Left = 0
  Top = 0
  Width = 777
  Height = 342
  Color = clBtnFace
  ParentColor = False
  TabOrder = 0
  object rgrDecode: TRadioGroup
    Left = 504
    Top = 0
    Width = 129
    Height = 73
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
    TabOrder = 0
    OnClick = rgrDecodeClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 169
    Height = 153
    Caption = ' Power Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object chbPwrTxRfMods: TCheckBox
      Left = 8
      Top = 16
      Width = 129
      Height = 17
      Caption = 'TxRF Modules Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chbPwrTxRfModsClick
    end
    object chbPD_DRVAUX: TCheckBox
      Left = 8
      Top = 32
      Width = 145
      Height = 17
      Caption = 'Auxiliary PA Power Down'
      TabOrder = 1
      OnClick = chbPD_DRVAUXClick
    end
    object chbPD_PKDET: TCheckBox
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'PDED Power Down'
      TabOrder = 2
      OnClick = chbPD_PKDETClick
    end
    object chbPwrVga1_I: TCheckBox
      Left = 8
      Top = 64
      Width = 121
      Height = 17
      Caption = 'VGA1 I Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = chbPwrVga1_IClick
    end
    object chbPwrVga1_Q: TCheckBox
      Left = 8
      Top = 80
      Width = 137
      Height = 17
      Caption = 'VGA1 Q Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = chbPwrVga1_QClick
    end
    object chbPwrVga2: TCheckBox
      Left = 8
      Top = 128
      Width = 145
      Height = 17
      Caption = 'MIX and VGA2 Disabled'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = chbPwrVga2Click
    end
    object chbPD_TXLOBUF: TCheckBox
      Left = 8
      Top = 112
      Width = 121
      Height = 17
      Caption = 'TxLOBUF Disabled'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = chbPD_TXLOBUFClick
    end
    object chbPD_TXDRV: TCheckBox
      Left = 8
      Top = 96
      Width = 153
      Height = 17
      Caption = 'PA1, PA2, AUXPA Disabled'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      OnClick = chbPD_TXDRVClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 368
    Top = 80
    Width = 265
    Height = 113
    Caption = ' VGA1 Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label3: TLabel
      Left = 8
      Top = 16
      Width = 75
      Height = 13
      Caption = 'VGA1 Gain, dB:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label1: TLabel
      Left = 120
      Top = 16
      Width = 134
      Height = 13
      Caption = 'LO Leakage I DAC Out, mV:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 120
      Top = 64
      Width = 139
      Height = 13
      Caption = 'LO Leakage Q DAC Out, mV:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 64
      Width = 105
      Height = 13
      Caption = 'VGA1 Gain (Test), dB:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbVga1G_u: TComboBox
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
      OnChange = cmbVga1G_uChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbVga1DcI: TComboBox
      Left = 120
      Top = 32
      Width = 137
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
      OnChange = cmbVga1DcIChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbVga1DcQ: TComboBox
      Left = 120
      Top = 80
      Width = 137
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 2
      OnChange = cmbVga1DcQChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbVga1G_t: TComboBox
      Left = 8
      Top = 80
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
      OnChange = cmbVga1G_tChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
  end
  object GroupBox3: TGroupBox
    Left = 368
    Top = 200
    Width = 265
    Height = 65
    Caption = ' VGA2 Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Label5: TLabel
      Left = 8
      Top = 16
      Width = 75
      Height = 13
      Caption = 'VGA2 Gain, dB:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 152
      Top = 16
      Width = 86
      Height = 13
      Caption = 'VGA2 Gain (Test):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbVga2G_u: TComboBox
      Left = 8
      Top = 32
      Width = 121
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
      OnChange = cmbVga2G_uChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbVga2G_t: TComboBox
      Left = 136
      Top = 32
      Width = 121
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
      OnChange = cmbVga2G_tChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
  end
  object rgrLOOPBBEN: TRadioGroup
    Left = 184
    Top = 232
    Width = 177
    Height = 97
    Caption = 'BB Loop Back Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Items.Strings = (
      'Switches Open'
      'TxLPF Output to BBLB'
      'TxVGA1 Output to BBLB'
      'PDED Output to BBLB')
    ParentFont = False
    TabOrder = 4
    OnClick = rgrLOOPBBENClick
  end
  object rgrPA: TRadioGroup
    Left = 368
    Top = 0
    Width = 129
    Height = 73
    Caption = ' PA Selection '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Items.Strings = (
      'PA1 and PA2 Off'
      'PA1 Selected'
      'PA2 Selected')
    ParentFont = False
    TabOrder = 5
    OnClick = rgrPAClick
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 160
    Width = 169
    Height = 169
    Caption = ' EDPD Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    object Label7: TLabel
      Left = 7
      Top = 16
      Width = 77
      Height = 13
      Caption = 'Detector Select:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 7
      Top = 56
      Width = 108
      Height = 13
      Caption = 'Signal for AC Coupling:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 7
      Top = 96
      Width = 86
      Height = 13
      Caption = 'PDED Bandwidth:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbENVD: TComboBox
      Left = 8
      Top = 32
      Width = 145
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
      OnChange = cmbENVDChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbENVD2: TComboBox
      Left = 8
      Top = 72
      Width = 145
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
      OnChange = cmbENVD2Change
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbPKDBW: TComboBox
      Left = 8
      Top = 112
      Width = 145
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 2
      OnChange = cmbPKDBWChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object chbFST_PKDET: TCheckBox
      Left = 8
      Top = 144
      Width = 150
      Height = 17
      Caption = 'Short the Resistors in PDED'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = chbFST_PKDETClick
    end
  end
  object GroupBox5: TGroupBox
    Left = 184
    Top = 0
    Width = 177
    Height = 225
    Caption = ' Bias Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    object Label10: TLabel
      Left = 7
      Top = 48
      Width = 108
      Height = 13
      Caption = 'LO Buffer Bias Current:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 7
      Top = 88
      Width = 116
      Height = 13
      Caption = 'PA Cascode NPNs Bias:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 7
      Top = 128
      Width = 103
      Height = 13
      Caption = 'MIX Bias Current, mA:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label13: TLabel
      Left = 7
      Top = 168
      Width = 103
      Height = 13
      Caption = 'PAs Bias Current, mA:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object chbFST_TXHFBIAS: TCheckBox
      Left = 8
      Top = 24
      Width = 161
      Height = 17
      Caption = 'Tx HF Bias Resistors Shorted'
      TabOrder = 0
      OnClick = chbFST_TXHFBIASClick
    end
    object cmbICT_TXLOBUF: TComboBox
      Left = 8
      Top = 64
      Width = 145
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
      OnChange = cmbICT_TXLOBUFChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbVBCAS_TXDRV: TComboBox
      Left = 8
      Top = 104
      Width = 145
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 2
      OnChange = cmbVBCAS_TXDRVChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbICT_TXMIX: TComboBox
      Left = 8
      Top = 144
      Width = 145
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
      OnChange = cmbICT_TXMIXChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbICT_TXDRV: TComboBox
      Left = 8
      Top = 184
      Width = 145
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
      OnChange = cmbICT_TXDRVChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
  end
end
