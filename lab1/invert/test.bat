set PROGRAM="%~1"

rem провереяем запуск без параметров командной строки
%PROGRAM% > out.txt
if not errorlevel 1 goto error

rem Проверяем запуск с несуществующим файлом
%PROGRAM% undefined.txt > out.txt
if not errorlevel 1 goto error

rem Проверяем запуск с неполной матрицой
%PROGRAM% incompleteMatrix.txt > out.txt
if not errorlevel 1 goto error

rem Проверяем запуск с матрицей определителей, которой равен 0
%PROGRAM% matrix0.txt > out.txt
if not errorlevel 1 goto error
                                            
rem  Проверяем запуск с матрицией, определитель которой не равен 0
%PROGRAM% matrix1.txt > out.txt
if errorlevel 1 goto error
fc out.txt inverseMatrix1.txt
if errorlevel 1 goto error

rem Повторная проверка с матрицией, определитель которой не равен 0
%PROGRAM% matrix2.txt > out.txt
if errorlevel 1 goto error
fc out.txt inverseMatrix2.txt
if errorlevel 1 goto error 

rem Повторная проверка с матрицией, определитель которой не равен 0
%PROGRAM% matrixEgoshin.txt > out.txt
if errorlevel 1 goto error
fc out.txt resultEgoshin.txt
if errorlevel 1 goto error 


echo Program testing succeeded
exit 0

:error
echo Test failed
exit 1