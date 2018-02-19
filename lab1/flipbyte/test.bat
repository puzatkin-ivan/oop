set PROGRAM="%~1"

rem провереяем запуск без параметров командной строки
%PROGRAM% > out.txt
if not errorlevel 1 goto error

rem Проверяем запуск с входным и выходным файлом
%PROGRAM% 256 > out.txt
if not errorlevel 1 goto error

%PROGRAM% B > %TEMP%/out.txt
if not errorlevel 1 goto error

%PROGRAM% 128 > out.txt
if errorlevel 1 goto error
fc out.txt result1.txt
if errorlevel 1 goto error

%PROGRAM% 1 > out.txt
if errorlevel 1 goto error
fc out.txt result128.txt
if errorlevel 1 goto error

%PROGRAM% 56 > out.txt
if errorlevel 1 goto error
fc out.txt result28.txt
if errorlevel 1 goto error

%PROGRAM% 154 > out.txt
if errorlevel 1 goto error
fc out.txt result89.txt
if errorlevel 1 goto error

echo Program testing succeeded
exit 0

:error
echo Test failed
exit 1