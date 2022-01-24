//
// Created by Phoebe Lu on 2021/11/27.
//

#include <iostream>
#include "function.h"
#include <vector>
#include <fstream>
using namespace std;

void GetInPuts(int n2, int *pairs,istream &fin, ostream &fout){
    int front,back;
    for (int i = 0; i < n2; i++) {
        fin >> front >> back;
        pairs[front]=back;
        pairs[back]=front;

//        cout << "pairs["<<front<<"]="<<pairs[front]<< " pairs["<<back<<"]="<<pairs[back]<<"\n";
    }

}

void CheckErr(istream &fin, ostream &fout){
    int endingMsg;
    fin>> endingMsg;
    if(endingMsg!=0){
        cout<<"Not ending properly.\n";
    }
    else{
        cout<<"All Data in. OKAY!\n";
    }
}

int Max(int a, int b){
    if(a>=b){
        return a;
    } else{
        return b;
    }
}


MaxPlanner::MaxPlanner(int outN2, istream &fin, ostream &fout){
    //init M
    n2=outN2;
    M =new int*[n2];
    for (int i = 0; i <n2 ; i++) {
        M[i]= new int[n2];
//            cout<<"M["<<i<<"] created.\n";
        for (int j = 0; j < n2; j++) {
            M[i][j]=-1;
        }
    }

}

int MaxPlanner::Compute_Num(int start, int end, int *pairs){
    int i=start, j=end;
//    cout<<"\nNOW COMPUTE NUM OF M["<<i<<"]["<<j<<"]"<<endl;
    if(M[i][j]<0){
        if(j==i){
//                cout<<"\nM["<<i<<"]["<<j<<"] belongs to case i=j"<<endl;
            M[i][j]=0;
        }
        else if(pairs[j]==i){
//                cout<<"\nM["<<i<<"]["<<j<<"] belongs to case k=j"<<endl;
            M[i][j]=Compute_Num(i,j-1,pairs)+1;

        } else if(pairs[j]<=j && pairs[j]>=i){
            M[i][j]=Max(Compute_Num(i,j-1,pairs),(1+Compute_Num(i,pairs[j]-1,pairs)+Compute_Num(pairs[j]+1,j,pairs)));
//        cout<<"M["<<i<<"]["<<pairs[j]<<"] accessed.\n";
//        cout<<"M["<<pairs[j]<<"]["<<j<<"] accessed.\n";
//        cout<<"M["<<i<<"]["<<j<<"] allocated.\n";
        } else{
//                cout<<"\nM["<<i<<"]["<<j<<"] belongs to case k outside"<<endl;
            M[i][j]=Compute_Num(i,j-1,pairs);;
        }

    }

//    cout<<"M["<<i<<"]["<<j<<"]="<<M[i][j]<<endl;
    return M[i][j];

}

void MaxPlanner::Compute_Chord(int start, int end, int *pairs){
    if(start>end){
        return;
    }
    int i=start, j=end;
//    cout<<"\nNOW COMPUTE Chord OF M["<<i<<"]["<<j<<"]"<<endl;
//    cout<<"\tpairs[j]="<<pairs[j]<<endl;
    if(j==i){
//        cout<<"\tM["<<i<<"]["<<j<<"] belongs to case i=j"<<endl;
        // do nothing
    }
    else if(pairs[j]==i){
//        cout<<"\tM["<<i<<"]["<<j<<"] belongs to case k=j"<<endl;
        pairDetail.push_back(pairs[j]);
//        cout<<"\tPUSH1  "<<pairs[j]<<endl;
        Compute_Chord(i+1,j-1,pairs);

    } else if(pairs[j]<=j && pairs[j]>=i){

        if(M[i][j-1]>M[i][pairs[j]-1]+M[pairs[j]+1][j]){
//            cout<<"\tM["<<i<<"]["<<j<<"] belongs to case k < M[i][j-1]"<<endl;
          //push noting
            Compute_Chord(i,j-1, pairs);

        } else{
//            cout<<"\tM["<<i<<"]["<<j<<"] belongs to case k > M[i][j-1]"<<endl;
            Compute_Chord(i,pairs[j]-1,pairs);
            pairDetail.push_back(pairs[j]);
//            cout<<"\tPUSH2  "<<pairs[j]<<endl;
            Compute_Chord(pairs[j]+1,j-1,pairs);



        }
    } else{
//        cout<<"\tM["<<i<<"]["<<j<<"] belongs to case k outside"<<endl;
        //push noting
        Compute_Chord(i,j-1, pairs);
    }

//    cout<<"OUT OF M["<<i<<"]["<<j<<"]"<<endl;
}


MaxPlanner::~MaxPlanner(){

    for (int i = 0; i <n2 ; i++) {
        delete[] M[i];
    }
    delete[] M;

}

void MaxPlanner::PrintDetail(int *pairs, istream &fin, ostream &fout){
    fout << M[0][n2-1]<<"\n";

    for (int i= 0; i<pairDetail.size(); i++) {

        fout<< pairDetail[i] << " "<< pairs[pairDetail[i]]<<"\n";

    }

}

