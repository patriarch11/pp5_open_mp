#include <stdio.h>
#include <stdlib.h>

int sum(int *array, size_t n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    return sum;
}

void print_array(int *array, size_t n)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
    {
        if (i + 1 == n) {
            printf("%d", array[i]);
        } else {
            printf("%d, ", array[i]);
        }
    }
    printf(" ]\n");
}

int wave_sum(int *array, size_t n)
{
    printf("%d", n);
    print_array(array, n);
    int half = n / 2;

    if (half == 0)
    {
        return array[0];
    }

    int *wave_array = (int *)malloc(half * sizeof(int));

    for (int i = 0; i < half; i++)
    {
        if (i == half - 1)
        {
            wave_array[i] = array[i];
        }
        else
        {
            wave_array[i] = array[i] + array[n - 1 - i];
        }
    }
    return wave_sum(wave_array, half);
}

int main()
{
    const size_t array_length = 6;
    int *array = (int *)malloc(array_length * sizeof(int));

    for (int i = 0; i < array_length; i++)
    {
        array[i] = i + 1;
    }

    printf("Синхронно порахована сума масиву: %d\n", sum(array, array_length));
    printf("Хвилями %d\n", wave_sum(array, array_length));

    printf("%d", 1 / 2);
    return 0;
}