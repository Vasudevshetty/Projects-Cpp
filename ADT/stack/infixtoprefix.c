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

int isOperand(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void infixToPostfix(char infix[], char postfix[]){
    int i = 0, len = strlen(infix);
    int j = 0;

    while(i < len){
        char token = infix[i];
        if(isOperand(token))
            postfix[j++] = token;
        else if(token == '(')
            stack[++top] = token;
        else if(token == ')'){
            while(top != -1 && stack[top] != '(')
                postfix[j++] = stack[top--];
            top--; // to rmeove the (  opening parenthesis.
        }else{
            while(top!= -1 && precdence(token) <= precdence(stack[top]))
                postfix[j++] = stack[top--];
            
            // if the encountered token is of highest priority.
            stack[++top] = token;
        }
        i++;
    }
    while(top!=-1)
        postfix[j++] = stack[top--];
    postfix[j] = '\0';
}

void infixToPrefix(char infix[], char prefix[]){
    int i = 0, len = strlen(infix);
    int j = 0;

    for (i = len - 1; i >= 0; i--){
        char token = infix[i];
        if(isOperand(token))
            prefix[j++] = token;
        else if (token == ')') // if it is the opening parenthesis
            stack[++top] = token;
        else if(token == '('){ // fif it is the closing parenthesisi.
            while(top != -1 && stack[top] != ')')
                prefix[j++] = stack[top--];
            top--;
        }else{
            while(top != -1 && precdence(token) < precdence(stack[top]))
                prefix[j++] = stack[top--];
            stack[++top] = token;
        }
    }

    while(top != -1)
        prefix[j++] = stack[top--];

    prefix[j] = '\0';

    for (i = 0, j = len - 1; i < j; i++, j--){
        char temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
}


int main()
{
    char infix[100], prefix[100], postfix[100];
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    top = -1;
    infixToPrefix(infix, prefix);
    printf("%s %s", postfix, prefix);
    return 0;
}