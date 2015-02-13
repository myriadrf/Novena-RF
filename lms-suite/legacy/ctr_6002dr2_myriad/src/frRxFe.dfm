object frmRxFe: TfrmRxFe
  Left = 0
  Top = 0
  Width = 777
  Height = 356
  TabOrder = 0
  object GroupBox2: TGroupBox
    Left = 528
    Top = 80
    Width = 201
    Height = 65
    Caption = ' DC Offset Cancellation '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 48
      Height = 13
      Caption = 'Channel I:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 104
      Top = 16
      Width = 53
      Height = 13
      Caption = 'Channel Q:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbDCOFF_I_RXFE: TComboBox
      Left = 8
      Top = 32
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
      OnChange = cmbDCOFF_I_RXFEChange
    end
    object cmbDCOFF_Q_RXFE: TComboBox
      Left = 104
      Top = 32
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
      TabOrder = 1
      OnChange = cmbDCOFF_Q_RXFEChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 528
    Top = 8
    Width = 201
    Height = 65
    Caption = ' IP2 Cancellation '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Label3: TLabel
      Left = 8
      Top = 16
      Width = 48
      Height = 13
      Caption = 'Channel I:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 104
      Top = 16
      Width = 53
      Height = 13
      Caption = 'Channel Q:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbIP2TRIM_I_RXFE: TComboBox
      Left = 8
      Top = 32
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
      OnChange = cmbIP2TRIM_I_RXFEChange
    end
    object cmbIP2TRIM_Q_RXFE: TComboBox
      Left = 104
      Top = 32
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
      TabOrder = 1
      OnChange = cmbIP2TRIM_Q_RXFEChange
    end
  end
  object rgrDecode: TRadioGroup
    Left = 8
    Top = 8
    Width = 161
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
    TabOrder = 2
    OnClick = rgrDecodeClick
  end
  object GroupBox6: TGroupBox
    Left = 408
    Top = 8
    Width = 113
    Height = 201
    Caption = ' MIX Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Label16: TLabel
      Left = 6
      Top = 16
      Width = 82
      Height = 13
      Caption = 'MIX Bias Current:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label17: TLabel
      Left = 6
      Top = 56
      Width = 49
      Height = 13
      Caption = 'MIX Input:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label18: TLabel
      Left = 6
      Top = 152
      Width = 98
      Height = 13
      Caption = 'LO Bias Of The MIX:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label19: TLabel
      Left = 5
      Top = 104
      Width = 100
      Height = 13
      Caption = 'MXLOB Bias Current:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbICT_MIX_RXFE: TComboBox
      Left = 8
      Top = 32
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
      TabOrder = 0
      OnChange = cmbICT_MIX_RXFEChange
    end
    object cmbICT_MXLOB_RXFE: TComboBox
      Left = 8
      Top = 120
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
      TabOrder = 1
      OnChange = cmbICT_MXLOB_RXFEChange
    end
    object cmbLOBN_MIX_RXFE: TComboBox
      Left = 8
      Top = 168
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
      TabOrder = 2
      OnChange = cmbLOBN_MIX_RXFEChange
    end
    object cmbIN1SEL_MIX_RXFE: TComboBox
      Left = 8
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
      OnChange = cmbIN1SEL_MIX_RXFEChange
    end
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 72
    Width = 161
    Height = 137
    Caption = ' Power Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object chbPwrRxFeMods: TCheckBox
      Left = 8
      Top = 24
      Width = 129
      Height = 17
      Caption = 'RxFE Modules Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chbPwrRxFeModsClick
    end
    object chkPD_TIA_RXFE: TCheckBox
      Left = 8
      Top = 40
      Width = 121
      Height = 17
      Caption = 'TIA Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chkPD_TIA_RXFEClick
    end
    object chkPD_MXLOB_RXFE: TCheckBox
      Left = 8
      Top = 56
      Width = 121
      Height = 17
      Caption = 'MXLOB Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chkPD_MXLOB_RXFEClick
    end
    object chkPD_LNA_RXFE: TCheckBox
      Left = 8
      Top = 88
      Width = 121
      Height = 17
      Caption = 'LNA Modules Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = chkPD_LNA_RXFEClick
    end
    object chkPD_MIX_RXFE: TCheckBox
      Left = 8
      Top = 72
      Width = 121
      Height = 17
      Caption = 'MIX Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = chkPD_MIX_RXFEClick
    end
    object chkRINEN_MIX_RXFE: TCheckBox
      Left = 8
      Top = 104
      Width = 145
      Height = 17
      Caption = 'MIX Term Resistor Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = chkRINEN_MIX_RXFEClick
    end
  end
  object GroupBox4: TGroupBox
    Left = 176
    Top = 8
    Width = 225
    Height = 201
    Caption = ' LNA Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    object Label5: TLabel
      Left = 8
      Top = 56
      Width = 79
      Height = 13
      Caption = 'LNA Gain Mode:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 96
      Width = 57
      Height = 13
      Caption = 'Active LNA:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 8
      Top = 136
      Width = 92
      Height = 13
      Caption = 'LNA Load Resistor,'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 120
      Top = 136
      Width = 92
      Height = 13
      Caption = 'LNA Load Resistor,'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 8
      Top = 152
      Width = 99
      Height = 13
      Caption = 'External Load (Gain):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 120
      Top = 152
      Width = 96
      Height = 13
      Caption = 'Internal Load (Gain):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 120
      Top = 96
      Width = 84
      Height = 13
      Caption = 'LNA Bias Current:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 120
      Top = 8
      Width = 92
      Height = 13
      Caption = 'Capacitance to BE:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label20: TLabel
      Left = 120
      Top = 56
      Width = 78
      Height = 13
      Caption = 'LNA3 Fine Gain:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object chkINLOAD_LNA_RXFE: TCheckBox
      Left = 8
      Top = 16
      Width = 113
      Height = 17
      Caption = 'Internal LNA Load'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chkINLOAD_LNA_RXFEClick
    end
    object chkXLOAD_LNA_RXFE: TCheckBox
      Left = 8
      Top = 32
      Width = 113
      Height = 17
      Caption = 'External LNA Load'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chkXLOAD_LNA_RXFEClick
    end
    object cmbG_LNA_RXFE: TComboBox
      Left = 8
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
      TabOrder = 2
      OnChange = cmbG_LNA_RXFEChange
    end
    object cmbLNASEL_RXFE: TComboBox
      Left = 8
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
      TabOrder = 3
      OnChange = cmbLNASEL_RXFEChange
    end
    object cmbRDLEXT_LNA_RXFE: TComboBox
      Left = 8
      Top = 168
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
      OnChange = cmbRDLEXT_LNA_RXFEChange
    end
    object cmbRDLINT_LNA_RXFE: TComboBox
      Left = 120
      Top = 168
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
      TabOrder = 5
      OnChange = cmbRDLINT_LNA_RXFEChange
    end
    object cmbICT_LNA_RXFE: TComboBox
      Left = 120
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
      TabOrder = 6
      OnChange = cmbICT_LNA_RXFEChange
    end
    object cmbCBE_LNA_RXFE: TComboBox
      Left = 120
      Top = 24
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
      TabOrder = 7
      OnChange = cmbCBE_LNA_RXFEChange
    end
    object cmbG_FINE_LNA3_RXFE: TComboBox
      Left = 120
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
      TabOrder = 8
      OnChange = cmbG_FINE_LNA3_RXFEChange
    end
  end
  object GroupBox5: TGroupBox
    Left = 8
    Top = 216
    Width = 345
    Height = 73
    Caption = ' VGA1 Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    object Label13: TLabel
      Left = 8
      Top = 16
      Width = 123
      Height = 13
      Caption = 'Feedback Resistor (Gain):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label14: TLabel
      Left = 136
      Top = 16
      Width = 126
      Height = 13
      Caption = 'Feedback Capacitor (BW):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 272
      Top = 16
      Width = 60
      Height = 13
      Caption = 'Bias Current:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbRFB_TIA_RXFE: TComboBox
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
      OnChange = cmbRFB_TIA_RXFEChange
    end
    object cmbCFB_TIA_RXFE: TComboBox
      Left = 136
      Top = 32
      Width = 129
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
      OnChange = cmbCFB_TIA_RXFEChange
    end
    object cmbICT_TIA_RXFE: TComboBox
      Left = 272
      Top = 32
      Width = 65
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
      OnChange = cmbICT_TIA_RXFEChange
    end
  end
end
