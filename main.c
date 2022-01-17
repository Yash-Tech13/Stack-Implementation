#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct stack
{
  int ele;
  struct stack *next;
};

struct stack *top = NULL; 

void push(int x)
{
  struct stack *temp;
  temp = (struct stack*)malloc(sizeof(struct stack));
  if(top == NULL)
  {
    temp->ele = x;
    temp->next = NULL;
    top = temp;
  }

  else
  {
    temp->ele = x;
    temp->next = top;
    top = temp;
  }
}

int pop()
{
  struct stack *temp;
  int item;

  if(top == NULL)
  {
    puts("Empty Stack\n");
  }
  else if(top->next == NULL)
  {
    temp = top;
    item = top->ele;
    top = NULL;
    free(temp);
  }
  else
  {
    temp = top;
    item = top->ele;
    top = top->next;
    free(temp);
  }
  return item;
}

int precedence(char x)
{
  switch(x)
  {
    case '^': return 4;
    case '*':
    case '/': return 3;
    case '+': 
    case '-': return 2;

    default: return 0;
  }
}

void infix_to_postfix(char infix[20])
{
  char postfix[20];
  int i=0,j=0;

  while(infix[i] != '\0')
  {
    if(isalnum(infix[i]))
    {
      postfix[j++] = infix[i];
    }
    else
    {
      if(top == NULL)
      {
        push(infix[i]);
      }
      else
      {
        if(precedence(top->ele) >= precedence(infix[i]))
        {
          postfix[j++] = pop();
          push(infix[i]);
        }
        else
        {
          push(infix[i]);
        }
      }
    }
    i++;
  }

  while(top != NULL)
  {
    postfix[j++] = pop();
  }
  postfix[j] = '\0';

  printf("Postfix expression: ");
  puts(postfix);
  getchar();
}


void infix_to_prefix(char infix[20])
{
  char prefix[20];
  int i=0,j=0;
  strrev(infix);

  while(infix[i] != '\0')
  {
    if(isalnum(infix[i]))
    {
      prefix[j++] = infix[i];
    }
    else
    {
      if(top == NULL)
      {
        push(infix[i]);
      }
      else
      {
        if(precedence(top->ele) >= precedence(infix[i]))
        {
          prefix[j++] = pop();
          push(infix[i]);
        }
        else
        {
          push(infix[i]);
        }
      }
    }
    i++;
  }

  while(top != NULL)
  {
    prefix[j++] = pop();
  }
  prefix[j] = '\0';

  strrev(prefix);
  printf("Postfix expression: ");
  puts(prefix);
  getchar();

}

int main(void) 
{
  char infix[20];

  printf("Enter Infix expression: ");
  scanf("%s",infix);

  infix_to_postfix(infix);
  infix_to_prefix(infix);  
  return 0;
}
