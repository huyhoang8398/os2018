#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

int main()
{
	//Item declaration 
	item i1, i2;
	i1.type = '0';
	i1.amount = 3;
	i1.unit = '1';
	printf("First item: %c, %d, %c\n", i1.type, i1.amount, i1.unit);
	i2.type = '1';
	i2.amount = 4;
	i2.unit = '0';
	printf("Second item: %c, %d, %c\n", i2.type, i2.amount, i2.unit);
	
	printf("first = %d, last = %d\n\n", first, last);
	
	produce(&i1);
	printf("After produce:\tItem 1: %c, %d, %c\tfirst = %d, last=%d\n\n", i1.type, i1.amount, i1.unit, first, last);
	produce(&i2);
	printf("After produce:\tItem 2: %c, %d, %c\tfirst = %d, last=%d\n\n", i2.type, i2.amount, i2.unit, first, last);
	//consume item
	item *consumed_item = consume();
	printf("After consume:\tConsumed item: %c, %d, %c\tfirst = %d, last=%d\n\n", consumed_item->type, consumed_item->amount, consumed_item->unit, first, last);
	return 0;
}