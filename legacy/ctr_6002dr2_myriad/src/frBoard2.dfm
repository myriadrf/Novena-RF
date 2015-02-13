object frmBoard2: TfrmBoard2
  Left = 0
  Top = 0
  Width = 716
  Height = 236
  TabOrder = 0
  object LMS6002D: TGroupBox
    Left = 8
    Top = 8
    Width = 161
    Height = 97
    Caption = 'LMS6002D'
    TabOrder = 0
    object btnLmsRd: TButton
      Left = 8
      Top = 24
      Width = 145
      Height = 25
      Caption = 'Register write/read test'
      TabOrder = 0
      OnClick = btnLmsRdClick
    end
    object btnRdMem: TButton
      Left = 8
      Top = 56
      Width = 145
      Height = 25
      Caption = 'Memory read test'
      TabOrder = 1
      OnClick = btnRdMemClick
    end
  end
  object Si5356A: TGroupBox
    Left = 176
    Top = 8
    Width = 201
    Height = 97
    Caption = 'Si5356A'
    TabOrder = 1
    object btnConfigureSi5356A: TButton
      Left = 16
      Top = 24
      Width = 169
      Height = 25
      Caption = 'Upload register map to Si5356A'
      TabOrder = 0
      OnClick = btnConfigureSi5356AClick
    end
    object btnLoadFile: TButton
      Left = 16
      Top = 56
      Width = 169
      Height = 25
      Caption = 'Load register map from File'
      TabOrder = 1
      OnClick = btnLoadFileClick
    end
  end
  object dlgOpen: TOpenDialog
    Left = 680
    Top = 16
  end
end
