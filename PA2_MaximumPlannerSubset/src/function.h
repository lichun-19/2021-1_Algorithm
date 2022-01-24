//
// Created by Phoebe Lu on 2021/11/27.
//

#ifndef ALG_PA2_FUNCTION_H
#define ALG_PA2_FUNCTION_H
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void GetInPuts(int n, int *pairs, istream &fin, ostream &fout);
int Max(int a, int b);
void CheckErr(istream &fin, ostream &fout);

class MaxPlanner{

public:
    MaxPlanner(int outN2, istream &fin, ostream &fout);
    int Compute_Num(int start, int end, int *pairs);
    void Compute_Chord(int start, int end, int *pairs);
    ~MaxPlanner();
    void PrintDetail(int *pairs, istream &fin, ostream &fout);

private:
    vector<int> pairDetail;
    int **M;
    int n2;
};



#endif //ALG_PA2_FUNCTION_H

