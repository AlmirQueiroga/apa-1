#include <iostream>
#define n 8
#define k 5


int main(int argc, char const *argv[])
{
    int a[n] = {2, 5, 3, 0, 2, 3, 0, 3};
    int b[n], c[k+1] = {0};

    for(int i = 0; i < n; i++){
        c[a[i]]++;
    }

    for(int i = 1; i <= k; i++){
        c[i] += c[i-1];
    }

    for(int i = n - 1; i >= 0; i--){
        b[--c[a[i]]] = a[i];
    }
    
    for(int i = 0; i < n; i++){
        if(i == n-1){
            std::cout << b[i] << std::endl;
            continue;
        }
        std::cout << b[i] << ", ";
    }

    return 0;
}
