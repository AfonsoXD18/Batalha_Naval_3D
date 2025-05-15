@echo off
chcp 65001 > nul
echo Compilando jao.cpp com g++...
g++ -std=c++14 jao.cpp -o jao.exe
if %errorlevel% neq 0 (
    echo Houve um erro na compilação.
    pause