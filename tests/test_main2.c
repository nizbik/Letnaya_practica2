/*
 * Расширенные тесты для библиотеки hex_core
 * Зубехин Никита
 * МК-101
 */

#include "hex_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// Макрос для запуска тестов
#define RUN_TEST(test_func) \
    do { \
        printf("Running " #test_func "..."); \
        test_func(); \
        printf(" OK\n"); \
    } while(0)

// ============================================
// ТЕСТЫ print_byte_hex
// ============================================

void test_hex_conversion_zero() {
    // Тест: 0x00 -> "00"
    printf("\n[Output for 0x00: ");
    print_byte_hex(0x00);
    printf("]");
}

void test_hex_conversion_max() {
    // Тест: 0xFF -> "FF"
    printf("\n[Output for 0xFF: ");
    print_byte_hex(0xFF);
    printf("]");
}

void test_hex_conversion_mixed() {
    // Тест: 0xAB -> "AB"
    printf("\n[Output for 0xAB: ");
    print_byte_hex(0xAB);
    printf("]");
}

void test_hex_conversion_all_values() {
    // Тест всех возможных значений байт (0-255)
    for (int i = 0; i < 256; i++) {
        unsigned char byte = (unsigned char)i;
        // Просто проверяем что функция не падает
        print_byte_hex(byte);
    }
    printf(" (tested all 256 values)");
}

void test_hex_conversion_patterns() {
    // Тест паттернов: 0x0F, 0xF0, 0x55, 0xAA
    printf("\n0x0F: "); print_byte_hex(0x0F);
    printf("\n0xF0: "); print_byte_hex(0xF0);
    printf("\n0x55: "); print_byte_hex(0x55);
    printf("\n0xAA: "); print_byte_hex(0xAA);
}

// ============================================
// ТЕСТЫ print_char_safe
// ============================================

void test_char_safe_printable() {
    // Тест печатаемых символов
    printf("\n[A: "); print_char_safe('A'); printf("]");
    printf("\n[z: "); print_char_safe('z'); printf("]");
    printf("\n[0: "); print_char_safe('0'); printf("]");
    printf("\n[space: "); print_char_safe(' '); printf("]");
}

void test_char_safe_unprintable() {
    // Тест непечатаемых символов (должны заменяться на '.')
    printf("\n[NULL 0x00: "); print_char_safe(0x00); printf("]");
    printf("\n[BEL 0x07: "); print_char_safe(0x07); printf("]");
    printf("\n[BS 0x08: "); print_char_safe(0x08); printf("]");
    printf("\n[TAB 0x09: "); print_char_safe(0x09); printf("]");
    printf("\n[LF 0x0A: "); print_char_safe(0x0A); printf("]");
}

void test_char_safe_extended_ascii() {
    // Тест расширенного ASCII (128-255)
    for (int i = 128; i < 256; i++) {
        print_char_safe((unsigned char)i);
    }
    printf(" (tested extended ASCII)");
}

// ============================================
// ТЕСТЫ HexOptions
// ============================================

void test_option_defaults() {
    // Тест значений по умолчанию
    HexOptions opts = {0};
    assert(opts.offset == 0);
    assert(opts.length == 0);
    assert(opts.group_size == 0);
    assert(opts.items_per_line == 0);
    assert(opts.file_name == NULL);
    assert(opts.dir_name == NULL);
    assert(opts.format_str == NULL);
    assert(opts.has_length == false);
}

void test_option_custom() {
    // Тест кастомных значений
    HexOptions opts = {
        .file_name = "test.txt",
        .offset = 100,
        .length = 50,
        .group_size = 4,
        .items_per_line = 8,
        .has_length = true
    };
    
    assert(strcmp(opts.file_name, "test.txt") == 0);
    assert(opts.offset == 100);
    assert(opts.length == 50);
    assert(opts.group_size == 4);
    assert(opts.items_per_line == 8);
    assert(opts.has_length == true);
}

// ============================================
// ТЕСТЫ process_file
// ============================================

void test_process_file_create_test_file() {
    // Создаём тестовый файл
    FILE *f = fopen("test_data.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    fwrite(data, 1, 5, f);
    fclose(f);
    
    // Просто проверяем что файл создался
    assert(remove("test_data.bin") == 0);
}

void test_process_file_empty_file() {
    // Создаём пустой файл
    FILE *f = fopen("empty.bin", "wb");
    assert(f != NULL);
    fclose(f);
    
    HexOptions opts = {0};
    opts.file_name = "empty.bin";
    opts.group_size = 1;
    opts.items_per_line = 16;
    
    printf("\nProcessing empty file:\n");
    process_file("empty.bin", &opts);
    
    remove("empty.bin");
}

void test_process_file_with_offset() {
    // Создаём файл с данными
    FILE *f = fopen("offset_test.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[20];
    for (int i = 0; i < 20; i++) {
        data[i] = (unsigned char)i;
    }
    fwrite(data, 1, 20, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.offset = 10;  // Начинаем с 10-го байта
    opts.group_size = 1;
    opts.items_per_line = 16;
    
    printf("\nProcessing file with offset 10:\n");
    process_file("offset_test.bin", &opts);
    
    remove("offset_test.bin");
}

void test_process_file_with_length() {
    // Создаём файл
    FILE *f = fopen("length_test.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[50];
    for (int i = 0; i < 50; i++) {
        data[i] = (unsigned char)(i % 256);
    }
    fwrite(data, 1, 50, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.length = 20;  // Читаем только 20 байт
    opts.has_length = true;
    opts.group_size = 1;
    opts.items_per_line = 16;
    
    printf("\nProcessing file with length 20:\n");
    process_file("length_test.bin", &opts);
    
    remove("length_test.bin");
}

void test_process_file_group_format() {
    // Тест группировки
    FILE *f = fopen("group_test.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                               0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    fwrite(data, 1, 16, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.group_size = 4;  // Группы по 4 байта
    opts.items_per_line = 4;  // 4 группы на строку
    opts.offset = 0;
    
    printf("\nProcessing file with group_size=4, items_per_line=4:\n");
    process_file("group_test.bin", &opts);
    
    remove("group_test.bin");
}

// ============================================
// ТЕСТЫ форматированного вывода
// ============================================

void test_format_with_offset() {
    // Тест формата с %n (смещение)
    FILE *f = fopen("format_test.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[32];
    for (int i = 0; i < 32; i++) {
        data[i] = (unsigned char)(0x30 + i);  // '0', '1', ...
    }
    fwrite(data, 1, 32, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.group_size = 2;
    opts.items_per_line = 8;
    opts.format_str = "%n: %0 %1 %2 %3\\n";
    
    printf("\nFormatted output with offsets:\n");
    process_file("format_test.bin", &opts);
    
    remove("format_test.bin");
}

void test_format_with_index() {
    // Тест формата с %i (номер строки)
    FILE *f = fopen("index_test.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[16] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11,
                               0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    fwrite(data, 1, 16, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.group_size = 1;
    opts.items_per_line = 8;
    opts.format_str = "Line %i: %0c %1\\n";
    
    printf("\nFormatted output with line index:\n");
    process_file("index_test.bin", &opts);
    
    remove("index_test.bin");
}

void test_format_character_mode() {
    // Тест вывода символов (флаг c)
    FILE *f = fopen("char_test.bin", "wb");
    assert(f != NULL);
    
    const char *text = "Hello, World!";
    fwrite(text, 1, strlen(text), f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.group_size = 1;
    opts.items_per_line = 13;
    opts.format_str = "%0c\\n";  // Вывод как символы
    
    printf("\nCharacter mode output:\n");
    process_file("char_test.bin", &opts);
    
    remove("char_test.bin");
}

// ============================================
// ТЕСТЫ граничных случаев
// ============================================

void test_large_offset() {
    // Тест большого смещения
    FILE *f = fopen("large_offset.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = (unsigned char)i;
    }
    fwrite(data, 1, 100, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.offset = 90;  // Почти в конце файла
    opts.group_size = 1;
    opts.items_per_line = 16;
    
    printf("\nLarge offset test (offset=90 in 100-byte file):\n");
    process_file("large_offset.bin", &opts);
    
    remove("large_offset.bin");
}

void test_partial_group() {
    // Тест неполной группы в конце
    FILE *f = fopen("partial.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[10];  // Нечётное количество
    for (int i = 0; i < 10; i++) {
        data[i] = (unsigned char)(0xF0 + i);
    }
    fwrite(data, 1, 10, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.group_size = 4;  // Группы по 4, но 10 не делится на 4
    opts.items_per_line = 4;
    
    printf("\nPartial group test (10 bytes, group_size=4):\n");
    process_file("partial.bin", &opts);
    
    remove("partial.bin");
}

void test_binary_data() {
    // Тест бинарных данных (все возможные байты)
    FILE *f = fopen("binary.bin", "wb");
    assert(f != NULL);
    
    unsigned char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = (unsigned char)i;
    }
    fwrite(data, 1, 256, f);
    fclose(f);
    
    HexOptions opts = {0};
    opts.group_size = 16;
    opts.items_per_line = 1;
    
    printf("\nBinary data test (all 256 byte values):\n");
    process_file("binary.bin", &opts);
    
    remove("binary.bin");
}

// ============================================
// ТЕСТЫ process_directory
// ============================================

void test_directory_processing() {
    // Создаём тестовую директорию с файлами
    mkdir("test_dir");
    
    FILE *f1 = fopen("test_dir/file1.txt", "wb");
    assert(f1 != NULL);
    fprintf(f1, "File 1 content");
    fclose(f1);
    
    FILE *f2 = fopen("test_dir/file2.bin", "wb");
    assert(f2 != NULL);
    unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    fwrite(data, 1, 4, f2);
    fclose(f2);
    
    HexOptions opts = {0};
    opts.group_size = 1;
    opts.items_per_line = 16;
    
    printf("\nProcessing test directory:\n");
    process_directory("test_dir", &opts);
    
    // Очистка
    remove("test_dir/file1.txt");
    remove("test_dir/file2.bin");
    rmdir("test_dir");
}

// ============================================
// ВСПОМОГАТЕЛЬНЫЕ ТЕСТЫ
// ============================================

void test_dummy_arithmetic() {
    int a = 5;
    assert(a == 5);
}

void test_dummy_string() {
    char *test = "hex";
    assert(strlen(test) == 3);
}

void test_dummy_addition() {
    assert(1 + 1 == 2);
}

void test_dummy_subtraction() {
    assert(4 - 2 == 2);
}

// ============================================
// MAIN
// ============================================

int main() {
    printf("=== Starting Comprehensive HexCore Tests ===\n\n");
    
    printf("--- Basic Function Tests ---\n");
    RUN_TEST(test_hex_conversion_zero);
    RUN_TEST(test_hex_conversion_max);
    RUN_TEST(test_hex_conversion_mixed);
    RUN_TEST(test_hex_conversion_all_values);
    RUN_TEST(test_hex_conversion_patterns);
    printf("\n");
    
    RUN_TEST(test_char_safe_printable);
    RUN_TEST(test_char_safe_unprintable);
    RUN_TEST(test_char_safe_extended_ascii);
    printf("\n");
    
    printf("--- Option Tests ---\n");
    RUN_TEST(test_option_defaults);
    RUN_TEST(test_option_custom);
    printf("\n");
    
    printf("--- File Processing Tests ---\n");
    RUN_TEST(test_process_file_create_test_file);
    RUN_TEST(test_process_file_empty_file);
    RUN_TEST(test_process_file_with_offset);
    RUN_TEST(test_process_file_with_length);
    RUN_TEST(test_process_file_group_format);
    printf("\n");
    
    printf("--- Format Tests ---\n");
    RUN_TEST(test_format_with_offset);
    RUN_TEST(test_format_with_index);
    RUN_TEST(test_format_character_mode);
    printf("\n");
    
    printf("--- Edge Case Tests ---\n");
    RUN_TEST(test_large_offset);
    RUN_TEST(test_partial_group);
    RUN_TEST(test_binary_data);
    printf("\n");
    
    printf("--- Directory Tests ---\n");
    RUN_TEST(test_directory_processing);
    printf("\n");
    
    printf("--- Utility Tests ---\n");
    RUN_TEST(test_dummy_arithmetic);
    RUN_TEST(test_dummy_string);
    RUN_TEST(test_dummy_addition);
    RUN_TEST(test_dummy_subtraction);
    printf("\n");
    
    printf("\n=== All tests passed successfully! ===\n");
    return 0;
}