object Form1: TForm1
  Left = 400
  Top = 135
  Width = 596
  Height = 113
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GenerateButton: TButton
    Left = 48
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Generate'
    TabOrder = 0
    OnClick = GenerateButtonClick
  end
  object ExtractButton: TButton
    Left = 136
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Extract'
    TabOrder = 1
    OnClick = ExtractButtonClick
  end
  object EditButton: TButton
    Left = 224
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Edit'
    TabOrder = 2
    OnClick = EditButtonClick
  end
  object FormatButton: TButton
    Left = 312
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Format'
    TabOrder = 3
    OnClick = FormatButtonClick
  end
  object CustomButton: TButton
    Left = 400
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Custom'
    TabOrder = 4
    OnClick = CustomButtonClick
  end
  object InvoiceButton: TButton
    Left = 488
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Invoice'
    TabOrder = 5
    OnClick = InvoiceButtonClick
  end
end
