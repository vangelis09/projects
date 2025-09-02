object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 309
  ClientWidth = 560
  Color = clYellow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesktopCenter
  OnCanResize = FormCanResize
  TextHeight = 13
  object Shape1: TShape
    Left = 56
    Top = 216
    Width = 25
    Height = 26
    Brush.Color = clNavy
    Shape = stRoundSquare
  end
  object Label1: TLabel
    Left = 144
    Top = 64
    Width = 16
    Height = 60
    Color = clCream
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -50
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 240
    Width = 561
    Height = 71
    Color = clRed
    ParentBackground = False
    TabOrder = 0
    OnClick = Panel1Click
    object Label2: TLabel
      Left = 376
      Top = 16
      Width = 41
      Height = 13
      Caption = 'SCORE: '
    end
    object Button2: TButton
      Left = 464
      Top = 8
      Width = 75
      Height = 25
      Caption = 'START'
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 464
      Top = 39
      Width = 75
      Height = 25
      Caption = 'Pause'
      TabOrder = 1
      OnClick = Button3Click
    end
  end
  object MediaPlayer1: TMediaPlayer
    Left = 160
    Top = 24
    Width = 253
    Height = 30
    DoubleBuffered = True
    FileName = 
      'D:\'#1059#1053#1048#1042#1045#1056#1057#1048#1058#1045#1058'\'#1055#1088#1086#1077#1082#1090#1099' '#1089'++ builder\geometry dash\Win32\Debug\eas' +
      'y.mp3'
    Visible = False
    ParentDoubleBuffered = False
    TabOrder = 1
  end
  object Timer1: TTimer
    Interval = 4
    OnTimer = Timer1Timer
    Left = 96
    Top = 248
  end
  object Timer2: TTimer
    Enabled = False
    OnTimer = Timer2Timer
    Left = 24
    Top = 248
  end
  object Timer3: TTimer
    Enabled = False
    OnTimer = Timer3Timer
    Left = 152
    Top = 248
  end
  object MainMenu1: TMainMenu
    Left = 400
    Top = 280
    object N1: TMenuItem
      Caption = #1054#1087#1094#1080#1080
      object N4: TMenuItem
        Caption = #1048#1079#1084#1077#1085#1080#1090#1100
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
        OnClick = N5Click
      end
    end
    object N2: TMenuItem
      Caption = #1057#1083#1086#1078#1085#1086#1089#1090#1100
    end
    object N3: TMenuItem
      Caption = #1042#1099#1093#1086#1076
    end
  end
end
