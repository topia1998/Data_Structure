#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10000000
#define MAX_PATTERN 3000

int* fail;

void fail_func(char* tmp) {
	int i, j;
	int n = strlen(tmp);
	fail[0] = -1;
	for (j = 1; j < n; j++) {
		i = fail[j - 1];
		while ((tmp[j] != tmp[i + 1]) && (i >= 0)) i = fail[i]; 
		if (tmp[j] == tmp[i + 1]) fail[j] = i + 1;
		else {
			fail[j] = -1;
		}
	}
}

int main() {
	char *str = (char*)malloc(sizeof(char) * MAX_STRING);
	char *pat = (char*)malloc(sizeof(char) * MAX_PATTERN);
	FILE *fp_1 = fopen("string.txt", "r");
	FILE *fp_2 = fopen("pattern.txt", "r");
	FILE *fp_3 = fopen("result_kmp.txt", "wr");
	int len_str, len_pat;
	int i, j, x, num = 0; 
	int *result = (int*)malloc(sizeof(int));
	if (!fp_1) {
		printf("Error. Can't read string text file\n");
		return 0;
	}
	if (!fp_2) {
		printf("Error. Can't read pattern text file\n");
		return 0;
	}
	if (!fp_3) {
		printf("Error. Result file doesn't exist\n");
		return 0;
	}
	fgets(str, MAX_STRING, fp_1);
	fgets(pat, MAX_PATTERN, fp_2);
	len_str = strlen(str) - 1;
	len_pat = strlen(pat) - 1;
	fail = (int*)malloc(sizeof(int) * (len_pat + 1));
	fail_func(pat);
	for (i = 0, j = 0; i < len_str; i++) {
		while (str[i] != pat[j] && j > 0) {
			j = fail[j - 1] + 1;
		}
		if (str[i] == pat[j]) {
			j++;	
			if (j == len_pat) {
				num++;
				result = realloc(result, sizeof(int) * (num + 1));
				*(result + num - 1) = i - len_pat + 1;
			}
		}
	}
	fprintf(fp_3, "%d\n", num);
	for (x = 0; x < num; x++) {
		if (x == num - 1) fprintf(fp_3, "%d", *(result + x));
		else fprintf(fp_3, "%d ", *(result + x));
	}
	free(str);
	free(pat);
	fclose(fp_1);
	fclose(fp_2);
	fclose(fp_3);
	return 0;	
}
