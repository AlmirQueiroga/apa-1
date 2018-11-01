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

#define PII pair<int,int>
using namespace std;

int main() {
    vector<pair<int,int>> v;
    v.push_back(PII(1,2));
    v.push_back(PII(2,4));
    v.push_back(PII(5,6));
    v.push_back(PII(4,6));
    v.push_back(PII(3,1));
    v.push_back(PII(6,3));
    int i = 1;
    sort(v.begin(), v.end(), [](const pair<int,int> &left, const pair<int,int> &right) {
        return left.second < right.second;});
    for (vector<pair<int, int>>::const_iterator iter = v.begin();
        iter != v.end();
        ++iter)
   {
        cout << "First: "    << iter->first
                << ", Second: " << iter->second << endl;
   }
    //cout << accumulate(v.begin(),v.end(),0,[](auto &a, auto &b){return a + b.second;}) << endl;
    return 0;
}

/*
while(LC.size() != 0){
        sort(paux[vertice].begin(), (paux[vertice].begin() + paux->size()));
        tmin = p[vertice][0].first;
        tmax = p[vertice][size - 1].first;

        if(estaContidoLC(vertice)){
            for(int j = 0; p[vertice].size() > 0; j++){
                if(p[vertice][j].first <= tmin + alfa*(tmax - tmin)){
                    LCR.push_back(p[vertice][j].second);
                    vertice = p[vertice][j].second;
                    break;
                }
            }
            r = rand() % (LCR.size() - 1);
            s.push_back(LCR[r]);
            LC.erase(remove(LC.begin(), LC.end(), r), LC.end());
        }
    }
*/