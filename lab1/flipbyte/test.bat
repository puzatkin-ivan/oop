set PROGRAM="%~1"

rem провереяем запуск без параметров командной строки
%PROGRAM% > out.txt
IF NOT ERRORLEVEL 1 GOTO error

rem Проверяем запуск с входным и выходным файлом
%PROGRAM% 256 > out.txt
IF NOT ERRORLEVEL 1 GOTO error

%PROGRAM% B > %TEMP%/out.txt
IF NOT ERRORLEVEL 1 GOTO error

%PROGRAM% 128 > out.txt
IF ERRORLEVEL 1 GOTO error
FC out.txt result1.txt
IF ERRORLEVEL 1 GOTO error

%PROGRAM% 1 > out.txt
IF errorlevel 1 goto error
FC out.txt result128.txt
IF ERRORLEVEL 1 GOTO error

ECHO Program testing succeeded
EXIT 0

:error
ECHO Test failed
EXIT 1