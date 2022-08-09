#include <stdio.h>

/* This function computes x^n by multiplying x^(n/2)*x^(n/2)(*x -> if n id odd)
x - real number
n - natural number
*/
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

// This function reads two numbers x(float) and n(int) and prints x^n
void a ()
{
    int n;
    float x, result;
    printf ("x= ");
    scanf ("%f", &x);
    printf ("n= ");
    scanf ("%d", &n);
    result = xpowern (x, n);
    printf ("%f", result);
}

/* This function reads from the keyboard a string that ends with 0 and computes
longest contiguous subsequence such that any two consecutive elements have
contrary signs by comparing their product with 0.
*/
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

    int searched_length = 1, current_length = 1, searched_array[100] = {0}, current_array[100] = {0};
    for (int i = 0; i < length-1; i++)
    {
        if (array[i] * array[i + 1] < 0)
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

    printf("%d\n", searched_length);
    for (int i = 0; i < searched_length-1; i++)
        printf ("%d,", searched_array[i]);
    printf("%d", searched_array[searched_length-1]);
}

//This function receives a number as a parameter and checks if it is prime(return 1) or not(return 0)
int is_prime(int p)
{
    if(p>2 && p%2==0 || p<=1)
        return 0;
    for(int d=2; d*d<=p; d++)
        if(p%d==0)
            return 0;
    return 1;
}

// This function computes exponent of the second parameter in the decomposition of the first.
int exponent_func(int n, int p)
{
    int e=0;
    while(n%p==0)
    {
        e+=1;
        n/=p;
    }
    return e;
}

/*This function reads two numbers from the console and prints the exponent of
the second number in the decomposition of the first.
*/
void c()
{
    int p, n, exponent=0;
    printf("n= ");
    scanf("%d", &n);
    printf("p= ");
    scanf("%d", &p);
    if(n<=0 || is_prime(p)==0)
        printf("The numbers you introduced are not valid!");
    else
    {
        exponent = exponent_func(n, p);
        printf("The exponent of p in n is %d", exponent);
    }
}

void print_menu()
{
    printf("\nType 1 to determine the value x^n, where x is a real number and n is a natural number.\n");
    printf("Tybe 2 to find the longest contiguous subsequence such that any two consecutive elements have contrary signs.\n");
    printf("Type 3 to print the exponent of a prime number p from the decomposition in prime factors of a non-null natural number n.\n).\n");
    printf("Type 4 to exit.\n");
    printf("Your choice: ");
}


//int main ()
//{
//    int user_command;
//    while(1)
//    {
//        print_menu();
//        scanf("%d", &user_command);
//        if(user_command==4)
//            break;
//        switch(user_command)
//        {
//            case 1:
//                a();
//                break;
//            case 2:
//                b();
//                break;
//            case 3:
//                c();
//                break;
//            default:
//                printf("Menu command not available!");
//        }
//    }
//    return 0;
//}
