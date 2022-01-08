#define MAX_ELEMENTS 1000001
#define MAX_LINE 30
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int key;
} element;

element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
element tmp1_heap[MAX_ELEMENTS];
element tmp2_heap[MAX_ELEMENTS];
element result_ascend[MAX_ELEMENTS];
element result_descend[MAX_ELEMENTS];

int size = 0;

void InsertMaxHeap(element item, int* size) {
	int i;
	if (HEAP_FULL(*size)) {
		printf("The heap is full.\n");
		exit(1);
	}
	i = ++(*size);
	while((i != 1) && (item.key > max_heap[i / 2].key)) {
		max_heap[i] = max_heap[i / 2];
		tmp1_heap[i] = tmp1_heap[i / 2];
		i /= 2;
	}
	max_heap[i] = item;
	tmp1_heap[i] = item;
}

void InsertMinHeap(element item, int* size) {
	int i;
	if (HEAP_FULL(*size)) {
		printf("The heap is full.\n");
		exit(1);
	}
	i = ++(*size);
	while ((i != 1) && (item.key < min_heap[i / 2].key)) {
		min_heap[i] = min_heap[i / 2];
		tmp2_heap[i] = tmp2_heap[i / 2];
		i /= 2;
	}
	min_heap[i] = item;
	tmp2_heap[i] = item;
}

void DeleteMaxHeap(int size) {
	int parent, child, tmp;
	tmp = size;
	element item, temp;
	if (HEAP_EMPTY(size)) {
		printf("The heap is empty.\n");
		exit(1);
	}
	for (int i = size; i > 0; i--) {
		item = tmp1_heap[1];
		temp = tmp1_heap[size];
		size -= 1;
		parent = 1;
		child = 2;
		while (child <= size) {
			if ((child < size) && (tmp1_heap[child].key < tmp1_heap[child + 1].key)) child++;
			if (temp.key >= tmp1_heap[child].key) break;
			tmp1_heap[parent] = tmp1_heap[child];
			parent = child;
			child *= 2;
		}
		tmp1_heap[parent] = temp;
		result_descend[tmp - i] = item;
	}
	for (int i = 0; i <= tmp; i++) {
		tmp1_heap[i] = max_heap[i];
	}
}

void DeleteMinHeap(int size) {
	int parent, child, tmp;
	tmp = size;
	element item, temp;
	if (HEAP_EMPTY(size)) {
		printf("The heap is empty.\n");
		exit(1);
	}
	for (int i = size; i > 0; i--) {
		item = tmp2_heap[1];
		temp = tmp2_heap[size];
		size -= 1;
		parent = 1;
		child = 2;
		while (child <= size) {
			if ((child < size) && (tmp2_heap[child].key > tmp2_heap[child + 1].key)) child++;
			if (temp.key <= tmp2_heap[child].key) break;
			tmp2_heap[parent] = tmp2_heap[child];
			parent = child;
			child *= 2;
		}
		tmp2_heap[parent] = temp;
		result_ascend[tmp - i] = item;
	}
	for (int i = 0; i <= tmp; i++) {
		tmp2_heap[i] = min_heap[i];
	}
}

int main(int argc, char* argv[]) {
	clock_t start, end;
	double result;
	char *cmd;
	char *line = (char*)malloc(sizeof(char) * MAX_LINE);
	int num, i;
	element input;
	start = clock();
	if (!argv[1] || argv[2]) {
		printf("usage: ./hw2 input_filename\n");
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");
	FILE *sp = fopen("hw2_result.txt", "w");
	if (!fp) {
		printf("The input file does not exist.\n");
		return 1;
	}
	while (fgets(line, MAX_LINE, fp)) {
		if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		cmd = strtok(line, " ");
		if (!strcmp(cmd, "INSERT"))	{ 
			char *cnum = strtok(NULL, " ");
			num = (int)strtol(cnum, NULL, 10);
			input.key = num;
			InsertMaxHeap(input, &size);
			size--;
			InsertMinHeap(input, &size);
		}
		int cnt = size;
		if (!strcmp(cmd, "DESCEND")) {
			DeleteMaxHeap(size);
			for (i = 0; i < size; i++) {
				if (i == size - 1) fprintf(sp, "%d", result_descend[i].key);
				else fprintf(sp, "%d ", result_descend[i].key);
			}
			fprintf(sp, "\n");
		}
		else if (!strcmp(cmd, "ASCEND")) {
			DeleteMinHeap(size);
			for (i = 0; i < size; i++) {
				if (i == size - 1) fprintf(sp, "%d", result_ascend[i].key);
				else fprintf(sp, "%d ", result_ascend[i].key);
			}
			fprintf(sp, "\n");
		}
	}
	end = clock();
	result = (double)(end - start) / CLOCKS_PER_SEC;
	printf("output written to hw2_result.txt\n");
	printf("running time: %f seconds\n", result);
	fclose(fp);
	fclose(sp);
	free(line);
	return 0;
}
