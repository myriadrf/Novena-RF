object frmRxVGA2: TfrmRxVGA2
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
      Top = 16
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
      Top = 16
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
      Top = 32
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
      Top = 32
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
      Top = 48
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
      Top = 48
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
      Top = 64
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
      Top = 64
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
    Height = 201
    Caption = ' Power Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object chbPwrVGA2Mods: TCheckBox
      Left = 8
      Top = 16
      Width = 145
      Height = 17
      Caption = 'RXVGA2 Modules Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chbPwrVGA2ModsClick
    end
    object chbPwrDCCurrR: TCheckBox
      Left = 8
      Top = 32
      Width = 161
      Height = 17
      Caption = 'DC Current Regulator Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chbPwrDCCurrRClick
    end
    object chbPwrDCDACB: TCheckBox
      Left = 8
      Top = 48
      Width = 161
      Height = 17
      Caption = 'VGA2B DC Cal. DAC Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chbPwrDCDACBClick
    end
    object chbPwrDCCmpB: TCheckBox
      Left = 8
      Top = 64
      Width = 164
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'VGA2B DC Cal. Comp. Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 3
      OnClick = chbPwrDCCmpBClick
    end
    object chbPwrDCDACA: TCheckBox
      Left = 8
      Top = 80
      Width = 161
      Height = 17
      Caption = 'VGA2A DC Cal. DAC Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = chbPwrDCDACAClick
    end
    object chbPwrDCCmpA: TCheckBox
      Left = 8
      Top = 96
      Width = 161
      Height = 17
      Caption = 'VGA2A DC Cal. Comp. Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = chbPwrDCCmpAClick
    end
    object chbPwrBG: TCheckBox
      Left = 8
      Top = 112
      Width = 161
      Height = 17
      Caption = 'Band Gap Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = chbPwrBGClick
    end
    object chbPwrBypAB: TCheckBox
      Left = 8
      Top = 128
      Width = 165
      Height = 17
      Caption = 'Out Buff. in Both VGAs Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      OnClick = chbPwrBypABClick
    end
    object chbPwrBypB: TCheckBox
      Left = 8
      Top = 144
      Width = 161
      Height = 17
      Caption = 'VGA2B Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
      OnClick = chbPwrBypBClick
    end
    object chbPwrBypA: TCheckBox
      Left = 8
      Top = 160
      Width = 153
      Height = 17
      Caption = 'VGA2A Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      OnClick = chbPwrBypAClick
    end
    object chbPwrCurrRef: TCheckBox
      Left = 8
      Top = 176
      Width = 161
      Height = 17
      Caption = 'Current Reference Enable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 10
      OnClick = chbPwrCurrRefClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 192
    Top = 96
    Width = 137
    Height = 169
    Caption = ' VGA2 Control '
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
    object Label2: TLabel
      Left = 8
      Top = 112
      Width = 112
      Height = 13
      Caption = 'VGA2A Gain (Test), dB:'
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
      Width = 112
      Height = 13
      Caption = 'VGA2B Gain (Test), dB:'
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
      Width = 113
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
    object cmbVga2GA_t: TComboBox
      Left = 8
      Top = 128
      Width = 113
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
      OnChange = cmbVga2GA_tChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbVga2GB_t: TComboBox
      Left = 8
      Top = 80
      Width = 113
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
      OnChange = cmbVga2GB_tChange
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
    Left = 336
    Top = 96
    Width = 137
    Height = 65
    Caption = ' VGA2 CM Voltage '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object cmbVCM: TComboBox
      Left = 8
      Top = 32
      Width = 113
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
      OnChange = cmbVCMChange
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
