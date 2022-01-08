#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10000000
#define MAX_PATTERN 3000

int main() {
	char *str = (char*)malloc(sizeof(char) * MAX_STRING);
	char *pat = (char*)malloc(sizeof(char) * MAX_PATTERN);
	FILE *fp_1 = fopen("string.txt", "r");
	FILE *fp_2 = fopen("pattern.txt", "r");
	FILE *fp_3 = fopen("result_naive.txt", "wr");
	int len_str, len_pat;
	int i, j, num = 0;
	int *result = (int*)malloc(sizeof(int));;
	if (!fp_1) { // string.txt가 없거나 읽을 수 없을 때.
		printf("Error. Can't read string text file\n");
		return 0;
	}
	if (!fp_2) { // pattern.txt가 없거나 읽을 수 없을 때
		printf("Error. Can't read pattern text file\n");
		return 0;
	}
	fgets(str, MAX_STRING, fp_1);
	fgets(pat, MAX_PATTERN, fp_2);
	len_str = strlen(str) - 1;
	len_pat = strlen(pat) - 1;
	for (i = 0; i < len_str; i++) {
		for (j = 0; j < len_pat; j++) {
			if (str[i + j] != pat[j]) break;
		}
		if (j == len_pat) { //string 안에서 pattern을 찾았을 때
			num++;
			result = realloc(result, sizeof(int) * (num + 1));
			*(result + num - 1) = i;
		}
	}
	fprintf(fp_3, "%d\n", num);
	for (int k = 0; k < num; k++) {
		if (k == num - 1) fprintf(fp_3, "%d", *(result + k));
		else fprintf(fp_3, "%d ", *(result + k));
	}
	free(str);
	free(pat);
	free(result);
	fclose(fp_1);
	fclose(fp_2);
	fclose(fp_3);
	return 0;
}

