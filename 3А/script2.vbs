Set WshShell = CreateObject ("WScript.Shell")
Set objEnv = WshShell.Environment("Process")
objEnv("MyVar") = "C:\Windows\notepad.exe D:\БГТУ\3 курс\5 семестр\ОСиСПр\3А\ex1.vbs"
WshShell.Run objEnv("MyVar"),1