#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int stack[100];
int top = -1;

int precdence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*' || c == '%')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

bool isOperand(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void infixtoprefix(char infix[], char prefix[])
{
    int j = 0;
    for (int i = strlen(infix) - 1; i >= 0; i--)
    {
        char token = infix[i];
        if (isOperand(token))
            prefix[j++] = token;
        else if (token == ')')
            stack[++top] = token;
        else if (token == '(')
        {
            while (top != -1 && stack[top] != ')')
                prefix[j++] = stack[top--];
            if (top != -1)
                top--;
        }
        else
        {
            while (top != -1 && precdence(token) < precdence(stack[top]))
                prefix[j++] = stack[top--];
            stack[++top] = token;
        }
    }
    while (top != -1)
        prefix[j++] = stack[top--];
    prefix[j] = '\0';

    for (int i = 0, j = strlen(prefix) - 1; i < j; i++, j--)
    {
        char temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
}

int main()
{
    char infix[100], prefix[100];
    scanf("%s", infix);
    infixtoprefix(infix, prefix);
    printf("%s", prefix);
    return 0;
}