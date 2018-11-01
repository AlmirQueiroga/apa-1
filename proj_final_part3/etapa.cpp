#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cmath>
#include <numeric>

#define MAX_TRY 2000
#define INF std::numeric_limits<int>::max()

using namespace std;

vector<int> caminhoG;
int alfa = 0;
vector<int> s;

//Calcula o valor do caminho presente no ciclo presente em resultados
int calcularValorCaminho(std::vector<pair<int, int>> p[], vector<int> caminho, int size){
    int soma = 0;

    for(int i = 0, j = 1; j < caminho.size(); i++, j++){
        soma += p[caminho[i]][caminho[j]].first;
    }

    soma += p[caminho[0]][caminho[size - 1]].first;

    return soma;
}

//movimenta�ao de vizinhan�a utilizando swap
void swapVizinhanca(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
 /* cout << "Swap" << endl;
  for(int i = 0; i < caminho.size(); i++)
  	cout << caminho[i] << " ";
  cout << endl;*/
    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor;
    int menor;


    menor = calcularValorCaminho(p, caminhoaux, size);
    for(int i = 0; i < caminhoaux.size(); i++){
       // for(int j = i + 1; j < caminhoaux.size(); j++){
            caminhoaux = caminho;
            swap(caminhoaux[i], caminhoaux[8]);

            if(calcularValorCaminho(p, caminhoaux, size) < menor){
                menor = calcularValorCaminho(p, caminhoaux, size);
                caminhomenor = caminhoaux;

                cout << calcularValorCaminho(p, caminhoaux, size) << endl;
                for(int k = 0; k < caminhoaux.size(); k++)
                    cout << caminhoaux[k] << " ";
                cout << endl;
            }
        //}
    }
    
    caminho = caminhomenor;
}

//movimenta�ao de vizinhan�a utilizando 2-opt
void reInsertion(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
   // cout << "ReInsertion" << endl;
   /* for(int i = 0; i < caminho.size(); i++)
    	cout << caminho[i] << " ";
    cout << endl;*/
    srand (time(NULL));
    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor;
    int menor;
    int n1;
    int n2;
    int i = 0;

    while(i < MAX_TRY){
        caminhoaux = caminho;
        n1 = rand() % (size - 1);
        n2 = rand() % (size - 1);

        if(n1 == 0)
            n1++;
        if(n2 == 0)
            n2++;

        while(abs(n1 - n2) < 4){
            n2 = rand() % (size - 1);
            if(n2 == 0)
                n2++;
        }

        if(n2 < n1){
            int aux = n1;
            n1 = n2;
            n2 = aux;
        }

        while(n1+3 != n2){
            swap(caminhoaux[n1], caminhoaux[n1 +1]);
            n1++;
        }

        if(i == 0){
            menor = calcularValorCaminho(p, caminhoaux, size);
            i++;
            continue;
        }

        if(calcularValorCaminho(p, caminhoaux, size) < menor){
            menor = calcularValorCaminho(p, caminhoaux, size);
            caminhomenor = caminhoaux;

            cout << calcularValorCaminho(p, caminhoaux, size) << endl;
            for(int i = 0; i < caminhoaux.size(); i++)
                cout << caminhoaux[i] << " ";
            cout << endl;
        }

        i++;
    }
    caminho = caminhomenor;
}

void vnd(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int x = 0;
    vector<int> caminhoaux = caminho;
    while(x < 2){
        if(!x)
            swapVizinhanca(p, caminhoaux, size);
        cout << "---------------------" << endl;
        if(x)
            //reInsertion(p, caminhoaux, size);

        if(calcularValorCaminho(p, caminhoaux, size) < calcularValorCaminho(p, caminho, size)){
            caminho = caminhoaux;
            x = 0;
        }
        else
            x++;
    }
}

//verifica se um dado vertice esta contido na atual solu�ao
int estaContido(int a){
    for(int i = 0; i < caminhoG.size(); i++){
        if(a == caminhoG[i])
            return 1;
    }
    return 0;
}

