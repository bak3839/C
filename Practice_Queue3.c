#include <stdio.h>
#include <Stdlib.h>
#define MAX 100

typedef int element;

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

int main(void) {
	QueueType f;
	init_queue(&f);

	enqueue(&f, 0);
	enqueue(&f, 1);

	int n;
	printf("�Ǻ���ġ ���� �Է�:");
	scanf("%d", &n);

	for (int i = 2; i < n; i++) {
		int sum = dequeue(&f) + peek(&f);
		enqueue(&f, sum);
	}
	printf("%d��° ��:%d", n, dequeue(&f) + dequeue(&f));
	return 0;
}