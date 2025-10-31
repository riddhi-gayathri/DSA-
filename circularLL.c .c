#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
        int data;
        struct Node *next;
} Node;


// Function Prototypes
Node* createnode(int);
void insertFront(Node**, int);
void insertRear(Node**, int);
void deleteFront(Node**);
void deleteRear(Node**);
void deleteByKey(Node**, int);
void searchByKey(Node*, int);
void reverseList(Node**);
void displayList(Node*);
void insertAtPosition(Node**, int, int);
void deleteAtPosition(Node**, int);
void createOrderedList(Node**);
Node* createCopy(Node* head);


int main() {
        Node *head = NULL;
        int choice, data, key, pos;
        while (1) {
                printf("\nMenu:\n");
                printf("1. Insert at front\n");
                printf("2. Insert at rear\n");
                printf("3. Delete at front\n");
                printf("4. Delete at rear\n");
                printf("5. Delete by key\n");
		printf("6. Insert by position\n");
		printf("7. Delete by position\n");
		printf("8. Create an ordered list\n");
		printf("9. Create a copy of list\n");
		printf("10. search by key\n");
		printf("11. Reverse list\n");
		printf("12. Display list\n");
		printf("13. Exit\n");
		printf("\n");

                printf("\nEnter your choice: ");
                scanf("%d",&choice);

                switch(choice) {
                        case 1: printf("Enter data: ");
                                scanf("%d",&data);
                                insertFront(&head,data);
                                break;
                        case 2: printf("Enter data: ");
                                scanf("%d",&data);
                                insertRear(&head,data);
                                break;
                        case 3: deleteFront(&head); break;
                        case 4: deleteRear(&head); break;
                        case 5: printf("Enter key to delete: ");
                                scanf("%d",&key);
                                deleteByKey(&head,key);
                                break;
			case 6 : printf("Enter data to insert :");
				 scanf("%d", &data);
				 printf("Enter position : ");
				 scanf("%d", &pos);
				 insertAtPosition(&head, data, pos);
				 break;
                        case 7: printf("Enter position to delete : ");
				scanf("%d",&pos);
                                deleteAtPosition(&head, pos);
                                break;
			case 8: createOrderedList(&head);
				break;
			case 9: {Node* copy = createCopy(head);
				printf("Copied List : ");
				displayList(copy);
				break;}
			case 10: printf("Enter key to search : ");
				 scanf("%d", &key);
				 searchByKey(head, key);
				 break;
                        case 11: reverseList(&head); break;
                        case 12: displayList(head); break;
                        case 13: printf("Exiting...\n"); return 0;
                        default: printf("Invalid choice! Try again\n");
                }
        }
        return 0;
}

// Function to create a new node
Node * createNode (int data) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = newNode; // Circular link
        return newNode;
}


// Insertion at the front
void insertFront(Node **head, int data) {
        Node *newNode = createNode(data);
        if (*head == NULL) {
                *head = newNode;
                printf("Data inserted at front\n");
                return;
        }
        Node *temp = *head;
        while (temp->next != *head)
                temp = temp->next;
        temp->next = newNode;
        newNode->next = *head;
        *head = newNode;
        printf("Data inserted at front\n");
}

// Insertion at the rear
void insertRear(Node **head, int data) {
        Node *newNode = createNode(data);
        if (*head == NULL) {
                *head = newNode;
                printf("Data inserted at rear\n");
                return;
        }
        Node *temp = *head;
         while (temp->next != *head)
                temp = temp->next;
        temp->next = newNode;
        newNode->next = *head;
        printf("Data inserted at rear\n");
}

// Deletion at the front
void deleteFront(Node **head) {
        if (*head == NULL) {
                printf("List is empty\n");
                return;
        }
        Node *temp = *head;
        if (temp->next == *head) { // Single Node Case
                free(temp);
                *head = NULL;
                printf("Front Node Deleted\n");
                return;
        }
        Node *last = *head;
        while (last->next != *head)
                last = last->next;
        last->next = temp->next;
        *head = temp->next;
        free(temp);
        printf("Front Node Deleted\n");
}

// Deletion at the rear
void deleteRear(Node **head) {
        if (*head == NULL) {
                printf("List is empty\n");
                return;
        }
        Node *temp = *head;
        if (temp->next == *head) { // Single Node Case
                free(temp);
                *head = NULL;
                printf("Node deleted\n");
                return;
        }
        Node *prev = NULL;
        while (temp->next != *head) {
                prev = temp;
                temp = temp->next;
        }
        prev->next = *head;
        free(temp);
        printf("Rear Node Deleted\n");
}

