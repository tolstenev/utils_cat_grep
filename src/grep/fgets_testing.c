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

int main(int argc, char **argv) {
	int errcode = OK;

	FILE *file_pattern;
	const char *file_name_pattern = argv[argc - 1];
	printf("%s\n", file_name_pattern);

	if (NULL == fopen(file_name_pattern, "r")) {
		printf("s21_grep: %s: No such file or directory\n", file_name_pattern);
		errcode = STOP;
	} else {
		printf("file was opened\n");

		char *buff_str_pattern = calloc(BUFF_SIZE, sizeof(char));

		if (NULL == buff_str_pattern) {
			printf("buff_str_pattern not allocated\n");
			errcode = STOP;
		} else {
			if (errcode == OK) {
				char sample[] = "texttexttext";

				buff_str_pattern = sample;

				printf("%s\n", buff_str_pattern);
				printf("%s\n", file_name_pattern);

				fgets(buff_str_pattern, BUFF_SIZE, file_pattern);

//				printf("%s\n", buff_str_pattern);


/*
			int n = 0;
			unsigned short c = 0;

			while (NULL != fgets(buff_str_pattern, BUFF_SIZE, file_pattern)) {
				n = strlen(buff_str_pattern);

				printf("\nc = %u\n", c);
				printf("s = %s\n", buff_str_pattern);

				if (buff_str_pattern[n] == '\n') {

				}
				n = 0;
			}
			}*/

			}



/*		if (NULL != buff_str_pattern) {
			free(buff_str_pattern);
			buff_str_pattern = NULL;
		}*/
		}

		fclose(file_pattern);
		return (errcode);
	}
}