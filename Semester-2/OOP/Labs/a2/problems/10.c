#include <stdio.h>
#include <string.h>

int isPrime(int p)
{
    if(p<2 || (p>2 && p%2==0))
        return 0;
    int d=2;
    while(d*d<=p)
    {
        if(p%d==0) return 0;
        d++;
    }
    return 1;
}

int containAtLeast2SameDigits(int a, int b){
    char Achar[100], Bchar[100];
    sprintf(Achar, "%d", a);
    sprintf(Bchar, "%d", b);
    char Adigits[10]={0}, Bdigits[10]={0};
    for(int i=0; i<strlen(Achar); i++)
        Adigits[Achar[i]-'0']=1;
    for(int i=0; i<strlen(Bchar); i++)
        Bdigits[Bchar[i]-'0']=1;
    int counter=0;
    for(int i=0; i<10; i++)
        if(Adigits[i]==Bdigits[i] && Adigits[i]==1)
            counter+=1;
    if(counter>=2)
        return 1;
    return 0;
}

void a()
{
    int n, p1, p2, ok=1;
    printf ("n= ");
    scanf ("%d", &n);
    if(n%2) {
        printf("impossible\n");
        return;
    }
    for(int i=2; i<=n/2 && ok==1; i++)
        if(isPrime(i) && isPrime(n-i))
        {
            ok=0;
            p1=i; p2=n-i;
        }
    printf("%d %d\n", p1, p2);
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
        if (containAtLeast2SameDigits(array[i], array[i + 1])==1)
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

int main() {
    a();
    b();
    return 0;
}