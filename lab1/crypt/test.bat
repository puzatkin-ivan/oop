set PROGRAM="%~1"

rem Проверка на количество преданных параметров
%PROGRAM% > out.txt
if not errorlevel 1 goto error

rem Проверка корректности action-слово
%PROGRAM% decrpts empty.txt %TEMP%/out.txt 25 > out.txt
if not errorlevel 1 goto error

rem Проверка корректности key
%PROGRAM% decrpts input.txt %TEMP%/out.txt 456 > out.txt
if not errorlevel 1 goto error

rem Проверка на открытие входного файла
%PROGRAM% crypt not-exist.txt %TEMP%/out.txt 12 > out.txt
if not errorlevel 1 goto error

rem Проверка на открытие выходного файла
%PROGRAM% crypt input.txt "" 12 > out.txt
if not errorlevel 1 goto error

rem Проверка шифрования числового значения 
%PROGRAM% crypt value53.txt out.txt 12
if errorlevel 1 goto error
fc out.txt resultForValue53.txt
if errorlevel 1 goto error

rem Проверка дешифрования числового значения
%PROGRAM% decrypt resultForValue53.txt out.txt 12
if errorlevel 1 goto error
fc out.txt value53.txt
if errorlevel 1 goto error

rem Проверка шифрования предложения
%PROGRAM% crypt sentence.txt out.txt 12
if errorlevel 1 goto error
fc out.txt resultSentence.txt
if errorlevel 1 goto error

rem Проверка дешифрования предложения
%PROGRAM% decrypt resultSentence.txt out.txt 12
if errorlevel 1 goto error
fc out.txt sentence.txt
if errorlevel 1 goto error

echo Program testing succeeded
exit 0

:error
echo Test failed
exit 1