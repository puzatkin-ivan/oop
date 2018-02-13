set PROGRAM="%~1"

rem провереяем запуск без параметров командной строки
%PROGRAM% > response.txt
IF NOT ERRORLEVEL 1 GOTO error

rem Проверяем запуск с входным и выходным файлом
%PROGRAM% undefined.txt %TEMP%\out.txt > response.txt
IF NOT ERRORLEVEL 1 GOTO error

%PROGRAM% name-list.txt "" Arthur Ivan > response.txt
IF NOT ERRORLEVEL 1 GOTO error

%PROGRAM% name-list.txt %TEMP%\out.txt "" Arthur  > response.txt
IF NOT ERRORLEVEL 1 GOTO error

%PROGRAM% name-list.txt %TEMP%\out.txt Charlotte Anna  > response.txt
IF ERRORLEVEL 1 GOTO error
FC %TEMP%\out.txt replace-Charlotte-by-Anna.txt
if ERRORLEVEL 1 GOTO error 

%PROGRAM% name-list.txt %TEMP%\out.txt Barbara "" > response.txt
IF ERRORLEVEL 1 GOTO error
FC %TEMP%\out.txt without-Barbara.txt
if ERRORLEVEL 1 GOTO error

%PROGRAM% replay.txt %TEMP%\out.txt ma mama > response.txt
IF ERRORLEVEL 1 GOTO error
FC %TEMP%\out.txt check-by-replay.txt
if ERRORLEVEL 1 GOTO error


ECHO Program testing succeeded
EXIT 0

:error
ECHO Test failed
EXIT 1