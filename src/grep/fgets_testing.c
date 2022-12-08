#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024

enum error_codes {
	STOP = -1,
	OK = 0,
	NO_MATCHES_FOUND = 1,
	ERROR = 2,
};

void init_pattern(char *pattern, const char *src) {
	if (!pattern[0]) {
		strcpy(pattern, src);
	} else {
		strcat(pattern, "|");
		strcat(pattern, src);
	}

	int n = strlen(pattern);

	if (pattern[n - 1] == '\n') {
		pattern[n - 1] = '\0';
	}
}

int main(int argc, char **argv) {
	int errcode = OK;

	char pattern[BUFF_SIZE] = {0};

	FILE *file_pattern;
	const char *file_name_pattern = argv[argc - 1];

	if ((file_pattern = fopen(file_name_pattern, "r")) == NULL) {
		printf("s21_grep: %s: No such file or directory\n", file_name_pattern);
		errcode = STOP;
	} else {

		char *buff_str_pattern = calloc(BUFF_SIZE, sizeof(char));

		if (NULL == buff_str_pattern) {
			printf("buff_str_pattern not allocated\n");
			errcode = STOP;
		} else {

			while (NULL != fgets(buff_str_pattern, BUFF_SIZE, file_pattern)) {

				//TODO: потестить сюда ещё strlen
				//TODO: ещё раз увидеть, что fgets возвращает строку с \n, даже если его нет в конце строки. он дописывает, \а если есть, то не трогает?\
				//TODO: прописать основные кейсы, что получаем в pattern file и ожидаемое поведение



				printf("%s", buff_str_pattern);
				init_pattern(pattern, buff_str_pattern);

			}

		}

		if (NULL != buff_str_pattern) {
			free(buff_str_pattern);
			buff_str_pattern = NULL;
		}
	}

	printf("pattern = %s\n", pattern);

	fclose(file_pattern);
	return (errcode);
}


/*

char a[] = "123"; //    3
char b[] = "123\n"; //  4
char c[] = "123\0"; //  3
char d[] = "\n"; //     1
char e[] = "\0"; //     0

printf("a 123 = %lu\n", strlen(a));
printf("b 123\\n = %lu\n", strlen(b));
printf("c 123\\0 = %lu\n", strlen(c));
printf("d \\n = %lu\n", strlen(d));
printf("e \\0 = %lu\n", strlen(e));*/
