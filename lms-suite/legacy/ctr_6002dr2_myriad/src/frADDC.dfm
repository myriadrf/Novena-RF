object frmADDC: TfrmADDC
  Left = 0
  Top = 0
  Width = 777
  Height = 378
  TabOrder = 0
  object GroupBox4: TGroupBox
    Left = 0
    Top = 128
    Width = 233
    Height = 121
    Caption = ' ADC/DAC Miscellaneous Control  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object rgrRX_FSYNC_P: TRadioGroup
      Left = 8
      Top = 16
      Width = 105
      Height = 33
      Caption = ' Rx Fsync Polarity '
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '0'
        '1')
      ParentFont = False
      TabOrder = 0
      OnClick = rgrRX_FSYNC_PClick
    end
    object rgrRX_INTER: TRadioGroup
      Left = 8
      Top = 48
      Width = 105
      Height = 33
      Caption = ' Rx Interleave '
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'I, Q'
        'Q, I')
      ParentFont = False
      TabOrder = 1
      OnClick = rgrRX_INTERClick
    end
    object rgrDAC_CLK_P: TRadioGroup
      Left = 8
      Top = 80
      Width = 105
      Height = 33
      Caption = ' DAC Edge '
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'Pos'
        'Neg')
      ParentFont = False
      TabOrder = 2
      OnClick = rgrDAC_CLK_PClick
    end
    object rgrTX_FSYNC_P: TRadioGroup
      Left = 120
      Top = 16
      Width = 105
      Height = 33
      Caption = ' Tx Fsync Polarity '
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '0'
        '1')
      ParentFont = False
      TabOrder = 3
      OnClick = rgrTX_FSYNC_PClick
    end
    object rgrTX_INTER: TRadioGroup
      Left = 120
      Top = 48
      Width = 105
      Height = 33
      Caption = ' Tx Interleave '
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'I, Q'
        'Q, I')
      ParentFont = False
      TabOrder = 4
      OnClick = rgrTX_INTERClick
    end
  end
  object GroupBox5: TGroupBox
    Left = 240
    Top = 0
    Width = 529
    Height = 65
    Caption = ' ADC/DAC Reference Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 104
      Height = 13
      Caption = 'Bandgap Temp Coeff:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 120
      Top = 16
      Width = 71
      Height = 13
      Caption = 'Bandgap Gain:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 216
      Top = 16
      Width = 90
      Height = 13
      Caption = 'Ref Amps Bias Adj:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 320
      Top = 16
      Width = 90
      Height = 13
      Caption = 'Ref Amps Bias UP:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 424
      Top = 16
      Width = 91
      Height = 13
      Caption = 'Ref Amps Bias DN:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbBandgapTemp: TComboBox
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
      OnChange = cmbBandgapTempChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbBandgapGain: TComboBox
      Left = 120
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
      OnChange = cmbBandgapGainChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefAmpsBiasAdj: TComboBox
      Left = 216
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
      TabOrder = 2
      OnChange = cmbRefAmpsBiasAdjChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefAmpsBiasUp: TComboBox
      Left = 320
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
      TabOrder = 3
      OnChange = cmbRefAmpsBiasUpChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefAmpsBiasDn: TComboBox
      Left = 424
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
      TabOrder = 4
      OnChange = cmbRefAmpsBiasDnChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
  end
  object GroupBox7: TGroupBox
    Left = 240
    Top = 144
    Width = 529
    Height = 217
    Caption = ' ADC Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label10: TLabel
      Left = 360
      Top = 40
      Width = 92
      Height = 13
      Caption = 'Common Mode Adj:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 456
      Top = 40
      Width = 63
      Height = 13
      Caption = 'Ref Gain Adj:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label14: TLabel
      Left = 8
      Top = 40
      Width = 83
      Height = 13
      Caption = 'Ref Bias Res Adj:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label16: TLabel
      Left = 104
      Top = 40
      Width = 61
      Height = 13
      Caption = 'Ref Bias UP:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label18: TLabel
      Left = 184
      Top = 40
      Width = 62
      Height = 13
      Caption = 'Ref Bias DN:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label19: TLabel
      Left = 264
      Top = 40
      Width = 72
      Height = 13
      Caption = 'Ref Buff Boost:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 88
      Width = 68
      Height = 13
      Caption = 'Main Bias DN:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 120
      Top = 88
      Width = 111
      Height = 13
      Caption = 'Clock Non-Overlap Adj:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 240
      Top = 88
      Width = 104
      Height = 13
      Caption = 'ADC Sampling Phase:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbCoomonModeAdj: TComboBox
      Left = 360
      Top = 56
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
      OnChange = cmbCoomonModeAdjChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefGainAdj: TComboBox
      Left = 456
      Top = 56
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
      TabOrder = 1
      OnChange = cmbRefGainAdjChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefResistorBiasAdj: TComboBox
      Left = 8
      Top = 56
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
      TabOrder = 2
      OnChange = cmbRefResistorBiasAdjChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefBiasUp: TComboBox
      Left = 104
      Top = 56
      Width = 73
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
      OnChange = cmbRefBiasUpChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbRefBiasDn: TComboBox
      Left = 184
      Top = 56
      Width = 73
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
      OnChange = cmbRefBiasDnChange
    end
    object cmbRefBufferBoost: TComboBox
      Left = 264
      Top = 56
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
      TabOrder = 5
      OnChange = cmbRefBufferBoostChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object rgrADCAmp1Stage2BasUp: TRadioGroup
      Left = 8
      Top = 176
      Width = 160
      Height = 33
      Caption = 'ADC Amp1 Stage2 Bias Up, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 6
      OnClick = rgrADCAmp1Stage2BasUpClick
    end
    object rgrADCAmp24Stage2BasUp: TRadioGroup
      Left = 176
      Top = 176
      Width = 177
      Height = 33
      Caption = 'ADC Amp2-4 Stage2 Bias Up, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 7
      OnClick = rgrADCAmp24Stage2BasUpClick
    end
    object rgrQuantizerBiasUp: TRadioGroup
      Left = 360
      Top = 136
      Width = 161
      Height = 33
      Caption = 'Quantizer Bias Up, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 8
      OnClick = rgrQuantizerBiasUpClick
    end
    object rgrInputBufferBiasUp: TRadioGroup
      Left = 360
      Top = 176
      Width = 160
      Height = 33
      Caption = 'Input Buffer Bias Up, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 9
      OnClick = rgrInputBufferBiasUpClick
    end
    object rgrADCAmp1Stage1BasUp: TRadioGroup
      Left = 8
      Top = 136
      Width = 160
      Height = 33
      Caption = 'ADC Amp1 Stage1 Bias Up, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 10
      OnClick = rgrADCAmp1Stage1BasUpClick
    end
    object rgrADCAmp24Stage1BasUp: TRadioGroup
      Left = 176
      Top = 136
      Width = 177
      Height = 33
      Caption = 'ADC Amp2-4 Stage1 Bias Up, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 11
      OnClick = rgrADCAmp24Stage1BasUpClick
    end
    object rgrADCBiasResistorAdjust: TRadioGroup
      Left = 360
      Top = 88
      Width = 160
      Height = 36
      Caption = 'ADC Bias Resistor Adjust, uA'
      Columns = 4
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        '20'
        '40'
        '10'
        '15')
      ParentFont = False
      TabOrder = 12
      OnClick = rgrADCBiasResistorAdjustClick
    end
    object cmbMainBiasDN: TComboBox
      Left = 8
      Top = 104
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
      TabOrder = 13
      OnChange = cmbMainBiasDNChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbClockNonOverlapAdjust: TComboBox
      Left = 120
      Top = 104
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
      TabOrder = 14
      OnChange = cmbClockNonOverlapAdjustChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbADCSamplingPhase: TComboBox
      Left = 240
      Top = 104
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
      TabOrder = 15
      OnChange = cmbADCSamplingPhaseChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object chkInputBufferDisable: TCheckBox
      Left = 8
      Top = 16
      Width = 121
      Height = 17
      Caption = 'Input Buffer Disabled'
      Checked = True
      State = cbChecked
      TabOrder = 16
      OnClick = chkInputBufferDisableClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 240
    Top = 72
    Width = 529
    Height = 65
    Caption = ' DAC Control  '
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
      Width = 166
      Height = 13
      Caption = 'DAC Internal Output Load Resistor:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 368
      Top = 16
      Width = 146
      Height = 13
      Caption = 'DAC Full Scale Output Current:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object rgrDACReferenceCurrentResistor: TRadioGroup
      Left = 184
      Top = 16
      Width = 177
      Height = 36
      Caption = ' DAC Reference Current Resistor '
      Columns = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      Items.Strings = (
        'Internal '
        'External')
      ParentFont = False
      TabOrder = 0
      OnClick = rgrDACReferenceCurrentResistorClick
    end
    object cmbDACInternalOutputLoadResistor: TComboBox
      Left = 8
      Top = 32
      Width = 169
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
      OnChange = cmbDACInternalOutputLoadResistorChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
    object cmbDACFullScaleOutputCurrent: TComboBox
      Left = 368
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
      TabOrder = 2
      OnChange = cmbDACFullScaleOutputCurrentChange
      Items.Strings = (
        'MUX Inputs Disconnected'
        'MUX Input 1 Connected to TX1'
        'MUX Input 2 Connected to TX2')
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 48
    Width = 233
    Height = 73
    Caption = ' ADC/DAC Enable Control  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object chkEN_ADC_I: TCheckBox
      Left = 8
      Top = 32
      Width = 97
      Height = 17
      Caption = 'ADC1 (I) Enable'
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = chkEN_ADC_IClick
    end
    object chkEN_ADC_Q: TCheckBox
      Left = 8
      Top = 48
      Width = 105
      Height = 17
      Caption = 'ADC2 (Q) Enable'
      Checked = True
      State = cbChecked
      TabOrder = 1
      OnClick = chkEN_ADC_QClick
    end
    object chkEN_ADC_REF: TCheckBox
      Left = 120
      Top = 16
      Width = 97
      Height = 17
      Caption = 'ADC Ref Enable'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = chkEN_ADC_REFClick
    end
    object chkEN_DAC: TCheckBox
      Left = 120
      Top = 32
      Width = 97
      Height = 17
      Caption = 'DAC Enable'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = chkEN_DACClick
    end
    object chkEN_M_REF: TCheckBox
      Left = 120
      Top = 48
      Width = 110
      Height = 17
      Caption = 'Master Ref Enable'
      Checked = True
      State = cbChecked
      TabOrder = 4
      OnClick = chkEN_M_REFClick
    end
    object chbEN_ADC_DAC: TCheckBox
      Left = 8
      Top = 16
      Width = 97
      Height = 17
      Caption = 'ADDC Enable'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 5
      OnClick = chkEN_ADC_REFClick
    end
  end
  object rgrDecode: TRadioGroup
    Left = 0
    Top = 0
    Width = 233
    Height = 41
    Caption = ' Decoding '
    Columns = 2
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
    TabOrder = 5
    OnClick = rgrDecodeClick
  end
end
