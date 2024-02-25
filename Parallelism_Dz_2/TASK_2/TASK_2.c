#include "stdio.h"
#include "math.h"
#include "time.h"
#include "omp.h"

const double PI = 3.14159265358979323846;
const double a = -4.0;
const double b = 4.0;
const int nsteps = 40000000;

double cpuSecond()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ((double)ts.tv_sec + (double)ts.tv_nsec * 1.e-9);
}

double func(double x)
{
    return exp(-x * x);
}

double integrate(double (*func)(double), double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += func(a + h * (i + 0.5));

    sum *= h;

    return sum;
}

double integrate_omp(double (*func)(double), double a, double b, int n, int thr)
{
    double h = (b - a) / n;
    double sum = 0.0;

	#pragma omp parallel num_threads(thr)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (n - 1) : (lb + items_per_thread - 1);
        double sumlock = 0.0;
        for (int i = lb; i <= ub; i++)
            sumlock += func(a + h * (i + 0.5));

        #pragma omp atomic
        sum += sumlock;
    }
    sum *= h;

    return sum;
}

double run_serial()
{
    double t = cpuSecond();
    double res = integrate(func, a, b, nsteps);
    t = cpuSecond() - t;
    printf("Result (serial): %.12f; error %.12f\n", res, fabs(res - sqrt(PI)));
    return t;
}

double run_parallel(int thr)
{
    double t = cpuSecond();
    double res = integrate_omp(func, a, b, nsteps, thr);
    t = cpuSecond() - t;
    printf("Result (parallel): %.12f; error %.12f\n", res, fabs(res - sqrt(PI)));
    return t;
}


int main(int argc, char **argv)
{
    FILE *file = fopen("result.txt", "w");
	
	printf("Integration f(x) on [%.12f, %.12f], nsteps = %d\n", a, b, nsteps);
	fprintf(file, "%d\n", nsteps);
	
    double tserial = run_serial();
	printf("Execution time (serial): %.6f\n\n", tserial);
	fprintf(file, "%.6f\n", tserial);
	
    double tparallel = 0.0;
	
	for (int i = 1; i <= 40; i++)
	{
		if (i == 1 || i == 2 || i == 4 || i == 7 || i == 8 || i == 16 || i == 20 || i == 40)
		{
			tparallel = run_parallel(i);
			printf("Execution time (parallel) on %d thread(s): %.6f\n", i, tparallel);
			printf("Speedup: %.2f\n\n", tserial / tparallel);
			fprintf(file, "%.6f\n", tparallel);
		}
	}
	
	fclose(file);
    return 0;
}