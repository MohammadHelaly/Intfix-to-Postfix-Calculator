#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 100

typedef union
{
    float fData;
    char cData;
}item;

typedef struct
{
    item items[MAXSIZE];
    int top;
}stack;

stack* initialize()
{
    stack*s=malloc(sizeof(stack));
    s->top=0;
    return s;
}

int isEmpty(stack*s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
}

item top(stack*s)
{
    return s->items[s->top-1];
}

item pop(stack*s)
{
    item value;
    s->top--;
    value=s->items[s->top];
    return value;
}

void push(stack *s,item value)
{
    s->items[s->top]=value;
    s->top++;
}

int priority(char c)
{
    switch(c)
    {
    case '(':
    case ')':
        return 2;
    case '*':
    case '/':
    case '%':
        return 1;
    case '+':
    case '-':
        return 0;
    }
}

int evaluate(char x,int op1,int op2)
{
    if(x=='+')
        return(op1+op2);
    if(x=='-')
        return(op1-op2);
    if(x=='*')
        return(op1*op2);
    if(x=='/')
        return(op1/op2);
    if(x=='%')
        return(op1%op2);
    if(x=='^')
        return(op1^op2);
}

void infixToPostfix(char *infix,char *postfix)
{
    stack *temporary = malloc(sizeof(stack));
    temporary = initialize();
    item storage;
    int i=0,j=0;
    for(i=0;i<strlen(infix);i++)
     {
      if(infix[i]==' ')
        {
       i++;
        }
        if(isdigit(infix[i]))
          {
        while(infix[i]!=' ')
            {
            postfix[j]=infix[i];
            j++;
            i++;
            }
         postfix[j]=' ';
                j++;
          }
              if(infix[i]=='-' && infix[i+1]!= ' ')
                {
                while(infix[i]=='-' || infix[i]!=' ')
                  {
                    postfix[j]=infix[i];
                    i++;
                    j++;
                  }
                postfix[j]=' ';
                j++;
                continue;
                }
    else if(isEmpty(temporary) || infix[i]=='(')
           {
            storage.cData=infix[i];
            push(temporary,storage);
           }
        else if(infix[i]==')')
               {
            while(top(temporary).cData!='(')
                 {
                postfix[j]= pop(temporary).cData;
                j++;
                 postfix[j]=' ';
                j++;
                 }
        pop(temporary);
               }
        else
            {
            while(!isEmpty(temporary) && priority(top(temporary).cData)>=priority(infix[i]) )
              {
                postfix[j]=pop(temporary).cData ;
                j++;
                postfix[j]=' ';
                j++;
              }
            storage.cData=infix[i];
            push(temporary,storage);
            }
         }
     while(!isEmpty(temporary))
        {
        postfix[j]=pop(temporary).cData;
        j++;
         postfix[j]=' ';
                j++;
        }
    while(!isEmpty(temporary))
        {
        storage=pop(temporary);
        postfix[j]=storage.fData;
        j++;
        }
}

float evaluatePostfix(char *postfix)
{
    stack *temporary = initialize();
    temporary =malloc(sizeof(stack));
    char storage[100];
    item op1,op2,value,k;
    int i=0,j=0;
    for(i=0;i<strlen(postfix);i++)
    {
    if(postfix[i]==' ')
     {
        continue;
     }
     else if(isdigit(postfix[i]) || ( postfix[i]=='-' &&  postfix[i+1] != ' '))
        {
          while(postfix[i]!=' ')
          {
              storage[j]=postfix[i];
              j++;
              i++;
          }
          k.fData=atof(storage);
            push(temporary,k);
          storage[j-1]='.';
          memset(storage,0,sizeof(storage));
          j=0;
        }
    else
        {
    k.cData=postfix[i];
    op2=pop(temporary);
    op1=pop(temporary);
    value.fData=evaluate(k.cData,op1.fData,op2.fData);
        }
   push(temporary,value);
    value=pop(temporary);
        }
    return value.fData;
}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
