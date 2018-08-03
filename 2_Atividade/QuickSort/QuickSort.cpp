#include <iostream>
#include <vector>
using namespace std;

void ExibeArray(vector <int> vetor){
    vector<int>::iterator v = vetor.begin();

    while( v != vetor.end()) {
        cout << *v << ", ";
        v++;
    }
    cout << endl << endl;
}

void Swap(vector <int>* a, int i, int j){
    int aux = (*a)[i];
    (*a)[i] = (*a)[j];
    (*a)[j] = aux;
}

int Partition(vector <int>* vetor, int l, int r){
    int i = l - 1, j, p = (*vetor)[r];

    for(j = l; j < r; j++){
        if((*vetor)[j] <= p){
            i++;
            Swap(vetor, i, j);
        }
    }
    Swap(vetor, i+1, r);
    ExibeArray(*vetor);

    return i + 1;
}

void QuickSort(vector <int>* vetor, int l, int r){
    if (l < r){
        int p = Partition(vetor, l, r);
        QuickSort(vetor, l, p -1);
        QuickSort(vetor, p+1, r);
    }
}

int main(){
    vector <int> v {8,7,6,5,4,3,2,1,5,2,3,51,7456,5};

    QuickSort(&v, 0, (v.size() - 1));
    ExibeArray(v);

    return 0;
}
