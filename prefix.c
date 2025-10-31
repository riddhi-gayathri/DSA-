#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 15

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
        return s->top == MAX-1;
}

void pushChar(CharStack *s, char ch) {
        if (!isCharStackFull(s))
                s->arr[++(s->top)] = ch;
}

char popChar(CharStack *s) {
        if (!isCharStackEmpty(s))
                return s->arr[(s->top)--];
        return '\0'; // Return null char if stack is empty
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
        return s->top == MAX-1;
}

void pushInt(IntStack *s, int val) {
        if (!isIntStackFull(s))
                s->arr[++(s->top)] = val;
}

int popInt(IntStack *s) {
        if (!isIntStackEmpty(s))
                return s->arr[(s->top)--];
        return 0; // Return 0 if stack is empty
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
	for (int i = 0 ; i < len/2 ; i++) {
		char temp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}
}

void infixToPrefix(char *infix, char *prefix) {
        CharStack stack;
        initCharStack(&stack);

	// Step 1: Reverse infix expression
	reverseString(infix);

	// Step 2: Replace '(' with ')' and vice versa
	for (int i = 0 ; i < strlen(infix) ; i++) {
		if (infix[i] == '(') 
			infix[i] = ')';
		else if (infix[i] = ')')
			infix[i] = '(';
	}

	// Step 3: Convert reversed infix to postfix
        int j = 0 ;
        for (int i = 0 ; infix[i] != '\0'; i++) {
                char ch = infix[i];
                if (isspace(ch))
                        continue; // Ignore whitespace
                else if (isalnum(ch))
                        prefix[j++] = ch; // Add operands to postfix
                else if (ch == '(')
                        pushChar(&stack,ch);
                else if (ch == ')') {
                       // Pop till matching '('
		       	while (!isCharStackEmpty(&stack) && peekChar(&stack) != '(')
                                prefix[j++] = popChar(&stack);
                        popChar(&stack); // Remove the '('
                }
                else if (isOperator(ch)) {
			// Pop operators with high precedence
                        while (!isCharStackEmpty(&stack) && precedence(peekChar(&stack)) > precedence(ch))
                                prefix[j++] = popChar(&stack);
			pushChar(&stack,ch); // Push current operator
                }
        }

        // If any operators are left over in stack
        while (!isCharStackEmpty(&stack))
                prefix[j++] = popChar(&stack);

        prefix[j] = '\0'; // Null-terminate the postfix expression
	
	// Step 4: Reverse postfix expression to get prefix
	reverseString(prefix);
}

int evaluatePrefix(char *prefix) {
        IntStack stack; initIntStack(&stack);

        for (int i = strlen(prefix)-1 ; i >= 0 ; i--) {
                char ch = prefix[i];
                if (isdigit(ch))
                        pushInt(&stack, ch - '0'); // Convert char to int
                else if (isOperator(ch)) {
                        int a = popInt(&stack);
                        int b = popInt(&stack);
                        int result;
                        switch(ch) {
                                case '+': result = a+b; break;
                                case '-': result = a-b; break;
                                case '*': result = a*b; break;
                                case '/': if (b == 0) {
                                                  printf("Error: Division by zero\n");
                                                  exit(1);
                                          }
                                          result = a/b; break;
                                case '^': result = 1;
                                          for (int j = 0 ; j < b ; j++)
                                                  result *= a;
                                          break;
                                default: result = 0 ; break;
                        }
                        pushInt(&stack, result); // Push result back into stack 
                }
        }
        return popInt(&stack); // Popping final result out of stack
}

// Function to check if a str is valid prefix expression
int isPrefix(char *expression) {
        int operands = 0, operators = 0, i = strlen(expression)-1; // Start from end of expression

	// Apply same logic as 'isPostfix' but for reversed prefix str
        while (i >= 0) {
                // Skip spaces
                if (isspace(expression[i])) {
                        i--; continue;
                }

                // Check if its a number
		if (isdigit(expression[i])) {
                        while (isdigit(expression[i])) { // Parse whole number
                                i--;
                                operands++; // Count operands till next operator
                        }
                }

                // Check if its an operator
                else if (isOperator(expression[i])) {
                        operators++; i--;
                        if (operators >= operands)
                                return 0; // More operators than operands is invalid ; If they are equal, then its not poatfix/prefix expression
                }

                // Invalid character
                else
                        return 0; // Not a valid prefix expression
        }

        // At end, operands must be exactly one more than operators
        return (operands == operators + 1);
}

int main() {
        char infix[MAX], prefix[MAX];

        while (1) {
                int choice;
                printf("\nMenu:\n1. Convert Infix to Prefix\n2. Evaluate Prefix Expression\n3. Exit\n\nEnter your choice: ");
                scanf("%d",&choice);

                switch(choice) {
                        case 1: printf("Enter an Infix Expression: ");
                                scanf("%s",infix);
                                infixToPrefix(infix,prefix);
                                printf("Prefix Expression: %s\n",prefix);
                                break;
                        case 2: printf("Enter a Prefix Expression: ");
                                scanf("%s",prefix);
                                if (!isPrefix(prefix))
                                        printf("This is NOT a Valid Prefix Expression\n");
                                else {
                                        int result = evaluatePrefix(prefix);
                                        printf("Result: %d\n",result);
                                }
                                break;
                        case 3: printf("Exiting...\n"); exit(0);
                        default: printf("Invalid choice. Please try again\n");
                }
        }
        return 0;
}