#include <stdio.h>

int isPrime(int n){
    if(n%2==0 && n>2 || n<=1)
        return 0;
    for(int i=2; i*i<=n; i++)
        if(n%i == 0)
            return 0;
    return 1;
}

int areRelativelyPrime(int a, int b){
    int maxim=a;
    if(b>a)
        maxim=b;
    for(int i=2; i*i<=maxim; i++)
        if(a%i==0 && b%i==0)
            return 0;
    return 1;
}

void a(){
    int n;
    printf("n=");
    scanf("%d", &n);
    int number=2, counter=0;
    while(counter<n){
        if(isPrime(number)==1) {
            printf("%d ", number);
            counter+=1;
        }
        number+=1;
    }
    printf("\n");
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

    int searched_length = 1, current_length = 1, searched_array[100] = {0}, current_array[100] = {0};
    for (int i = 0; i < length-1; i++)
    {
        if (areRelativelyPrime(array[i], array[i + 1])==1)
        {
            current_array[current_length - 1] = array[i];
            current_array[current_length] = array[i + 1];
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