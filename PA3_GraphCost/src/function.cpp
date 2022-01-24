//
// Created by Phoebe Lu on 2022/1/13.
//
#include "function.h"

void vertex::makeSet(int num) {
    set=num;
}
void vertex::init() {
    pre=-1;
    color=0;
}

uGraph::uGraph(int Vtotal, int Etotal) {
    V=Vtotal; E=Etotal;
    Vlist =new vertex[V];
    for (int i = 0; i < V; ++i) {
        Vlist[i].makeSet(i);
    }
//    cout<<"V number="<<V<<"; E number="<<E<<endl;
}

uGraph::~uGraph() {
    delete [] Vlist;
}

void uGraph::ConstructEdges(istream &fin){
    int startV,endV,weight;
    for (int i = 0; i < E; ++i) {
        fin >> startV >> endV >> weight;
        // add to edge list
        edge temp;
        temp.s=startV;
        temp.t=endV;
        temp.w=weight;
        Elist.push_back(temp);
//        cout<<"add"<< i<<" edge\n";
    }
}

void uGraph::Kruskal(){
    vector<vector<int> > set;
    for (int i = 0; i < V; ++i) {
        Vlist[i].makeSet(i);
        vector<int>temp;
        temp.push_back(i);
        set.push_back(temp);
    }
    Sort S;
    S.HeapSort(Elist);
//    cout<<"sorted!\n";
    for (int i = E-1; i >=0; i--) {
        if (Vlist[Elist[i].s].set != Vlist[Elist[i].t].set){
            //union
            int Vs=Elist[i].s, Vt=Elist[i].t;
            int sSet=Vlist[Vs].set, tSet=Vlist[Vt].set;
//            cout<<Vs<<" belongs to set"<<sSet<<"; "<<Vt<<" belongs to set"<<tSet<<"\tgoing to Union!\n";
            int k1=set[sSet].size(),k2=set[tSet].size();
            for (int j = 0; j <k2; j++) {
//                Vlist[set[tSet][j]].set=sSet;
                int temp= set[tSet][0];
                set[sSet].push_back(temp);
                set[tSet].erase(set[tSet].begin());
            }
            for (int j = k1;j<k1+k2 ; j++) {
                Vlist[set[sSet][j]].set=sSet;

            }
//            cout<<"Finished\t"<<Elist[i].s<<" belongs to set"<<Vlist[Elist[i].s].set<<"; "<<Elist[i].t<<" belongs to set"<<Vlist[Elist[i].t].set<<"\n";
//            cout<<"finished\tset"<<sSet<<"= ";
//            for (int j = 0; j < set[sSet].size(); ++j) {
//                cout<<set[sSet][j]<<"("<<Vlist[set[sSet][j]].set<<")"<<" ";
//            }
//            cout<<"\nset"<<tSet<<"= ";
//            for (int j = 0; j < set[tSet].size(); ++j) {
//                cout<<set[tSet][j]<<" ";
//            }cout<<"\n";

        } else{
            A.push_back(Elist[i]);
//            cout<<"PUSH BACK "<<Elist[i].s<<" "<<Elist[i].t<<" "<<Elist[i].w<<"\n";
            minCost+=Elist[i].w;
        }

    }

}

void uGraph::Print(ostream &fout) {
    cout<<"min Cost= "<<minCost<<"\n";
    fout<<minCost<<"\n";
    if(minCost!=0){
        for (int i = 0; i < A.size(); ++i) {
            fout<<A[i].s<<" "<<A[i].t<<" "<<A[i].w<<"\n";
        }
    }
}

//------------------------------------------------Directed Graph------------------------------------------------

dGraph::dGraph(int Vtotal, int Etotal) {
    V=Vtotal; E=Etotal;
    Vlist =new vertex[V];
    Ematrix= new int*[V];
    for (int i = 0; i < V; ++i) {
        Vlist[i].Vn=i;
        Ematrix[i]=new int [V];
        for (int j = 0; j < V; ++j) {
            Ematrix[i][j]=-1;
        }
//        Vlist[i].makeSet(i);
    }
//    cout<<"V number="<<V<<"; E number="<<E<<endl;
}

dGraph::~dGraph() {
    delete [] Vlist;
    for (int i = 0; i < V; ++i) {
        delete[] Ematrix[i];
//        Vlist[i].makeSet(i);
    }
    delete [] Ematrix;
}

void dGraph::ConstructEdges(istream &fin){
    int startV,endV,weight;
    for (int i = 0; i < E; ++i) {
        fin >> startV >> endV >> weight;
        // add to edge list
        edge temp;
        temp.s=startV;
        temp.t=endV;
        temp.w=weight;
        Elist.push_back(temp);
        Ematrix[startV][endV]=i;// from startV to endV via the ith edge
        Vlist[startV].adj.push_back(endV);
//        cout<<"add"<< i<<" edge\n";
    }
}

