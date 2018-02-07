replace.exe 
IF NOT ERRORLEVEL 1 GOTO error

replace.exe in.txt out.txt
IF NOT ERRORLEVEL 1 GOTO error

replace.exe  in.txt out.txt "" work
IF NOT ERRORLEVEL 1 GOTO error

replace.exe  in.txt out.txt easy
IF NOT ERRORLEVEL 1 GOTO error

replace.exe in.txt out.txt empty aaaa
IF ERRORLEVEL 1 GOTO error
FC /B out.txt result.txt
if ERRORLEVEL 1 GOTO error 

replace.exe in.txt out.txt ma mama
IF ERRORLEVEL 1 GOTO error
FC /B out.txt result1.txt
if ERRORLEVEL 1 GOTO error

ECHO Program testing succeeded
EXIT 0

:error
ECHO Test failed
EXIT 1