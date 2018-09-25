#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>

using namespace std;
const int MAX = 10000;
int root[MAX];
pair <int, pair<int, int>> p[MAX];
 
void make_set(){
    for(int i = 0; i < MAX; ++i)
        root[i] = i;
}
 
int find_set(int x){
    while(root[x] != x){
        root[x] = root[root[x]];
        x = root[x];
    }

    return x;
}
 
void union1(int x, int y){
    int u = find_set(x);
    int v = find_set(y);
    root[u] = root[v];
}
 
int kruskal(pair<int, pair<int, int>> p[], int aresta){
    int x, y;
    int cost, minimumCost = 0;

    make_set();
    sort(p, p + aresta);

    for(int i = 0; i < aresta; ++i){
        x = p[i].second.first;
        y = p[i].second.second;
    
        cost = p[i].first;

        if(find_set(x) != find_set(y))
        {
            minimumCost += cost;
            union1(x, y);
        }    
    }
    return minimumCost;
}
 
int main(){
    //leitura do arquivo
    FILE *fp;
    fp = fopen("instancias/dij10.txt", "r");

    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }
    
    int qLines = 0;
    int size;
    int tamanho;
    char line[999];
    char *token;

    fgets(line, 999,fp);

    size = atoi(line);

    int a[size][size] = {0};

    while(1){
        int  i = qLines;
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }
        token = strtok(line, "\t");
        while(token!=NULL){
            a[qLines][++i] = atoi(token);
            token = strtok(NULL, "\t");
        }
        qLines++;
    }
    fclose(fp);//fim da leitura

    pair <int, pair<int, int> > p[MAX];
    int aresta;
    for(int i = 0; i < size; i++){
        aresta += i;
    }

    int u = 0;
    for(int i = 0; i < size - 1;++i){
        for(int j = i + 1; j < size; ++j){
            p[u] = make_pair(a[i][j], make_pair(i, j));
            u++;
        }
    }


    int minimumCost;
    minimumCost = kruskal(p, aresta);
    cout << minimumCost << endl;
    
    return 0;
}