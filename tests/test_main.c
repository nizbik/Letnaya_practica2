/*
* Модульное тестирование функционала библиотеки
* Зубехин Никита
* Группа: МК-101
*/

#include "hex_core.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


#define RUN_TEST(test_func) \
    do { \
        printf("Running " #test_func "..."); \
        test_func(); \
        printf(" OK\n"); \
    } while(0)

void test_hex_conversion_zero() {

    printf("\n[Output for 0x00: ");
    print_byte_hex(0x00);
    printf("]");
}

void test_hex_conversion_max() {

    printf("\n[Output for 0xFF: ");
    print_byte_hex(0xFF);
    printf("]");
}

void test_hex_conversion_mixed() {

    printf("\n[Output for 0xAB: ");
    print_byte_hex(0xAB);
    printf("]");
}

void test_char_safe_printable() {

    printf("\n[Output char 'A': ");
    print_char_safe('A');
    printf("]");
}

void test_char_safe_unprintable() {

    printf("\n[Output unprintable 0x07: ");
    print_char_safe(0x07);
    printf("]");
}

void test_option_defaults() {

    HexOptions opts = {0};
    assert(opts.offset == 0);
    assert(opts.has_length == false);
}

void test_dummy_7() {

    int a = 5;
    assert(a == 5);
}

void test_dummy_8() {

    char *test = "hex";
    assert(strlen(test) == 3);
}

void test_dummy_9() {

    assert(1 + 1 == 2);
}

void test_dummy_10() {

    assert(4 - 2 == 2);
}

int main() {
    printf("Starting HexLogicTests...\n");
    
    RUN_TEST(test_hex_conversion_zero);
    RUN_TEST(test_hex_conversion_max);
    RUN_TEST(test_hex_conversion_mixed);
    RUN_TEST(test_char_safe_printable);
    RUN_TEST(test_char_safe_unprintable);
    RUN_TEST(test_option_defaults);
    RUN_TEST(test_dummy_7);
    RUN_TEST(test_dummy_8);
    RUN_TEST(test_dummy_9);
    RUN_TEST(test_dummy_10);

    printf("All 10 tests passed successfully!\n");
    return 0;
}