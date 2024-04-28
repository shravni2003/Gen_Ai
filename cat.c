// Write programs to simulate linux commands cat, ls, cp, mv, head etc.
// Cat:

#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *file;
	char ch;

	if (argc < 2) {
    	printf("Usage: %s <filename1> [filename2] ...\n", argv[0]);
    	return 1;
	}

	for (int i = 1; i < argc; i++) {
    	file = fopen(argv[i], "r");
    	if (file == NULL) {
        	printf("Cannot open file: %s\n", argv[i]);
        	continue;
    	}

    	while ((ch = fgetc(file)) != EOF) {
        	putchar(ch);
    	}

    	fclose(file);
	}

	return 0;
}
