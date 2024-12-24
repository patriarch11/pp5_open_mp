#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int sum(int *array, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    return sum;
}

int main()
{
    const size_t array_lenght = 5000000;
    const unsigned int theads_count = 8;
    /*
    виділяємо пам'ять під "масив" саме так,
    бо не факт що при великому розмірі стандартний масив поміститься в стекі
    */
    int *array = (int *)malloc(array_lenght * sizeof(int));
    int chunk_size = (int)ceil((double)array_lenght / (double)theads_count);

    for (size_t i = 0; i < array_lenght; i++)
    {
        array[i] = i + 1;
    }

    int sync_calculated_sum = sum(array, array_lenght);

    printf("Синхронно порахована сума масиву: %d\n", sync_calculated_sum);

    int concurrently_calculated_sum = 0;

/*
за допомогою директиви for, кожні ітерація буде виконуватись в окремому потоці,
їх к-ть задали параметром num_threads
щоб не використовувати критичну зону "напряму" використовуємо reduction
для сумуваання результатів кожного потоку
*/
#pragma omp for reduction(+ : concurently_calculated_sum) num_threads(theads_count)
    for (int i = 0; i < theads_count; i++)
    {
        int start = i * chunk_size;
        int end = (i + 1) * chunk_size;
        if (end > array_lenght)
        {
            end = array_lenght;
        }
        for (int j = start; j < end; j++)
        {
            concurrently_calculated_sum += array[j];
        }
    }

    printf("Паралельно порахована сума масиву: %d\n", concurrently_calculated_sum);
    free(array);
    return 0;
}