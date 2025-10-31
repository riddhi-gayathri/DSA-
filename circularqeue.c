//Circular Dynamic Queue

#include <stdio.h>
 #include <stdlib.h>
  int queue_size;
 
struct QueueDynamic {
	int front; // Index Of front element in Queue
	int rear;  // Index of rear element in Queue
	int *queue; // Base address of array to store Queue
} QD;

// Function to insert an element to rear of Queue
void insert() {
	int val;
	// Checking if Queue is Full
	if (QD.front == 0 && QD.rear == queue_size - 1) {
		printf("Queue is Full\n");
		printf("Reallocating Memory\n");
		queue_size++;
		QD.queue = (int *)realloc(QD.queue, queue_size * sizeof(int));
	}
	if (QD.front == -1 && QD.rear == -1) {
		QD.front = 0; // Initializing First element
	}
	printf("Enter the element to be inserted: ");
	scanf("%d", &val);
	QD.rear = (QD.rear + 1) % queue_size;
	QD.queue[QD.rear] = val;
	printf("Insertion Successful\n");
}

// Function to delete the front element of Queue
void delete() {
	// Checking if Queue is Empty
	if (QD.front == -1) {
		printf("Queue is Empty\n");
	} else if (QD.front == QD.rear) {
		printf("Deleted Element: %d\n", QD.queue[QD.front]);
		QD.front = QD.rear = -1;
	} else {
		// Deleting Element from front
		printf("Deleted Element: %d\n", QD.queue[QD.front]);
		QD.front = (QD.front + 1) % queue_size;
	}
}

// Function Display all elements of Queue
void display() {
	int i;
	// Checking if Queue is Empty
	if (QD.front == -1) {
		printf("Queue is Empty\n");
	} else {
		if (QD.front <= QD.rear) {
			for (i = QD.front; i <= QD.rear; i++) {
				printf("%d\n", QD.queue[i]);
			}
		} else {
			for (i = QD.front; i <= queue_size - 1; i++) {
				printf("%d\n", QD.queue[i]);
			}
			for (i = 0; i <= QD.rear; i++) {
				printf("%d\n", QD.queue[i]);
			}
		}
	}
}

void main() {
	int choice, val;
	QD.front = QD.rear = -1; // Initializing Empty Queue
	printf("Enter the Size: ");
	scanf("%d", &queue_size);
	QD.queue = (int *)malloc(queue_size * sizeof(int)); // Dynamically Allocating Array for Queue
	printf("Main Menu\n1.Insert\n2.Delete\n3.Display\n4.Exit\n");
	for (;;) {
		printf("Enter Your choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				display();
				break;
			case 4:
				printf("!! THANK YOU !!\n");
				exit(0);
			default:
				printf("Invalid Choice\nEnter Again\n");
		}
	}
}