// Deletion by key
void deleteByKey(Node **head, int key) {
        if (*head == NULL) {
                printf("List is empty\n");
                return;
        }
        Node *temp = *head;
        Node *prev = NULL;
        // Check if head node is the key
	if (temp->data == key) {
                deleteFront(head);
                return;
        }
        while (temp->next != *head && temp->data != key) {
                prev = temp;
                temp = temp->next;
        }
        if (temp->data == key) {
                prev->next = temp->next;
                free(temp);
                printf("Key found and deleted\n");
        }
        else {
                printf("Key not found\n");
        }
}

// Search by Key
void searchByKey(Node *head, int key) {
        if (head == NULL) {
                printf("List is empty\n");
                return;
        }
        Node *temp = head;
        int pos = 1;
        do {
                if (temp->data == key) {
                        printf("Key %d found at position %d\n",key,pos);
                        return;
                }
                temp = temp->next;
                pos++;
        } while (temp != head);
        printf("Key not found\n");
}

// Reverse the List
void reverseList(Node **head) {
        if (*head == NULL || (*head)->next == *head) return;
        Node *prev = NULL, *curr = *head, *next = NULL;
        Node *last = *head;
	while (last->next != *head)
		last = last->next;
        do {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
        } while (curr != *head);
        (*head)->next = prev;
        *head = prev;
        printf("List Reversed\n");
}

// Display list
void displayList(Node *head) {
        if (head == NULL) {
                printf("List is empty\n");
                return;
        }
        Node *temp = head;
        do {
                printf("%d -> ", temp->data);
                temp = temp->next;
        } while (temp != head);
        printf("(HEAD)\n");
}

//Insertion at specified position
void insertAtPosition(Node **head, int data, int pos){
	if(pos <= 0){
		printf("Invalid position\n");
		return;
	}
	Node* newNode = createNode(data);
	//Insert at front
	if(pos==1){
		if(*head == NULL){ //If list is empty, make the new node self-referential
			*head = newNode;
		}else{
			Node *temp = *head;
			while(temp->next != *head){
				temp = temp->next;
			}
			//Insert the new node at the front
			newNode->next = *head;
			temp->next = newNode;
			*head = newNode; //Update the head to the new node
			}
		printf("Inserted %d at position %d\n", data, pos);
		return;
	}

	//Case2 : Insert at any other position
	Node *temp = *head;
	for(int i=1; i<pos-1; i++){
		temp = temp->next;
		//If we loop back to head, then position is out of range
		if(temp == *head){
			printf("Position out of range\n");
			free(newNode);
			return;
		}
	}
	//Insert the new Node
	newNode->next = temp->next;
	temp->next = newNode;
	printf("Inserted %d at position %d\n", data, pos);
}

//Delete at specified position
void deleteAtPosition(Node **head, int pos){
	if(pos <= 0 || *head == NULL){
		printf("Invalid position or list is empty\n");
		return;
	}
	Node *temp = *head;
	//Case1 : Delete the first node at pos1
	if(pos == 1){
		if((*head)->next == *head){  //Only one node in the list
			free(*head);
			*head = NULL;
		}else{				//More than one node in list
			Node *last = *head;
			while(last->next != *head){
				last = last->next;
			}
			Node *toDelete = *head;
			last->next = (*head)->next;
			*head = (*head)->next;
			free(toDelete);
		}
		printf("Deleted element at position %d\n", pos);
		return;
	}
	//Case2 : Delete at any other position
	Node *prev = NULL;
	for(int i=1; i<pos; i++){
		prev = temp;
		temp = temp->next;
		//If we loop back to head, position is out of range
		if(temp == *head){
			printf("Position out of range\n");
			return;
		}
	}
	//Perform the deletion
	prev->next = temp->next;
	free(temp);
	printf("Deleted element at position %d\n", pos);
}

//Create Ordered list
void createOrderedList(Node **head){
	if(!(*head)){
		printf("List is empty\n");
		return;
	}
	for(Node *i = *head; i->next!= *head; i=i->next){
		for(Node *j = i->next; j!= *head; j=j->next){
			if(i->data > j->data){
				int temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
		}
	}
	printf("List sorted in ascending order\n");
}

//Copy list
Node* createCopy(Node *head){
	if(head == NULL){
		printf("List is empty\n");
		return NULL;
	}
	Node *newHead = NULL; Node *temp = head; Node *tail = NULL;
	do
	{
		Node *newNode = createNode(temp->data);
	if(!newHead){
		newHead = newNode;
		tail = newHead;
	}else{
		tail->next = newNode;
		tail = tail->next;
	}
	temp = temp->next;
	}while(temp!=head);
tail->next = newHead; //Circular link
printf("Copy of list created\n");
return newHead;
}