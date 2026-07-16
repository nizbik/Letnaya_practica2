/*
 * Главный модуль программы.
 * Заголовочный файл библиотеки ядра hex-просмотрщика. Содержит структуры и интерфейсы.
 * Зубехин Никита
 * МК-101
 */
#ifndef HEX_CORE_H
#define HEX_CORE_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

// Структура для хранения параметров командной строки
typedef struct {
    char *file_name;
    char *dir_name;
    long offset;
    long length;
    int group_size;
    int items_per_line;
    char *format_str;
    bool has_length;
} HexOptions;

// Ручной перевод одного байта в hex-символы и вывод в консоль
void print_byte_hex(unsigned char byte);

// Безопасный вывод символа (замена непечатаемых на '.')
void print_char_safe(unsigned char byte);

// Основная функция обработки файла
void process_file(const char *filepath, const HexOptions *options);

// Обработка директории
void process_directory(const char *dirpath, const HexOptions *options);

#endif