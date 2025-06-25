#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_VALUE 1000000

// ----------- FUNÇÕES DE GERAÇÃO E MEDIÇÃO -----------

void generateRandomArray(int *array, int size, int maxValue)
    //int *array é um ponteiro que vai apontar para o primeiro elemento de um array que será criado;
    //int size será para definir o tamanho desse array
    //int maxValue é o limitador para o valor máximo dos números gerados 
    {
    for (int i = 0; i < size; i++) //será um laço que vai de i=0 até i= size-1, gerando o array
        array[i] = rand() % maxValue; //Aqui é onde será gerado o número aleátorio de i=0 até i= size-1
    
}

void copyArray(int *src, int *dest, int size)
    //int *scr será um ponteiro para um array de origem, que vai ser de onde os dados vão ser copiados
    //ind *dest será um ponteiro de destino, para onde os dados copiados irão
    //int size será o tamanho de elementos a serem copiados
    {
    for (int i = 0; i < size; i++)//O laço incrementa de i=0 até i<size, adicionando sempre de 1 em 1
        dest[i] = src[i]; //Vai atribuir o valor da posição do array scr a mesma possição em dest
}

double measureExecutionTime(void (*sortFunc)(int *, int), int *array, int size) 
    //void (*sortFunc)(int *, int) é um ponteiro para a função, onde recebe um int *(array) e um int (Tamanho)
    {
    clock_t start = clock(); //conta os ticks de clock da cpu desde da hora que o programa começa a rodar
    sortFunc(array, size);
    return (double)(clock() - start) / CLOCKS_PER_SEC;//aqui será a divisão entre o tempo gasto pelos clocks da cpu por segundo
}

// ----------- ALGORITMOS DE ORDENAÇÃO -----------

// ----------- BUBBLE SORT -----------

void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) //Aqui é a quantidade de vezes que o algoritmo irá passar no array, fazendo o maior elemento subir para a última posição
        for (int j = 0; j < size - i - 1; j++) //Aqui é onde  vai comparar os pares adjacentes, e vai diminuindo a cada passada pois os elementos maiores já estão posicionados no final
            if (array[j] > array[j + 1]) //Aqui é onde se o elemento da esquerda for maior que o da direita vai ser trocado
             {
                int tmp = array[j]; //Variável temporária para colocar de array[j]
                array[j] = array[j + 1]; //Define array[j] como o novo guarda do valor de array[j+1]
                array[j + 1] = tmp; //Define array[j+1] como novo local para o valor que inicialmente estava em array[j] que foi enviado para a variável temp
            }
}

// ----------- SELECTION SORT -----------
void selectionSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) //Vai definir a posição onde o menor valor da sublista a partir da posição i
     {
        int min = i;
        for (int j = i + 1; j < size; j++) //Após inicializar em i, vai pecorrer todos os elementos a partir de i+1 até o final
            if (array[j] < array[min])
                min = j; //Se encontrar um valor menor que i, o valor vai ser atualizado para j, e assim por diante
        if (min != i)//Se o valor não estava na posição correta então faz a troca
         {
            int tmp = array[i];//Variável temporária para armazenar o valor de array[i]
            array[i] = array[min];//Array[i] vai assumir o valor de array[min]
            array[min] = tmp;//Array[min] se torna o "Novo array[i]", assim por diante
        }
    }
}

// ----------- INSERTION SORT -----------
void insertionSort(int *array, int size) {
    for (int i = 1; i < size; i++) //Começa de i=1 e não de i=0, pois o algoritmo já considera o primeiro como ordenado e vai percorrendo até size-1
     {
        int key = array[i]; //Vai guarda em uma chave, o valor de array[i], que vai ser comparado e inserido na sublista ordenada à esquerda
        int j = i - 1; //Vai comparar a key com os elementos à esquerda, que é a parte ordenada
        while (j >= 0 && array[j] > key) //Vai deslocar os elementos maiores para a direita
            array[j + 1] = array[j--]; //Vai copiando o array[j] para array[j+1], e vai movendo os elementos maiores que a key, para frente dela
        array[j + 1] = key; // Saindo do while, a nova key vai ser o menor elemento a direita da key anterior
    }
}

