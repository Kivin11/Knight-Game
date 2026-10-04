# Knight-Game
Игра про рыцаря и спасение принцессы на си++. включает жанры: платформер, пвп и некоторые другие глубоко проработанные механики
При сборке проекта для виндоус были использованы: 
    1. Компилятор GCC (MinGW-w64, окружение MSYS2 Ucrt64)
    2. Среда разработки VSCode
    3. Библиотека Raylib 6.0
    4. Команда компиляции: "cd $dir && g++ $fileName -o $fileNameWithoutExt -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows && $dir$fileNameWithoutExt" (уже готова для CodeRunner в файле ./.vscode/settings.json в папке проекта)