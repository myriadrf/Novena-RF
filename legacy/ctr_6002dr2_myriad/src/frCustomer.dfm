object frmCustomer: TfrmCustomer
  Left = 0
  Top = 0
  Width = 787
  Height = 410
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  ParentColor = False
  ParentFont = False
  TabOrder = 0
  object GroupBox4: TGroupBox
    Left = 0
    Top = 0
    Width = 97
    Height = 73
    Caption = ' LNA Control '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label6: TLabel
      Left = 8
      Top = 24
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
    object cmbLNASEL_Cust: TComboBox
      Left = 8
      Top = 40
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
      TabOrder = 0
    end
  end
  object GroupBox1: TGroupBox
    Left = 104
    Top = 0
    Width = 185
    Height = 73
    Caption = ' Automatic Calibration '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object btnClbrTx: TButton
      Left = 8
      Top = 16
      Width = 81
      Height = 25
      Caption = 'Transmitter'
      TabOrder = 0
    end
    object btnClbrRx: TButton
      Left = 96
      Top = 16
      Width = 83
      Height = 25
      Caption = 'Receiver'
      TabOrder = 1
    end
    object btnCalRxTIA: TButton
      Left = 96
      Top = 43
      Width = 83
      Height = 25
      Caption = 'Receiver TIA'
      TabOrder = 2
      Visible = False
    end
    object Button1: TButton
      Left = 8
      Top = 43
      Width = 81
      Height = 25
      Caption = 'LPF Core'
      TabOrder = 3
    end
  end
  object GroupBox2: TGroupBox
    Left = 296
    Top = 0
    Width = 489
    Height = 73
    Caption = ' Bypass Configurations '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 83
      Height = 13
      Caption = 'Rx Bypass Mode:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 312
      Top = 24
      Width = 123
      Height = 13
      Caption = 'RF / BB Loopback Mode:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 160
      Top = 24
      Width = 82
      Height = 13
      Caption = 'Tx Bypass Mode:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbBypass: TComboBox
      Left = 8
      Top = 40
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
      Items.Strings = (
        'Normal Operation'
        'Bypass RxLPF'
        'Bypass RxLPF, RxVGA2')
    end
    object cmbLoopback: TComboBox
      Left = 312
      Top = 40
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
      Items.Strings = (
        'Normal Operation'
        'BB loopback to RxLPF Input'
        'BB loopback to RxVGA2 Input'
        'BB loopback to Output Pins'
        'RF loopback LNA1'
        'RF loopback LNA2'
        'RF loopback LNA3')
    end
    object cmbTxBypass: TComboBox
      Left = 160
      Top = 40
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
      Items.Strings = (
        'Normal Operation'
        'Bypass TxLPF')
    end
  end
  object GroupBox3: TGroupBox
    Left = 296
    Top = 80
    Width = 289
    Height = 73
    Caption = ' Uplink (Rx) Frequency Band and Channel '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Label4: TLabel
      Left = 8
      Top = 24
      Width = 28
      Height = 13
      Caption = 'Band:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 58
      Top = 24
      Width = 42
      Height = 13
      Caption = 'Channel:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 128
      Top = 24
      Width = 65
      Height = 13
      Caption = 'Fast Channel:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 200
      Top = 24
      Width = 81
      Height = 13
      Caption = 'Frequency, MHz:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnULRXFChan_B: TSpeedButton
      Left = 125
      Top = 40
      Width = 23
      Height = 22
      AllowAllUp = True
      GroupIndex = 10
      Caption = 'B'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnULRXFChan_M: TSpeedButton
      Left = 149
      Top = 40
      Width = 23
      Height = 22
      AllowAllUp = True
      GroupIndex = 10
      Caption = 'M'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnULRXFChan_T: TSpeedButton
      Left = 173
      Top = 40
      Width = 23
      Height = 22
      AllowAllUp = True
      GroupIndex = 10
      Caption = 'T'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbULRXBands: TComboBox
      Left = 8
      Top = 40
      Width = 45
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
      Items.Strings = (
        'I'
        'II'
        'III'
        'IV'
        'V'
        'VI'
        'VII'
        'VIII'
        'IX'
        'X'
        'XI'
        'XII'
        'XIII'
        'XIV')
    end
    object cmbULRXChan: TComboBox
      Left = 58
      Top = 40
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
      Items.Strings = (
        '10000')
    end
    object txtULRXFreq: TEdit
      Left = 200
      Top = 40
      Width = 81
      Height = 21
      Enabled = False
      TabOrder = 2
      Text = '1922,4'
    end
  end
  object GroupBox5: TGroupBox
    Left = 0
    Top = 80
    Width = 289
    Height = 73
    Caption = ' Downlink (Tx) Frequency Band and Channel '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    object Label9: TLabel
      Left = 8
      Top = 24
      Width = 28
      Height = 13
      Caption = 'Band:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 58
      Top = 24
      Width = 42
      Height = 13
      Caption = 'Channel:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 128
      Top = 24
      Width = 65
      Height = 13
      Caption = 'Fast Channel:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 200
      Top = 24
      Width = 81
      Height = 13
      Caption = 'Frequency, MHz:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnDLTXFChan_B: TSpeedButton
      Left = 125
      Top = 40
      Width = 23
      Height = 22
      AllowAllUp = True
      GroupIndex = 10
      Caption = 'B'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnDLTXFChan_M: TSpeedButton
      Left = 149
      Top = 40
      Width = 23
      Height = 22
      AllowAllUp = True
      GroupIndex = 10
      Caption = 'M'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object btnDLTXFChan_T: TSpeedButton
      Left = 173
      Top = 40
      Width = 23
      Height = 22
      AllowAllUp = True
      GroupIndex = 10
      Caption = 'T'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object cmbDLTXBands: TComboBox
      Left = 8
      Top = 40
      Width = 45
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
      Items.Strings = (
        'I'
        'II'
        'III'
        'IV'
        'V'
        'VI'
        'VII'
        'VIII'
        'IX'
        'X'
        'XI'
        'XII'
        'XIII'
        'XIV')
    end
    object cmbDLTXChan: TComboBox
      Left = 58
      Top = 40
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
      Items.Strings = (
        '10000')
    end
    object txtDLTXFreq: TEdit
      Left = 200
      Top = 40
      Width = 81
      Height = 21
      Enabled = False
      TabOrder = 2
      Text = '1922,4'
    end
  end
end
