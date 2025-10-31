#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node *head = NULL;

// Function Prototypes
void insertAtFront(int data);
void insertAtRear(int data);
void deleteAtFront();
void deleteAtRear();
void insertAtPosition(int data, int position);
void deleteAtPosition(int position);
void deleteByKey(int key);
void searchByKey(int key);
void createOrderedList();
void reverseList();
Node *createCopy();
void displayList();

// Helper Function to create a new node
Node * createNode(int data) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (!newNode) {
		printf("Memory allocation failed\n");
		exit(1); // Error
	}
	newNode -> data = data;
	newNode -> next = NULL;
	return newNode;
}

int main() {
	int choice, data, position, key, n;
	Node *copy;

	
	printf("\nMenu:\n");
	printf("1. Insert at Front\n2. Insert At Rear\n3. Delete At Front\n4. Delete At Rear\n5. Insert at Position\n6. Delete at Position\n");
	printf("7. Delete by Key\n8. Search by Key\n9. Create Ordered List\n10. Reverse List\n11. Create Copy of List\n12. Display List\n");
	printf("13. Exit\n");
	while (1) {
		printf("\nEnter your choice: ");
		scanf("%d",&choice);

		switch (choice) {
			case 1: printf("Enter number of elements to be inserted at front: ");
				scanf("%d",&n);
				for (int i = 0 ; i < n ; i++) {
					printf("Enter data %d to insert at front: ",i+1);
					scanf("%d",&data);
					insertAtFront(data);
				}
				break;
			case 2: printf("Enter data to insert at rear: ");
				scanf("%d",&data);
				insertAtRear(data);
				break;
			case 3: deleteAtFront();
				break;
			case 4: deleteAtRear();
				break;
			case 5: printf("Enter data to insert: ");
				scanf("%d",&data);
				printf("Enter position: ");
				scanf("%d",&position);
				insertAtPosition(data, position);
				break;
			case 6: printf("Enter position to delete: ");
				scanf("%d",&position);
				deleteAtPosition(position);
				break;
			case 7: printf("Enter key to delete: ");
				scanf("%d",&key);
				deleteByKey(key);
				break;
			case 8: printf("Enter key to search: ");
				scanf("%d",&key);
				searchByKey(key);
				break;
			case 9: createOrderedList();
				break;
			case 10: reverseList();
				 break;
			case 11: copy = createCopy();
				 printf("Copied List: ");
				 Node *temp = copy;
				 while (temp) {
					 printf("%d -> ", temp->data);
					 temp = temp->next;
				}
				 printf("NULL\n");
				 break;
			case 12: displayList();
				 break;
			case 13: printf("Exiting...\n");
				 exit(0);
			default: printf("Invalid choice! Try again\n");
		}
	}
	return 0;
}

void insertAtFront(int data) {
	Node *newNode = createNode(data);
	newNode->next = head;
	head = newNode;
	printf("Inserted %d at front\n",data);
}

void insertAtRear(int data) {
	Node *newNode = createNode(data);
	if (!head) 
		head = newNode;
	else {
		Node *temp = head;
		while (temp->next) 
			temp = temp->next;
		temp->next = newNode;
	}
	printf("Inserted %d at rear\n",data);
}

void deleteAtFront() {
	if (!head) {
		printf("List is empty\n");
		return;
	}
	Node *temp = head;
	head = head->next;
	free(temp);
	printf("Deleted element at front\n");
}

void deleteAtRear() {
	if (!head) {
		printf("List is empty\n");
		return;
	}
	if (!head->next) {
		free(head);
		head = NULL;
	}
	else {
		Node *temp = head;
		while(temp->next->next) 
			temp = temp->next;
		free(temp->next);
		temp->next = NULL;
	}
	printf("Deleted element at rear\n");
}

void insertAtPosition(int data, int position) {
	if (position <= 0) {
		printf("Invalid position\n");
		return;
	}
	if (position == 1) {
		insertAtFront(data);
		return;
	}
	Node *newNode = createNode(data);
	Node *temp = head;
	for (int i = 1 ; i < position - 1 && temp ; i++) 
		temp = temp->next;
	if (!temp) {
		printf("Position out of range\n");
		free(newNode);
		return;
	}
	newNode->next = temp->next;
	temp->next = newNode;
	printf("Inserted %d at position %d\n",data, position);
}

void deleteAtPosition(int position) {
	if (position <= 0 || !head) {
		printf("Invalid position or list is empty\n");
		return;
	}
	if (position == 1) {
		deleteAtFront();
		return;
	}
	Node *temp = head;
	for (int i = 1 ; i < position - 1 && temp -> next ; i++)
		temp = temp->next;
	if (!temp->next) {
		printf("Position out of range\n");
		return;
	}
	Node *toDelete = temp -> next;
	temp->next = toDelete->next;
	free(toDelete);
	printf("Deleted element at position %d\n", position);
}

void deleteByKey(int key) {
	if (!head) {
		printf("List is empty\n");
		return;
	}
	if (head->data == key) {
		deleteAtFront();
		return;
	}
	Node *temp = head;
	while (temp->next && temp->next->data != key) 
		temp = temp->next;
	if (!temp->next) {
		printf("Key not found\n");
		return;
	}
	Node *toDelete = temp->next;
	temp->next = toDelete->next;
	free(toDelete);
	printf("Deleted element with key %d\n",key);
}

void searchByKey(int key) {
	Node *temp = head;
	int position = 1;
	while (temp) {
		if (temp->data == key) {
			printf("Key %d found at position %d\n",key,position);
			return;
		}
		temp = temp->next;
		position++;
	}
	printf("Key %d not found\n",key);
}

void createOrderedList() {
	if (!head) {
		printf("List is empty\n");
		return;
	}
	for (Node *i = head; i ; i = i->next) {
		for (Node *j = i->next; j ; j= j->next) {
			if (i->data > j->data) {
				int temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
	printf("List sorted in ascending order\n");
}

void reverseList() {
	Node *prev = NULL, *current = head, *next = NULL;
	while (current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	printf("List reversed\n");
}

Node *createCopy() {
	if (!head) {
		printf("list is empty\n");
		return NULL;
	}
	Node *newHead = NULL, *temp = head, *tail = NULL;
	while (temp) {
		Node *newNode = createNode(temp->data);
		if (!head) {
			newHead = newNode;
			tail = newHead;
		}
		else {
			tail->next = newNode;
			tail = tail->next;
		}
		temp = temp->next;
	}
	printf("Copy of list created\n");
	return newHead;
}

void displayList() {
	if (!head) {
		printf("List is empty\n");
		return;
	}
	Node *temp = head;
	while (temp) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}