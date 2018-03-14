set PROGRAM="%~1"

rem �������� �� ���������� ��������� ����������
%PROGRAM% > out.txt
if not errorlevel 1 goto error

rem �������� ������������ action-�����
%PROGRAM% decrpts empty.txt %TEMP%/out.txt 25 > out.txt
if not errorlevel 1 goto error

rem �������� ������������ key
%PROGRAM% decrpts input.txt %TEMP%/out.txt 456 > out.txt
if not errorlevel 1 goto error

rem �������� �� �������� �������� �����
%PROGRAM% crypt not-exist.txt %TEMP%/out.txt 12 > out.txt
if not errorlevel 1 goto error

rem �������� �� �������� ��������� �����
%PROGRAM% crypt input.txt "" 12 > out.txt
if not errorlevel 1 goto error

rem �������� ���������� ��������� �������� 
%PROGRAM% crypt value53.txt out.txt 12
if errorlevel 1 goto error
fc out.txt resultForValue53.txt
if errorlevel 1 goto error

rem �������� ������������ ��������� ��������
%PROGRAM% decrypt resultForValue53.txt out.txt 12
if errorlevel 1 goto error
fc out.txt value53.txt
if errorlevel 1 goto error

rem �������� ���������� �����������
%PROGRAM% crypt sentence.txt out.txt 12
if errorlevel 1 goto error
fc out.txt resultSentence.txt
if errorlevel 1 goto error

rem �������� ������������ �����������
%PROGRAM% decrypt resultSentence.txt out.txt 12
if errorlevel 1 goto error
fc out.txt sentence.txt
if errorlevel 1 goto error

echo Program testing succeeded
exit 0

:error
echo Test failed
exit 1