@echo off
copy x64\Release\LZ_MainWindow.exe C:\Users\asus\Desktop\兰州隧道进出洞检测程序\
rd /s /q ipch\
rd /s /q LZ_MainWindow\x64
del /s /q *.sdf *.opensdf *.suo
del /s /q LZ_MainWindow\*.aps LZ_MainWindow\*.user 
