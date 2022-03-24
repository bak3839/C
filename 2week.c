#include <stdio.h>
#include <stdlib.h>

void pass(char* pw,int len) { //1번 문자판별
	int num1 = 0, num2 = 0, num3 = 0, num4 = 0;

	for (int i = 0; i < len; i++) {
		if ('A' <= pw[i] && pw[i] <= 'Z') ++num1; //대문자
		else if ('a' <= pw[i] && pw[i] <= 'z') ++num2; //소문자
		else if ('1' <= pw[i] && pw[i] <= '9') ++num3; //숫자
		else if (pw[i] == '!'|| pw[i] == '?' || pw[i] == '*' || pw[i] == '#' || pw[i] == '$') ++num4; //특수문자
	}

	if (len >= 10) printf("\n길이가 10이상 입니다.");
	else  printf("\n길이가 10이하 입니다.");

	if (num1 > 0 && num2 > 0 && num3 > 0 && num4 > 0)
		printf("\n대소문자, 숫자, 특수문자(!,?,*,#,$)가 포함되어 있습니다.");
	
	else 
		printf("\n대소문자, 숫자, 특수문자(!,?,*,#,$)가 포함되어 있지 않습니다.");
}

typedef struct complex { //2번 복소수 구조체
	int a;
	int b;
}com;

int summaryA(com* arr, int num) { //실수부분 계산
	if (num < 0) return 0;
	else {
		return arr[num].a + summaryA(arr, num - 1);
	}
}
int summaryB(com* arr, int num) { //허수부분 계산
	if (num < 0) return 0;
	else {
		return arr[num].b + summaryB(arr, num - 1);
	}
}
int length(char* str) {//3번 길이 구하기
	
	if (*str != '\0') return 1 + length(++str);
	else return 0;
}

void search(int first, int last, int want, int* arr) { //4번 이진탐색
	int mid = (first + last) / 2;
	if (first > last) return printf("\n찾는 값이 없습니다.");

	if (want == arr[mid]) {
		printf("\narr[%d]~arr[%d] arr[%d]에 위치! 이진탐색 완료:%d", first, last, mid, want);
	}

	else if (want < arr[mid]) {
		printf("\narr[%d]~arr[%d]사이 중앙값 arr[%d]:%d 보다 작음", first, last, mid, arr[mid]);
		return search(first, mid - 1, want, arr);
	}

	else if (want > arr[mid]) {
		printf("\narr[%d]~arr[%d]사이 중앙값 arr[%d]:%d 보다 큼", first, last, mid, arr[mid]);
		return search(mid + 1, last, want, arr);
	}
}

int main(void) {
	while (1) {
		int a;
		printf("\n\n문제를 선택하시오\n0.종료  1.문자열 판별  2.복소수합  3.문자열 길이계산  4.이진탐색\n");
		scanf_s("%d", &a);

		switch (a) {

		case 0: {
			printf("프로그램 종료");
			return 0;
		}

		case 1: {// 1. 대소문자, 숫자, 특수문자 판별하기
			printf("\n문자를 입력하시오(20자이하):");
			char pw[21];
			scanf_s("%s", pw, sizeof(pw)); 
			int len = length(pw); //문제3번 길이구하는 함수 활용
			pass(pw,len);
			break;
		}
		case 2: {//복소수 계산
			com arr[5] = { {1,4},{3,5},{2,1},{4,4},{5,2} };// 1+4i, 3+5i, 2+1i, 4+4i, 5+2i 실수:15 허수:16
			printf("\n복소수의 합:%d+%di", summaryA(arr, 4), summaryB(arr, 4));
			break;
		}
		case 3: {//문자열 길이
			char str[31];
			printf("\n문자열을 입력하시오(30자이하):");
			scanf_s("%s", str, sizeof(str));
			printf("\n문자열의 길이: %d", length(str));
			break;
		}
		case 4: {
			int num = 0;
			int want = 0;
			printf("\n입력할 숫자의 개수:");
			scanf_s("%d", &num);
			int *arr = malloc(sizeof(int) * num);
			printf("\n문자를 입력하시오:");
			for (int i = 0; i < num; i++)
				scanf_s("%d", &arr[i]);
		
			for (int i = 0; i < num; i++) { //오름차수 정렬
				for (int j = i + 1; j < num; j++) {
					if (arr[i] > arr[j]) {
						int temp = arr[j];
						arr[j] = arr[i];
						arr[i] = temp;
					}
				}
			}

			printf("\n찾고싶은 수를 입력하시오:");
			scanf_s("%d", &want);
			int first = 0;
			int last = num-1; // 입력할 수의 개수-1 == 배열 마지막 인덱스
			search(first, last, want, arr);
			break;
		}
		}
	}
}