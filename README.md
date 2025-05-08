# COMChecker2
COMChecker2.0, обновление кода и рефакторинг  
# Компиляция из исходников
Для компиляции сначала клонируйте репозиторий с подмодулями  
`git clone --recurse-submodules https://github.com/ZReticules/COMChecker2`  
Затем в командной строке используя FASM со всеми пакетами макросов по умолчанию  
(Примечание: необходимо исправить баг - заменить в `INCLUDE\MACRO\PROC64.INC` строчку `stdcall fix fastcall` на `macro stdcall arg& {fastcall arg}`)  
`fasm -m 999999 COMChecker2.fasm COMChecker2.exe`  
Для выбора архитектуры x86 в файле COMChecker2.fasm замените  
`include "FASM_OOP\x64.inc"`  
на  
`include "FASM_OOP\x86.inc"`  