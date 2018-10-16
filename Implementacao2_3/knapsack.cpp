#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int knapSack(int W, int wt[], int val[], int n)
{
   int i, w;
   int K[n+1][W+1];

   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }

   return K[n][W];
}

int main(){
    //leitura do arquivo
    FILE *fp;
    fp = fopen("mochila01.txt", "r");

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

    cout << x << endl;

    return 0;
}
