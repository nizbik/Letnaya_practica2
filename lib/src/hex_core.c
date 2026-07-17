/*
Главный модуль программы.
Реализация логики чтения, ручного перевода в hex и кастомного форматирования.
Зубехин Никита
МК-101
*/
#include "hex_core.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
void print_byte_hex(unsigned char byte) {
const char hex_chars[] = "0123456789ABCDEF";
printf("%c%c", hex_chars[(byte >> 4) & 0x0F], hex_chars[byte & 0x0F]);
}
void print_char_safe(unsigned char byte) {
if (isprint(byte)) {
printf("%c", byte);
} else {
printf(".");
}
}
static void print_piece(const unsigned char *data, int piece_size, bool as_char) {
if (as_char) {
for (int i = 0; i < piece_size; i++) {
print_char_safe(data[i]);
}
} else {
    for (int i = piece_size - 1; i >= 0; i--) {
        print_byte_hex(data[i]);
    }
}
}
static void print_formatted_line(const HexOptions *opts, int line_idx, long line_offset, const unsigned char *buffer, int bytes_read) {
if (!opts->format_str) {
printf("%08lx  ", line_offset);

int group_size = opts->group_size;
if (group_size <= 0) group_size = 1;


for (int i = 0; i < bytes_read; i += group_size) {

int end = (i + group_size <= bytes_read) ? i + group_size : bytes_read;


for (int j = end - 1; j >= i; j--) {
print_byte_hex(buffer[j]);
}

printf(" ");  
}

printf("\n");
return;
}
const char *f = opts->format_str;
 while (*f) {
     if (*f == '\\') {
         f++;
         switch (*f) {
             case 'n': printf("\n"); break;
             case 'r': printf("\r"); break;
             case 't': printf("\t"); break;
             case '\\': printf("\\"); break;
             default: printf("\\%c", *f); break;
         }
     } else if (*f == '%') {
         f++;
         if (*f == 'i') {
             printf("%d", line_idx);
         } else if (*f == 'n') {
             printf("%08lx", line_offset); 
         } else if (isdigit(*f)) {
             int piece_idx = 0;
             while (isdigit(*f)) {
                 piece_idx = piece_idx * 10 + (*f - '0');
                 f++;
             }
             bool is_char = (*f == 'c');
             int byte_offset = piece_idx * opts->group_size;
             int piece_actual_size = opts->group_size;
             if (byte_offset < bytes_read) {
                 if (byte_offset + piece_actual_size > bytes_read) {
                     piece_actual_size = bytes_read - byte_offset;
                 }
                 print_piece(&buffer[byte_offset], piece_actual_size, is_char);
             }
         } else {
             printf("%%%c", *f);
         }
     } else {
         printf("%c", *f);
     }
     f++;
 }
}
void process_file(const char *filepath, const HexOptions *opts) {
FILE *file = fopen(filepath, "rb");
if (!file) {
perror("Error opening file");
return;
}
if (opts->offset > 0) {
     fseek(file, opts->offset, SEEK_SET);
 }
 int bytes_per_line = opts->group_size * opts->items_per_line;
 unsigned char *buffer = (unsigned char *)malloc(bytes_per_line);
 long total_read = 0;
 int line_index = 0;
 long current_offset = opts->offset;
 while (1) {
     int to_read = bytes_per_line;
     if (opts->has_length && (total_read + bytes_per_line > opts->length)) {
         to_read = opts->length - total_read;
     }
     if (to_read <= 0) break;
     size_t bytes_read = fread(buffer, 1, to_read, file);
     if (bytes_read == 0) break;
     print_formatted_line(opts, line_index, current_offset, buffer, bytes_read);
     total_read += bytes_read;
     current_offset += bytes_read;
     line_index++;
     if (bytes_read < (size_t)to_read) break;
 }
 free(buffer);
 fclose(file);
}
void process_directory(const char *dirpath, const HexOptions *opts) {
WIN32_FIND_DATA find_file_data;
char search_path[1024];
snprintf(search_path, sizeof(search_path), "%s\\*", dirpath);
 HANDLE hFind = FindFirstFileA(search_path, &find_file_data);
 if (hFind == INVALID_HANDLE_VALUE) {
     printf("Error: Directory not found or cannot be opened (%s)\n", dirpath);
     return;
 }
 do {
     if (strcmp(find_file_data.cFileName, ".") != 0 && strcmp(find_file_data.cFileName, "..") != 0) {
         if (!(find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
             char filepath[1024];
             snprintf(filepath, sizeof(filepath), "%s\\%s", dirpath, find_file_data.cFileName);
             printf("=== File: %s ===\n", filepath);
             process_file(filepath, opts);
         }
     }
 } while (FindNextFileA(hFind, &find_file_data) != 0);
 FindClose(hFind);
}