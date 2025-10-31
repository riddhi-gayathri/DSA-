#include<stdio.h>
#include<stdlib.h>
#define MAX 5

//Static Queue sturcture
typedef struct {
        int arr[MAX];
        int front;
        int rear;
}StaticQueue;

//Dynamic Queue structure
typedef struct {
        int front, rear, *arr, capacity;
}DynamicQueue;

//Function prototypes for Static Queue
void initStaticQueue(StaticQueue *sq);
int isStaticQueueFull(StaticQueue *sq);
int isStaticQueueEmpty(StaticQueue *sq);
void enqueueStatic(StaticQueue *sq, int value);
int dequeueStatic(StaticQueue *sq);
void peekStatic(StaticQueue *sq);
void displayStaticQueue(StaticQueue *sq);

//Function prototypes for Dynamic Queue
void initDynamicQueue(DynamicQueue *dq);
int isDynamicQueueFull(DynamicQueue *dq);
int isDynamicQueueEmpty(DynamicQueue *dq);
void enqueueDynamic(DynamicQueue *dq, int value);
int dequeueDynamic(DynamicQueue *dq);
void peekDynamic(DynamicQueue *dq);
void displayDynamicQueue(DynamicQueue *dq);
void freeDynamicQueue(DynamicQueue *dq);

int main()
{
        StaticQueue staticQueue;
        DynamicQueue dynamicQueue;
        int choice, value, n, count = 1;

        initStaticQueue(&staticQueue);

        while(1){
                printf("\nMenu : \n1. Enqueue (Static Queue)\n");
                printf("2. Dequeue (StaticQueue)\n");
                printf("3. Peek (Static Queue)\n");
                printf("4. Display (Static Queue)\n");
                printf("5. Enqueue (Dynamic Queue)\n");  
                printf("6. Dequeue (Dynamic Queue)\n");
                printf("7. Peek (Dynamic Queue)\n");
                printf("8. Display (Dynamic Queue)\n");
                printf("9. Exit \n\n Enter your choice : ");
                scanf("%d", &choice);

                switch(choice){
                        case 1 : printf("Enter no of elements to be enqueued to static queue : ");
                                 scanf("%d", &n);
                                 for(int i = 0; i < n; i++){
                                         printf("Enter value to enqueue (Static Queue) : ");
                                         scanf("%d", &value);
                                         enqueueStatic(&staticQueue, value);
                                         if(isStaticQueueFull(&staticQueue)){
                                                 printf("Only %d Elements can be Added to Queue at Max\n", MAX);
                                                 break;
                                         }
                                 }
                                 break;
                        case 2 : value = dequeueStatic(&staticQueue);
                                 if(value != -1)
                                         printf("Dequeued from Static Queue : %d\n", value);
                                 break;
                        case 3 : peekStatic(&staticQueue);
                                 break;
                        case 4 : displayStaticQueue(&staticQueue); break;
                        case 5 : if(count == 1){
                                         initDynamicQueue(&dynamicQueue);
                                         //initializatin for dynamic stack
                                         count++;
                                 }
                                 printf("Enter no of elements to be enqueued to dynamic queue : ");
                                 scanf("%d", &n);
                                 for(int i = 0; i < n; i++){
                                         printf("Enter value to enqueue (Dynamic Queue) : ");
                                         scanf("%d", &value);
                                         enqueueDynamic(&dynamicQueue, value);
                                 }
                                 break;
                        case 6 : if (count == 1){
                                         printf("Dynamic Queue Not Initialized Try Enqueueing an Element to Dynamic Queue to Initialize it \n");
                                         break;
                                 }
                                 value = dequeueDynamic(&dynamicQueue);
                                 if(value != 1){
                                         printf("Dequeued from Dynamic Queue : %d\n", value);
                                 }
                                         break;
                        case 7 : if(count == 1){
                                          printf("Dynamic Queue Not Initialized. Try Enqueueing an Element to Dynamic Queue to Initialize it\n");
                                          break;
                                 }
                                peekDynamic(&dynamicQueue); break;
                        case 8 : if(count == 1){
                                           printf("Dynamic Queue Not Initialized. Try Enqueueing an Element to Dynamic Queue to Initialize it \n");
                                           break;
                                }
                                displayDynamicQueue(&dynamicQueue); break;
                        case 9 : printf("Exiting...\n"); freeDynamicQueue(&dynamicQueue);
                                 exit(0);
                        default : printf("Invalid choice. Please try again\n");
                        }
                  }
        return 0;
}