// ----------- PARTES DO MERGE SORTE E ELE -----------
void merge(int *array, int left, int mid, int right)
    //int *array: ponteiro para o array principal
    //int left: índice inicial da subparte esquerda
    //int mid: índice do meio (último elemento da subparte esquerda)
    //int right: índice final da subparte direita

    //Em resumo, vai devidir o array em dois e vai ordenando as partes individualmente
 {
    int n1 = mid - left + 1, n2 = right - mid; //Vai definir o tamanho das duas metades
    int *L = malloc(sizeof(int) * n1);//Guarda a metade esquerda
    int *R = malloc(sizeof(int) * n2);//Guarda a metade direita
    for (int i = 0; i < n1; i++) L[i] = array[left + i];//O vetor L pega os elementos do array[left] até array[mid]
    for (int i = 0; i < n2; i++) R[i] = array[mid + 1 + i];//O vetor R pega os elementos de array[mid+1] até array[right]
    int i = 0, j = 0, k = left;//i pecorre o vetor L, j pecorre o vetor R e k pecorre o array principal
    while (i < n1 && j < n2)
        array[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];//Aqui vai comparar o menor entre os vetores L e R e copia ele para o k
    while (i < n1) array[k++] = L[i++];//Se ainda restam elementos em L, copia todos para o array
    while (j < n2) array[k++] = R[j++];//Parecido com o de cima
    free(L);
    free(R);
}

void mergeSortRec(int *array, int left, int right) {
    if (left < right)//Se a subparte tem mais de um elemento (left < right), a função continua dividindo. caso seja igual, para.
     {
        int mid = (left + right) / 2;//Vai calcular o indice do meio
        mergeSortRec(array, left, mid);//Ordena recursivamente os elementos entre left e mid.
        mergeSortRec(array, mid + 1, right);//Ordena recursivamente os elementos entre mid + 1 e right.
        merge(array, left, mid, right);//Vai chamar a função merge para intercalar as duas subpartes ordenadas, para o array principal
    }
}

void mergeSort(int *array, int size) {
    mergeSortRec(array, 0, size - 1);//Vai chamar a função MergeSortRec, pasando o indice de inicio e de fim
}

// ----------- PARTES DO QUICK SORT E ELE -----------
void quickSwap(int *a, int *b)//*a ponteiro para o primeiro inteiro, e *b é o ponteiro do segundo inteiro
 {
    int t = *a; *a = *b; *b = t;//Atribui o valor de *a à t, atribui o valor de *b para *a fazendo com que b fique no lugar de a, e coloca o valor de a no endereço de b
}

int quickPartition(int *array, int low, int high)
    //int *array: ponteiro para o array que está sendo ordenado.
    //int low: índice inicial da subparte do array.
    //int high: índice final da subparte (onde está o pivô).
 {
    int pivot = array[high], i = low - 1;//Define o pivô como o último elemento da subparte de cima
    for (int j = low; j < high; j++)//Itera sobre a subparte do array, de low até high - 1.
        if (array[j] < pivot)//Para cada elemento menor que o pivô, vai trocar o array[i] com o array[j], puxando o menor valor para a area dos menores
            quickSwap(&array[++i], &array[j]);
    quickSwap(&array[i + 1], &array[high]);//Troca o pivô (array[high]) com array[i + 1], colocando-o na posição correta e definitiva da ordenação.
    return i + 1;//vai retornar o indice onde o pivo foi colocado
}

void quickSortRec(int *array, int low, int high) {
    if (low < high)//Se low>=high significa que tem 0 ou 1 elemento e já está ordenado. Caso for low< high, precisa ser ordenado
         {
        int pi = quickPartition(array, low, high);//Chama a função quickPartition e Retorna o índice pi onde o pivô foi colocado.
        quickSortRec(array, low, pi - 1);//Vai ordenar os elementos antes do pivô
        quickSortRec(array, pi + 1, high);//Vai ordenar os elementos depois do pivô
    }
}

