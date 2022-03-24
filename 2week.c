#include <stdio.h>
#include <stdlib.h>

void pass(char* pw,int len) { //1�� �����Ǻ�
	int num1 = 0, num2 = 0, num3 = 0, num4 = 0;

	for (int i = 0; i < len; i++) {
		if ('A' <= pw[i] && pw[i] <= 'Z') ++num1; //�빮��
		else if ('a' <= pw[i] && pw[i] <= 'z') ++num2; //�ҹ���
		else if ('1' <= pw[i] && pw[i] <= '9') ++num3; //����
		else if (pw[i] == '!'|| pw[i] == '?' || pw[i] == '*' || pw[i] == '#' || pw[i] == '$') ++num4; //Ư������
	}

	if (len >= 10) printf("\n���̰� 10�̻� �Դϴ�.");
	else  printf("\n���̰� 10���� �Դϴ�.");

	if (num1 > 0 && num2 > 0 && num3 > 0 && num4 > 0)
		printf("\n��ҹ���, ����, Ư������(!,?,*,#,$)�� ���ԵǾ� �ֽ��ϴ�.");
	
	else 
		printf("\n��ҹ���, ����, Ư������(!,?,*,#,$)�� ���ԵǾ� ���� �ʽ��ϴ�.");
}

typedef struct complex { //2�� ���Ҽ� ����ü
	int a;
	int b;
}com;

int summaryA(com* arr, int num) { //�Ǽ��κ� ���
	if (num < 0) return 0;
	else {
		return arr[num].a + summaryA(arr, num - 1);
	}
}
int summaryB(com* arr, int num) { //����κ� ���
	if (num < 0) return 0;
	else {
		return arr[num].b + summaryB(arr, num - 1);
	}
}
int length(char* str) {//3�� ���� ���ϱ�
	
	if (*str != '\0') return 1 + length(++str);
	else return 0;
}

void search(int first, int last, int want, int* arr) { //4�� ����Ž��
	int mid = (first + last) / 2;
	if (first > last) return printf("\nã�� ���� �����ϴ�.");

	if (want == arr[mid]) {
		printf("\narr[%d]~arr[%d] arr[%d]�� ��ġ! ����Ž�� �Ϸ�:%d", first, last, mid, want);
	}

	else if (want < arr[mid]) {
		printf("\narr[%d]~arr[%d]���� �߾Ӱ� arr[%d]:%d ���� ����", first, last, mid, arr[mid]);
		return search(first, mid - 1, want, arr);
	}

	else if (want > arr[mid]) {
		printf("\narr[%d]~arr[%d]���� �߾Ӱ� arr[%d]:%d ���� ŭ", first, last, mid, arr[mid]);
		return search(mid + 1, last, want, arr);
	}
}

int main(void) {
	while (1) {
		int a;
		printf("\n\n������ �����Ͻÿ�\n0.����  1.���ڿ� �Ǻ�  2.���Ҽ���  3.���ڿ� ���̰��  4.����Ž��\n");
		scanf_s("%d", &a);

		switch (a) {

		case 0: {
			printf("���α׷� ����");
			return 0;
		}

		case 1: {// 1. ��ҹ���, ����, Ư������ �Ǻ��ϱ�
			printf("\n���ڸ� �Է��Ͻÿ�(20������):");
			char pw[21];
			scanf_s("%s", pw, sizeof(pw)); 
			int len = length(pw); //����3�� ���̱��ϴ� �Լ� Ȱ��
			pass(pw,len);
			break;
		}
		case 2: {//���Ҽ� ���
			com arr[5] = { {1,4},{3,5},{2,1},{4,4},{5,2} };// 1+4i, 3+5i, 2+1i, 4+4i, 5+2i �Ǽ�:15 ���:16
			printf("\n���Ҽ��� ��:%d+%di", summaryA(arr, 4), summaryB(arr, 4));
			break;
		}
		case 3: {//���ڿ� ����
			char str[31];
			printf("\n���ڿ��� �Է��Ͻÿ�(30������):");
			scanf_s("%s", str, sizeof(str));
			printf("\n���ڿ��� ����: %d", length(str));
			break;
		}
		case 4: {
			int num = 0;
			int want = 0;
			printf("\n�Է��� ������ ����:");
			scanf_s("%d", &num);
			int *arr = malloc(sizeof(int) * num);
			printf("\n���ڸ� �Է��Ͻÿ�:");
			for (int i = 0; i < num; i++)
				scanf_s("%d", &arr[i]);
		
			for (int i = 0; i < num; i++) { //�������� ����
				for (int j = i + 1; j < num; j++) {
					if (arr[i] > arr[j]) {
						int temp = arr[j];
						arr[j] = arr[i];
						arr[i] = temp;
					}
				}
			}

			printf("\nã����� ���� �Է��Ͻÿ�:");
			scanf_s("%d", &want);
			int first = 0;
			int last = num-1; // �Է��� ���� ����-1 == �迭 ������ �ε���
			search(first, last, want, arr);
			break;
		}
		}
	}
}