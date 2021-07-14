#include "myMath.h"

#define N 5

/*to avoid confusion,the minus operator has being considered as the sign of a negative number.Thus,if the program
encountered a "-" operator between two operands(an operand can be a number or an expression like(8*9-2)),it will
consider it as an addition*/

//get the top of a stack and assign its value to the parameter result,return -1 if the stack is empty
int top(struct node *stack, double *result);

int isOperator(char c);
int isNumber(char c);

//get the value of an expression
double calculateIntegers(struct expression **exp);

//perform the operation: operand1 c operand2
double perform(char c, double operand1, double operand2);

//return the last node of a linked list;
struct expression *endList(struct expression *head);

/*return an improved version of an infix which is more easier to read for the program.This function
put an addition operator before a minus operator.For example:
7-8 ----> 7+-8 ,-5-9 ---->-5+-9.*/
struct expression *infixCorrect(struct expression *exp);

//convert an infix expression to a postfix expression and return that last one;
struct expression *infixPostfix(struct expression *exp);

//return the value of a postfix expression
int evaluatePostfix(struct expression *exp, double *result);

//compare operator1 to operator2 by the rule of operator precedence
int highPrecedence(char operator1, char operator2);

void calculator();

int main()
{
    calculator();
    return 0;
}

int top(struct node *stack, double *result)
{
    int error = 0;
    if (stack == NULL)
        error = -1;
    else
        *result = stack->n;
    return error;
}

int isOperator(char c)
{
    return (c == '+' || c == '*' || c == '/' || c == '^');
}

int isNumber(char c)
{
    return ((c >= '0' && c <= '9') || c == '-' || c == '.');
}

double calculateIntegers(struct expression **exp)
{
    int negate = 0, isFloat = 0;

    double result = 0;

    while (isNumber((*exp)->c))
    {
        if ((*exp)->c == '-')
            ++negate;

        else if (!isFloat && isNumber((*exp)->c))
            result = result * 10 + (((*exp)->c) - '0');

        else if ((*exp)->c == '.')
            isFloat = -1;

        else
        {
            result = result + ((((*exp)->c) - '0') * power(10, isFloat));
            --isFloat;
        }

        *exp = (*exp)->next;
    }

    if (negate % 2 != 0)
        result = result * (-1);

    return result;
}

double perform(char c, double operand1, double operand2)
{
    double result;

    switch (c)
    {
    case '+':
        result = operand1 + operand2;
        break;

    case '*':
        result = operand1 * operand2;
        break;

    case '/':
        result = operand1 / operand2;
        break;

    case '^':
        result = power(operand1, (int)operand2);
    }

    return result;
}

struct expression *infixCorrect(struct expression *exp)
{
    int count = 0, check;
    struct expression *result = NULL, *end = NULL;

    while (exp != NULL)
    {
        end = endList(result);
        check = 1;

        if (exp->c == '-')
        {

            if (count != 0)
            {
                if (result != NULL && end->c == '(')
                    check = 0;

                else if (check)
                    letterInsert(&result, '+');
            }
        }

        letterInsert(&result, exp->c);
        exp = exp->next;
        ++count;
    }

    return result;
}

struct expression *infixPostfix(struct expression *exp)
{
    struct expression *stack = NULL, *temp = NULL, *result = NULL, *end = NULL, *next = NULL;

    temp = infixCorrect(exp);

    while (temp != NULL)
    {
        if (isNumber(temp->c))
        {
            letterInsert(&result, temp->c);
        }

        else if (isOperator(temp->c))
        {
            if (stack != NULL && isOperator(stack->c))
            {
                if (highPrecedence(temp->c, stack->c))
                {
                    letterPush(&stack, temp->c);
                    letterInsert(&result, ' ');
                }

                else
                {
                    while (stack != NULL && stack->c != '(')
                    {
                        letterInsert(&result, stack->c);
                        letterPop(&stack);
                    }
                    letterPush(&stack, temp->c);
                }
            }

            else
            {
                end = endList(result);

                /*if the last character in result is a number,the program put a space character next to it.
                That is,it becomes easier to separate two operand in the postfix expression*/
                if (result != NULL && isNumber(end->c))
                    letterInsert(&result, ' ');

                letterPush(&stack, temp->c);
            }
        }

        else if (temp->c == '(')
        {
            letterPush(&stack, temp->c);
        }

        else if (temp->c == ')')
        {
            while (stack->c != '(')
            {
                letterInsert(&result, stack->c);
                letterPop(&stack);
            }
            letterPop(&stack);
        }

        else
            return 0;

        temp = temp->next;
    }

    while (stack != NULL)
    {
        letterInsert(&result, stack->c);
        letterPop(&stack);
    }

    return result;
}

int evaluatePostfix(struct expression *exp, double *result)
{
    struct node *stack = NULL;
    int error = 0;
    double operand1, operand2, temp;
    *result = 0;

    while (error != -1 && exp != NULL)
    {

        if (isNumber(exp->c))
        {
            operand1 = calculateIntegers(&exp);
            push(&stack, operand1);
        }

        else if (isOperator(exp->c))
        {
            error = top(stack, &operand2);
            pop(&stack);
            if (error != -1)
            {
                error = top(stack, &operand1);
                pop(&stack);
            }
            if (error != -1)
            {
                temp = perform(exp->c, operand1, operand2);
                push(&stack, temp);
                exp = exp->next;
            }
        }

        else if (exp->c == ' ')
            exp = exp->next;
        else
            error = -1;
    }

    if (error != -1)
    {
        error = top(stack, result);
        pop(&stack);
    }

    return error;
}

//go to the end of a linked list
struct expression *endList(struct expression *head)
{
    struct expression *result = head;

    if (result != NULL)
        while (result->next != NULL)
            result = result->next;

    return result;
}

int highPrecedence(char operator1, char operator2)
{
    int result = 1;

    switch (operator1)
    {
    case '+':
        if (operator2 == '*' || operator2 == '/' || operator2 == '^')
            result = 0;
        break;

    case '*':
        if (operator2 == '^')
            result = 0;
        break;

    case '/':
        if (operator2 == '^')
            result = 0;
        break;

    case '^':
        if (operator2 == '^')
            result = 0;
        break;
    }

    return result;
}

void calculator()
{
    double result;
    char choice = 'y';
    struct expression *exp1 = NULL, *exp2 = NULL;
    int error;
    printf("\n\t ========================================================================= ");
    printf("\n\t|                                                                         |");
    printf("\n\t|                             CALCULATRICE                                |");
    printf("\n\t|                                                                         |");
    printf("\n\t ========================================================================= \n\n");

    printf("\n (+): Addition (ex: 1+1)");
    printf("\n (-): Soustraction (ex: 1-1)");
    printf("\n (*): Multiplication (ex: 1*1)");
    printf("\n (^): Puissance (ex: 1^1)\n");

    while (choice == 'y')
    {
        result = 0.0;
        clearExpression(&exp1);
        clearExpression(&exp2);

        getExpression(&exp1);

        exp2 = infixPostfix(exp1);

        error = evaluatePostfix(exp2, &result);

        display(exp1);
        printf(" = %.4f", result);

        printf("\n\nVoulez-vous continuer y(Yes)/ n(No)? : ?");
        scanf("%c", &choice);

        getchar();
    }
    free(exp1);
    free(exp2);
}
