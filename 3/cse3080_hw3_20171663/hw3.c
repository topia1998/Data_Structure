#define MAX_LINE 100
#define MAX_INPUT 50000001
#define MAX_VERTEX 10000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { 
	int v1;
	int v2;
	int weight;
} Tree;

typedef struct {
	int key;
} element;

FILE *sp;
Tree min_heap[MAX_INPUT];
int size = 0, sum = 0, vertex, edge;
int parent[MAX_VERTEX];

void init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}
	
int find(int i) {
	for(; parent[i] >= 0; i = parent[i]);
	return i;
}

void _union(int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

void InsertMinHeap(Tree heap, int *size) {
	int i;
	i = ++(*size);
	while ((i != 1) && (heap.weight < min_heap[i / 2].weight)) {
		min_heap[i] = min_heap[i / 2];
		i /= 2;
	}
	min_heap[i] = heap;
}

Tree DeleteMinHeap(int size) {
	int parent, child, tmp;
	Tree item, temp;
	item = min_heap[1];
	temp = min_heap[size--];
	parent = 1;
	child = 2;
	while (child <= size) {
		if ((child < size) && (min_heap[child].weight > min_heap[child + 1].weight)) child++;
		if (temp.weight <= min_heap[child].weight) break;
		min_heap[parent] = min_heap[child];
		parent = child;
		child *= 2;
	}
	min_heap[parent] = temp;
	return item;
}

void Kruskal(int n) {
	int cnt = 0;
	int tmp = edge, u, v;
	Tree new;
	while (cnt < (n - 1)) {
		new = DeleteMinHeap(tmp--);
		u = find(new.v1);
		v = find(new.v2);
		if (u != v) {	
			fprintf(sp, "%d %d %d\n", new.v1, new.v2, new.weight);
			sum += new.weight;
			cnt++;
			_union(u, v);
		}
		if (cnt == vertex - 1) break;
		if (tmp == 0) break;
	}
	fprintf(sp, "%d\n", sum);
	if (cnt == vertex - 1) fprintf(sp, "CONNECTED\n");
	else fprintf(sp, "DISCONNECTED\n");
}
	

int main(int argc, char* argv[]) {
	clock_t start, end;
	double result;
	start = clock();
	Tree min;
	FILE *fp = fopen(argv[1], "r");
	sp = fopen("hw3_result.txt","w");
	if (!argv[1] || argv[2]) {
		printf("usage:./hw3 input_filename\n");
		return 1;
	}
	if (!fp) {
		printf("The input file does not exist.\n");
		return 1;
	}
	int cnt = 1;
	char *line = (char*)malloc(sizeof(char) * MAX_LINE);
	fscanf(fp, "%d%d", &vertex, &edge);
	init(vertex);
	while (1) {
		fscanf(fp, "%d %d %d", &min.v1, &min.v2, &min.weight);
		InsertMinHeap(min, &size);
		if (cnt++ == edge) break;
	}
	Kruskal(vertex);
	end = clock();
	result = (double)(end - start) / CLOCKS_PER_SEC;
	printf("output written to hw3_result.txt.\n");
	printf("running time: %lf seconds\n", result);
	fclose(fp);
	fclose(sp);
	return 0;
}
