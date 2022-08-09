#include <stdio.h>

int isPrime(int n){
    if(n%2==0 && n>2 || n<=1)
        return 0;
    for(int i=2; i*i<=n; i++)
        if(n%i == 0)
            return 0;
    return 1;
}

float xpowern (float x, int n)
{
    float result = 1;
    while (n)
    {
        if (n % 2 == 1)
            result = result * x;
        x = x * x;
        n = n / 2;
    }
    return result;
}

int combination(int n, int k)
{
//    c(n, k) = n!/(k!*(n-k)!)
    int result = 1;
    for(int i=n-k+1; i<=n; i++){
        result *= i;
    }
    for(int i=2; i<=k; i++)
        result /= i;
    return result;
}

void a(){
    int n;
    printf("n=");
    scanf("%d", &n);
    for(int m=0; m<=n; m++) {
        for (int k = 0; k <= m; k++)
            printf("%d ", combination(m, k));
        printf("\n");
    }
}

void b(){
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

    int searched_length = 0, current_length = 0, searched_array[100] = {0}, current_array[100] = {0};
    for (int i = 0; i < length; i++)
    {
        if (isPrime(array[i])==1)
        {
            current_array[current_length] = array[i];
            current_length += 1;
            if (current_length > searched_length)
            {
                for (int j = 0; j < current_length; j++)
                    searched_array[j] = current_array[j];
                searched_length = current_length;
            }
        }
        else
        {
            for (int j = 0; j < 100; j++)
                current_array[j] = 0;
            current_length = 1;
        }
    }

    printf("length is: %d\nthe searched array is: ", searched_length);
    for (int i = 0; i < searched_length-1; i++)
        printf ("%d,", searched_array[i]);
    printf("%d", searched_array[searched_length-1]);
}

//int main() {
//    a();
//    b();
//    return 0;
//}