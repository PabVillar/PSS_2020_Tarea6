#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef unsigned long long Set;

Set buscarSecuencial(int a[], int i,int j,int n){
    for (Set k = i; k <= j; k++)
    {
        //k es el mapa de bits para el subconjunto {a[i]| bit ki de k es 1}
        long long sum = 0;
        for (int m = 0; m < n; m++)
        {
            if (k & ((Set)1<<m))
            {
                sum += a[m];
            }
        }
        if (sum == 0 && k!=0)
        {
            return k;
        }
    }
    return 0;     
}

typedef struct
{
    int *a;
    int n,i,j;
    Set res;
}Args;

void *thread_buscar(void *params){
    Args *p = (Args *)params;
    p->res = buscarSecuencial(p->a,p->i,p->j,p->n); 
    return NULL;
}

Set buscar(int a[], int n){
    pthread_t t[8];
    Args args[8];
    Set comb = ((1<<(n-1)<<1)-1);
    Set step = ((comb))/8;
    Set result = 0;
    for (int k = 0; k < 8; k++)
    {
        args[k].a = a;
        args[k].n = n;
        args[k].i = 1+step*k;
        args[k].j = step*(k+1)-1 > comb ? comb : step*(k+1)-1; 
        args[k].res = 0;

        pthread_create(&t[k],NULL,thread_buscar,&args[k]);
    }

    for (int k = 0; k < 8; k++)
    {
        pthread_join(t[k],NULL);
        if (args[k].res!=0)
        {
            result = args[k].res;
        }
    }
    return result;
    
    
}



 
