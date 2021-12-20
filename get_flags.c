#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char * strncat(char *restrict s1, const char *restrict s2, size_t n);
// int fprintf(FILE * restrict stream, const char * restrict format, ...);
// int strcmp(const char *s1, const char *s2);

#define SUPPORTED_CAP 5

char* supported[SUPPORTED_CAP] = {
  "cal",
  "hw",
  "du",
  "date"
};

char* matched[SUPPORTED_CAP];
size_t matched_sz = 0;

void dump_commands()
{
  for (size_t i = 0; i < SUPPORTED_CAP - 1; ++i)
    printf("\t%s\n", supported[i]);
}

void dump_help()
{
  printf("Supported commands:\n");
  dump_commands();
}

void dump_matched()
{
	for (size_t i = 0; i < matched_sz; i++) {
		printf("%s\n", matched[i]);
	}
}

void run_commands()
{
	if (matched_sz > 1) {
		for (size_t i = 0; i < matched_sz; i++) {
			fputs("----------------", stdout);
			system(matched[i]);
			fputs("\n", stdout);
		}
		return;
	}
	system(matched[0]);
}

int main(int argc, char** argv)
{

  if (argc < 2) {
    fprintf(stderr, "ERROR: no arguments supplied\n");
  }

  int exists;

  memset(matched, 0, sizeof(matched));

  for (size_t i = 1; i < argc; ++i) {
    char* curr_flag = argv[i];
    exists = 0;
   
    switch(*curr_flag) {
      case '-':
        curr_flag++; // move pointer to one char past hyphen
        for (size_t j = 0; j < SUPPORTED_CAP - 1; ++j) {
          if (!strcmp(curr_flag, supported[j])) {
						matched[matched_sz++] = supported[j];
						exists = 1;
          }
        }

				if (!exists) {
	  			fprintf(stderr, "ERROR: unsupported command: '%s'\n", curr_flag);
	  			dump_help();
	  			exit(1);
				}
      	break;
    }
  }

	run_commands();

  return 0;
}
