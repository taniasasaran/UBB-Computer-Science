#include <stdio.h>

int isPrime(int n){
    if(n%2==0 && n>2 || n<=1)
        return 0;
    for(int i=2; i*i<=n; i++)
        if(n%i == 0)
            return 0;
    return 1;
}

int isInInterval(int a, int b, int n){
    if(a<=n && n<=b)
        return 1;
    return 0;
}

int getExponent(int n, int p){
    int result=0;
    while(n%p==0)
    {
        n/=p;
        result+=1;
    }
    return result;
}

void a(){
    int array[100][100], length[100]={0}, numberOfSequences=0;
    int end=0;
    printf ("array = ");
    for(int i=0; i<100; i++){
        for (int j = 0; j < 100; j++)
        {
            scanf ("%d", &array[i][j]);
            if (array[i][j] == 0)
                break;
            if(array[i][j]==-1) {
                end = 1;
                break;
            }
            length[i] += 1;
        }
        if(end == 1)
            break;
        numberOfSequences+=1;
    }
    int maxim[100]={0}, maximum=0;
    for(int i=0; i<numberOfSequences; i++){
        for (int j = 0; j < length[i]; j++){
            if(maxim[i]<array[i][j])
                maxim[i] = array[i][j];
        }
    }
    for(int i=0; i<numberOfSequences; i++)
        if(maximum<maxim[i])
            maximum=maxim[i];
    for(int i=0; i<numberOfSequences; i++)
        printf("%d ", maxim[i]);
    printf("%d\n", maximum);
}


void b(){
    int array[100], length = 0;
    int a, b;
    printf("a=");
    scanf("%d", &a);
    printf("b=");
    scanf("%d", &b);
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
        if (isInInterval(a, b, array[i])==1)
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

int main() {
    a();
    b();
    return 0;
}