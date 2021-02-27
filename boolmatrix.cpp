#include "boolmatrix.h"

BoolMatrix::BoolMatrix(int size){
    this->size=size;
    bool **DAG = new bool*[size];
    for(size_t i = 0; i < size; ++i){
        DAG[i] = new bool[size];
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            DAG[i][j] = false;
        }
    }
    this->matrix = DAG;
    vector<string> newVector;
}

int BoolMatrix::getSize(){
    return this->size;
}

void BoolMatrix::removeNode(int n){
    bool **decreasedDAG = new bool*[this->size-1];
    for(int i = 0; i < this->size-1; ++i){
        decreasedDAG[i] = new bool[this->size-1];
    }
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-1;j++){
            decreasedDAG[i][j] = false;
        }
    }
    int k=0; int l=0;
    for(int i = 0; i < size;i++){
        l=0;
        for(int j = 0; j < size;j++){
            if(i!=n && j!=n){
                decreasedDAG[k][l] = this->matrix[i][j];
                l++;
            }
        }
        if(i!=n){
            k++;
        }
    }
    this->matrix = decreasedDAG;
    this->size -=1;
}

vector<int> BoolMatrix::getNodes(){
    bool found;
    vector<int> nodes;
    cout << "Get nodes called with this matrix: " << endl;
    for(int i=0;i<this->size;i++){
        found = true;
        for(int j=0;j<this->size;j++){
            if(this->matrix[i][j] != 0){
                found = false;
            }
        }
        if(found){
            nodes.push_back(i);
        }
    }
    return nodes;
}

void BoolMatrix::topologicalsort(stack<vector<string>> &S,vector<string> &C){
    vector<int> nodes = this->getNodes();
    vector<string> courseplan;
    cout << "Topological sort called" << endl;
    if(this->size==0){
        cout << "Topological sort finished" << endl;
        return;
    } else{
        cout << "Node zeroes : ";
        for(int i=0;i<nodes.size();i++){
            cout << nodes[i] << " ";
            courseplan.push_back(C[nodes[i]]);
        }
        cout << endl;
        S.push(courseplan);
        while(nodes.size()>0){
            int temp = nodes[0];
            cout << "Nodes[0] : " << nodes[0] << endl;
            this->removeNode(nodes[0]);
            for(int i=0;i<nodes.size();i++){
                if(nodes[i]>temp){
                    nodes[i] = nodes[i] - 1;
                }
            }
            cout << "Deleting " << C[nodes[0]] << " with index " << nodes[0] <<endl;
            C.erase(C.begin()+nodes[0]);
            nodes.erase(nodes.begin());
        }
        // cout << "Current remaining courses: " << endl;
        // for(int i=0;i<C.size();i++){
        //     cout << i << " : " << C[i] << endl;
        // }
        this->topologicalsort(S,C);
    }
}
