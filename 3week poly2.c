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

void attach(float coef, int expon){// avail의 위치에 값 저장
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++; // c다항식의 다음위치
}

void poly_minus(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {

		case '>': // A의 차수 > B의 차수
			attach(terms[As].coef, terms[As].expon);
			As++; break;

		case '=': // A의 차수 == B의 차수
			tempcoef = terms[As].coef - terms[Bs].coef;

			if (tempcoef) // 0이 아닐 경우 값 저장
				attach(tempcoef, terms[As].expon);

			As++; Bs++; break;

		case '<': // A의 차수 < B의 차수
			attach(terms[Bs].coef*(-1), terms[Bs].expon);
			Bs++; break;
		}

	for (; As <= Ae; As++)// A의 나머지 항들을 이동함
		attach(terms[As].coef, terms[As].expon);

	for (; Bs <= Be; Bs++)// B의 나머지 항들을 이동함
		attach(terms[Bs].coef, terms[Bs].expon);

	*Ce = avail - 1; // 두 다항식을 뺀 다항식의 마지막 저장 위치
}

void input(Ae, Be) {// 다항식의 차수와 계수 입력받기
	for (int i = 0; i <= Ae; i++) {
		printf("\nA항의 계수와 차수 입력:");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}
	for (int i = Ae + 1; i <= Be; i++) {
		printf("\nB항의 계수와 차수 입력:");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}
}

float poly_eval(int s, int e,int x) {
	float result = 0;
	float n = 1; //x값 임시 저장용
	for (int i = s; i < e; i++) { //C의 시작인덱스부터 마지막인덱스 까지
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
	printf("A의 항의 개수:");
	scanf("%d", &Ae);
	printf("B의 항의 개수:");
	scanf("%d", &Be);

	Ae -= 1; //A다항식끝 인덱스 값
	Bs = Ae + 1; //B다항식의 시작점은 A다항식의 끝 다음
	Be += Ae;
	avail = Be + 1; // 빼기 한 다항식을 저장하는 시작위치 B다항식끝 다음부터
	input(Ae, Be);

	poly_minus(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	print_poly(Cs, Ce);

	printf("\nX의 값을 입력:");
	scanf("%d", &x);
	printf("X=%d 일때 다항식의 값:%3.1f", x, poly_eval(Cs, Ce, x));
	return 0;
}