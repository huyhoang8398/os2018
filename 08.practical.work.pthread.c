#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define  BUFFER_SIZE 10	

typedef struct {
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
	
void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
	// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item* consume() {
	item *i = (item*)malloc(sizeof(item));
	while (first == last) {
	// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}
//Produce Thread
void *produceThread(){	
	item iT[3];
	iT[0].type = '0';
	iT[0].amount = 3;
	iT[0].unit = '1';

	iT[1].type = '1';
	iT[1].amount = 2;
	iT[1].unit = '1';

	iT[2].type = '1';
	iT[2].amount = 2;
	iT[2].unit = '1';
	for (int i = 0; i < 3; ++i)
	{
		/* code */	
		produce(&iT[i]);
		printf("\nItem %d: %c, %d, %c\nfirst = %d, last = %d\n", i, iT[i].type, iT[i].amount, iT[i].unit, first, last);

	}
}
//Consumer thread
void *consumerThread(){
	item *consItem;
	for (int i = 0; i < 3; ++i)
	{
		consItem = consume();
		printf("\nConsumed item %d: %c, %d, %c\nfirst = %d, last = %d\n", i, consItem->type, consItem->amount, consItem->unit, first, last);
	}
}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(
		&tid1,
		NULL,
		produceThread,
		NULL
		);
	pthread_create(
		&tid2,
		NULL,
		consumerThread,
		NULL
		);
	pthread_join(tid2,NULL);
	return 0;

}
