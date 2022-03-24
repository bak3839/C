#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}poly;

poly poly_minus(poly A, poly B){ //다항식 빼기 함수
	poly C = { 0,{0,} }; // 결과 다항식

	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A항 > B항
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}

		else if (degree_a == degree_b) {  // A항 == B항
			if (A.coef[Apos] - B.coef[Bpos] == 0 && C.coef[0] == 0) { //최고차항 0일떄 저장안함
				C.degree--; //최고차수 줄이기
				Apos++; Bpos++; // 값 저장 없이 넘어감
				degree_a--; degree_b--;
			}
			else {//최고차항이 0이 아니면
				C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
				degree_a--; degree_b--;
			}
		}
		else { // B항 > A항
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

poly input(poly p) {
	printf("\n최고차항의 차수를 입력:");
	scanf("%d", &p.degree);

	for (int i = 0; i <= p.degree; i++) {
		printf("\n%d차수의 계수:", p.degree - i);
		scanf("%f", &p.coef[i]);
	}
	return p;
}

void print_poly(poly p){
	for (int i = p.degree; i > 0; i--) {
		if (p.coef[p.degree - i] != 0)// 계수가 0이 아니면 출력
			printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1f\n\n", p.coef[p.degree]);
}

float poly_eval(poly p, int x) {
	int sum = 1; //제곱을 저장
	float result = p.coef[p.degree]; //상수부분은 저장
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

	printf("\n\nX의 값 입력:");
	scanf("%d", &x);
	printf("\n\nX = %d 일때 다항식의 값:%3.1f", x, poly_eval(c, x));
	return 0;
}