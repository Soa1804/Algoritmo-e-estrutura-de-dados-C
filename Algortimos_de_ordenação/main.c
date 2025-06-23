#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_VALUE 1000000

// ----------- FUNÇÕES DE GERAÇÃO E MEDIÇÃO -----------

void generateRandomArray(int *array, int size, int maxValue) {
    for (int i = 0; i < size; i++)
        array[i] = rand() % maxValue;
}

void copyArray(int *src, int *dest, int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}

double measureExecutionTime(void (*sortFunc)(int *, int), int *array, int size) {
    clock_t start = clock();
    sortFunc(array, size);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

// ----------- ALGORITMOS DE ORDENAÇÃO -----------

void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
}

void selectionSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++)
            if (array[j] < array[min])
                min = j;
        if (min != i) {
            int tmp = array[i];
            array[i] = array[min];
            array[min] = tmp;
        }
    }
}

void insertionSort(int *array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
            array[j + 1] = array[j--];
        array[j + 1] = key;
    }
}

void merge(int *array, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int *L = malloc(sizeof(int) * n1);
    int *R = malloc(sizeof(int) * n2);
    for (int i = 0; i < n1; i++) L[i] = array[left + i];
    for (int i = 0; i < n2; i++) R[i] = array[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        array[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSortRec(int *array, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortRec(array, left, mid);
        mergeSortRec(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void mergeSort(int *array, int size) {
    mergeSortRec(array, 0, size - 1);
}

void quickSwap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int quickPartition(int *array, int low, int high) {
    int pivot = array[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (array[j] < pivot)
            quickSwap(&array[++i], &array[j]);
    quickSwap(&array[i + 1], &array[high]);
    return i + 1;
}

void quickSortRec(int *array, int low, int high) {
    if (low < high) {
        int pi = quickPartition(array, low, high);
        quickSortRec(array, low, pi - 1);
        quickSortRec(array, pi + 1, high);
    }
}

void quickSort(int *array, int size) {
    quickSortRec(array, 0, size - 1);
}

void countingSort(int *array, int size) {
    if (size <= 0) return;
    int max = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > max) max = array[i];
    int *count = calloc(max + 1, sizeof(int));
    int *output = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) count[array[i]]++;
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--) output[--count[array[i]]] = array[i];
    memcpy(array, output, sizeof(int) * size);
    free(count); free(output);
}

int getMax(int *array, int size) {
    int max = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > max) max = array[i];
    return max;
}

void countingSortByDigit(int *array, int size, int exp) {
    int output[size], count[10] = {0};
    for (int i = 0; i < size; i++) count[(array[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--)
        output[--count[(array[i] / exp) % 10]] = array[i];
    memcpy(array, output, sizeof(int) * size);
}

void radixSort(int *array, int size) {
    int max = getMax(array, size);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortByDigit(array, size, exp);
}

// ----------- EXECUÇÃO DOS TESTES -----------

void executarTestes(const char *nome, void (*sortFunc)(int *, int)) {
    int tamanhos[] = {5000, 10000, 25000, 50000, 100000, 250000, 500000};
    printf("\n### Testes para %s ###\n", nome);
    for (int i = 0; i < 7; i++) {
        int size = tamanhos[i];
        int *original = malloc(sizeof(int) * size);
        int *copia = malloc(sizeof(int) * size);
        generateRandomArray(original, size, MAX_VALUE);
        copyArray(original, copia, size);
        double tempo = measureExecutionTime(sortFunc, copia, size);
        printf("Tamanho %d: %.3f segundos\n", size, tempo);
        free(original);
        free(copia);
    }
}

int main() {
    srand(time(NULL));
    executarTestes("Bubble Sort", bubbleSort);
    executarTestes("Selection Sort", selectionSort);
    executarTestes("Insertion Sort", insertionSort);
    executarTestes("Merge Sort", mergeSort);
    executarTestes("Quick Sort", quickSort);
    executarTestes("Counting Sort", countingSort);
    executarTestes("Radix Sort", radixSort);
    return 0;
}