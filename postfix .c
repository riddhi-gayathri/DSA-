  #include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 15

// Stack for characters (used in conversion)
typedef struct {
	char data[MAX];
	int top;
} CharStack;
  
// Stack for integers (used in evaluation)
typedef struct {
	int top, data[MAX];
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

void pushChar(CharStack *s, char value) {
	if (!isCharStackFull(s)) 
		s->data[++(s->top)] = value;
}

char popChar(CharStack *s) {
	if (!isCharStackEmpty(s))
		return s->data[(s->top)--];
	return '\0'; // Return null char if stack is empty
}

char peekChar(CharStack *s) {
	if (!isCharStackEmpty(s))
		return s->data[s->top];
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

void pushInt(IntStack *s, int value) {
        if (!isIntStackFull(s))
                s->data[++(s->top)] = value;
}       

int popInt(IntStack *s) {
        if (!isIntStackEmpty(s))
                return s->data[(s->top)--];
        return 0; // Return 0 if stack is empty
}                    

// Utility Functions
int precedence(char op) {
	switch(op) {
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		case '^': return 3;
		default: return 0;
	}
}

int isOperator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char *infix, char *postfix) {
	CharStack stack;
	initCharStack(&stack);
	int j = 0 ;

	for (int i = 0 ; infix[i] != '\0'; i++) {
		char ch = infix[i];
		if (isspace(ch))
			continue; // Ignore whitespace
		else if (isalnum(ch))
			postfix[j++] = ch; // Add operands to postfix
		else if (ch == '(')
			pushChar(&stack,ch);
		else if (ch == ')') {
			while (!isCharStackEmpty(&stack) && peekChar(&stack) != '(') 
				postfix[j++] = popChar(&stack);
			popChar(&stack); // Remove the '('
		}
		else if (isOperator(ch)) {
			while (!isCharStackEmpty(&stack) && precedence(peekChar(&stack)) >= precedence(ch)) 
				postfix[j++] = popChar(&stack);
			pushChar(&stack,ch);
		}
	}

	// If any operators are left over in stack
	while (!isCharStackEmpty(&stack))
		postfix[j++] = popChar(&stack);

	postfix[j] = '\0'; // Null-terminate the postfix expression
}

int evaluatePostfix(char *postfix) {
	IntStack stack; initIntStack(&stack);

	for (int i = 0 ; postfix[i] != '\0' ; i++) {
		char ch = postfix[i];
		if (isdigit(ch))
			pushInt(&stack, ch - '0'); // Convert char to int
		else if (isOperator(ch)) {
			int b = popInt(&stack);
			int a = popInt(&stack);
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
int isPostfix(char *expression) {
	int operands = 0, operators = 0, i = 0;
	
	while (expression[i] = '\0') {
		// Skip spaces
		if (isspace(expression[i])) {
			i++; continue;
		}

		// Check if its a number
		if (isdigit(expression[i])) {
			while (isdigit(expression[i])) { // Parse whole number
				i++;
				operands++; // Count operands till next operator
			}
		}

		// Check if its an operator
		else if (isOperator(expression[i])) {
			operators++; i++; // Move to next character
			if (operators >= operands)
				return 0; // More operators than operands is invalid ; If they are equal, then its not poatfix/prefix expression
		}

		// Invalid character
		else 
			return 0;
	}

	// At end, operands must be exactly one more than operators
	return (operands == operators + 1);
}

int main() {
	char infix[MAX], postfix[MAX];

	while (1) {
		int choice;
		printf("\nMenu:\n1. Convert Infix to Postfix\n2. Evaluate Postfix Expression\n3. Exit\n\nEnter your choice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1: printf("Enter an Infix Expression: ");
				scanf("%s",infix);
				infixToPostfix(infix,postfix);
				printf("Postfix Expression: %s\n",postfix);
				break;
			case 2: printf("Enter a Postfix Expression: ");
				scanf("%s",postfix);
				if (!isPostfix(postfix))
					printf("This is NOT a Valid Postfix Expression\n");
				else {
					int result = evaluatePostfix(postfix);
					printf("Result: %d\n",result);
				}
				break;
			case 3: printf("Exiting...\n"); exit(0);
			default: printf("Invalid choice. Please try again\n");
		}
	}
	return 0;
}