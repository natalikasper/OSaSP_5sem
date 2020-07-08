Option Explicit
Dim FSO, Batch, path, WshShell
Set FSO = CreateObject("Scripting.FileSystemObject")
Set Batch = FSO.OpenTextFile("D:\БГТУ\3 курс\5 семестр\ОСиСПр\4\script4.bat", 2, True)
Batch.Write "start Excel.exe"
Batch.Close
Set WshShell = CreateObject("WScript.Shell")
WshShell.Run "script4.bat", 1, True