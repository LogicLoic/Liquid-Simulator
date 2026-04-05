@echo off
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo g++ introuvable ! Ajoutez MinGW dans votre PATH.
    pause
    exit /b 1
)

@echo off
REM Nettoyer l'ancien build
if exist main.exe del main.exe

REM Compiler tous les fichiers .cpp du projet
g++ main.cpp class/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o main.exe

if %errorlevel% neq 0 (
    echo Erreur de compilation !
    pause
    exit /b %errorlevel%
)

echo Compilation terminée avec succès !
pause