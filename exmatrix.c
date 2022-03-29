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
	int rows;  //10행
	int cols;  //7열
	int terms; //6개
}sparseMatrix;

sparseMatrix trans_Matrix(sparseMatrix a) { //전치 시키는 함수
	sparseMatrix t;

	int index = 0;
	int n = a.cols;
	int i = 0, j = 0;

	t.cols = a.rows;
	t.rows = a.cols;
	t.terms = a.terms;

	while (j < a.cols) { // j는 0부터
		for (i = 0; i < a.terms; i++) {
			if (a.data[i].col == j) { // j열에 있는 값이 data[i]에 열 값이랑 같으면
				t.data[index].row = a.data[i].col;
				t.data[index].col = a.data[i].row;
				t.data[index++].value = a.data[i].value;
			}
			if (j < a.data[i].col && a.data[i].col < n) n = a.data[i].col; // 값이 없는 열을 거르기 위함
		}
		i = 0;
		j = n;
		n = a.cols;
	}
	return t;
}

void print_Matrix(sparseMatrix a) { // 행 열 값 출력
	for (int i = 0; i < a.terms; i++)
		printf("{ %d,  %d,  %d }\n", a.data[i].row, a.data[i].col, a.data[i].value);
}

void print_Matrix2(sparseMatrix a) { // 0도 출력하는 희소행열
	int index = 0;
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (i == a.data[index].row && j == a.data[index].col) printf("%d  ", a.data[index++].value);
			else printf("0  ");
		}
		printf("\n");
	}
}

sparseMatrix add_Matrix(sparseMatrix a, sparseMatrix b) {
	sparseMatrix c;
	c.cols = a.cols;
	c.rows = a.rows;
	c.terms = a.terms + b.terms; // 넘겨줄 값의 개수
	
	int aindex = 0;
	int bindex = 0;
	int cindex = 0;

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[aindex].row == i && a.data[aindex].col == j) { //a의 행열이 같고
				if (b.data[bindex].row == i && b.data[bindex].col == j) { //b의 행열도 같으면
					c.data[cindex] = a.data[aindex++]; //a와 b가 행열이 같으므로 데이터 이전
					c.data[cindex++].value += b.data[bindex++].value; //위에서 a데이터는 넘겨줬으니 b value 만 더해준다
					c.terms--; //값 두개가 합쳐졌으므로 값의 개수가 하나 줄어듬
					continue;
				}
				c.data[cindex++] = a.data[aindex++]; //a의 행열만 같으면
			}

			else if (b.data[bindex].row == i && b.data[bindex].col == j) { //b의 행열도 같고
				if (a.data[aindex].row == i && a.data[bindex].col == j) { //a의 행열이 같으면
					c.data[cindex] = a.data[aindex++]; //a와 b가 행열이 같으므로 데이터 이전
					c.data[cindex++].value += b.data[bindex++].value; //위에서 a데이터는 넘겨줬으니 b value 만 더해준다
					c.terms--; //값 두개가 합쳐졌으므로 값의 개수가 하나 줄어듬
					continue;
				}
				c.data[cindex++] = b.data[bindex++]; //b의 행열만 같으면
			}
		}
	}
	return c;
}

int main(void) {
	sparseMatrix a = { //10행 7열 값6개
		{ {2,4,2}, {4,0,6}, {5,2,1}, {6,3,7}, {8,5,5}, {9,2,3} }, //data
		10, //rows
		7,  //cols
		6   //terms 
	};

	sparseMatrix b = {
		{ {0,2,5}, {3,3,8}, {4,0,3}, {5,4,6}, {7,1,2}, {8,5,2} },
		10,
		7,
		6
	};

	sparseMatrix c;
	sparseMatrix d;
	sparseMatrix dt;

	c = trans_Matrix(a);

	print_Matrix(a);
	print_Matrix2(a);

	printf("\n\n");

	print_Matrix(c);
	print_Matrix2(c);
	printf("\n---------------\n");
	d = add_Matrix(a, b);

	printf("\n\n");

	print_Matrix(d);

	printf("\n\n");

	print_Matrix2(d);

	dt = trans_Matrix(d);
	printf("\n\n");
	print_Matrix2(dt);
	return 0;
}