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
    fp = fopen("bays29.txt", "r");

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

	std::vector<pair<int, int>> p[size];

    while(1){
        int  i = qLines;
        fgets(line, 999, fp);

        if (feof(fp))
            break;
        
        int index = 0;

        token = strtok(line, " ");

        while(token!=NULL){
            p[qLines].push_back(make_pair(atoi(token), index));
            
            token = strtok(NULL, " ");
            index++;
        }
        qLines++;
    }
    fclose(fp);//fim da leitura
/*
    int minimumCost;
    int raiz = 0;

    minimumCost = prim(adj, raiz, size);

    cout << minimumCost << endl;
  */  

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){ 
            cout << p[i][j].second << " ";
        }       
        cout << endl;
    }
    return 0;
}