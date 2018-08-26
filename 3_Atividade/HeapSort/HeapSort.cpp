#include <iostream>

int tamanho = NULL;
int comprimento = 11;

void exibe(int a[]){
    for(int j = 0; j < comprimento; j++){
        if(j == comprimento-1){
            std::cout << a[j] << std::endl;
            continue;
        }
        std::cout << a[j] << ", ";
    }
}

int Pai(int i){
    if(i = 0)
        return 0;

    return (i - 1)/2;
}

int FilhoEsquerdo(int i){
    return 2*i + 1;
}

int FilhoDireito(int i){
    return 2*i + 2;
}

void MaxHeapify(int a[], int i){
    int l = FilhoEsquerdo(i);
    int r = FilhoDireito(i);

    int maior = i;

    if(l < tamanho && a[l] > a[maior])
        maior = l;
    
    if(r < tamanho && a[r] > a[maior])
        maior = r;

    if(maior != i){
        std::swap(a[i], a[maior]);
        MaxHeapify(a, maior);
    }
}

void BuildMaxHeap(int a[]){
    tamanho = comprimento;
    for(int i = (comprimento - 1)/2; i >= 0; i--){
        MaxHeapify(a, i);
    }
}

void HeapSort(int a[]){
    BuildMaxHeap(a);

    for(int i = comprimento - 1; i > 0; i--){
        std::swap(a[0], a[i]);
        tamanho--;
        MaxHeapify(a, 0);
    }
}

int main(int argc, char const *argv[])
{
    int a[11] ={1, 16, 5, 30, 27, 17, 20, 2, 57, 3, 90};

    HeapSort(a);
    exibe(a);
    return 0;
}
