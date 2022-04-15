#include <bits/stdc++.h>
using namespace std;

class Node {

public:
    string label;
    vector <Node*> children;

    Node() {
        this -> label = "";
    }
};