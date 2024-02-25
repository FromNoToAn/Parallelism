#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"
#include "inttypes.h"


double cpuSecond()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ((double)ts.tv_sec + (double)ts.tv_nsec * 1.e-9);
}

/*
 * matrix_vector_product: Вычисление произведения матрицы-вектора c[m] = a[m][n] * b[n]
 */
void matrix_vector_product(double *a, double *b, double *c, size_t m, size_t n)
{
    for (int i = 0; i < m; i++)
    {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
            c[i] += a[i * n + j] * b[j];
    }
}

void matrix_vector_product_omp(double *a, double *b, double *c, size_t m, size_t n, size_t thr)
{
    #pragma omp parallel num_threads(thr)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = m / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);
        for (int i = lb; i <= ub; i++)
        {
            c[i] = 0.0;
            for (int j = 0; j < n; j++)
                c[i] += a[i * n + j] * b[j];
        }
    }
}

double run_serial(size_t n, size_t m)
{
    double *a, *b, *c;
    a = (double*)malloc(sizeof(*a) * m * n);
    b = (double*)malloc(sizeof(*b) * n);
    c = (double*)malloc(sizeof(*c) * m);

    if (a == NULL || b == NULL || c == NULL)
    {
        free(a);
        free(b);
        free(c);
        printf("Error allocate memory!\n");
        exit(1);
    }

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
            a[i * n + j] = i + j;
    }

    for (size_t j = 0; j < n; j++)
        b[j] = j;

    double t = cpuSecond();
    matrix_vector_product(a, b, c, m, n);
    t = cpuSecond() - t;

    printf("Elapsed time (serial): %.6f sec.\n", t);
    free(a);
    free(b);
    free(c);
	return t;
}

double run_parallel(size_t n, size_t m, size_t thr)
{
    double *a, *b, *c;
    // Выделение памяти для двумерного массива a[m, n]
    a = malloc(sizeof(*a) * m * n);
    b = malloc(sizeof(*b) * n);
    c = malloc(sizeof(*c) * m);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            a[i * n + j] = i + j;
    }

    for (int j = 0; j < n; j++)
        b[j] = j;
    double t = cpuSecond();
    matrix_vector_product_omp(a, b, c, m, n, thr);
    t = cpuSecond() - t;
	#pragma omp critical
	{
		printf("Elapsed time (parallel) on %lu thread(s): %.6f sec.\n", thr, t);
	}
    free(a);
    free(b);
    free(c);
	return t;
}

int main(int argc, char **argv)
{
    int size_koeff = 2;
	FILE *file = fopen("result.txt", "w");
	
	for (int len = 1; len <= size_koeff; len++)
	{
		double t = 0.0;
		int n = len * 20000, m = len * 20000;
		printf("Matrix-vector product (c[m] = a[m, n] * b[n]; m = %d, n = %d)\n", m, n);
		printf("Used memory: %" PRIu64 " MiB\n", ((m * n + m + n) * sizeof(double)) >> 20);
		fprintf(file, "%d %d\n", n, m);
		t = run_serial(n, m);
		fprintf(file, "%.6f\n", t);
		for (int i = 1; i <= 40; i++)
		{
			if (i == 1 || i == 2 || i == 4 || i == 7 || i == 8 || i == 16 || i == 20 || i == 40)
			{
				t = run_parallel(n, m, i);
				fprintf(file, "%.6f\n", t);
			}
		}
		printf("\n");
	}
	
	fclose(file);
    return 0;
}