void quickSort(int *array, int size) {
    quickSortRec(array, 0, size - 1);//Inicia o processo de ordenação, passando os parametros de inicio, final do array.
}

// ----------- COUNTING SORT -----------
void countingSort(int *array, int size) {
    if (size <= 0) return; //Se o array tá vazio ou é invalido, retorna a função logo

    int max = array[0];
    for (int i = 1; i < size; i++)//Vai definir o tamanho necessário do array, para o vetor de contagem
        if (array[i] > max) max = array[i];

    int *count = calloc(max + 1, sizeof(int));//Vai armazenar a quantidade de vezes que um número aparece
    int *output = malloc(sizeof(int) * size);//Vai copiar os elementos ordenados, antes de copia eles no original
    for (int i = 0; i < size; i++) count[array[i]]++;//Vai contar cada elemento que for igual e armazenar no indice correspondente no count
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];//Tranforma o vetor de contagem em um vetor de posição final, e agora count[i] informa o último i deve ficar no saída
    for (int i = size - 1; i >= 0; i--) output[--count[array[i]]] = array[i];//Vai preencher o vetor saída com os valores ordenados, pecorrendo de trás para frente para manter a estabilidade e usando --count[array[i]] para descobrir a posição correta de cada valor.
    memcpy(array, output, sizeof(int) * size);//Copia o vetor output (ordenado) para o array original.
    free(count); free(output);
}

//************** ESSE É O NOSSO **************
// ----------- PARTES DO RADIX SORT E ELE -----------
int getMax(int *array, int size) {
    int max = array[0];//Assume que o maior valor tá em array[0], no inicio

    for (int i = 1; i < size; i++)
        if (array[i] > max) max = array[i];//vai pecorrer todo o array, se encontrar um número maior que max, então esse agora é o max

    return max;
}

void countingSortByDigit(int *array, int size, int exp) {
    int output[size], count[10] = {0};//Vai guardar os valores ordenados temporariamente, 0 a 9
    for (int i = 0; i < size; i++) count[(array[i] / exp) % 10]++;//Essa linha extrai o dígito da posição exp de cada número e conta quantas vezes ele aparece.
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];//Vai indicar onde count[d] deve ficar com o último número de d
    for (int i = size - 1; i >= 0; i--)
        output[--count[(array[i] / exp) % 10]] = array[i];//Percorre o array de trás para frente para garantir estabilidade
    memcpy(array, output, sizeof(int) * size);//Copia o vetor output (já ordenado por dígito) de volta para array.
}

void radixSort(int *array, int size) {
    int max = getMax(array, size);//Vai determinar o maior número do array, necessário para saber quantos digitos vão ser processados
    for (int exp = 1; max / exp > 0; exp *= 10)//exp representa a "casa decimal" atual,  A condição max / exp > 0 garante que o loop continue enquanto houver dígitos a serem processados.
        countingSortByDigit(array, size, exp);// Para cada valor de exp, ordena o array com base apenas naquele dígito.
}

// ----------- EXECUÇÃO DOS TESTES -----------

void executarTestes(const char *nome, void (*sortFunc)(int *, int))//Vai mostrar o nome do algoritmo e o ponteiro vai chamar a sua função especifica
 {
    int tamanhos[] = {5000, 10000, 25000, 50000, 100000, 250000, 500000};
    printf("\n---- Testes para %s ----\n", nome);
    for (int i = 0; i < 7; i++) {
        int size = tamanhos[i];// Define o tamanho atual do teste
        int *original = malloc(sizeof(int) * size);//Preencido com valores aleatorios
        int *copia = malloc(sizeof(int) * size);//copia do original que vai ser ordenado
        generateRandomArray(original, size, MAX_VALUE);//preenche o original com valores aleatorios
        copyArray(original, copia, size);//Copia o conteúdo do vetor original para o vetor copia, que será de fato ordenado.
        double tempo = measureExecutionTime(sortFunc, copia, size);//vai medir o tempo da execução de cada teste de cada função
        printf("Tamanho %d: %.3f segundos\n", size, tempo);
        free(original);
        free(copia);
    }
}

// ----------- MAIN -----------

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