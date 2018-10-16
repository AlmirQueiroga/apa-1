#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int knapSack(int W, int wt[], int val[], int n){
   int i, w;
   int memo[W+1][n+1];

   for (w = 0; w <= W; w++){
       for (i = 0; i <= n; i++){
           if (i==0 || w==0)
               memo[w][i] = 0;
           else if (w < wt[i-1])
                 memo[w][i] = memo[w][i-1];
           else
                 memo[w][i] = max(val[i-1] + memo[w-wt[i-1]][i-1],  memo[w][i-1]);
       }   
   }

   return memo[W][n];
}

int main(){
    //leitura do arquivo
    FILE *fp;
    fp = fopen("instancias/mochila01.txt", "r");

    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }

    int qLines = 0;
    int items;
    char line[999];
    char *token;
    int weight;

    //pega as duas primeiras informações
    while(1){
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }
        if(qLines == 1)
            break;

        token = strtok(line, " ");

        int k = 0;
        while(token!=NULL){
            if(qLines == 0){
                if(k == 0)
                    items = atoi(token);
                else
                    weight = atoi(token);
            }
            token = strtok(NULL, " ");
            k++;
        }
        qLines++;
    }

    int val[items];
    int wt[items];

    while(1){
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }

        token = strtok(line, " ");

        int k = 0;
        while(token!=NULL){
            if(!k)
                wt[qLines - 1] = atoi(token);
            else
                val[qLines - 1] = atoi(token);

            token = strtok(NULL, " ");
            k++;
        }
        qLines++;
    }
    fclose(fp);//fim da leitura

    int x = knapSack(weight, wt, val, items);

    cout << "valor : " << x << endl;

    return 0;
}
