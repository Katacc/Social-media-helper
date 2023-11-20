@echo off

start g++ -std=c++2a main.cpp -o mediaHelper.exe

mklink "../mediaHelper.exe" mediaHelper.exe
