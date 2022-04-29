#include <stdio.h>
#include <Stdlib.h>
#define MAX 100

typedef struct {
	int id;
	int arrival_t;
	int service_t;
}element;

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
	QueueType q;
	init_queue(&q);

	int minute = 60;
	int wait = 0;
	int total_customer = 0;

	int service_t = 0;
	int service_customer; // ����� 1�� ó��

	int service_t2 = 0;
	int service_customer2; // ����� 2�� ó��

	srand(time(NULL));
	for (int clock = 0; clock < minute; clock++) {
		int rest_t = 0, rest_t2 = 0;
		printf("-----------------����ð� = %d-----------------\n\n", clock);
		if ((rand() % 10) < 4) {
			element ct;
			ct.id = total_customer++;
			ct.arrival_t = clock;
			ct.service_t = (rand() % 3) + 1;
			enqueue(&q, ct);
			printf("�� %d�� %d�п� ���ɴϴ�. ����ó�� �ð� = %d��\n\n", ct.id, ct.arrival_t, ct.service_t);
		}

		if (service_t > 0) {
			printf("����� 1�� �� %d�� ������ ó�����Դϴ�. \n\n", service_customer);
			service_t--;
			rest_t++; // ���� �ð� �ȿ��� ������ ��ġ�� �ٷ� ���� ��Ī�� ��������
		}

		if (service_t2 > 0) {
			printf("����� 2�� �� %d�� ������ ó�����Դϴ�. \n\n", service_customer2);
			service_t2--;
			rest_t2++; // ���� �ð� �ȿ��� ������ ��ġ�� �ٷ� ���� ��Ī�� ��������
		}
		

		if((service_t == 0 || service_t2 == 0)) {
			if (!is_empty(&q)) {
				if (service_t == 0 && rest_t == 0) {
					element ct = dequeue(&q);
					service_customer = ct.id;
					service_t = ct.service_t;
					printf("����� 1�� �� %d�� ���� %d�п� �����մϴ�. ���ð��� %d�� �̾����ϴ�.\n\n", ct.id, clock, clock - ct.arrival_t);
					wait += clock - ct.arrival_t;
				}
				else if (service_t2 == 0 && rest_t2 == 0) {
					element ct = dequeue(&q);
					service_customer2 = ct.id;
					service_t2 = ct.service_t;
					printf("����� 2�� �� %d�� ���� %d�п� �����մϴ�. ���ð��� %d�� �̾����ϴ�.\n\n", ct.id, clock, clock - ct.arrival_t);
					wait += clock - ct.arrival_t;
				}
			}
		}
	}
	printf("��ü ��� �ð� = %d\n\n", wait); 
	return 0;
}