#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 

# define INF std::numeric_limits<int>::max()

using namespace std;

int prim(vector<pair<int , int>> adj[], int raiz, int N){
    int chave[N];
    int pai[N];
    for(int i = 0; i < N; i++){
        chave[i] = INF;
        pai[i] = -1;
    }
    
    std::vector<bool> inMST(N, false);

    priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq;
    pq.push(make_pair(0, raiz)); 

    chave[raiz] = 0;

    while(!pq.empty()){
        int u = pq.top().second; 
        pq.pop(); 

        inMST[u] = true;

        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if(inMST[v] == false && w < chave[v]){
                pai[v] = u;
                chave[v] = w;  
                pq.push(make_pair(chave[v], v));
                cout << chave[v] << endl << endl;
            }
        }
    }

    int soma = 0;
    for(int i = 0; i < N; i++){
        soma += chave[i];  
        cout<<soma<<endl;
    }
    return soma;
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

	std::vector<pair<int, int>> adj[size];

    std::vector<int> v[size];

    while(1){
        int  i = qLines;
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }
        token = strtok(line, "\t");
        while(token!=NULL){
        	int index = ++i;
            a[qLines][index] = atoi(token);
            adj[qLines].push_back(make_pair(index, a[qLines][index])); 
			adj[index].push_back(make_pair(qLines, a[qLines][index])); 
            
            token = strtok(NULL, "\t");
        }
        qLines++;
    }
    fclose(fp);//fim da leitura

    int minimumCost;
    int raiz = 0;

    minimumCost = prim(adj, raiz, size);

    cout << minimumCost << endl;
    
    return 0;
}