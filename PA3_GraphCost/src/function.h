//
// Created by Phoebe Lu on 2022/1/13.
//

#ifndef DRAFT2_FUNCTION_H
#define DRAFT2_FUNCTION_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


class edge{
public:
    int s;
    int t;
    int w;
};

class vertex{
public:
    void makeSet(int num);
    void init();
    int set,Vn;
    vector<int> adj;
    int color=0;//white=0 gray=1 black=2
    int pre=-1, postInAdj=-1;
};

class uGraph{
public:
    uGraph(int Vtotal, int Etotal);
    void ConstructEdges(istream &fin);
    void Kruskal();
    void Print(ostream &fout);

    ~uGraph();
    int V,E; // total num of Vertices and Edges
    vertex *Vlist;// list of vertices
    vector<edge> Elist;
    int minCost=0;
    vector<edge> A;
};

class dGraph{
public:
    dGraph(int Vtotal, int Etotal);
    void ConstructEdges(istream &fin);
//    void Kruskal();
    void init();
    void DFS(int Vn);
    void DFS_Help(int Vn);
    void ListCycle(int startV,int endV,vector<int>&cycleEdge);
    void Print(ostream &fout);

    ~dGraph();
    int V,E; // total num of Vertices and Edges
    vertex *Vlist;// list of vertices
    vector<edge> Elist;
    int ** Ematrix;
    int minCost=0,lMC=200,lME=-1;
    vector<edge> B;
    bool foundCycle=false;
};

class Sort{
public:
    void        HeapSort(vector<edge>&); // sort data using heap sort
    void        MaxHeapify(vector<edge>&, int); // make tree with given root be a max-heap
    void        BuildMaxHeap(vector<edge>&); // make data become a max-heap
    int         heapSize; // heap size used in heap sort
};


void errorCheck(istream &fin);


#endif //DRAFT2_FUNCTION_H