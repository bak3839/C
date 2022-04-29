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

void init_queue(QueueType* q) { // 큐 초기화
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) { // 큐가 비어있는지 확인
	return (q->front == q->rear);
}

int is_full(QueueType* q) { // 큐가 포화 상태인지 확인
	return ((q->rear + 1) % MAX == q->front);
}

void enqueue(QueueType* q, element item) { // 큐 삽입
	if (is_full(q))
		error("큐 포화");
	q->rear = (q->rear + 1) % MAX;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) { // 큐 삭제
	if (is_empty(q))
		error("큐 공백");
	q->front = (q->front + 1) % MAX;
	return q->data[q->front];
}

element peek(QueueType* q) { // 큐 확인
	if (is_empty(q))
		error("큐 공백");
	return q->data[(q->front + 1) % MAX];
}

int main(void) {
	QueueType q;
	init_queue(&q);

	int minute = 60;
	int wait = 0;
	int total_customer = 0;

	int service_t = 0;
	int service_customer; // 은행원 1가 처리

	int service_t2 = 0;
	int service_customer2; // 은행원 2가 처리

	srand(time(NULL));
	for (int clock = 0; clock < minute; clock++) {
		int rest_t = 0, rest_t2 = 0;
		printf("-----------------현재시각 = %d-----------------\n\n", clock);
		if ((rand() % 10) < 4) {
			element ct;
			ct.id = total_customer++;
			ct.arrival_t = clock;
			ct.service_t = (rand() % 3) + 1;
			enqueue(&q, ct);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리 시간 = %d분\n\n", ct.id, ct.arrival_t, ct.service_t);
		}

		if (service_t > 0) {
			printf("은행원 1이 고객 %d의 업무를 처리중입니다. \n\n", service_customer);
			service_t--;
			rest_t++; // 같은 시간 안에서 업무를 마치고 바로 업무 매칭을 막기위함
		}

		if (service_t2 > 0) {
			printf("은행원 2이 고객 %d의 업무를 처리중입니다. \n\n", service_customer2);
			service_t2--;
			rest_t2++; // 같은 시간 안에서 업무를 마치고 바로 업무 매칭을 막기위함
		}
		

		if((service_t == 0 || service_t2 == 0)) {
			if (!is_empty(&q)) {
				if (service_t == 0 && rest_t == 0) {
					element ct = dequeue(&q);
					service_customer = ct.id;
					service_t = ct.service_t;
					printf("은행원 1이 고객 %d의 업무 %d분에 시작합니다. 대기시간은 %d분 이었습니다.\n\n", ct.id, clock, clock - ct.arrival_t);
					wait += clock - ct.arrival_t;
				}
				else if (service_t2 == 0 && rest_t2 == 0) {
					element ct = dequeue(&q);
					service_customer2 = ct.id;
					service_t2 = ct.service_t;
					printf("은행원 2이 고객 %d의 업무 %d분에 시작합니다. 대기시간은 %d분 이었습니다.\n\n", ct.id, clock, clock - ct.arrival_t);
					wait += clock - ct.arrival_t;
				}
			}
		}
	}
	printf("전체 대기 시간 = %d\n\n", wait); 
	return 0;
}