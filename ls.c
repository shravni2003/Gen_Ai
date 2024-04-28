//Ls:
// #include <stdio.h>
// #include <dirent.h>

// int main() {
// 	DIR *dir;
// 	struct dirent *entry;

// 	dir = opendir(".");
// 	if (dir == NULL) {
//     	perror("opendir");
//     	return 1;
// 	}

// 	while ((entry = readdir(dir)) != NULL) {
//     	printf("%s\n", entry->d_name);
// 	}

// 	closedir(dir);
// 	return 0;
// }

// cp
// #include <stdio.h>

// int main(int argc, char *argv[]) {
// 	FILE *src, *dest;
// 	char ch;

// 	if (argc != 3) {
//     	printf("Usage: %s <source> <destination>\n", argv[0]);
//     	return 1;
// 	}

// 	src = fopen(argv[1], "r");
// 	if (src == NULL) {
//     	perror("fopen");
//     	return 1;
// 	}

// 	dest = fopen(argv[2], "w");
// 	if (dest == NULL) {
//     	perror("fopen");
//     	fclose(src);
//     	return 1;
// 	}

// 	while ((ch = fgetc(src)) != EOF) {
//     	fputc(ch, dest);
// 	}

// 	fclose(src);
// 	fclose(dest);

// 	return 0;
// }

//Head
// #include <stdio.h>

// #define DEFAULT_LINES 10

// int main(int argc, char *argv[]) {
// 	FILE *file;
// 	char ch;
// 	int lines = DEFAULT_LINES;
// 	int count = 0;

// 	if (argc < 2) {
//     	printf("Usage: %s <filename> [lines]\n", argv[0]);
//     	return 1;
// 	}

// 	if (argc >= 3) {
//     	lines = atoi(argv[2]);
// 	}

// 	file = fopen(argv[1], "r");
// 	if (file == NULL) {
//     	perror("fopen");
//     	return 1;
// 	}

// 	while ((ch = fgetc(file)) != EOF && count < lines) {
//     	putchar(ch);
//     	if (ch == '\n') {
//         	count++;
//     	}
// 	}

// 	fclose(file);
// 	return 0;
// }


//MV
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    // Rename the file
    if (rename(argv[1], argv[2]) != 0) {
        perror("rename");
        return 1;
    }

    printf("File moved successfully.\n");

    return 0;
}
