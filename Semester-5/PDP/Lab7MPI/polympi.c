#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <mpi.h>

typedef struct
{
    int *coeffs;
    int degree;
} Polynomial;

Polynomial initPolynomial(int *coeffs, int degree)
{
    Polynomial poly;
    poly.coeffs = coeffs;
    poly.degree = degree;
    return poly;
}

void printPolynomial(Polynomial poly)
{
    printf("Polynomial(");
    for (int i = 0; i <= poly.degree; i++)
    {
        printf("%d", poly.coeffs[i]);
        if (i < poly.degree)
        {
            printf(", ");
        }
    }
    printf(")\n");
}

Polynomial addPolynomials(Polynomial poly1, Polynomial poly2)
{
    int resultDegree = poly1.degree > poly2.degree ? poly1.degree : poly2.degree;
    int *resultCoeffs = (int *)calloc(resultDegree + 1, sizeof(int));

    for (int i = 0; i <= resultDegree; i++)
    {
        resultCoeffs[i] = (i <= poly1.degree && i <= poly2.degree) ? poly1.coeffs[i] + poly2.coeffs[i] : (i <= poly1.degree) ? poly1.coeffs[i]
                                                                                                                             : poly2.coeffs[i];
    }

    Polynomial result = initPolynomial(resultCoeffs, resultDegree);
    return result;
}

Polynomial subtractPolynomials(Polynomial poly1, Polynomial poly2)
{
    int resultDegree = poly1.degree > poly2.degree ? poly1.degree : poly2.degree;
    int *resultCoeffs = (int *)calloc(resultDegree + 1, sizeof(int));

    for (int i = 0; i <= resultDegree; i++)
    {
        resultCoeffs[i] = (i <= poly1.degree && i <= poly2.degree) ? poly1.coeffs[i] - poly2.coeffs[i] : (i <= poly1.degree) ? poly1.coeffs[i]
                                                                                                                             : -poly2.coeffs[i];
    }

    Polynomial result = initPolynomial(resultCoeffs, resultDegree);
    return result;
}

int polynomialDegree(Polynomial poly)
{
    return poly.degree;
}

Polynomial getFirstHalf(Polynomial poly, int k)
{
    k -= 1;
    int *coeffs1 = (int *)calloc(k + 1, sizeof(int));

    for (int i = 0; i <= k; i++)
    {
        coeffs1[i] = poly.coeffs[i];
    }
    Polynomial result1 = initPolynomial(coeffs1, k);
    return result1;
}

Polynomial getSecondHalf(Polynomial poly, int k)
{
    int *coeffs2 = (int *)calloc(poly.degree - k + 1, sizeof(int));

    for (int i = 0; i <= poly.degree - k; i++)
    {
        coeffs2[i] = poly.coeffs[k + i];
    }

    Polynomial result2 = initPolynomial(coeffs2, poly.degree - k);
    return result2;
}

Polynomial addShifted(Polynomial poly1, Polynomial poly2, int shift)
{
    int resultDegree = poly1.degree + poly2.degree + 1;
    int *resultCoeffs = (int *)calloc(resultDegree + 1, sizeof(int));

    for (int i = 0; i <= poly1.degree; i++)
    {
        resultCoeffs[i] = poly1.coeffs[i];
    }

    for (int i = 0; i <= poly2.degree; i++)
    {
        resultCoeffs[shift + i] += poly2.coeffs[i];
    }

    Polynomial result = initPolynomial(resultCoeffs, resultDegree);
    return result;
}

Polynomial removeTrailingZeros(Polynomial poly)
{
    int i = poly.degree;
    while (poly.coeffs[i] == 0)
    {
        i--;
    }
    poly.degree = i;
    return poly;
}

Polynomial multiplyNaive(Polynomial poly1, Polynomial poly2)
{
    int resultDegree = poly1.degree + poly2.degree;
    int *resultCoeffs = (int *)calloc(resultDegree + 1, sizeof(int));

    for (int i = 0; i <= poly1.degree; i++)
    {
        for (int j = 0; j <= poly2.degree; j++)
        {
            resultCoeffs[i + j] += poly1.coeffs[i] * poly2.coeffs[j];
        }
    }

    Polynomial result = initPolynomial(resultCoeffs, resultDegree);
    return result;
}

Polynomial multiplyKaratsuba(Polynomial poly1, Polynomial poly2)
{

    if (poly1.degree < 0 || poly2.degree < 0)
    {
        int coeffs[] = {0};
        return initPolynomial(coeffs, 0);
    }

    if (poly1.degree == 0 && poly2.degree == 0)
    {
        int *coeffs = (int *)calloc(1, sizeof(int));
        coeffs[0] = poly1.coeffs[0] * poly2.coeffs[0];
        Polynomial result = initPolynomial(coeffs, 0);
        return result;
    }

    int size = poly1.degree > poly2.degree ? poly1.degree : poly2.degree;
    int halfSize = (size + 1) / 2;

    Polynomial a = getFirstHalf(poly1, halfSize);
    Polynomial b = getSecondHalf(poly1, halfSize);
    Polynomial c = getFirstHalf(poly2, halfSize);
    Polynomial d = getSecondHalf(poly2, halfSize);
    Polynomial ac = multiplyKaratsuba(a, c);
    Polynomial bd = multiplyKaratsuba(b, d);
    Polynomial aplusb = addPolynomials(a, b);
    Polynomial cplusd = addPolynomials(c, d);
    Polynomial abcd = multiplyKaratsuba(aplusb, cplusd);
    Polynomial ad_bc = subtractPolynomials(subtractPolynomials(abcd, ac), bd);
    Polynomial result = addShifted(addShifted(ac, ad_bc, halfSize), bd, 2 * halfSize);
    Polynomial result2 = removeTrailingZeros(result);

    return result2;
}

