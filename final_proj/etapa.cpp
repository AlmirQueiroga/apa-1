#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cmath>

#define MAX_TRY 10000

# define INF std::numeric_limits<int>::max()

using namespace std;

vector<int> caminhoG;

//Calcula o valor do caminho presente no ciclo presente em resultados
int calcularValorCaminho(std::vector<pair<int, int>> p[], vector<int> caminho){
    int soma = 0;

    for(int i = 0, j = 1; j < caminho.size(); i++, j++){
        soma += p[caminho[i]][caminho[j]].first;
    }

    soma += p[caminho[0]][caminho[28]].first;

    return soma;
}

//movimentaçao de vizinhança utilizando swap
void swapVizinhanca(std::vector<pair<int, int>> p[], vector<int> &caminho){
  srand (time(NULL));
  vector<int> caminhoaux = caminho;
  vector<int> caminhomenor;
  int menor;
  int n1;
  int n2;
  int i = 0;

  while(i < MAX_TRY){
    caminhoaux = caminho;
    n1 = rand() % 28;
    n2 = rand() % 28;

    while(n1 == n2)
        n2 = rand() % 28;

    if(n1 == 0)
        n1++;
    if(n2 == 0)
        n2++;

    swap(caminhoaux[n1], caminhoaux[n2]);

    if(i == 0){
        menor = calcularValorCaminho(p, caminhoaux);
        i++;
        continue;
    }

    if(calcularValorCaminho(p, caminhoaux) < menor){
        menor = calcularValorCaminho(p, caminhoaux);
        caminhomenor = caminhoaux;

        cout << calcularValorCaminho(p, caminhoaux) << endl;
        cout << n1 << " " << n2<< endl;
        for(int i = 0; i < caminhoaux.size(); i++)
            cout << caminhoaux[i] << " ";
        cout << endl;
    }
    i++;
  }
  caminho = caminhomenor;
}

//movimentaçao de vizinhança utilizando 2-opt
void reInsertion(std::vector<pair<int, int>> p[], vector<int> &caminho){
    srand (time(NULL));
    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor;
    int menor;
    int n1;
    int n2;
    int i = 0;

    while(i < MAX_TRY){
        caminhoaux = caminho;
        n1 = rand() % 28;
        n2 = rand() % 28;

        if(n1 == 0)
            n1++;
        if(n2 == 0)
            n2++;

        if(n2 < n1){
            int aux = n1;
            n1 = n2;
            n2 = aux;
        }

        while(n1 != n2){
            swap(caminhoaux[n1], caminhoaux[n1 + 1]);
            n1++;
        }

        if(i == 0){
            menor = calcularValorCaminho(p, caminhoaux);
            i++;
            continue;
        }

        if(calcularValorCaminho(p, caminhoaux) < menor){
            menor = calcularValorCaminho(p, caminhoaux);
            caminhomenor = caminhoaux;

            cout << calcularValorCaminho(p, caminhoaux) << endl;
            cout << n1 << " " << n2<< endl;
            for(int i = 0; i < caminhoaux.size(); i++)
                cout << caminhoaux[i] << " ";
            cout << endl;
        }

        i++;
    }
    caminho = caminhomenor;
}

void vnd(std::vector<pair<int, int>> p[], vector<int> &caminho){
    int x = 0;
    vector<int> caminhoaux = caminho;
    while(x < 2){
        if(!x)
            swapVizinhanca(p, caminhoaux);
        cout << "---------------------" << endl;
        if(x)
            reInsertion(p, caminhoaux);

        if(calcularValorCaminho(p, caminhoaux) < calcularValorCaminho(p, caminho)){
            caminho = caminhoaux;
            x = 0;
        }
        else
            x++;
    }
}

//verifica se um dado vertice esta contido na atual soluçao
int estaContido(int a){
    for(int i = 0; i < caminhoG.size(); i++){
        if(a == caminhoG[i])
            return 1;
    }
    return 0;
}

//Metodo do vizinho mais proximo
void construir(std::vector<pair<int, int>> p[]){
    int vertice = 0;
    caminhoG.push_back(0);
    while(1){
        sort(p[vertice].begin(), p[vertice].begin() + 29);
        for(int i = 0; i < 29; i++){
            if(p[vertice][i].first != 0 && !estaContido(p[vertice][i].second)){
                caminhoG.push_back(p[vertice][i].second);
                vertice = p[vertice][i].second;
                break;
            }
        }
        if(caminhoG.size() == 29)
            break;
    }
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

    /*vector<int> caminho = caminhoG;
    swapVizinhanca(p, caminho);

    for(int i = 0; i < caminhoG.size(); i++)
        cout << caminhoG[i] << " ";
    cout << endl;
    for(int i = 0; i < caminho.size(); i++)
        cout << caminho[i] << " ";
*/
    cout << calcularValorCaminho(p, caminhoG) << endl;
    for(int i = 0; i < caminhoG.size(); i++)
        cout << caminhoG[i] << " ";
    cout << endl;

    vnd(p, caminhoG);

    cout << "Custo Final: " << calcularValorCaminho(p, caminhoG) << endl;

    return 0;
}
