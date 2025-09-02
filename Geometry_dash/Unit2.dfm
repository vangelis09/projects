object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 340
  ClientWidth = 380
  Color = clRed
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesktopCenter
  TextHeight = 15
  object Label1: TLabel
    Left = 146
    Top = 8
    Width = 105
    Height = 25
    Caption = #1053#1040#1057#1058#1056#1054#1049#1050#1048
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -18
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 56
    Width = 193
    Height = 225
    TabOrder = 0
    object Label2: TLabel
      Left = 48
      Top = 0
      Width = 90
      Height = 19
      Caption = #1048#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 16
      Top = 35
      Width = 90
      Height = 15
      Caption = #1062#1074#1077#1090#1086#1074#1072#1103' '#1089#1093#1077#1084#1072':'
    end
    object RadioButton1: TRadioButton
      Left = 16
      Top = 56
      Width = 113
      Height = 17
      Caption = #1057#1074#1077#1090#1083#1072#1103
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 16
      Top = 80
      Width = 113
      Height = 17
      Caption = #1058#1077#1084#1085#1072#1103
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 199
    Top = 56
    Width = 185
    Height = 225
    TabOrder = 1
    object Label4: TLabel
      Left = 80
      Top = 3
      Width = 28
      Height = 15
      Caption = #1047#1074#1091#1082':'
    end
    object Label6: TLabel
      Left = 16
      Top = 35
      Width = 36
      Height = 15
      Caption = #1057#1090#1080#1083#1100':'
    end
    object RadioButton3: TRadioButton
      Left = 16
      Top = 56
      Width = 113
      Height = 17
      Caption = #1042#1077#1089#1077#1083#1099#1081
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton4: TRadioButton
      Left = 16
      Top = 79
      Width = 113
      Height = 17
      Caption = #1069#1083#1077#1082#1090#1088#1086#1085#1080#1082#1072
      TabOrder = 1
    end
    object RadioButton5: TRadioButton
      Left = 16
      Top = 102
      Width = 113
      Height = 17
      Caption = #1056#1086#1079#1086#1074#1072#1103' '#1087#1072#1085#1090#1077#1088#1072
      TabOrder = 2
    end
    object RadioButton6: TRadioButton
      Left = 16
      Top = 125
      Width = 113
      Height = 17
      Caption = #1041#1077#1079' '#1079#1074#1091#1082#1072
      TabOrder = 3
    end
  end
  object Button2: TButton
    Left = 96
    Top = 296
    Width = 97
    Height = 25
    Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 199
    Top = 296
    Width = 98
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 3
    OnClick = Button3Click
  end
end
