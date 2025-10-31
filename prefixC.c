#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

// Stack for characters (used in conversion)
typedef struct {
    char arr[MAX];
    int top;
} CharStack;

// Stack for integers (used in evaluation)
typedef struct {
    int top, arr[MAX];
} IntStack;

// Character Stack Functions
void initCharStack(CharStack *s) {
    s->top = -1;
}

int isCharStackEmpty(CharStack *s) {
    return s->top == -1;
}

int isCharStackFull(CharStack *s) {
    return s->top == MAX - 1;
}

void pushChar(CharStack *s, char ch) {
    if (!isCharStackFull(s))
        s->arr[++(s->top)] = ch;
}

char popChar(CharStack *s) {
    if (!isCharStackEmpty(s))
        return s->arr[(s->top)--];
    return '\0';
}

char peekChar(CharStack *s) {
    if (!isCharStackEmpty(s))
        return s->arr[s->top];
    return '\0';
}

// Integer Stack Functions
void initIntStack(IntStack *s) {
    s->top = -1;
}

int isIntStackEmpty(IntStack *s) {
    return s->top == -1;
}

int isIntStackFull(IntStack *s) {
    return s->top == MAX - 1;
}

void pushInt(IntStack *s, int val) {
    if (!isIntStackFull(s))
        s->arr[++(s->top)] = val;
}

int popInt(IntStack *s) {
    if (!isIntStackEmpty(s))
        return s->arr[(s->top)--];
    return 0;
}

// Utility Functions
int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    CharStack stack;
    initCharStack(&stack);

    // Step 1: Reverse infix expression
    reverseString(infix);

    // Step 2: Replace '(' with ')' and vice versa
    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }

    // Step 3: Convert reversed infix to postfix
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (isspace(ch))
            continue;
        else if (isalnum(ch))
            prefix[j++] = ch;
        else if (ch == '(')
            pushChar(&stack, ch);
        else if (ch == ')') {
            while (!isCharStackEmpty(&stack) && peekChar(&stack) != '(')
                prefix[j++] = popChar(&stack);
            popChar(&stack);
        } else if (isOperator(ch)) {
            while (!isCharStackEmpty(&stack) && precedence(peekChar(&stack)) >= precedence(ch))
                prefix[j++] = popChar(&stack);
            pushChar(&stack, ch);
        }
    }

    while (!isCharStackEmpty(&stack))
        prefix[j++] = popChar(&stack);

    prefix[j] = '\0';

    // Step 4: Reverse postfix expression to get prefix
    reverseString(prefix);
}

int evaluatePrefix(char *prefix) {
    IntStack stack;
    initIntStack(&stack);

    for (int i = strlen(prefix) - 1; i >= 0; i--) {
        char ch = prefix[i];

        if (isdigit(ch)) {
            int num = 0;
            int place = 1;

            while (isdigit(prefix[i])) {
                num = (prefix[i] - '0') * place + num;
                place *= 10;
                i--;
            }
            i++;

            pushInt(&stack, num);
        } else if (isOperator(ch)) {
            int a = popInt(&stack);
            int b = popInt(&stack);
            int result;
            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    result = a / b;
                    break;
                case '^':
                    result = 1;
                    for (int j = 0; j < b; j++)
                        result *= a;
                    break;
                default: result = 0; break;
            }
            pushInt(&stack, result);
        }
    }

    return popInt(&stack);
}

int main() {
    char infix[MAX], prefix[MAX];

    while (1) {
        int choice;
        printf("\nMenu:\n1. Convert Infix to Prefix\n2. Evaluate Prefix Expression\n3. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter an Infix Expression: ");
                getchar();
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0';
                infixToPrefix(infix, prefix);
                printf("Prefix Expression: %s\n", prefix);
                break;
            case 2:
                printf("Enter a Prefix Expression: ");
                getchar();
                fgets(prefix, MAX, stdin);
                prefix[strcspn(prefix, "\n")] = '\0';
                int result = evaluatePrefix(prefix);
                printf("Result: %d\n", result);
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
