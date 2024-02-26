#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int stack[100];
int top = -1;

int calculate(char operator, int operand1, int operand2)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    }
    return -1;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

int evaluatePostfix(char postfix[])
{
    int i = 0, len = strlen(postfix);

    for (i = 0; i < len; i++)
    {
        char token = postfix[i];
        if (isDigit(token))
            stack[++top] = token - '0';
        else if (isOperator(token))
        {
            int operand2 = stack[top--];
            int operand1 = stack[top--];

            stack[++top] = calculate(token, operand1, operand2);
        }
    }
    return stack[top--];
}

int evaluatePrefix(char prefix[])
{
    int i = 0, len = strlen(prefix);

    for (i = len - 1; i >= 0; i--)
    {
        char token = prefix[i];
        if (isDigit(token))
            stack[++top] = token - '0';
        else if (isOperator(token))
        {
            int operand1 = stack[top--];
            int operand2 = stack[top--];

            stack[++top] = calculate(token, operand1, operand2);
        }
    }
    return stack[top--];
}

int main()
{
    char postfix[] = "543*+";
    printf("%d ", evaluatePostfix(postfix));
    char prefix[] = "+5*43";
    printf("%d", evaluatePrefix(prefix));
    return 0;
}