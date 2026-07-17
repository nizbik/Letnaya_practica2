/*
 * Главный модуль программы.
 * Основной исполняемый файл. Разбор аргументов командной строки.
 * Зубехин Никита
 * МК-101
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <hex_core.h>

int main(int argc, char *argv[]) {
    HexOptions opts = {
        .file_name = NULL,
        .dir_name = NULL,
        .offset = 0,
        .length = 0,
        .group_size = 1,
        .items_per_line = 16,
        .format_str = NULL,
        .has_length = false
    };

    int opt;
    // Разбор аргументов с помощью getopt 
    while ((opt = getopt(argc, argv, "i:o:l:g:n:d:f:")) != -1) {
        switch (opt) {
            case 'i': opts.file_name = optarg; break;
            case 'o': opts.offset = strtol(optarg, NULL, 10); break;
            case 'l': 
                opts.length = strtol(optarg, NULL, 10); 
                opts.has_length = true;
                break;
            case 'g': opts.group_size = atoi(optarg); break;
            case 'n': opts.items_per_line = atoi(optarg); break;
            case 'd': opts.dir_name = optarg; break;
            case 'f': opts.format_str = optarg; break;
            default:
                fprintf(stderr, "Usage: %s -i file [-o offset] [-l size] [-g group] [-n count] [-d dir] [-f format]\n", argv[0]);
                return 1;
        }
    }

    if (opts.dir_name) {
        process_directory(opts.dir_name, &opts);
    } else if (opts.file_name) {
        process_file(opts.file_name, &opts);
    } else {
        fprintf(stderr, "Error: Must specify input file (-i) or directory (-d).\n");
        return 1;
    }

    return 0;
}