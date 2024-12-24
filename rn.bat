@echo off
g++ cp.cpp -o cp.exe
g++ oth.cpp -o oth.exe
g++ gen.cpp -o gen.exe

set i=0

:loop
set /a i=i+1
echo %i%
gen.exe %i% > in
cp.exe < in > out1 2>nul
oth.exe < in > out2 2>nul
fc /b out1 out2 > nul
if not errorlevel 1 goto loop

echo Done.