//Static Queue Functions
void initStaticQueue(StaticQueue *sq){
sq->front = -1; sq->rear = -1;
}

int isStaticQueueFull(StaticQueue *sq){
return sq->rear == MAX-1;
}

int isStaticQueueEmpty(StaticQueue *sq){
return sq->front == -1 || sq->front > sq->rear;
}

void enqueueStatic(StaticQueue *sq, int value){
        if(isStaticQueueFull(sq)){
                printf("Static Queue is full\n");
                return;
        }

        if(isStaticQueueEmpty(sq))
                sq->front = 0;
        sq->arr[++(sq->rear)] = value;
        printf("Value Enqueued to Static Queue\n");
}

int dequeueStatic(StaticQueue *sq){
        if(isStaticQueueEmpty(sq)){
                printf("Static Queue is empty\n");
                return -1;
        }return sq->arr[(sq->front)++];
}

void peekStatic(StaticQueue *sq){
        if(isStaticQueueEmpty(sq)){
                printf("Static Queue is emtpy\n");
                return;
        }
        printf("Static Queue Front Element : %d\n", sq->arr[sq->front]);
}

void displayStaticQueue(StaticQueue *sq){
        if(isStaticQueueEmpty(sq)){
                printf("Static Queue is empty\n");
                return;
        }
        printf("Static Queue elements (from Front to Rear) : ");
        for(int i= sq->front; i<=sq->rear; i++)
                printf("%d", sq->arr[i]);
        printf("\n");
}

//Dynamic Queue Functions
void initDynamicQueue(DynamicQueue *dq){
        int size;
        printf("Enter the size of Dynamic Stack : ");
        scanf("%d", &size);
        dq->arr = (int *)malloc(size * sizeof(int));
        if(!dq->arr){
                printf("Memory allocation fialed\n");
                return;
        }
        dq->front = -1;
        dq->rear = -1;
        dq->capacity = size;
}

int isDynamicQueueFull(DynamicQueue *dq){
        return dq->rear == dq->capacity-1;
}

int isDynamicQueueEmpty(DynamicQueue *dq){
        return dq->front == -1 || dq->front > dq->rear;
}

void enqueueDynamic(DynamicQueue *dq, int value){
        if(isDynamicQueueFull(dq)){
                int newSize, ans;
                printf("Dynamic Queue is Filled. Do you want to Resize (1 for 'yes' (OR) 0 for 'no') : ");
                scanf("%d", &ans);
                if(!ans){
                        printf("Resizing is Not Performed\n");
                        return;
                }
                printf("Enter the New Size of Dynamic Queue : ");
                scanf("%d", &newSize);
                dq->capacity = newSize;
                dq->arr = (int *)realloc(dq->arr, (dq->capacity) * sizeof(int));
                if(!dq->arr){
                        printf("Memeory reallocation failed\n");
                        return;
                }
        }

        if(isDynamicQueueEmpty(dq))
                dq->front = 0;
        dq->arr[++(dq->rear)] = value;
        printf("Value Enqueued to Dynamic Queue\n");
}

int dequeueDynamic(DynamicQueue *dq){
        if(isDynamicQueueEmpty(dq)){
                printf("Dynamic Queue is empty\n");
                return -1;
        }
        return dq->arr[(dq->front)++];
}

void peekDynamic(DynamicQueue *dq){
        if(isDynamicQueueEmpty(dq)){
                printf("Dynamic Queue is empty\n");
                return;
        }
        printf("Dynamic Queue Front Element : %d\n", dq->arr[dq->front]);
}

void displayDynamicQueue(DynamicQueue *dq){
        if(isDynamicQueueEmpty(dq)){
                printf("Dynamic Queue is empty\n");
                return;
        }

        printf("Dynamic Queue elements (from Front to Rear) : ");
        for(int i= dq->front; i <= dq->rear; i++)
                printf("%d", dq->arr[i]);
        printf("\n");
}

void freeDynamicQueue(DynamicQueue *dq){
        free(dq->arr);
}