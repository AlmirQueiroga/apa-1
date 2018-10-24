#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

# define INF std::numeric_limits<int>::max()

using namespace std;

vector<int> resultado;

//verifica se um dado vertice esta contido na atual soluçao
int estaContido(int a){
    for(int i = 0; i < resultado.size(); i++){
        if(a == resultado[i])
            return 1;
    }
    return 0;
}

//Metodo do vizinho mais proximo
void construir(std::vector<pair<int, int>> p[]){
    int vertice = 0;
    resultado.push_back(0);
    while(1){
        sort(p[vertice].begin(), p[vertice].begin() + 29);
        for(int i = 0; i < 29; i++){
            if(p[vertice][i].first != 0 && !estaContido(p[vertice][i].second)){
                resultado.push_back(p[vertice][i].second);
                vertice = p[vertice][i].second;
                break;
            }
        }
        if(resultado.size() == 29)
            break;
    }
}

//Calcula o valor do caminho presente no ciclo presente em resultados
int calcularValorCaminho(std::vector<pair<int, int>> p[]){
    int soma = 0;

    for(int i = 0, j = 1; j < resultado.size(); i++, j++){
        soma += p[resultado[i]][resultado[i]].first;
    }

    soma += p[resultado[0]][resultado[28]].first;

    return soma;
}

//leitura do arquivo e chamada de funçoes
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
        //cout << qLines << endl;
        while(token!=NULL){
            p[qLines].push_back(make_pair(atoi(token), index));
            //cout << index << "# :" << atoi(token) << " ";
            token = strtok(NULL, " ");
            index++;
        }
        qLines++;
    }

    fclose(fp);//fim da leitura

    construir(p);
    calcularValorCaminho(p);

    return 0;
}
