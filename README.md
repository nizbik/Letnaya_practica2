Сборка проекта
Выполните команды в консоли в директории проекта:
mkdir build
cd build
cmake -S .. -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Release


Запуск программы
После сборки исполняемый файл letnaya_practica_2.exe находится в каталоге build\app\Release (или build\app\Debug).
Параметры командной строки:
-i file_name : Имя выводимого файла
-d dir : Директория для обработки всех файлов в ней
-o offset : Смещение от начала файла (по умолчанию 0)
-l size : Количество байт для вывода
-g size : Размер "кусочка" (группы байт, по умолчанию 1)
-n count : Количество кусочков в одной строке (по умолчанию 16)
-f format : Форматная строка для кастомного вывода

Пример использования:
Вывод содержимого файла в hex формате с группировкой по 4 байта:
build\app\Release\letnaya_practica_2.exe -i input.bin -g 4 -n 8

Вывод первых 100 байт файла со смещением 50:
build\app\Release\letnaya_practica_2.exe -i input.bin -o 50 -l 100

Обработка всех файлов в директории:
build\app\Release\letnaya_practica_2.exe -d ./data_folder -g 2
