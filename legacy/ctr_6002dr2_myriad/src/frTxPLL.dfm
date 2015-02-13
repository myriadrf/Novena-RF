object frmTxPLL: TfrmTxPLL
  Left = 0
  Top = 0
  Width = 786
  Height = 363
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object rgrDecode: TRadioGroup
    Left = 0
    Top = 8
    Width = 113
    Height = 65
    Caption = ' Decoding '
    ItemIndex = 0
    Items.Strings = (
      'Decode Signals'
      'Direct Signals')
    TabOrder = 0
    OnClick = rgrDecodeClick
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 80
    Width = 249
    Height = 137
    Caption = ' Power Control '
    TabOrder = 1
    object chbPwrPllMods: TCheckBox
      Left = 8
      Top = 16
      Width = 121
      Height = 17
      Caption = 'PLL Modules Enable'
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = chbPwrPllModsClick
    end
    object chkENLAMP: TCheckBox
      Left = 8
      Top = 48
      Width = 121
      Height = 17
      Caption = 'Input Limiter Amp. En.'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = chkENLAMPClick
    end
    object chkENLOBUF: TCheckBox
      Left = 8
      Top = 32
      Width = 105
      Height = 17
      Caption = 'LO Buffer Enable'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = chkENLOBUFClick
    end
    object chkPFDPD: TCheckBox
      Left = 138
      Top = 16
      Width = 87
      Height = 17
      Caption = 'PFD/CP En.'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = chkPFDPDClick
    end
    object chkENFEEDDIV: TCheckBox
      Left = 8
      Top = 64
      Width = 121
      Height = 17
      Caption = 'Feedback Divider En.'
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = chkENFEEDDIVClick
    end
    object cmbPD_VCOCOMP_SX: TCheckBox
      Left = 138
      Top = 32
      Width = 95
      Height = 17
      Caption = 'VCO COMP En.'
      TabOrder = 5
      OnClick = cmbPD_VCOCOMP_SXClick
    end
    object chkPFDCLKP: TCheckBox
      Left = 8
      Top = 80
      Width = 217
      Height = 17
      Caption = 'PFD Clk Inverted (Unchecked-in Phase)'
      TabOrder = 6
      OnClick = chkPFDCLKPClick
    end
    object chkTRI: TCheckBox
      Left = 8
      Top = 96
      Width = 229
      Height = 17
      Caption = 'CP Out Mode: Tri-state (Unchecked-Normal)'
      TabOrder = 7
      OnClick = chkTRIClick
    end
    object chkPOL: TCheckBox
      Left = 8
      Top = 112
      Width = 233
      Height = 17
      Caption = 'CP Out Inverted (Unchecked-Normal)'
      TabOrder = 8
      OnClick = chkPOLClick
    end
    object chbAUTOBYP: TCheckBox
      Left = 138
      Top = 48
      Width = 105
      Height = 17
      Caption = 'DSMN Auto Byp.'
      TabOrder = 9
      OnClick = chbAUTOBYPClick
    end
    object chbEN_PFD_UP: TCheckBox
      Left = 138
      Top = 64
      Width = 105
      Height = 17
      Caption = 'PFD Up Pulses'
      TabOrder = 10
      OnClick = chbEN_PFD_UPClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 224
    Width = 249
    Height = 65
    Caption = ' CP Current and Offset '
    TabOrder = 2
    object Label3: TLabel
      Left = 8
      Top = 16
      Width = 56
      Height = 13
      Caption = 'Current, uA:'
    end
    object Label4: TLabel
      Left = 87
      Top = 16
      Width = 67
      Height = 13
      Caption = 'Up Offset, uA:'
    end
    object Label1: TLabel
      Left = 167
      Top = 16
      Width = 67
      Height = 13
      Caption = 'Dn Offset, uA:'
    end
    object cmbICHP: TComboBox
      Left = 8
      Top = 32
      Width = 70
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cmbICHPChange
      Items.Strings = (
        'All Detectors Powered Down'
        'Rx ED Output'
        'Rx PD Output'
        'Rx ED Output (from TX1)'
        'Rx PD Output (from TX1)'
        'Rx ED Output (from TX2)'
        'Rx PD Output (from TX2)')
    end
    object cmbOFFUP: TComboBox
      Left = 87
      Top = 32
      Width = 70
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      OnChange = cmbOFFUPChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbOFFDOWN: TComboBox
      Left = 167
      Top = 32
      Width = 70
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      OnChange = cmbOFFDOWNChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
  end
  object GroupBox4: TGroupBox
    Left = 104
    Top = 296
    Width = 145
    Height = 65
    Caption = ' Dithering Control '
    TabOrder = 3
    object Label2: TLabel
      Left = 80
      Top = 16
      Width = 51
      Height = 13
      Caption = 'Bits Dither:'
    end
    object chkDITHEN: TCheckBox
      Left = 12
      Top = 32
      Width = 61
      Height = 17
      Caption = 'Use'
      TabOrder = 0
      OnClick = chkDITHENClick
    end
    object cmbDITHN: TComboBox
      Left = 80
      Top = 32
      Width = 57
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      OnChange = cmbDITHNChange
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
  object GroupBox5: TGroupBox
    Left = 0
    Top = 296
    Width = 97
    Height = 65
    Caption = ' Output Buffer '
    TabOrder = 4
    object cmbSELOUT: TComboBox
      Left = 8
      Top = 32
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cmbSELOUTChange
      Items.Strings = (
        'Disabled'
        'First'
        'Second'
        'Third')
    end
  end
  object GroupBox9: TGroupBox
    Left = 232
    Top = 8
    Width = 225
    Height = 65
    Caption = ' VCO Capacitance '
    TabOrder = 5
    object Label19: TLabel
      Left = 104
      Top = 16
      Width = 30
      Height = 13
      Caption = 'Value:'
    end
    object Label21: TLabel
      Left = 8
      Top = 16
      Width = 33
      Height = 13
      Caption = 'Status:'
    end
    object lblAutoTuneStatus: TLabel
      Left = 48
      Top = 16
      Width = 15
      Height = 13
      Caption = 'NA'
    end
    object cmbVCOCAP: TComboBox
      Left = 104
      Top = 32
      Width = 41
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cmbVCOCAPChange
      Items.Strings = (
        'Powered Down'
        'First Enabled'
        'Second Enabled'
        'Third Enabled')
    end
    object btnClbr: TButton
      Left = 152
      Top = 8
      Width = 65
      Height = 25
      Caption = 'Calibration'
      TabOrder = 1
      OnClick = btnClbrClick
    end
    object btnChoose: TButton
      Left = 152
      Top = 35
      Width = 65
      Height = 25
      Caption = 'Select'
      TabOrder = 2
      OnClick = btnChooseClick
    end
    object btnTune: TButton
      Left = 8
      Top = 35
      Width = 41
      Height = 25
      Caption = 'Tune'
      TabOrder = 3
      OnClick = btnTuneClick
    end
    object chkCapLog: TCheckBox
      Left = 56
      Top = 40
      Width = 41
      Height = 17
      Caption = 'Log'
      TabOrder = 4
    end
  end
  object GroupBox11: TGroupBox
    Left = 120
    Top = 8
    Width = 105
    Height = 65
    Caption = ' Test Signal '
    TabOrder = 6
    object chkOEN_TSTD_SX: TCheckBox
      Left = 8
      Top = 16
      Width = 89
      Height = 17
      Caption = 'Buffer Enabled'
      TabOrder = 0
      OnClick = chkOEN_TSTD_SXClick
    end
    object chkPASSEN_TSTOD_SD: TCheckBox
      Left = 8
      Top = 40
      Width = 89
      Height = 17
      Caption = 'Pass Enabled'
      TabOrder = 1
      OnClick = chkPASSEN_TSTOD_SDClick
    end
  end
  object GroupBox12: TGroupBox
    Left = 680
    Top = 8
    Width = 105
    Height = 65
    Caption = ' VCO Comparators '
    TabOrder = 7
    object Label15: TLabel
      Left = 8
      Top = 16
      Width = 25
      Height = 13
      Caption = 'High:'
    end
    object Label18: TLabel
      Left = 56
      Top = 16
      Width = 23
      Height = 13
      Caption = 'Low:'
    end
    object lblVTUNE_H: TLabel
      Left = 37
      Top = 16
      Width = 6
      Height = 13
      Caption = '0'
    end
    object lblVTUNE_L: TLabel
      Left = 85
      Top = 16
      Width = 6
      Height = 13
      Caption = '0'
    end
    object btnReadVtune: TButton
      Left = 8
      Top = 32
      Width = 89
      Height = 25
      Caption = 'Read'
      TabOrder = 0
      OnClick = btnReadVtuneClick
    end
  end
  object Panel1: TPanel
    Left = 255
    Top = 72
    Width = 529
    Height = 289
    BevelOuter = bvNone
    TabOrder = 8
    object PageControl1: TPageControl
      Left = 0
      Top = 8
      Width = 521
      Height = 273
      ActivePage = TabSheet1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Style = tsFlatButtons
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'Frequency Control'
        object rgrMODE: TRadioGroup
          Left = 0
          Top = 0
          Width = 145
          Height = 33
          Caption = ' PLL Mode '
          Columns = 2
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemIndex = 0
          Items.Strings = (
            'Fractional'
            'Integer')
          ParentFont = False
          TabOrder = 0
          OnClick = rgrMODEClick
        end
        object grbOutFreq: TGroupBox
          Left = 0
          Top = 40
          Width = 145
          Height = 81
          Caption = ' Output Frequency, GHz '
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          TabOrder = 1
          object btnCalc: TButton
            Left = 8
            Top = 48
            Width = 129
            Height = 25
            Caption = 'Calculate'
            TabOrder = 0
            OnClick = btnCalcClick
          end
          object txtDesFreq: TRxSpinEdit
            Left = 8
            Top = 24
            Width = 129
            Height = 21
            Decimal = 8
            Increment = 0.1
            ValueType = vtFloat
            TabOrder = 1
          end
        end
        object GroupBox8: TGroupBox
          Left = 0
          Top = 124
          Width = 145
          Height = 113
          Caption = ' A and B Counter Values '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object Label16: TLabel
            Left = 8
            Top = 16
            Width = 80
            Height = 13
            Caption = 'Counter A Value:'
          end
          object Label17: TLabel
            Left = 8
            Top = 64
            Width = 80
            Height = 13
            Caption = 'Counter B Value:'
          end
          object cmbACODE: TComboBox
            Left = 8
            Top = 32
            Width = 97
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 0
            OnChange = cmbACODEChange
            Items.Strings = (
              'All Detectors Powered Down'
              'Rx ED Output'
              'Rx PD Output'
              'Rx ED Output (from TX1)'
              'Rx PD Output (from TX1)'
              'Rx ED Output (from TX2)'
              'Rx PD Output (from TX2)')
          end
          object cmbBCODE: TComboBox
            Left = 8
            Top = 80
            Width = 97
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 1
            OnChange = cmbBCODEChange
            Items.Strings = (
              'MUX Inputs Disconnected'
              'MUX Input 1 Connected to TX1'
              'MUX Input 2 Connected to TX2')
          end
        end
        object GroupBox7: TGroupBox
          Left = 152
          Top = 0
          Width = 209
          Height = 121
          Caption = ' Calculated Values for Fractional Mode '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          object Label6: TLabel
            Left = 8
            Top = 16
            Width = 47
            Height = 13
            Caption = 'N Integer:'
          end
          object Label7: TLabel
            Left = 8
            Top = 32
            Width = 60
            Height = 13
            Caption = 'N Fractional:'
          end
          object Label8: TLabel
            Left = 8
            Top = 48
            Width = 36
            Height = 13
            Caption = 'Divider:'
          end
          object Label9: TLabel
            Left = 8
            Top = 64
            Width = 111
            Height = 13
            Caption = 'Real Output Freq, GHz:'
          end
          object Label10: TLabel
            Left = 8
            Top = 80
            Width = 76
            Height = 13
            Caption = 'VCO Freq, GHz:'
          end
          object lblNint: TLabel
            Left = 120
            Top = 16
            Width = 18
            Height = 13
            Caption = '130'
          end
          object lblNfrac: TLabel
            Left = 120
            Top = 32
            Width = 42
            Height = 13
            Caption = '2097152'
          end
          object lblDiv: TLabel
            Left = 120
            Top = 48
            Width = 6
            Height = 13
            Caption = '0'
          end
          object lblROutF: TLabel
            Left = 120
            Top = 64
            Width = 6
            Height = 13
            Caption = '0'
          end
          object lblVcoF: TLabel
            Left = 120
            Top = 80
            Width = 6
            Height = 13
            Caption = '0'
          end
        end
        object GroupBox10: TGroupBox
          Left = 152
          Top = 124
          Width = 209
          Height = 113
          Caption = ' Calculated Values for Integer Mode '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          object Label5: TLabel
            Left = 8
            Top = 16
            Width = 47
            Height = 13
            Caption = 'Divider N:'
          end
          object Label11: TLabel
            Left = 8
            Top = 32
            Width = 54
            Height = 13
            Caption = 'Fvco, GHz:'
          end
          object Label12: TLabel
            Left = 8
            Top = 48
            Width = 65
            Height = 13
            Caption = 'Fvco/2, GHz:'
          end
          object Label13: TLabel
            Left = 8
            Top = 64
            Width = 65
            Height = 13
            Caption = 'Fvco/4, GHz:'
          end
          object Label14: TLabel
            Left = 8
            Top = 80
            Width = 65
            Height = 13
            Caption = 'Fvco/8, GHz:'
          end
          object lblN: TLabel
            Left = 120
            Top = 16
            Width = 18
            Height = 13
            Caption = '130'
          end
          object lblFvcoInt: TLabel
            Left = 120
            Top = 32
            Width = 42
            Height = 13
            Caption = '2097152'
          end
          object lblFvco2Int: TLabel
            Left = 120
            Top = 48
            Width = 6
            Height = 13
            Caption = '0'
          end
          object lblFvco4Int: TLabel
            Left = 120
            Top = 64
            Width = 6
            Height = 13
            Caption = '0'
          end
          object lblFvco8Int: TLabel
            Left = 120
            Top = 80
            Width = 6
            Height = 13
            Caption = '0'
          end
          object Label22: TLabel
            Left = 8
            Top = 96
            Width = 71
            Height = 13
            Caption = 'Fvco/16, GHz:'
          end
          object lblFvco16Int: TLabel
            Left = 120
            Top = 96
            Width = 6
            Height = 13
            Caption = '0'
          end
        end
        object rgrSELVCO: TRadioGroup
          Left = 368
          Top = 0
          Width = 137
          Height = 121
          Caption = ' Current VCO '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemIndex = 2
          Items.Strings = (
            'All Powered Down'
            'Low Frequency'
            'Mid Low Frequency'
            'Mid High Frequency'
            'High Frequency')
          ParentFont = False
          TabOrder = 5
          OnClick = rgrSELVCOClick
        end
        object rgrFRANGE: TRadioGroup
          Left = 368
          Top = 124
          Width = 137
          Height = 113
          Caption = ' MUX/DIV Selection '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemIndex = 1
          Items.Strings = (
            'All Powered Down'
            'Fvco/2'
            'Fvco/4'
            'Fvco/8'
            'Fvco/16')
          ParentFont = False
          TabOrder = 6
          OnClick = rgrFRANGEClick
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'BIST Control'
        ImageIndex = 1
        object btnBSTART: TButton
          Left = 192
          Top = 104
          Width = 121
          Height = 25
          Caption = 'Start BIST'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = btnBSTARTClick
        end
        object GroupBox1: TGroupBox
          Left = 0
          Top = 0
          Width = 121
          Height = 81
          Caption = ' BIST State '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object lblBSTATE: TLabel
            Left = 16
            Top = 24
            Width = 52
            Height = 13
            Caption = 'lblBSTATE'
          end
          object btnReadBISTState: TButton
            Left = 8
            Top = 48
            Width = 105
            Height = 25
            Caption = 'Read BIST State'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = btnReadBISTStateClick
          end
        end
        object GroupBox6: TGroupBox
          Left = 128
          Top = 0
          Width = 121
          Height = 81
          Caption = ' BIST Signature '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          object lblBSIG: TLabel
            Left = 16
            Top = 24
            Width = 35
            Height = 13
            Caption = 'lblBSIG'
          end
          object Button1: TButton
            Left = 8
            Top = 48
            Width = 105
            Height = 25
            Caption = 'Read Signature'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = Button1Click
          end
        end
        object rgrBCLKSEL: TRadioGroup
          Left = 256
          Top = 0
          Width = 121
          Height = 81
          Caption = ' DSMN/BIST Clock '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Items.Strings = (
            'Clock Disabled'
            'Ref Clk for BIST'
            'Feedback Div Out')
          ParentFont = False
          TabOrder = 3
          OnClick = rgrBCLKSELClick
        end
        object rgrBINSEL: TRadioGroup
          Left = 384
          Top = 0
          Width = 121
          Height = 81
          Caption = ' DSMN/BIST Input '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Items.Strings = (
            'NINT/NFRAC'
            'LFSR')
          ParentFont = False
          TabOrder = 4
          OnClick = rgrBINSELClick
        end
      end
    end
  end
  object GroupBox13: TGroupBox
    Left = 464
    Top = 8
    Width = 81
    Height = 65
    Caption = ' VCO Output '
    TabOrder = 9
    object Label23: TLabel
      Left = 8
      Top = 16
      Width = 52
      Height = 13
      Caption = 'Voltage, V:'
    end
    object cmbVOVCOREG: TComboBox
      Left = 8
      Top = 32
      Width = 65
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cmbVOVCOREGChange
      Items.Strings = (
        'Disabled'
        'First'
        'Second'
        'Third')
    end
  end
  object GroupBox14: TGroupBox
    Left = 552
    Top = 8
    Width = 121
    Height = 65
    Caption = ' Variuos VCO Controls '
    TabOrder = 10
    object chbBYPVCOREG: TCheckBox
      Left = 8
      Top = 13
      Width = 105
      Height = 17
      Caption = 'VCO Reg. Bypass'
      TabOrder = 0
      OnClick = chbBYPVCOREGClick
    end
    object chbPDVCOREG: TCheckBox
      Left = 8
      Top = 29
      Width = 105
      Height = 17
      Caption = 'VCO Reg. PD'
      TabOrder = 1
      OnClick = chbPDVCOREGClick
    end
    object chbFSTVCOBG: TCheckBox
      Left = 8
      Top = 45
      Width = 105
      Height = 17
      Caption = 'BG Res. Shorted'
      TabOrder = 2
      OnClick = chbFSTVCOBGClick
    end
  end
end
