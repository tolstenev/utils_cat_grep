#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFF_SIZE 1024

typedef struct {
	char v;
	char i;
	char o;
	char l;
	char n;
	char c;
	char e;
	char f;
	char s;
	char h;
} Options;

enum error_codes {
	STOP = -1,
	OK = 0,
	NO_MATCHES_FOUND = 1,
	ERROR = 2,
};

enum option_codes {
	CLEAR = 0,
	SET = 1,
	HELP = 2,
};

int init_struct(Options *Opt, int symbol, char *pattern);

int main(int argc, char **argv) {

	int num_files = 0;

	int errcode = OK;
	Options Opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char *pattern = calloc(BUFF_SIZE, sizeof(char));

	if (NULL == pattern) errcode = STOP;

	if ((errcode == OK) && (argc > 2)) {
		int opt_symbol = 0;
		char *optstring = "violnce:f:sh?";

		while (-1 != (opt_symbol = getopt_long(argc, argv, optstring, 0, NULL))) {
			errcode = init_struct(&Opt, opt_symbol, pattern);

			if ((Opt.e || Opt.f) && (argc < 4)) errcode = ERROR;

			if (errcode == OK) {
				for (int i = optind; argv[i] != NULL; i++) {
					printf("optind = %d\n", optind);

					char a = argv[i][0];
					char b = argv[i - 1][0];
					char c = argv[i - 1][1];
					if (argv[i][0] != '-' ||
						(argv[i - 1][0] != '-' && argv[i - 1][1] != 'f')) {
							num_files = num_files + 1;

							printf("a = %c\n", a);
							printf("b = %c\n", b);
							printf("c = %c\n", c);
							printf("i am in\n");
							printf("num_files = %d\n", num_files);

					}
				}

			}
		}
	}

	if (NULL != pattern) free(pattern);

	return (errcode);
}

int init_struct(Options *Opt, int symbol, char *pattern) {
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
			errcode = ERROR;
	}
	return (errcode);
}
