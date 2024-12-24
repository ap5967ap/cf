@echo off

:: Default file name if no argument is provided
set "defaultFile=cp.cpp"

:: Check if an argument is provided
if "%~1"=="" (
    set "fileToCompile=%defaultFile%"
) else (
    set "fileToCompile=%~1"
)

:: Compile the file with g++
g++ -DLOCAL -Wall -Wextra -pedantic -std=c++20 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fno-sanitize-recover -fstack-protector -Wno-unused-result "%fileToCompile%" -o "a.exe"
a.exe
:: Check the compilation status and set the exit code
if %ERRORLEVEL%==0 (
    exit 0
) else (
    exit %ERRORLEVEL%
)
