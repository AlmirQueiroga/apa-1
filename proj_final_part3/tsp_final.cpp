#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//Calcula o valor do caminho presente no ciclo presente em resultados
int calcularValorCaminho(std::vector<pair<int, int>> p[], vector<int> caminho, int size){
    int soma = 0;

    for(int i = 0, j = 1; j < caminho.size(); i++, j++){
        soma += p[caminho[i]][caminho[j]].first;
    }

    soma += p[caminho[0]][caminho[size - 1]].first;

    return soma;
}

//movimentaçao de vizinhança utilizando swap
int swapVizinhanca(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int mudou = 0;

    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor = caminho;
    int menor = calcularValorCaminho(p, caminho, size);

    for(int i = 0; i < caminho.size(); i++){
    for(int j = i + 1; j < caminho.size(); j++){
        caminhoaux = caminho;
        swap(caminhoaux[i], caminhoaux[j]);

        if(calcularValorCaminho(p, caminhoaux, size) < menor){
            menor = calcularValorCaminho(p, caminhoaux, size);
            caminhomenor = caminhoaux;
            mudou++;
        }
    }
    }

    caminho = caminhomenor;
    return mudou;
    }

//movimentaçao de vizinhança utilizando 2-opt
int reInsertion(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int mudou = 0;

    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor = caminho;
    int menor = calcularValorCaminho(p, caminho, size);

    int n1;
    int n2;

    for(int i = 0; i < caminho.size(); i++){
        for(int j = 0; j < caminho.size(); j++){
            n1 = i;
            n2 = j;

            caminhoaux = caminho;

            if(n1 != n2){
                if(n1 < n2){
                    while(n1+1 != n2){
                        swap(caminhoaux[n1], caminhoaux[n1 +1]);
                        n1++;
                    }
                }else{
                    while(n2+1 != n1){
                    swap(caminhoaux[n2], caminhoaux[n2 +1]);
                    n2++;   
                    }
                }
            }

            if(calcularValorCaminho(p, caminhoaux, size) < menor){
                menor = calcularValorCaminho(p, caminhoaux, size);
                caminhomenor = caminhoaux;
                mudou++;
            }
        }
    }

    caminho = caminhomenor;
    return mudou;
}

vector<int> vnd(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int select = 0;
    vector<int> caminhoaux = caminho;

    while(select < 2){
        switch(select){
            case 0:
                if(swapVizinhanca(p, caminho, size) != 0){
                        select = 0;
                }else{
                    select++;
                }
                break;
            case 1:
                if(reInsertion(p, caminho, size) != 0){
                        select = 0;
                }else{
                    select++;
                }
                break;
            default:
                break;  
        }
    }        
    return caminho;
}

//verifica se um dado vertice esta contido na atual soluçao
int estaContido(int a, vector<int> &caminho){
    for(int i = 0; i < caminho.size(); i++){
        if(a == caminho[i])
            return 1;
    }
    return 0;
}

//Metodo do vizinho mais proximo
void construir(std::vector<pair<int, int>> p[], int size, vector<int> &caminho){
    caminho.clear();
    std::vector<pair<int, int>>* paux = p;

    srand((int)time(0));

    int vertice = rand()%size;
    caminho.push_back(vertice);

    while(1){
        vector <int> LCR;

        sort(paux[vertice].begin(), paux[vertice].begin() + size);

        for(int i = 0; i < paux[vertice].size(); i++){
            if(p[vertice][i].first != 0 && !estaContido(p[vertice][i].second, caminho) && LCR.size() < (alfa * size)+1){
                LCR.push_back(p[vertice][i].second);
            }
        }

        srand((int)time(0));
        vertice = LCR[rand()%(LCR.size())];
        caminho.push_back(vertice);

        if(caminho.size() == size)
            break;
    }
}

void GRASP(vector<pair<int, int>> p[], vector<pair<int, int>> paux[], int size, vector<int> &caminho, int GraspMax, int alfa){
    construir(p, size, caminho);
    vector<int> caminhomenor = caminho;
    int f = calcularValorCaminho(paux, caminho, size);

    for(int i = 0; GraspMax > i; i++){
        construir(p, size, caminho);

        vnd(paux, caminho, size);

        if(calcularValorCaminho(paux, caminho, size) < f){
            caminhomenor = caminho;
            f = calcularValorCaminho(paux, caminho, size);
        }
    }

    caminho = caminhomenor;
    cout << "---------------------------------------\nCaminho final:" << endl;
    for(int j = 0; j < caminho.size(); j++){
        cout << caminho[j] << " ";
    }
    cout << endl;
    cout << "---------------------------------------\nCusto final:" << endl;
    cout << calcularValorCaminho(paux, caminho, size) << endl;
}

//leitura do arquivo e chamada de funçoes
int main(){
    string instancia;

    cout << "digite o nome da instancia" << endl;
    cin >> instancia;

    instancia = "instancias/" + instancia + ".txt";
    //leitura do arquivo
    FILE *fp;
    fp = fopen(instancia.c_str(), "r");

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

    std::vector<pair<int, int>> paux[size] = p;
    vector<int> caminho;

    int GraspMax =10;
    float alfa = 0;

    GRASP(p, paux, size, caminho, GraspMax, alfa);

    return 0;
}
