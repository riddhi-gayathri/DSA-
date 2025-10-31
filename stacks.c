#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

// Structure for Static Stack 
typedef struct {
	int  data[MAX_SIZE];
	int top;
}StaticStack;

// Structure for Dynamic Stack 
typedef struct {
	int *data,top,capacity;
}DynamicStack;

// Static Stack Functions
void initStaticStack(StaticStack *s) {
	s->top = -1;
}

int pushStatic(StaticStack *s, int value) {
	if (s->top == MAX_SIZE - 1) {
		printf("Static stack overflow\n");
		return -1;
	}
	s->data[++(s->top)] = value; // Increments 'top' ptr first, then pushes value
	printf("Value pushed to Static Stack\n");
	return 0;
}

int popStatic(StaticStack *s) {
	if (s->top == -1) {
		printf("Static Stack underflow\n0-");
		return -1;
	}
	return s->data[(s->top)--]; // First returns value, then decrements 'top' ptr
}

void peekStatic(StaticStack *s) {
	if (s->top == -1) {
		printf("Static stack is empty\n");
		return;
	}
	printf("Static Stack top element: %d\n",s->data[(s->top)]);
}

void displayStatic(StaticStack *s) {
	if (s->top == -1) {
		printf("Static stack is empty\n");
		return;
	}
	printf("Static Stack (From bottom to top of stack): ");
	for (int i = 0 ; i <= s->top ; i++)
		printf("%d ",s->data[i]);
	printf("\n");
}

// Dynamic Stack Functions
void initDynamicStack(DynamicStack *d) {
	int size;
	printf("Enter the Size of Dynamic Stack: ");
	scanf("%d",&size);
	d->data = (int *)malloc(size * sizeof(int));
	if (!d->data) {
		printf("Memory allocation failed\n");
		return;
	}
	d->top = -1;
	d->capacity = size;
}

void pushDynamic(DynamicStack *d, int value) {
        if ((d->top) == (d->capacity)-1) { // Resize the stack 
	 	int newSize, ans;
		printf("Dynamic Stack is Filled. Do you want to Resize (1 for 'yes' (OR) 0 for 'no'): ");
		scanf("%d",&ans);
		if (!ans) {
			printf("Resizing is not performed\n");
			return;
		}
		printf("Enter the new size of Dynamic Stack: ");
		scanf("%d",&newSize);
		d->capacity = newSize;
		d->data = (int *)realloc(d->data, (d->capacity) * sizeof(int));
		if (!d->data) {
			printf("Memory reallocation failed\n");
			return;
		}
	}
        d->data[++(d->top)] = value; // Increments 'top' ptr first, then pushes value
        printf("Value pushed to Dynamic Stack\n");
}       

int popDynamic(DynamicStack *d) {
        if (d->top == -1) {
                printf("Dynamic Stack underflow\n");
                return -1;
        }        
        return d->data[(d->top)--]; // First returns value, then decrements 'top' ptr
}                                   

void peekDynamic(DynamicStack *d) {
        if (d->top == -1) {
                printf("Dynamic stack is empty\n");
                return;
        }       
        printf("Dynamic Stack top element: %d\n",d->data[(d->top)]);
}       

void displayDynamic(DynamicStack *d) {
        if (d->top == -1) {
                printf("Dynamic stack is empty\n");
                return;
        }       
        printf("Dynamic Stack (From bottom to top of stack): ");
        for (int i = 0 ; i <= d->top ; i++)
                printf("%d ",d->data[i]);
        printf("\n");
}

void freeDynamicStack(DynamicStack *d) {      
	free(d->data);
	d->data = NULL;
	d->top = -1;
	d->capacity = 0;
}

int main() {
	StaticStack staticStack;
	DynamicStack dynamicStack;

	initStaticStack(&staticStack);
	int choice, value, n, count = 1;

	do {
		printf("\nMenu:\n1. Push to Static Stack\n2. Pop from Static Stack\n3. Peek Static Stack\n4. Display Static Stack\n5. Push to Dynamic Stack\n6. Pop from Dynamic Stack\n");
		printf("7. Peek Dynamic Stack\n8. Display Dynamic Stack\n9. Exit\n\nEnter your choice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1: printf("Enter no of elements to be pushed to static stack: ");
				scanf("%d",&n);
				for (int i = 0 ; i < n ; i++) {
					printf("Enter value to push to static stack: ");
					scanf("%d",&value);
					int res = pushStatic(&staticStack, value);
					if (res == -1)
						break;
				}
				break;
			case 2: value = popStatic(&staticStack);
				if (value != -1)
					printf("Popped value from static stack: %d\n",value);
				break;
			case 3: peekStatic(&staticStack); break;
			case 4: displayStatic(&staticStack); break;
			case 5: if (count == 1) {
					initDynamicStack(&dynamicStack);
					count++;
				}
				printf("Enter no of elements to be pushed to dynamic stack: ");
                                scanf("%d",&n);
                                for (int i = 0 ; i < n ; i++) {
                                        printf("Enter value to push to dynamic stack: ");
                                        scanf("%d",&value);
                                        pushDynamic(&dynamicStack, value);
                                }
                                break;
			case 6: if (count == 1) {
					printf("Dynamic Stack Not Initialized. Try Pushing an Element to Dynamic Stack to Initialize it\n");
					break;
				}
				value = popDynamic(&dynamicStack);
				if (value != -1) 
					printf("Popped value from dynamic stack: %d\n",value);
				break;
			case 7: if (count == 1) {
                                        printf("Dynamic Stack Not Initialized. Try Pushing an Element to Dynamic Stack to Initialize it\n");
                                        break;
                                }
                                peekDynamic(&dynamicStack);
                                break;
			case 8: if (count == 1) {
                                        printf("Dynamic Stack Not Initialized. Try Pushing an Element to Dynamic Stack to Initialize it\n");
                                        break;
                                }
                                displayDynamic(&dynamicStack);
                                break;
			case 9: printf("Exiting...\n"); break;
			default: printf("Invalid choice. Please try again\n");
		}
	} while (choice != 9);

	freeDynamicStack(&dynamicStack); // Free dynamic memory
	return 0;
}