/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_cat.h"

int main(int argc, char **argv) {
    int errcode = OK;
    Options Opt = {0, 0, 0, 0, 0, 0};

	errcode = parser(argc, argv, errcode, &Opt);

    for (int i = 1; (i < argc) && (errcode == OK); ++i)
        if (argv[i][0] != '-')
            print_file(argv[i], &Opt);

    return (errcode);
}

int parser(int argc, char **argv, int errcode, Options *Opt) {
	int opt_long = CLEAR;

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			size_t arg_len = strlen(argv[i]);
			char *opt_phrase = argv[i] + 2;

			for (size_t j = 1; (j < arg_len) && opt_long == CLEAR && errcode == OK; ++j) {
				switch (argv[i][j]) {
					case '-':
						if (strcmp(opt_phrase, "help")                    == 0) {
							print_file("dir/USAGE.txt", Opt);
							errcode = STOP;
						} else if (strcmp(opt_phrase, "number")           == 0) { Opt->n = opt_long = SET;
						} else if (strcmp(opt_phrase, "number-nonblank")  == 0) { Opt->b = opt_long = SET;
						} else if (strcmp(opt_phrase, "squeeze-blank")    == 0) { Opt->s = opt_long = SET;
						} else if (strcmp(opt_phrase, "show-nonprinting") == 0) { Opt->v = opt_long = SET;
						} else if (strcmp(opt_phrase, "show-ends")        == 0) { Opt->e = opt_long = SET;
						} else if (strcmp(opt_phrase, "show-tabs")        == 0) { Opt->t = opt_long = SET;
						} else if (strcmp(opt_phrase, "show-all")         == 0) { Opt->v = Opt->t = Opt->e =
																				  opt_long = SET;
						} else {
							printf("s21_cat: unrecognized option --%s\n", opt_phrase);
							puts("Try './s21_cat --help' for more information.");
							errcode = ERROR;
						}                                   break;
					case 'n': Opt->n = SET;                  break;
					case 'b': Opt->b = SET;                  break;
					case 's': Opt->s = SET;                  break;
					case 'v': Opt->v = SET;                  break;
					case 'E': Opt->e = SET;                  break;
					case 'T': Opt->t = SET;                  break;
					case 'e': Opt->v = Opt->e = SET;          break;
					case 't': Opt->v = Opt->t = SET;          break;
					case 'A': Opt->v = Opt->t = Opt->e = SET;  break;
					default:
						printf("s21_cat: invalid option -- '%c'\n", argv[i][j]);
						puts("Try 's21_cat --help' for more information.");
						errcode = ERROR;
				}
			}
		}
	}

	return errcode;
}

int file_exist(FILE *file) {
    return !(feof(file) || ferror(file));
}

void print_file(char *file_name, Options *Opt) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("s21_cat: No such file or directory '%s'\n", file_name);
    } else {
        int c = fgetc(file);
        unsigned int num_str = 0;
		char position = IS_BEGIN;

//		b_handler();
//		n_handler();
		s_handler(file, &c, Opt, &num_str, position);

		position = IS_MID;
		do {
//			t_handler();
			s_handler(file, &c, Opt, &num_str, position);
//			e_handler();
			
			putchar(c);
			
//			b_handler();
//			n_handler();
			c = fgetc(file);
		} while (file_exist(file));
    }
	fclose(file);
}

void s_opt_handler(FILE *file, int *fut_c, int *c, Options *Opt, unsigned int *num_str, char *position) {
	if (*fut_c == '\n') {
		if (Opt->e) {
			printf("$");
		}
		while (*fut_c == '\n') {
			*fut_c = fgetc(file);
		}
		putchar('\n');
		if (*position == IS_BEGIN) {
			*c = *fut_c;
		}
		if (Opt->n || (Opt->b && *position == IS_BEGIN)) {
			printf("%6d\t", *(++num_str));
		}
	}
}

void s_handler(FILE *file, int *c, Options *Opt, unsigned int *num_str, char position) {
	if (Opt->s) {
		int fut_c = fgetc(file);
		if (position == IS_BEGIN) {
			if (*c != '\n') {
				fseek(file, -1, SEEK_CUR);
			}
			s_opt_handler(file, &fut_c, c, Opt, num_str, &position);
		} else if (position == IS_MID) {
			if (*c == '\n') {
				s_opt_handler(file, &fut_c, c, Opt, num_str, &position);
			}
			if (file_exist(file)) {
				fseek(file, -1, SEEK_CUR);
			}
		}
	}
}

