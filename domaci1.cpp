#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

int unos(int* nadr) {
	scanf("%d", nadr);
	if (*nadr <= 0) return 1;
	else return 0;
}

int **unos_matrice(int n) {
	int **p;
	p = (int**) calloc(n*n, sizeof(int));
	if (p == NULL) {
		printf("MEM_GRESKA");
		return NULL;
	}
	for (int i = 0; i < n*n; i++) {
		*(p + i) = (int*) calloc(n*n, sizeof(int*));
		if (*(p + i) == NULL) {
			printf("MEM_GRESKA");
			return NULL;
		}
		for (int j = 0; j < n*n; j++) {
			scanf("%d", &p[i][j]);
		}
	}
	return p;
}

int provera_opsega(int** p, int n) {
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++)
			if (p[i][j]<1 || p[i][j]>n * n) {
				printf("LOS OPSEG");
				return 1;
			}
	}
	return 0;
}

void ispis_matrice(int** p, int n) {
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

int provera_kolona(int** p, int n) {
	int* temp1;
	for (int i = 0; i < n * n; i++) {
		temp1 = (int*) calloc(n * n + 1, sizeof(int));
		if (temp1 == NULL) {
			printf("MEM_GRESKA");
			return -1;
		}
		for (int j = 0; j < n * n; j++) {
			temp1[p[j][i]]++;
		}
		int t1 = 0;
		for (int k = 1; k <= n * n; k++) {
			if (temp1[k] > 1)
				t1 = 1;
			if (t1) break;
		}
		free(temp1);
		if (t1) return 1;
	}
	return 0;
}

int provera_redova(int** p, int n) {
	int* temp2;
	for (int i = 0; i < n * n; i++) {
		temp2 = (int*) calloc(n * n + 1, sizeof(int));
		if (temp2 == NULL) {
			printf("MEM_GRESKA");
			return -1;
		}
		for (int j = 0; j < n * n; j++) {
			temp2[p[i][j]]++;
		}
		int t2 = 0;
		for (int k = 1; k <= n * n; k++) {
			if (temp2[k] > 1)
				t2 = 1;
			if (t2) break;
		}
		free(temp2);
		if (t2) return 1;
	}
	return 0;
}

int provera_regiona(int** p, int n) {
	int* temp3;
	for (int s = 0; s < n*n; s += n) {
		for (int r = 0; r < n * n; r += n) {
			temp3 = (int*)calloc(n * n + 1, sizeof(int));
			if (temp3 == NULL) {
				printf("MEM_GRESKA");
				return -1;
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					temp3[p[s + i][r + j]]++;
				}
			}
			int t3 = 0;
			for (int k = 1; k <= n * n; k++) {
				if (temp3[k] > 1)
					t3 = 1;
				if (t3) break;
			}
			free(temp3);
			if (t3) return 1;
		}
	}
	return 0;
}

void provera(int** p, int n) {
	int p1 = provera_kolona(p, n);
	int p2 = provera_redova(p, n);
	int p3 = provera_regiona(p, n);
	if (p1 < 0 || p2 < 0 || p3 < 0) {
		printf("MEM_GRESKA");
		return;
	}
	if (p1) printf("LOSE KOLONE");
	if (p1 && p2) printf("\n");
	if (p2) printf("LOSI REDOVI");
	if ((p1 && p3) || (p2 && p3)) printf("\n");
	if (p3) printf("LOSI REGIONI");
	if (p1 + p2 + p3 == 0) printf("VALIDNO RESENJE");
}

int main () {
	int n;
	if (unos(&n)) return 0;
	int **mat;
	mat = unos_matrice(n);
	if (mat == NULL) {
		printf("MEM_GRESKA");
		return 0;
	}
	if (provera_opsega(mat, n)) {
		for (int i = 0; i < n*n; i++) {
			free(*(mat+i));
		}
		free(mat);
		return 0;
	}
	ispis_matrice(mat, n);
	provera(mat, n);
	for (int i = 0; i < n * n; i++) {
		free(*(mat + i));
	}
	free(mat);
	return 0;
}