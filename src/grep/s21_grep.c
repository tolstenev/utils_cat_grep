/**
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_grep.h"

void print_options(Options *Opt);
int init_struct (Options *Opt, int symbol, char *pattern);
void file_handler();
void flag_handler();

int main(int argc, char **argv) {
	int errcode = OK;
	Options Opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char *optstring = "violnce:f:sh?";
	int symbol = 0;
	char *pattern = calloc(BUFF_SIZE, sizeof(char));

	if (NULL == pattern)
		errcode = STOP;

	if (errcode == OK) {
		while ((symbol = getopt_long(argc, argv, optstring, 0, NULL)) != -1) {
			errcode = init_struct(&Opt, symbol, pattern);

// Отладочный вывод переменных

//			if (!errcode) {
//				printf("optind = %d\n", optind);
//				printf("file_name = %s\n", argv[optind]);
//				printf("optarg = %s\n", optarg);
//				printf("pattern = %s\n", pattern);
//			}

			FILE *file;
			char *file_name = argv[optind];

			if (NULL == (file = fopen(file_name, "r"))) {
				printf("s21_grep: %s: No such file or directory\n", file_name);
				errcode = STOP;
			} else {
				regex_t reg;

				regcomp(&reg, pattern, REG_EXTENDED);

				char buffer[BUFF_SIZE] = {0};
				while (fgets(buffer, BUFF_SIZE, file) != NULL) {
					if (regexec(&reg, buffer, 0, NULL, 0) == 0) {
						fputs(buffer, stdout);
					}
				}

				regfree(&reg);
			}
		}
	}

	free(pattern);
	return (errcode);
}

void init_e_pattern(char *pattern) {
	strcpy(pattern, optarg);
}

void flag_handler() {

}

void print_options(Options *Opt) {
	printf("Opt.v = %u\n", Opt->v);
	printf("Opt.i = %u\n", Opt->i);
	printf("Opt.o = %u\n", Opt->o);
	printf("Opt.l = %u\n", Opt->l);
	printf("Opt.n = %u\n", Opt->n);
	printf("Opt.c = %u\n", Opt->c);
	printf("Opt.e = %u\n", Opt->e);
	printf("Opt.f = %u\n", Opt->f);
	printf("Opt.s = %u\n", Opt->s);
	printf("Opt.h = %u\n", Opt->h);
}

int init_struct(Options *Opt, int symbol, char *pattern){
	int errcode = OK;

	switch (symbol) {
		case 'v':
			Opt->v = SET;
		break;
		case 'i':
			Opt->i = SET;
			break;
		case 'o':
			Opt->o = SET;
			break;
		case 'l':
			Opt->l = SET;
			break;
		case 'n':
			Opt->n = SET;
			break;
		case 'c':
			Opt->c = SET;
			break;
		case 'e':
			Opt->e = SET;
			init_e_pattern(pattern);
			break;
		case 'f':
			Opt->f = SET;
			break;
		case 's':
			Opt->s = SET;
			break;
		case 'h':
			Opt->h = SET;
			break;
		case '?':
// Закомментил default, потому что пока не корректно работает без обработки флага -е
//		default:
//			puts("s21_grep: unrecognized option");
			errcode = ERROR;
	}
	return (errcode);

}
