@echo off
chcp 65001 > nul
echo Compilando batalhaNaval.cpp com g++...

g++ -std=c++14 batalhaNaval.cpp -o batalhaNaval.exe
if %errorlevel% neq 0 (
    echo Houve um erro na compilação.
    pause
    exit /b
)

echo Compilação bem-sucedida. A executar...
echo.
batalhaNaval.exe

echo.
pause