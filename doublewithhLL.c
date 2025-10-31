#include <stdio.h>
#include <stdlib.h>

// Node Structure
typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
} Node;

// Global Pointer to header node
Node *header = NULL;

// Function Prototypes
Node *createNode(int value);
void initializeHeader();
void insertFront(int value);
void insertRear(int value);
void insertAtPosition(int value, int position);
void deleteFront();
void deleteRear();
void deleteAtPosition(int position);
void deleteByKey(int key);
Node* searchByKey(int key);
void createOrderedList(int value);
void reverseList();
Node* copyList();
void displayList();

int main() {
	initializeHeader();   // Initialize the header node
	int choice, value, position;
	Node *copy;

	while(1) {
		printf("\nMenu:\n");
		printf("1. Insert Front\n2. Insert Rear\n3. Insert at Position\n4. Delete Front\n5. Delete Rear\n6. Delete at Position\n7. Delete by Key\n8. Search by Key\n9. Create Ordered List\n");
		printf("10. Reverse List\n11. Create Copy of List\n12. Display List\n13. Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1 : printf("Enter value: ");
				 scanf("%d",&value);
				 insertFront(value);
				 break;
			case 2 : printf("Enter value: ");
				 scanf("%d",&value);
				 insertRear(value);
				 break;
			case 3 : printf("Enter value and position: ");
				 scanf("%d %d",&value, &position);
				 insertAtPosition(value, position);
				 break;
			case 4 : deleteFront(); break;
			case 5 : deleteRear(); break;
			case 6 : printf("Enter position: ");
				 scanf("%d",&position);
				 deleteAtPosition(position);
				 break;
			case 7 : printf("Enter key to delete: ");
				 scanf("%d",&value);
				 deleteByKey(value);
				 break;
			case 8 : printf("Enter key to search: ");
				 scanf("%d",&value);
				 Node* result = searchByKey(value);
				 if (result != NULL)
					 printf("Key found: %d\n",result->data);
				 else
					 printf("Key not found\n");
				 break;
			case 9 : printf("Enter value: ");
 				 scanf("%d",&value);
				 createOrderedList(value);
				 break;
			case 10 : reverseList(); break;
			case 12 : displayList(); break;
			case 11 : copy = copyList();
				  printf("Copied List: ");
				  displayList(copy);
				  break;
			case 13 : printf("Exiting...\n"); exit(0);
			default: printf("Invalid choice! Try again\n");
		}
	}
	return 0;
}

// Create a new node
Node* createNode(int value) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = value;
	newNode->prev = newNode->next = NULL;
	return newNode;
}

// Initialize the header node
void initializeHeader() {
	header = createNode(-1); 		// Header has dummy data
	header->next = header->prev = header;   // Circular Link
}

// Insert at front of the list
void insertFront(int value) {
	Node *newNode = createNode(value);
	newNode->next = header->next;
	newNode->prev = header;
	header->next->prev = newNode;
	header->next = newNode;
	printf("Inserted at front\n");
}

// Insert at Rear
void insertRear(int value) {
	Node *newNode = createNode(value);
	newNode->prev = header->prev;
	newNode->next = header;
	header->prev->next = newNode;
	header->prev = newNode;
	printf("Inserted at rear\n");
}

// Insert at Specified Position
void insertAtPosition(int value, int position) {
	if (position == 1) {
		insertFront(value);
		printf("Inserted at position\n");
		return;
	}
	Node *temp = header->next;
	int count = 1;
	// Traverse to position just before insertion point
	while(temp != header && count < (position-1)) {
		temp = temp->next;
		count++;
	}
	if (count == position-1 && temp != header) {
		Node *newNode = createNode(value);
		newNode->next = temp->next;
		newNode->prev = temp;
		temp->next->prev = newNode;
		temp->next = newNode;
		printf("Inserted at position\n");
	}
	else
		printf("Invalid Position\n");
}

// Delete from front
void deleteFront() {
	if (header->next == header) {
		printf("List is empty\n");
		return;
	}
	Node* first = header->next;
	header->next = first->next;
	first->next->prev = header;
	free(first);
	printf("Deleted from front\n");
}

// Delete from rear
void deleteRear() {
	if (header->prev == header) {
		printf("List is empty\n");
		return;
	}
	Node *last = header->prev;
	header->prev = last->prev;
	last->prev->next = header;
	free(last);
	printf("Deleted from rear\n");
}

// Delete at a specified position
void deleteAtPosition(int position) {
	if (header->next == header) {
		printf("List is empty!\n");
		return;
	}
	Node *temp = header->next;
	int count = 1;
	while (temp != header && count < position) {
		temp = temp->next;
		count++;
	}
	if (count == position && temp != header) {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		free(temp);
		printf("Deleted Node at given position\n");
	}
	else {
		printf("Invalid position\n");
	}
}

// Delete by key
void deleteByKey(int key) {
	if (header->next == header) {
		printf("List is empty\n");
		return;
	}
	Node *temp = header->next;
	while (temp != header) {
		if (temp->data == key) {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);
			printf("Key %d is deleted\n",key);
			return;
		}
		temp = temp->next;
	}
	printf("Key not found\n");
}

// Search by Key
Node* searchByKey(int key) {
	if (header->next == header) {
                printf("List is empty\n");
                return NULL;
        }
        Node *temp = header->next;
        while (temp != header) {
                if (temp->data == key) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

// Create ordered list
void createOrderedList(int value) {
	Node *temp = header->next;
	while (temp != header && temp->data < value)
		temp = temp->next;
	Node *newNode = createNode(value);
	// Update links for ordered insertion
	newNode->next = temp;
	newNode->prev = temp->prev;
	temp->prev->next = newNode;
	temp->prev = newNode;
	printf("Ordered List created\n");
}

// Reverse the list
void reverseList() {
	if (header->next == header) {
		printf("List is empty\n");
		return;
	}
	Node *current = header->next;
	Node *firstNode = header->next;
	Node *prevNode = header;
	do {
		Node *nextNode = current->next;
		// Swap prev and next pointers
		current->next = prevNode;
		current->prev = nextNode;
		prevNode = current;   // Update ptr
		current = nextNode;   // Update ptr
	} while (current != header);
	// Update header links
	header->next = prevNode;
	header->prev = firstNode;
	printf("List Reversed\n");
}

// Create a copy of list
Node* copyList() {
	Node* newHeader = createNode(-1);  // New Header
	newHeader->next = newHeader->prev = newHeader;
	Node* temp = header->next;
	while (temp != header) {
		Node *newNode = createNode(temp->data);
		// Insert at rear of new list
		newNode->prev = newHeader->prev;
		newNode->next = newHeader;
		newHeader->prev->next = newNode;
		newHeader->prev = newNode;
		temp = temp->next;
	}
	return newHeader;
}

// Display the list
void displayList() {
	if (header->next == header) {
		printf("List is empty\n");
		return;
	}
	Node *temp = header->next;
	while (temp != header) {
		printf("%d <-> ", temp->data);
		temp = temp->next;
	}
	printf("(header)\n");
}