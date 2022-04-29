#include <stdio.h>
#include <Stdlib.h>
#define MAX 100

typedef char* element;

typedef struct {
	element data[MAX];
	int rear, front;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) { // ť �ʱ�ȭ
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) { // ť�� ����ִ��� Ȯ��
	return (q->front == q->rear);
}

int is_full(QueueType* q) { // ť�� ��ȭ �������� Ȯ��
	return ((q->rear + 1) % MAX == q->front);
}

void enqueue(QueueType* q, element item) { // ť ����
	if (is_full(q))
		error("ť ��ȭ");
	q->rear = (q->rear + 1) % MAX;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) { // ť ����
	if (is_empty(q))
		error("ť ����");
	q->front = (q->front + 1) % MAX;
	return q->data[q->front];
}

element peek(QueueType* q) { // ť Ȯ��
	if (is_empty(q))
		error("ť ����");
	return q->data[(q->front + 1) % MAX];
}

void matching(QueueType* boy, QueueType* girl) {
	if (is_empty(boy) || is_empty(girl)) {
		printf("-- ���\n");
	}
	else {
		element b = dequeue(boy);
		element g = dequeue(girl);
		printf("-- %s / %s ��Ī\n", b, g);
	}
}
int main(void) {
	QueueType boy;
	QueueType girl;

	init_queue(&boy);
	init_queue(&girl);

	int b_num = 0, g_num = 0;

	for (int i = 0; i < 15; i++) {
		int random = rand() % 2;
		element e;
		if (random == 1) { // ��
			printf("��%d ����", ++b_num);
			sprintf(&e, "��%d", b_num);
			enqueue(&boy, &e);
			matching(&boy, &girl);
		}
		else {
			printf("��%d ����", ++g_num);
			sprintf(&e, "��%d", g_num);
			enqueue(&girl, &e);
			matching(&boy, &girl);
		}
	}
	return 0;
}