void dGraph::init() {
    //color initialized; no pre~
    for (int i = 0; i < V; ++i) {
        Vlist[i].init();
        lMC=200,lME=-1;
    }
//    cout<<"initialized\n";
}

void dGraph::DFS(int Vn) {
    init();
    //start DFS
    Vlist[Vn].color=1;
//    cout<<"Vn="<<Vn<<"---------vn's adj= ";
//    for (int i = 0; i < Vlist[Vn].adj.size(); ++i) {
//        cout<<Vlist[Vn].adj[i]<<"("<<Vlist[Vlist[Vn].adj[i]].color<<") ";
//    }cout<<"\n";

    for (int i = 0; i < V; ++i) {
        if(Vlist[i].color==0){
            DFS_Help(i);
        }
    }

    return;

}

void dGraph::DFS_Help(int Vn) {
    vector<int>cycleEdge;

    //start DFS
    Vlist[Vn].color=1;
//    cout<<"Vn="<<Vn<<"---------vn's adj= ";
//    for (int i = 0; i < Vlist[Vn].adj.size(); ++i) {
//        cout<<Vlist[Vn].adj[i]<<"("<<Vlist[Vlist[Vn].adj[i]].color<<") ";
//    }cout<<"\n";

    for (int i = 0; i < Vlist[Vn].adj.size(); ++i) {
        if(foundCycle){
            break;
        }

//        cout<<"Vn= "<<Vn<<"; Vn.adj["<<i<<"]="<<Vlist[Vn].adj[i]<<"\n";
        Vlist[Vn].postInAdj=i;
        int index=Vlist[Vn].adj[i];
        if(Vlist[index].color==0){

            foundCycle= false;
//            cout<<"white!\n";
            Vlist[index].color=1;
            Vlist[index].pre=Vn;

                DFS_Help(index);

        } else if(Vlist[index].color==2){
//            cout<<"Black!\n";
        }
        else {
            foundCycle=true;
//            cout<<"FOUND CYCLE!\n";
            cycleEdge.push_back(Ematrix[Vn][index]);
            lME=Ematrix[Vn][index];
            lMC=Elist[lME].w;
            ListCycle(Vn,index,cycleEdge);
            B.push_back(Elist[lME]);
            minCost+=lMC;
//            cout<<"the edge from "<<Vlist[Elist[lME].s].Vn<<" to "<<Vlist[Vlist[Elist[lME].s].Vn].adj[Vlist[Elist[lME].s].postInAdj]<<" is broken.\n";
            Vlist[Elist[lME].s].adj.erase(Vlist[Elist[lME].s].adj.begin()+Vlist[Elist[lME].s].postInAdj);

//            cout<<"lME="<<lME<<"; lMC="<<lMC<<"; minCost="<<minCost<<"\n";
            break;

        }
    }if(!foundCycle) { Vlist[Vn].color = 2; }

    return;

}

void dGraph::ListCycle(int startV,int endV, vector<int>&cycleEdge){

    int u= Vlist[startV].pre;
//    cout<<"u="<<u<<"\n";
    if(u<0) {
        return;
    }
    if((u!=endV)){
        if(Elist[Ematrix[u][startV]].w<lMC){
            lME=Ematrix[u][startV];
            lMC=Elist[lME].w;
        }
        cycleEdge.push_back(Ematrix[u][startV]);
//        cout<<"lME="<<lME<<"; lMC="<<lMC<<"\n";
        ListCycle(u,endV, cycleEdge);
    }


}

void dGraph::Print(ostream &fout) {

    cout<<"min Cost= "<<minCost<<"\n";
    fout<<minCost<<"\n";
    if(minCost!=0){
        for (int i = 0; i < B.size(); ++i) {
            fout<<B[i].s<<" "<<B[i].t<<" "<<B[i].w<<"\n";
        }
    }
}


//------------------------------------------------sort tool------------------------------------------------

// Heap sort method
void Sort::HeapSort(vector<edge> &data)  {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}
// //Max heapify
void Sort::MaxHeapify(vector<edge>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    int leftI=((root+1)*2-1);
    int rightI=(root+1)*2;
    int largest= root;
    if (leftI < heapSize && data[leftI].w > data[root].w){
        largest = leftI;
    }

    if (rightI < heapSize && data[rightI].w > data[largest].w){
        largest=rightI;
    }

    if (largest != root){
        swap(data[root], data[largest]);// datum in [root] becaome the largest
        MaxHeapify(data, largest);
    }

}
//Build max heap
void Sort::BuildMaxHeap(vector<edge>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    for (int i=heapSize/2-1; i>=0; i--){
        MaxHeapify(data, i);
    }
}

//------------------------------------------------sort tool------------------------------------------------

void errorCheck(istream &fin){
    int err;
    fin>>err;
    if(err==0){
        cout<<"input correctly~\n";
    } else{
        cout<<"sth wrong!\n";
    }
}


