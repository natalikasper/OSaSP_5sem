Set WshShell = CreateObject ("WScript.Shell")
Set objEnv = WshShell.Environment("Process")
objEnv("MyVar") = "C:\Windows\notepad.exe D:\����\3 ����\5 �������\������\3�\ex1.vbs"
WshShell.Run objEnv("MyVar"),1