#include <iostream>
#include "function.h"


using namespace std;



int main(int argc, char *argv[]) {
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);


    char gType;
    int V,E;
    fin>>gType>>V>>E;

    if(gType=='u'){
        cout<<"this is an undirected graph!\n";
        uGraph U(V,E);
        U.ConstructEdges(fin);
        errorCheck(fin);
        U.Kruskal();
        U.Print(fout);
        //    for (int i = 0; i < E; ++i) {
        //        cout<<"Elist["<<i<<"]= from "<< U.Elist[i].s<<" to "<<U.Elist[i].t<<" of weight "<<U.Elist[i].w<<endl;
        //    }
    }

    else if(gType=='d'){
        cout<<"this is a directed graph!\n";
        dGraph D(V,E);
        D.ConstructEdges(fin);
        errorCheck(fin);

        D.DFS(0);
//        cout<<"check done1!\n";

        while(D.foundCycle){
            D.foundCycle=false;
            D.DFS(0);
//            cout<<"check done2!\n";
        }
        D.Print(fout);

    }

    else{
        cout<<"wrong graph type.";
    }




    return 0;
}
