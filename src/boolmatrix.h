#ifndef __BOOLMATRIX__H
#define __BOOLMATRIX__H

#include <bits/stdc++.h>

using namespace std;

class BoolMatrix{
    private:
        int size;
    public:
        bool **matrix;
        BoolMatrix(int size);
        int getSize();
        void removeNode(int n);
        vector<int> getNodes();
        void topologicalsort(stack<vector<string>> &S,vector<string> &C);
};

#endif
