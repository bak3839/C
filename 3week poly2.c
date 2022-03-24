#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	float coef;
	int expon;
} poly;

poly terms[MAX_TERMS] = { {0,0}, };

int avail = 0;

void print_poly(int s, int e){
	for (int i = s; i < e; i++)
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);

	if (terms[e].expon == 0) printf("%3.1f\n\n", terms[e].coef);
	else printf("%3.1fx^%d\n\n", terms[e].coef, terms[e].expon);
}

char compare(int a, int b){
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void attach(float coef, int expon){// avail�� ��ġ�� �� ����
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ������ �ʹ� ����\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++; // c���׽��� ������ġ
}

void poly_minus(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {

		case '>': // A�� ���� > B�� ����
			attach(terms[As].coef, terms[As].expon);
			As++; break;

		case '=': // A�� ���� == B�� ����
			tempcoef = terms[As].coef - terms[Bs].coef;

			if (tempcoef) // 0�� �ƴ� ��� �� ����
				attach(tempcoef, terms[As].expon);

			As++; Bs++; break;

		case '<': // A�� ���� < B�� ����
			attach(terms[Bs].coef*(-1), terms[Bs].expon);
			Bs++; break;
		}

	for (; As <= Ae; As++)// A�� ������ �׵��� �̵���
		attach(terms[As].coef, terms[As].expon);

	for (; Bs <= Be; Bs++)// B�� ������ �׵��� �̵���
		attach(terms[Bs].coef, terms[Bs].expon);

	*Ce = avail - 1; // �� ���׽��� �� ���׽��� ������ ���� ��ġ
}

void input(Ae, Be) {// ���׽��� ������ ��� �Է¹ޱ�
	for (int i = 0; i <= Ae; i++) {
		printf("\nA���� ����� ���� �Է�:");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}
	for (int i = Ae + 1; i <= Be; i++) {
		printf("\nB���� ����� ���� �Է�:");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}
}

float poly_eval(int s, int e,int x) {
	float result = 0;
	float n = 1; //x�� �ӽ� �����
	for (int i = s; i < e; i++) { //C�� �����ε������� �������ε��� ����
		for (int j = 0; j < terms[i].expon; j++) n *= x;

		result += (n * terms[i].coef);
		n = 1;
	}
	result += terms[e].coef;
	return result;
}
int main(void) {
	int As = 0;
	int Ae, Bs, Be, Cs, Ce;
	int x;
	printf("A�� ���� ����:");
	scanf("%d", &Ae);
	printf("B�� ���� ����:");
	scanf("%d", &Be);

	Ae -= 1; //A���׽ĳ� �ε��� ��
	Bs = Ae + 1; //B���׽��� �������� A���׽��� �� ����
	Be += Ae;
	avail = Be + 1; // ���� �� ���׽��� �����ϴ� ������ġ B���׽ĳ� ��������
	input(Ae, Be);

	poly_minus(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	print_poly(Cs, Ce);

	printf("\nX�� ���� �Է�:");
	scanf("%d", &x);
	printf("X=%d �϶� ���׽��� ��:%3.1f", x, poly_eval(Cs, Ce, x));
	return 0;
}