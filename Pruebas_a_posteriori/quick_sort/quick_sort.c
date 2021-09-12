

void quickSort(A, p, r);
void pivote(A, p ,r);
void intercambiar(A, i, j);



void quickSort(A, p, r)
{
    if (p<r)
    {
        j=pivote(A, p, r);
        quickSort(A, p, j-1);
        quickSort(A, j+1, r);
    }
}

void pivote(A, p ,r)
{
    piv=A[p];
    i=p+1;
    j=r;
    while (A[i]<piv && i<r)
    {
        i++;
        while (A[j]>piv)
        {
            j--;
        }
        if (i<j)
        {
            intercambiar(A, i, j);
        }
        else
        {
            intercambiar(A, p, j);
        }
    }
}

void intercambiar(A, i, j)
{
    temp=A[j];
    A[j]=A[i];
    A[i]=temp;
}