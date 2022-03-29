#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

typedef struct {
	int row;
	int col;
	int value;
}element;

typedef struct sparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}sparseMatrix;

int a[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
			     { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int b[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	             { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 } };

int c[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				 { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 } };

void print_Matrix(sparseMatrix a) { // 0도 출력하는 희소행열 출력 함수
	int index = 0;
	int n = 0;
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (i == a.data[index].row && j == a.data[index].col) printf("%3d", a.data[index++].value); // a.data[index]에 있는 행열값이 i,j와 같으면 값출력
			else printf("%3d", n); // 아니면 0 출력
		}
		printf("\n");
	}
}

sparseMatrix add_Matrix(sparseMatrix a, sparseMatrix b) {
	sparseMatrix c;
	c.cols = a.cols;
	c.rows = a.rows;

	int aindex = 0;
	int bindex = 0;
	int cindex = 0;

	while (aindex < a.terms && bindex < b.terms) {
		if (a.data[aindex].row < b.data[bindex].row) c.data[cindex++] = a.data[aindex++]; // a행이 작으면

		else if(a.data[aindex].row > b.data[bindex].row) c.data[cindex++] = b.data[bindex++]; // b행이 작으면

		else { // 두 행이 같을때
			if(a.data[aindex].col < b.data[bindex].col) c.data[cindex++] = a.data[aindex++]; // a열이 작으면

			else if(a.data[aindex].col > b.data[bindex].col) c.data[cindex++] = b.data[bindex++];// b열이 작으면

			else {
				if ((a.data[aindex].value + b.data[bindex].value) == 0) { // 두합이 0이면 저장 안함
					aindex++; bindex++;
				}
				else { //두 합이 0이 아닐때
					c.data[cindex] = a.data[aindex++];
					c.data[cindex++].value += b.data[bindex++].value;
				}
			}
		}
	}
	
	//남은 자리 넣어주기
	for (int i = aindex; i < a.terms; i++) c.data[cindex++] = a.data[aindex++]; 
	for (int i = bindex; i < b.terms; i++) c.data[cindex++] = b.data[bindex++];
	c.terms = cindex;
	return c;
}

sparseMatrix change(int a[][10]) {
	sparseMatrix p;

	p.rows = 8; //행
	p.cols = 10; //열
	int term = 0; //값의 개수

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			if (a[i][j] != 0) { // a행열의 값이 0이 아니라면 행과 열 값을 p 구조체에 저장
				p.data[term].row = i;
				p.data[term].col = j;
				p.data[term++].value = a[i][j]; //term을 증가해서 다음 인덱스를 접근하고 값의 개수를 증가함
			}
		}
	}
	p.terms = term; //값의 개수를 넘겨줌
	return p;
}

int main(void) {
	sparseMatrix A;
	sparseMatrix B;
	sparseMatrix C;

	sparseMatrix AB;
	sparseMatrix AC;
	sparseMatrix BC;

	A = change(a);
	B = change(b);
	C = change(c);

	AB = add_Matrix(A, B);
	AC = add_Matrix(A, C);
	BC = add_Matrix(B, C);

	printf("\n-----------A+B의 값-----------\n\n");
	print_Matrix(AB);
	printf("\n-----------A+C의 값-----------\n\n");
	print_Matrix(AC);
	printf("\n-----------B+C의 값-----------\n\n");
	print_Matrix(BC);
	return 0;
}