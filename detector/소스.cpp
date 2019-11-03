#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

char* findNumber(int arr_size, int* arr, int k) {
	char *str = (char*)malloc(sizeof(char)*4);
	int i;

	for (i = 0; i < arr_size; i++)
		if (arr[i] == k) {
			strcpy(str, "YES");
			return str;
		}
	strcpy(str, "NO");
	return str;
}

int main() {
	char *output_path = getenv("OUTPUT_PATH");
	FILE *f;
	if (output_path != NULL) {
		f = fopen(output_path, "w");
	}
	else {
		f = stdout;
	}

	char* res;

	int _arr_size = 0;
	int _arr_i;
	scanf("%d\n", &_arr_size);
	int _arr[256];
	for (_arr_i = 0; _arr_i < _arr_size; _arr_i++) {
		int _arr_item;
		scanf("%d", &_arr_item);

		_arr[_arr_i] = _arr_item;
	}

	int _k;
	scanf("%d", &_k);

	res = findNumber(_arr_size, _arr, _k);
	fprintf(f, "%s\n", res);

	fclose(f);
	return 0;
}