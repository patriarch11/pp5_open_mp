#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void print_array(int *array, size_t n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        if (i + 1 == n) {
            printf("%d", array[i]);
        } else {
            printf("%d, ", array[i]);
        }
    }
    printf(" ]\n");
}

int wave_sum(int *array, size_t n) {
    int *current_array = array;
    int current_size = n;
    
    // Масив для зберігання проміжних результатів
    int *temp_array = NULL;
    
    while (current_size > 1) {
        printf("\nПоточний масив розміром %d: ", current_size);
        print_array(current_array, current_size);
        
        int half_size = current_size / 2;
        temp_array = (int *)malloc(half_size * sizeof(int));
        
        // Паралельне обчислення пар
        #pragma omp parallel
        {
            #pragma omp single
            printf("Запущено %d потоків\n", omp_get_num_threads());
            
            #pragma omp for schedule(static)
            for (int i = 0; i < half_size; i++) {
                int thread_num = omp_get_thread_num();
                int pair_sum;
                
                if (i == half_size - 1 && current_size % 2 != 0) {
                    // Якщо непарна кількість елементів, останній елемент переходить без змін
                    pair_sum = current_array[i];
                    printf("Потік %d: елемент %d без пари\n", thread_num, current_array[i]);
                } else {
                    pair_sum = current_array[i] + current_array[current_size - 1 - i];
                    printf("Потік %d: додаємо %d + %d = %d\n", 
                           thread_num, current_array[i], current_array[current_size - 1 - i], pair_sum);
                }
                temp_array[i] = pair_sum;
            }
        }
        
        // Якщо це не перша ітерація, звільняємо пам'ять
        if (current_array != array) {
            free(current_array);
        }
        
        current_array = temp_array;
        current_size = half_size;
    }
    
    int result = current_array[0];
    if (current_array != array) {
        free(current_array);
    }
    
    return result;
}

int main() {
    const size_t array_length = 6;
    int *array = (int *)malloc(array_length * sizeof(int));
    
    // Ініціалізація масиву
    for (int i = 0; i < array_length; i++) {
        array[i] = i + 1;
    }
    
    printf("Початковий масив: ");
    print_array(array, array_length);
    
    // Встановлюємо кількість потоків відповідно до кількості ядер
    omp_set_num_threads(omp_get_num_procs());
    
    int result = wave_sum(array, array_length);
    printf("\nФінальний результат: %d\n", result);
    
    free(array);
    return 0;
}