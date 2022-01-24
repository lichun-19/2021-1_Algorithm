#include <iostream>
#include "function.h"
#include <fstream>
#include <vector>

using namespace std;

//void GetInPuts(int n, int *pairs);
//int Max(int a, int b);
//void CheckErr();
//
//class MaxPlanner{
//
//public:
//    MaxPlanner(int outN2);
//    int Compute_Num(int start, int end, int *pairs);
//    void Compute_Chord(int start, int end, int *pairs);
//    ~MaxPlanner();
//    void PrintDetail(int *pairs);
//
//private:
//    vector<int> pairDetail;
//    int **M;
//    int n2;
//};



int main(int argc, char *argv[]) {
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);


    int N2, n;
//    cout<<"cin n:";
    fin>>N2;
    n=N2/2;
    int *pairs;
    pairs=new int[2*n];
//    cout<<"pairs created.\n";
//    cout<<"\nget inputs";
    GetInPuts(n,pairs, fin, fout);

    CheckErr(fin,fout);

    MaxPlanner maxP(N2,fin,fout);
//    cout<<"Compute_Num"<<N2-1<<endl;
    maxP.Compute_Num(0,N2-1,pairs);
    maxP.Compute_Chord(0,N2-1,pairs);

    maxP.PrintDetail(pairs,fin,fout);

    delete[] pairs;

    fin.close();
    fout.close();

    return 0;
}







