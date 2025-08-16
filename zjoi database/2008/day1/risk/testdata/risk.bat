@echo off
if "%1"=="" goto loop
copy risk%1.in risk.in >nul
echo Problem Test
echo Data %1
time<enter
risk
time<enter
fc risk.out risk%1.out
del risk.in
del risk.out
pause
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14) do call %0 %%i
:end
