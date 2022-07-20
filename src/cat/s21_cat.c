/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_cat.h"

int main(int argc, char **argv) {
    int errcode = OK;
    int optcode = OK;
    Options Opt;
    Opt.b = Opt.e = Opt.n = Opt.s = Opt.t = Opt.v = 0;

    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '-') {
            size_t arg_len = strlen(argv[i]);
            char *flag = argv[i] + 2;
            for (size_t j = 1; (j < arg_len) && optcode == OK && errcode != ERROR; ++j) {
                switch (argv[i][j]) {
                    case '-': {
                        if (strcmp(flag, "help") == 0) {
                            s21_print_file("dir/USAGE.txt", &Opt);
                            optcode = HELP;
                        } else if (strcmp(flag, "number") == 0) {
                            Opt.n = 1;
                            optcode = STOP;
                        } else if (strcmp(flag, "number-nonblank") == 0) {
                            Opt.b = 1;
                            optcode = STOP;
                        } else if (strcmp(flag, "squeeze-blank") == 0) {
                            Opt.s = 1;
                            optcode = STOP;
                        } else if (strcmp(flag, "show-nonprinting") == 0) {
                            Opt.v = 1;
                            optcode = STOP;
                        } else if (strcmp(flag, "show-ends") == 0) {
                            Opt.e = 1;
                            optcode = STOP;
                        } else if (strcmp(flag, "show-tabs") == 0) {
                            Opt.t = 1;
                            optcode = STOP;
                        } else if (strcmp(flag, "show-all") == 0) {
                            Opt.v = Opt.t = Opt.e = 1;
                            optcode = STOP;
                        } else {
                            printf("s21_cat: invalid option -- %s\n", flag);
                            puts("Try 's21_cat --help' for more information.");
                            errcode = ERROR;
                        }
                        break;
                    }
                    case 'n': Opt.n = 1;
                        break;
                    case 'b': Opt.b = 1;
                        break;
                    case 's': Opt.s = 1;
                        break;
                    case 'v': Opt.v = 1;
                        break;
                    case 'E': Opt.e = 1;
                        break;
                    case 'T': Opt.t = 1;
                        break;
                    case 'e': Opt.v = Opt.e = 1;
                        break;
                    case 't': Opt.v = Opt.t = 1;
                        break;
                    case 'A': Opt.v = Opt.t = Opt.e = 1;
                        break;
                    default: printf("s21_cat: invalid option -- %c\n", argv[i][j]);
                        puts("Try 's21_cat --help' for more information.");
                        errcode = ERROR;
                }
            }
            optcode = OK;
        }
    }

    for (int i = 1; (i < argc) && (errcode != ERROR); ++i)
        if (argv[i][0] != '-')
            errcode = s21_print_file(argv[i], &Opt);

    return (errcode);
}

/**
 * @brief Проверяет указатель file на конец файла или наличие ошибок
 * @param file
 * @return 0 - Конец файла или ошибка;
 *         Ненулевое значение - ОК.
 */
int s21_file_is_exist(FILE *file) {
    return !(feof(file) || ferror(file));
}

int s21_print_file(char *file_name, Options *Opt) {
    int errcode = OK;
    FILE *file = fopen(file_name, "r");

    if (NULL == file) {
        printf("s21_cat: No such file or directory'%s'\n", file_name);
    } else {
        int c = fgetc(file);
        int next_char = fgetc(file);
        unsigned int num_str = 0;

        if (Opt->n == 1 && Opt->b == 1)
            Opt->n = 0;

        if (Opt->n == 1 || (Opt->b == 1 && c != '\n'))
            printf("%6u\t", ++num_str);

        if (Opt->s == 1 && c == '\n' && next_char == '\n') {
            while (next_char == '\n') next_char = fgetc(file);
        }
        if (c == '\n') {
            if (Opt->e == 1) putchar('$');
            putchar('\n');
            c = next_char;
            if (Opt->n == 1 || (Opt->b == 1 && next_char != '\n'))
                printf("%6u\t", ++num_str);
        } else {
            fseek(file, -1, SEEK_CUR);
        }


        while (s21_file_is_exist(file) && errcode == OK) {
            if (c == '\n') {
                if (Opt->s == 1 || Opt->b == 1) {
                    next_char = fgetc(file);

                    if (s21_file_is_exist(file)) {
                        if (next_char == '\n') {
                            if (Opt->s == 1) {
                                if (Opt->e == 1) putchar('$');
                                putchar('\n');
                                while (next_char == '\n') {
                                    next_char = fgetc(file);
                                }
                                if (Opt->n == 1) printf("%6u\t", ++num_str);
                            }
                        }
                        if (Opt->b == 1 && next_char != '\n') {
                            if (Opt->e == 1) putchar('$');

                            putchar(c);
                            printf("%6u\t", ++num_str);
                            c = next_char;
                        } else {
                            fseek(file, -1, SEEK_CUR);
                        }
                    }
                }
                if (Opt->e == 1 && c == '\n') putchar('$');
            }
            if (Opt->t == 1 && c == '\t') {
                putchar('^');
                c += 64;
            }
            if (Opt->v == 1) {
                if ((0 <= c && c <= 8) || (11 <= c && c <= 31)) {
                    putchar('^');
                    c += 64;
                }
                if (c == 127) {
                    putchar('^');
                    c -= 64;
                }
            }

            putchar(c);

            if ((Opt->n == 1) && (c == '\n')) {
                fgetc(file);
                if (s21_file_is_exist(file))
                    printf("%6u\t", ++num_str);
                else
                    errcode = STOP;
                fseek(file, -1, SEEK_CUR);
            }

            c = fgetc(file);
        }
    }

    fclose(file);
    return (errcode);
}
