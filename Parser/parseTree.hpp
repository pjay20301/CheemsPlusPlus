#include <bits/stdc++.h>
#include "Node.hpp"
#include "productionRule.hpp"

using namespace std;


class ParseTree {

public:
    static set <string> terminals;
    static set <string> nonTerminals;
    Node *root;
    Node *left;
    Node *right;
    vector < ProductionRule > productions;
    map <int, vector <string> > levelOrderTraversal;
    ParseTree() {

    }

    ParseTree(string s) {
        this -> root -> label = s;
    }

    void setProductions(vector <ProductionRule> productions) {
        this -> productions = productions;
    }
    
    void createParseTree(Node *cur, int &cnt) {
        if(cur == NULL) {
            return;
        } 
        string curLabel = cur -> label;

        if(!terminals.count(cur -> label) ) {
            return;
        }
        vector <string> children = productions[cnt++].RHS;
        for(auto ch: children) {
            Node *node = new Node();
            node -> label = ch;
            cur -> children.emplace_back(node);
        }

        for(auto ch: cur -> children) {
            createParseTree(ch, cnt);
        }
    }

    void printParseTree(Node *cur, int level) {
        if(cur == NULL) {
            return;
        }

        string curLabel = cur -> label;
        if(!(terminals.count(curLabel))) {
            levelOrderTraversal[level].emplace_back(curLabel);
            return;
        }
        levelOrderTraversal[level].emplace_back(curLabel);
        for(auto ch: cur -> children) {
            printParseTree(ch, level+1);
        }
        return;
    }
};