void mpi_karatsuba()
{
    int rank, size;
    MPI_Init(0, 0);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = 15000;
    int halfSize = (n + 1) / 2;
    if (rank == 0)
    {
        int *coeffs1 = (int *)malloc(n * sizeof(int));
        int *coeffs2 = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
            coeffs1[i] = rand() % 100;
            coeffs2[i] = rand() % 100;
        }
        clock_t start = clock();
        MPI_Ssend(coeffs1, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Ssend(coeffs2, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Ssend(coeffs1, n, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Ssend(coeffs2, n, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Ssend(coeffs1, n, MPI_INT, 3, 0, MPI_COMM_WORLD);
        MPI_Ssend(coeffs2, n, MPI_INT, 3, 0, MPI_COMM_WORLD);
        int *result1 = (int *)malloc(2 * n * sizeof(int));
        int *result2 = (int *)malloc(2 * n * sizeof(int));
        int *result3 = (int *)malloc(2 * n * sizeof(int));
        MPI_Recv(result1, 2 * n, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Result from process 1: ");
        for (int i = 0; i < 2 * n; i++)
        {
            printf("%d ", result1[i]);
        }
        MPI_Recv(result2, 2 * n, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Result from process 2: ");
        for (int i = 0; i < 2 * n; i++)
        {
            printf("%d ", result2[i]);
        }
        MPI_Recv(result3, 2 * n, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Result from process 3: ");
        for (int i = 0; i < 2 * n; i++)
        {
            printf("%d ", result3[i]);
        }

        Polynomial ac = initPolynomial(result1, 2 * n);
        Polynomial bd = initPolynomial(result2, 2 * n);
        Polynomial abcd = initPolynomial(result3, 2 * n);
        Polynomial ad_bc = subtractPolynomials(subtractPolynomials(abcd, ac), bd);
        Polynomial resultPoly = addShifted(addShifted(ac, ad_bc, halfSize), bd, 2 * halfSize);
        Polynomial resultPoly2 = removeTrailingZeros(resultPoly);
        // printPolynomial(resultPoly2);
        double end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time spent: %f\n", time_spent);
    }
    if (rank == 1)
    {
        int *coeffs1 = (int *)malloc(n * sizeof(int));
        int *coeffs2 = (int *)malloc(n * sizeof(int));
        MPI_Recv(coeffs1, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(coeffs2, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        Polynomial poly1 = initPolynomial(coeffs1, n);
        Polynomial poly2 = initPolynomial(coeffs2, n);

        Polynomial a = getFirstHalf(poly1, halfSize);
        Polynomial c = getFirstHalf(poly2, halfSize);
        Polynomial ac = multiplyNaive(a, c);
        MPI_Send(ac.coeffs, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (rank == 2)
    {
        int *coeffs1 = (int *)malloc(n * sizeof(int));
        int *coeffs2 = (int *)malloc(n * sizeof(int));
        MPI_Recv(coeffs1, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(coeffs2, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        Polynomial poly1 = initPolynomial(coeffs1, n);
        Polynomial poly2 = initPolynomial(coeffs2, n);

        Polynomial b = getSecondHalf(poly1, halfSize);
        Polynomial d = getSecondHalf(poly2, halfSize);
        Polynomial bd = multiplyNaive(b, d);
        MPI_Send(bd.coeffs, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (rank == 3)
    {
        int *coeffs1 = (int *)malloc(n * sizeof(int));
        int *coeffs2 = (int *)malloc(n * sizeof(int));
        MPI_Recv(coeffs1, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(coeffs2, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        Polynomial poly1 = initPolynomial(coeffs1, n);
        Polynomial poly2 = initPolynomial(coeffs2, n);

        Polynomial a = getFirstHalf(poly1, halfSize);
        Polynomial b = getSecondHalf(poly1, halfSize);
        Polynomial c = getFirstHalf(poly2, halfSize);
        Polynomial d = getSecondHalf(poly2, halfSize);
        Polynomial aplusb = addPolynomials(a, b);
        Polynomial cplusd = addPolynomials(c, d);
        Polynomial abcd = multiplyNaive(aplusb, cplusd);
        MPI_Send(abcd.coeffs, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}

void mpi_classic()

    void multiplyPolynomials(int *poly1, int *poly2, int *result, int size, int start, int end)
{
    for (int i = start; i <= end; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            result[i + j] += poly1[i] * poly2[j];
        }
    }
}

void mpi_classic()
{
    int rank, size;
    MPI_Init(0, 0);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 15000;
    int *coeffs1 = (int *)malloc(n * sizeof(int));
    int *coeffs2 = (int *)malloc(n * sizeof(int));
    int *result = (int *)calloc(2 * n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        coeffs1[i] = rand() % 100;
        coeffs2[i] = rand() % 100;
    }

    int chunk_size = n / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? n - 1 : start + chunk_size - 1;

    multiplyPolynomials(coeffs1, coeffs2, result, n, start, end);

    for (int i = 0; i < size; ++i)
    {
        if (i != rank)
        {
            MPI_Ssend(&result[start], chunk_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    for (int i = 0; i < size; ++i)
    {
        if (i != rank)
        {
            int recv_start = i * chunk_size;
            int recv_end = (i == size - 1) ? n - 1 : recv_start + chunk_size - 1;

            MPI_Recv(&result[recv_start], recv_end - recv_start + 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rank == 0)
    {
        printf("Resulting polynomial: ");
        for (int i = 0; i < 2 * n; ++i)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
    free(coeffs1);
    free(coeffs2);
    free(result);

    MPI_Finalize();
}

int main()
{
    mpi_karatsuba();
    mpi_classic();
    return 0;
}
