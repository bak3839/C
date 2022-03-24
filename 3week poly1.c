#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}poly;

poly poly_minus(poly A, poly B){ //���׽� ���� �Լ�
	poly C = { 0,{0,} }; // ��� ���׽�

	int Apos = 0, Bpos = 0, Cpos = 0; // �迭 �ε��� ����
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // ��� ���׽� ����

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A�� > B��
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}

		else if (degree_a == degree_b) {  // A�� == B��
			if (A.coef[Apos] - B.coef[Bpos] == 0 && C.coef[0] == 0) { //�ְ����� 0�ϋ� �������
				C.degree--; //�ְ����� ���̱�
				Apos++; Bpos++; // �� ���� ���� �Ѿ
				degree_a--; degree_b--;
			}
			else {//�ְ������� 0�� �ƴϸ�
				C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
				degree_a--; degree_b--;
			}
		}
		else { // B�� > A��
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

poly input(poly p) {
	printf("\n�ְ������� ������ �Է�:");
	scanf("%d", &p.degree);

	for (int i = 0; i <= p.degree; i++) {
		printf("\n%d������ ���:", p.degree - i);
		scanf("%f", &p.coef[i]);
	}
	return p;
}

void print_poly(poly p){
	for (int i = p.degree; i > 0; i--) {
		if (p.coef[p.degree - i] != 0)// ����� 0�� �ƴϸ� ���
			printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1f\n\n", p.coef[p.degree]);
}

float poly_eval(poly p, int x) {
	int sum = 1; //������ ����
	float result = p.coef[p.degree]; //����κ��� ����
	for (int i = p.degree - 1; i >= 0; i--) {
		sum *= x;
		result += p.coef[i] * sum;
	}
	return result;
}

int main(void) {
	poly a = { 0,{0,} };
	poly b = { 0,{0,} };
	poly c = { 0,{0,} };
	int x;
	a=input(a);
	b=input(b);
	print_poly(a);
	print_poly(b);
	c = poly_minus(a, b);
	print_poly(c);

	printf("\n\nX�� �� �Է�:");
	scanf("%d", &x);
	printf("\n\nX = %d �϶� ���׽��� ��:%3.1f", x, poly_eval(c, x));
	return 0;
}