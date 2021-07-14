#include"stack.h"

void insert(struct node **head,int n)
{
    struct node *temp1,*temp2=*head;

    temp1=(struct node *)malloc(sizeof(struct node));
    temp1->n=n;
    temp1->next=NULL;

    if(*head==NULL)
        *head=temp1;

    else
    {
       while(temp2->next!=NULL)
            temp2=temp2->next;
       temp2->next=temp1;
    }

}


void  display(struct expression*stack)
{
    printf("===> ");
    while(stack!=NULL)
    {
        printf("%c",stack->c);
        stack=stack->next;
    }
}

void push(struct node **head,double n)
{
   struct node *temp=(struct node *)malloc(sizeof(struct node));
   temp->n=n;
   temp->next=*head;
   *head=temp;
}

void pop(struct node **head)
{
   struct node *temp;

   if(*head==NULL)
     return;

   temp=*head;
   *head=(*head)->next;
   free(temp);

}

void clearExpression(struct expression **head) {
    if(*head==NULL) {
        return;
    }

    while(*head) {
        letterPop(head);
    }


}

void letterInsert(struct expression **exp,char c)
{
    struct expression *temp1,*temp2=*exp;

    temp1=(struct expression *)malloc(sizeof(struct expression));
    temp1->c=c;
    temp1->next=NULL;

    if(*exp==NULL)
        *exp=temp1;

    else
    {
       while(temp2->next!=NULL)
            temp2=temp2->next;
       temp2->next=temp1;
    }
}


void getExpression(struct expression **exp)
{
    struct expression *temp=NULL,*tempNext=NULL;
    char c;

    printf("\nEnter an expression(ex: 1+(3*4): \n");
    printf("===> ");

    do
    {
        scanf("%c",&c);
        letterInsert(exp,c);

    }while(c!='\n');

     temp=*exp;

     do
     {
       temp=temp->next;
       tempNext=temp->next;

     }while(temp!=NULL && tempNext->next!=NULL);

     temp->next=NULL;

     free(tempNext);
}

void expressionDisplay(struct expression *exp)
{
    printf("\n");
    while(exp!=NULL)
    {

        printf("%c",exp->c);
        exp=exp->next;
    }

}

void letterPush(struct expression **stack,char c)
{
   struct expression *temp=(struct expression *)malloc(sizeof(struct expression));
   temp->c=c;
   temp->next=*stack;
   *stack=temp;
}

void letterPop(struct expression **stack)
{
    struct expression *temp;

   if(*stack==NULL) {
    return;
   }


   temp=*stack;
   *stack=(*stack)->next;
   free(temp);

}


