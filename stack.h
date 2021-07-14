#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


 struct node{
    double n;
    struct node *next;
};


struct expression{
    char c;
    struct expression *next;
};

// insert an element at the end of a linked list
void insert(struct node **head,int n);

// insert a letter at the end of an expression
void letterInsert(struct expression **exp,char c);

// get the expression from the user
void getExpression(struct expression **exp);

// push an element at the top of a stack
void push(struct node **stack,double n);

// pop(remove) an element from a stack
void pop(struct node **stack);

// display a stack
void display(struct expression *stack);

//display an expression
void expressionDisplay(struct expression *exp);

// push a letter to an expression
void letterPush(struct expression **stack,char c);

// pop(remove) an element from an expression
void letterPop(struct expression **stack);

void clearExpression(struct expression **exp);

#endif // STACK_H_INCLUDED