//Metodo do vizinho mais proximo
void construir(std::vector<pair<int, int>> p[], int size){
    std::vector<pair<int, int>>* paux = p;
    int vertice = 0;
    caminhoG.push_back(0);
    while(1){
        sort(paux[vertice].begin(), paux[vertice].begin() + size);
        for(int i = 0; i < size; i++){
            if(p[vertice][i].first != 0 && !estaContido(p[vertice][i].second)){
                caminhoG.push_back(p[vertice][i].second);
                vertice = p[vertice][i].second;
                break;
            }
        }
        if(caminhoG.size() == size)
            break;
    }
}

void construcao(int alfa, vector<pair<int, int>> p[], int size){
    int n = size;
    int aux = 0;
    std::vector<pair<int, int>> paux;
    vector<pair<int, int>> LCR;
    vector<int> aux2;
    int r, vertice, pesov;
    int soma = 0;
    srand(time(NULL));

    for(vertice = 0; vertice < size; vertice++){
        for(pesov = 0; pesov < size; pesov++){
            soma += p[vertice][pesov].first;
        }
        LCR.push_back(make_pair(vertice, soma));
        soma = 0;
    }
    sort(LCR.begin(), LCR.end(), [](const pair<int,int> &left, const pair<int,int> &right) {
        return left.second < right.second;});
    /*
    for (vector<pair<int, int>>::const_iterator iter = LCR.begin();
        iter != LCR.end();
        ++iter)
   {
        cout << "First: "    << iter->first
                << ", Second: " << iter->second << endl;
   }*/

    for(int i = 0; i < size; i++){
        if(n > 1){
            aux = (int)(alfa*n);
        }else{
            aux = 0;
        }
        //cout <<"\naux = " << aux << endl;
        if(aux > 1){
            r = rand() % (aux-1);
        }else{
            r = 0;
        }
        //cout << "\n r = " << r << endl;

        //cout << "\nnumero = " << n << endl;

        vertice = LCR[r].first;
        //cout << vertice << endl;
        LCR.erase(LCR.begin() + r);
        if(n > 0){
            n--;
        }
        aux2.push_back(vertice);
    }
    s = aux2;
}

void GRASP(int GraspMax, std::vector<pair<int, int>> p[], std::vector<pair<int, int>> paux[], int size, vector<int> &caminho){
    int f = INF;
    vector<int> snew;

    for(int i = 0; GraspMax > i; i++){
        for(int j = 0; j < caminho.size(); j++)
    	    cout << caminho[j] << " ";
        cout << endl;
        construcao(alfa, p, size);
        cout << "dps da construcao" << endl;
        for(int j = 0; j < caminho.size(); j++)
    	    cout << caminho[j] << " ";
        cout << endl;
        vnd(paux, caminho, size);
        cout << "dps da vnd" << endl;
        for(int j = 0; j < caminho.size(); j++)
    	    cout << caminho[j] << " ";
        cout << endl;
        if(calcularValorCaminho(paux, caminho, size) < f){
            snew = caminho;
            f = calcularValorCaminho(paux, caminho, size);
        }
    }

    caminho = snew;
    cout << "---------------------------------------\nCaminho final:" << endl;
    for(int j = 0; j < caminho.size(); j++){
    	cout << caminho[j] << " ";
    }
    cout << endl;
    cout << "---------------------------------------\nCusto final:" << endl;
    cout << calcularValorCaminho(paux, caminho, size) << endl;
}

//leitura do arquivo e chamada de fun�oes
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

    int graspmax = 8;
    /*construir(p, size);

    cout << calcularValorCaminho(paux, caminhoG, size) << endl;

    for(int i = 0; i < caminhoG.size(); i++)
        cout << caminhoG[i] << " ";
    cout << endl;

    cout << "Custo Final: " << calcularValorCaminho(paux, vnd(paux, caminhoG, size), size) << endl;
    */
    //construir(p, size);
    vector<pair<int, int>> paux[size] = p; 
    GRASP(graspmax, p, paux, size, s);

    return 0;
}
