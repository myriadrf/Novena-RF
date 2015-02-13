object frmBoard: TfrmBoard
  Left = 0
  Top = 0
  Width = 789
  Height = 376
  TabOrder = 0
  object Label20: TLabel
    Left = 544
    Top = 248
    Width = 196
    Height = 91
    Caption = 
      'NOTE:'#13#10'Configuration to ADF4002 is downloaded after pressing "Ca' +
      'lculate R, N and Download" or "Download All ADF4002 Configuratio' +
      'n" buttons only!'#13#10'Other objects do not update automatically.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 529
    Height = 361
    Caption = ' ADF4002 Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object GroupBox2: TGroupBox
      Left = 8
      Top = 16
      Width = 313
      Height = 73
      Caption = ' Reference Counter Latch '
      TabOrder = 0
      object Label1: TLabel
        Left = 208
        Top = 24
        Width = 93
        Height = 13
        Caption = 'Reference Counter:'
      end
      object Label16: TLabel
        Left = 128
        Top = 24
        Width = 68
        Height = 13
        Caption = 'Anti-Backlash:'
      end
      object Label2: TLabel
        Left = 8
        Top = 24
        Width = 108
        Height = 13
        Caption = 'Lock Detect Precision:'
      end
      object txtRCnt: TRxSpinEdit
        Left = 208
        Top = 40
        Width = 97
        Height = 21
        Decimal = 8
        MaxValue = 16383
        MinValue = 1
        Value = 125
        TabOrder = 0
        OnChange = txtRCntChange
      end
      object cmbABW: TComboBox
        Left = 128
        Top = 40
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
        OnChange = cmbABWChange
        Items.Strings = (
          '2.9ns'
          '6.0ns'
          '2.9ns')
      end
      object cmbLDP: TComboBox
        Left = 8
        Top = 40
        Width = 113
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        OnChange = cmbLDPChange
        Items.Strings = (
          'Three Cycles'
          'Five  Cycles')
      end
    end
    object GroupBox3: TGroupBox
      Left = 328
      Top = 16
      Width = 193
      Height = 73
      Caption = ' N Counter Latch '
      TabOrder = 1
      object Label3: TLabel
        Left = 88
        Top = 24
        Width = 51
        Height = 13
        Caption = 'N Counter:'
      end
      object Label4: TLabel
        Left = 8
        Top = 24
        Width = 42
        Height = 13
        Caption = 'CP Gain:'
      end
      object txtNCnt: TRxSpinEdit
        Left = 88
        Top = 40
        Width = 97
        Height = 21
        Decimal = 8
        MaxValue = 8191
        MinValue = 1
        Value = 384
        TabOrder = 0
        OnChange = txtNCntChange
      end
      object cmbCPG: TComboBox
        Left = 8
        Top = 40
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
        OnChange = cmbCPGChange
        Items.Strings = (
          '0'
          '1')
      end
    end
    object GroupBox5: TGroupBox
      Left = 8
      Top = 226
      Width = 513
      Height = 125
      Caption = ' Initialization Latch '
      TabOrder = 2
      object Label6: TLabel
        Left = 184
        Top = 16
        Width = 74
        Height = 13
        Caption = 'Muxout Control:'
      end
      object Label7: TLabel
        Left = 96
        Top = 16
        Width = 69
        Height = 13
        Caption = 'Timer Counter:'
      end
      object Label8: TLabel
        Left = 8
        Top = 16
        Width = 82
        Height = 13
        Caption = 'Current Setting 1:'
      end
      object Label9: TLabel
        Left = 8
        Top = 64
        Width = 82
        Height = 13
        Caption = 'Current Setting 2:'
      end
      object Label14: TLabel
        Left = 96
        Top = 64
        Width = 43
        Height = 13
        Caption = 'Fastlock:'
      end
      object rgrCR_i: TRadioGroup
        Left = 408
        Top = 16
        Width = 97
        Height = 49
        Caption = ' Counter Reset '
        Items.Strings = (
          'Normal'
          'R && N Reset')
        TabOrder = 0
        OnClick = rgrCR_iClick
      end
      object rgrPD1_i: TRadioGroup
        Left = 352
        Top = 16
        Width = 49
        Height = 49
        Caption = ' PD 1 '
        Items.Strings = (
          '0'
          '1')
        TabOrder = 1
        OnClick = rgrPD1_iClick
      end
      object rgrPD2_i: TRadioGroup
        Left = 352
        Top = 72
        Width = 49
        Height = 49
        Caption = ' PD 2 '
        Items.Strings = (
          '0'
          '1')
        TabOrder = 2
        OnClick = rgrPD2_iClick
      end
      object cmbMOC_i: TComboBox
        Left = 184
        Top = 32
        Width = 161
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 3
        OnChange = cmbMOC_iChange
        Items.Strings = (
          'Three-State Output'
          'Digital Lock Detect'
          'N Divider Output'
          'DVdd'
          'R Divider Output'
          'N-Chan OD Lock Detect'
          'Serial Data Output'
          'DGND')
      end
      object rgrPDP_i: TRadioGroup
        Left = 184
        Top = 56
        Width = 81
        Height = 49
        Caption = ' PD Polarity '
        Items.Strings = (
          'Negative'
          'Positive')
        TabOrder = 4
        OnClick = rgrPDP_iClick
      end
      object rgrCPS_i: TRadioGroup
        Left = 408
        Top = 72
        Width = 97
        Height = 49
        Caption = ' CP State '
        Items.Strings = (
          'Normal'
          'Three-State')
        TabOrder = 5
        OnClick = rgrCPS_iClick
      end
      object cmbTC_i: TComboBox
        Left = 96
        Top = 32
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 6
        OnChange = cmbTC_iChange
        Items.Strings = (
          '3'
          '7'
          '11'
          '15'
          '19'
          '23'
          '27'
          '31'
          '35'
          '39'
          '43'
          '47'
          '51'
          '55'
          '59'
          '63')
      end
      object cmbCS1_i: TComboBox
        Left = 8
        Top = 32
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 7
        OnChange = cmbCS1_iChange
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7')
      end
      object cmbCS2_i: TComboBox
        Left = 8
        Top = 80
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 8
        OnChange = cmbCS2_iChange
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7')
      end
      object cmbFL_i: TComboBox
        Left = 96
        Top = 80
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 9
        OnChange = cmbFL_iChange
        Items.Strings = (
          'Disabled'
          'Mode 1'
          'Mode 2')
      end
    end
    object GroupBox4: TGroupBox
      Left = 8
      Top = 96
      Width = 513
      Height = 125
      Caption = ' Function Latch '
      TabOrder = 3
      object Label5: TLabel
        Left = 184
        Top = 16
        Width = 74
        Height = 13
        Caption = 'Muxout Control:'
      end
      object Label10: TLabel
        Left = 96
        Top = 16
        Width = 69
        Height = 13
        Caption = 'Timer Counter:'
      end
      object Label11: TLabel
        Left = 8
        Top = 16
        Width = 82
        Height = 13
        Caption = 'Current Setting 1:'
      end
      object Label12: TLabel
        Left = 8
        Top = 64
        Width = 82
        Height = 13
        Caption = 'Current Setting 2:'
      end
      object Label13: TLabel
        Left = 96
        Top = 64
        Width = 43
        Height = 13
        Caption = 'Fastlock:'
      end
      object rgrCR_f: TRadioGroup
        Left = 408
        Top = 16
        Width = 97
        Height = 49
        Caption = ' Counter Reset '
        Items.Strings = (
          'Normal'
          'R && N Reset')
        TabOrder = 0
        OnClick = rgrCR_fClick
      end
      object rgrPD1_f: TRadioGroup
        Left = 352
        Top = 16
        Width = 49
        Height = 49
        Caption = ' PD 1 '
        Items.Strings = (
          '0'
          '1')
        TabOrder = 1
        OnClick = rgrPD1_fClick
      end
      object rgrPD2_f: TRadioGroup
        Left = 352
        Top = 72
        Width = 49
        Height = 49
        Caption = ' PD 2 '
        Items.Strings = (
          '0'
          '1')
        TabOrder = 2
        OnClick = rgrPD2_fClick
      end
      object cmbMOC_f: TComboBox
        Left = 184
        Top = 32
        Width = 161
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 3
        OnChange = cmbMOC_fChange
        Items.Strings = (
          'Three-State Output'
          'Digital Lock Detect'
          'N Divider Output'
          'DVdd'
          'R Divider Output'
          'N-Chan OD Lock Detect'
          'Serial Data Output'
          'DGND')
      end
      object rgrPDP_f: TRadioGroup
        Left = 184
        Top = 56
        Width = 81
        Height = 49
        Caption = ' PD Polarity '
        Items.Strings = (
          'Negative'
          'Positive')
        TabOrder = 4
        OnClick = rgrPDP_fClick
      end
      object rgrCPS_f: TRadioGroup
        Left = 408
        Top = 72
        Width = 97
        Height = 49
        Caption = ' CP State '
        Items.Strings = (
          'Normal'
          'Three-State')
        TabOrder = 5
        OnClick = rgrCPS_fClick
      end
      object cmbTC_f: TComboBox
        Left = 96
        Top = 32
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 6
        OnChange = cmbTC_fChange
        Items.Strings = (
          '3'
          '7'
          '11'
          '15'
          '19'
          '23'
          '27'
          '31'
          '35'
          '39'
          '43'
          '47'
          '51'
          '55'
          '59'
          '63')
      end
      object cmbCS1_f: TComboBox
        Left = 8
        Top = 32
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 7
        OnChange = cmbCS1_fChange
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7')
      end
      object cmbCS2_f: TComboBox
        Left = 8
        Top = 80
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 8
        OnChange = cmbCS2_fChange
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7')
      end
      object cmbFL_f: TComboBox
        Left = 96
        Top = 80
        Width = 81
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 9
        OnChange = cmbFL_fChange
        Items.Strings = (
          'Disabled'
          'Mode 1'
          'Mode 2')
      end
    end
  end
  object GroupBox6: TGroupBox
    Left = 536
    Top = 0
    Width = 225
    Height = 153
    Caption = ' Calculation of R && N '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Label15: TLabel
      Left = 12
      Top = 24
      Width = 49
      Height = 13
      Caption = 'Fref, MHz:'
    end
    object Label17: TLabel
      Left = 116
      Top = 24
      Width = 55
      Height = 13
      Caption = 'Fvco, MHz:'
    end
    object Label18: TLabel
      Left = 48
      Top = 72
      Width = 64
      Height = 13
      Caption = 'Fvco (MHz) ='
    end
    object lblFvco: TLabel
      Left = 120
      Top = 72
      Width = 34
      Height = 13
      Caption = 'lblFvco'
    end
    object lblFcomp: TLabel
      Left = 120
      Top = 88
      Width = 42
      Height = 13
      Caption = 'lblFcomp'
    end
    object Label19: TLabel
      Left = 81
      Top = 88
      Width = 31
      Height = 13
      Caption = 'LCM ='
    end
    object txtFref: TRxSpinEdit
      Left = 8
      Top = 40
      Width = 97
      Height = 21
      Decimal = 8
      MaxValue = 16383
      MinValue = 1
      ValueType = vtFloat
      Value = 10
      TabOrder = 0
      OnChange = txtFrefChange
    end
    object txtFvco: TRxSpinEdit
      Left = 112
      Top = 40
      Width = 97
      Height = 21
      Decimal = 8
      MaxValue = 16383
      MinValue = 1
      ValueType = vtFloat
      Value = 30.72
      TabOrder = 1
      OnChange = txtFvcoChange
    end
    object btnCalc: TButton
      Left = 8
      Top = 112
      Width = 201
      Height = 25
      Caption = 'Calculate R, N && Download'
      TabOrder = 2
      OnClick = btnCalcClick
    end
  end
  object btnDownload: TButton
    Left = 544
    Top = 208
    Width = 201
    Height = 25
    Caption = 'Download All ADF4002 Configuration'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = btnDownloadClick
  end
  object btnSaveRFIF: TButton
    Left = 544
    Top = 168
    Width = 201
    Height = 25
    Caption = 'Save ADF4002 Registers (rfif format)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = btnSaveRFIFClick
  end
  object dlgSave: TSaveDialog
    Left = 752
    Top = 168
  end
end
