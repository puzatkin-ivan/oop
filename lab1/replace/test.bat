set PROGRAM="%~1"

rem провереяем запуск без параметров командной строки
%PROGRAM% > log.txt
if not errorlevel 1 goto error

rem Проверяем запуск с входным и выходным файлом
%PROGRAM% undefined.txt %TEMP%\out.txt > log.txt
if not errorlevel 1 goto error

%PROGRAM% name-list.txt "" Arthur Ivan > log.txt 
if not errorlevel 1 goto error

%PROGRAM% name-list.txt %TEMP%\out.txt "" Arthur > log.txt  
if not errorlevel 1 goto error

%PROGRAM% name-list.txt out.txt Charlotte Anna > log.txt  
if errorlevel 1 goto error
fc out.txt replace-Charlotte-by-Anna.txt
if errorlevel 1 goto error 

%PROGRAM% name-list.txt out.txt Barbara "" > log.txt
if errorlevel 1 goto error
fc out.txt without-Barbara.txt
if errorlevel 1 goto error

%PROGRAM% replay.txt %TEMP%\out.txt ma mama > log.txt
if errorlevel 1 goto error
fc %TEMP%\out.txt check-by-replay.txt
if errorlevel 1 goto error


echo Program testing succeeded
exit 0

:error
echo Test failed
exit 1