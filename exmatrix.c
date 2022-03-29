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
	int rows;  //10��
	int cols;  //7��
	int terms; //6��
}sparseMatrix;

sparseMatrix trans_Matrix(sparseMatrix a) { //��ġ ��Ű�� �Լ�
	sparseMatrix t;

	int index = 0;
	int n = a.cols;
	int i = 0, j = 0;

	t.cols = a.rows;
	t.rows = a.cols;
	t.terms = a.terms;

	while (j < a.cols) { // j�� 0����
		for (i = 0; i < a.terms; i++) {
			if (a.data[i].col == j) { // j���� �ִ� ���� data[i]�� �� ���̶� ������
				t.data[index].row = a.data[i].col;
				t.data[index].col = a.data[i].row;
				t.data[index++].value = a.data[i].value;
			}
			if (j < a.data[i].col && a.data[i].col < n) n = a.data[i].col; // ���� ���� ���� �Ÿ��� ����
		}
		i = 0;
		j = n;
		n = a.cols;
	}
	return t;
}

void print_Matrix(sparseMatrix a) { // �� �� �� ���
	for (int i = 0; i < a.terms; i++)
		printf("{ %d,  %d,  %d }\n", a.data[i].row, a.data[i].col, a.data[i].value);
}

void print_Matrix2(sparseMatrix a) { // 0�� ����ϴ� ����࿭
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
	c.terms = a.terms + b.terms; // �Ѱ��� ���� ����
	
	int aindex = 0;
	int bindex = 0;
	int cindex = 0;

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[aindex].row == i && a.data[aindex].col == j) { //a�� �࿭�� ����
				if (b.data[bindex].row == i && b.data[bindex].col == j) { //b�� �࿭�� ������
					c.data[cindex] = a.data[aindex++]; //a�� b�� �࿭�� �����Ƿ� ������ ����
					c.data[cindex++].value += b.data[bindex++].value; //������ a�����ʹ� �Ѱ������� b value �� �����ش�
					c.terms--; //�� �ΰ��� ���������Ƿ� ���� ������ �ϳ� �پ��
					continue;
				}
				c.data[cindex++] = a.data[aindex++]; //a�� �࿭�� ������
			}

			else if (b.data[bindex].row == i && b.data[bindex].col == j) { //b�� �࿭�� ����
				if (a.data[aindex].row == i && a.data[bindex].col == j) { //a�� �࿭�� ������
					c.data[cindex] = a.data[aindex++]; //a�� b�� �࿭�� �����Ƿ� ������ ����
					c.data[cindex++].value += b.data[bindex++].value; //������ a�����ʹ� �Ѱ������� b value �� �����ش�
					c.terms--; //�� �ΰ��� ���������Ƿ� ���� ������ �ϳ� �پ��
					continue;
				}
				c.data[cindex++] = b.data[bindex++]; //b�� �࿭�� ������
			}
		}
	}
	return c;
}

int main(void) {
	sparseMatrix a = { //10�� 7�� ��6��
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