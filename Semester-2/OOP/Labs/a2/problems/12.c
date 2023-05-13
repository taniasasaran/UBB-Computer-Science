#include <stdio.h>

int areRelativelyPrime(int a, int b){
    int maxim=a;
    if(b>a)
        maxim=b;
    for(int i=2; i*i<=maxim; i++)
        if(a%i==0 && b%i==0)
            return 0;
    return 1;
}

void a ()
{
    int n;
    printf ("n= ");
    scanf ("%d", &n);
    for(int i=2;i<=n; i++)
        if(areRelativelyPrime(i,n)==1)
            printf("%d ", i);
    printf("\n");
}

int maxSubArraySum(int array[], int size)
{
    int max_so_far = -99999, max_ending_here = 0, start =0, end = 0, s=0;
    for (int i=0; i< size; i++ ){
        max_ending_here += array[i];
        if (max_so_far < max_ending_here){
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
        if (max_ending_here < 0){
            max_ending_here = 0;
            s = i + 1;
        }
    }
    for(int i=start; i<=end; i++)
         printf("%d ", array[i]);
    return max_so_far;
}

void b ()
{
    int array[100], length = 0;
    int n;
    printf("n=");
    scanf("%d", &n);
    printf ("array = ");
    for (int i = 0; i < n; i++)
    {
        scanf ("%d", &array[i]);
        length += 1;
    }
    int max_sum = maxSubArraySum(array, n);
    printf("Maximum contiguous sum is %d", max_sum);

}

int main() {
    a();
    b();
    return 0;
}
