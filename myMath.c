#include"myMath.h"

// convert an integer to its binary form and return it as a linked list.
struct node *binary(int n)
{
    struct node *result=NULL;

    while(n!=0)
    {
        insert(&result,n%2);
        n/=2;
    }

    return result;
}

// Power function using the Ruffini-Horner method
double power(double n,int exposant)
{
    int negate=0;
    double result=1;
    struct node *bin=NULL;

    if(exposant<0)
    {
        exposant*=(-1);
        negate=1;
    }


    bin=binary(exposant);

    while(bin!=NULL)
    {
        if(bin->n)
            result=result*n;
        n*=n;
        bin=bin->next;
    }

    if(negate)
        result=1/result;

    return result;
}
