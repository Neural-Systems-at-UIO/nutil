Module Module1

    Sub Main()

        Dim book As libxl.XmlBook
        Dim sheet As libxl.Sheet

        book = New libxl.XmlBook
        sheet = book.addSheet("my")
        sheet.writeStr(2, 2, "Hello, World !")
        sheet.writeNum(3, 2, 1000)

        book.save("example.xlsx")

    End Sub

End Module
