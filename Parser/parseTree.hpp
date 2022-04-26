#include <bits/stdc++.h>
#include "Node.hpp"
#include "productionRule.hpp"

using namespace std;


class ParseTree {

public:
    Node *root;
    Node *left;
    Node *right;
    vector < ProductionRule > productions;
    map <int, vector <string> > levelOrderTraversal;
    set <string> terminals = {"$","id","(",")","{","}","maimn","inmt","floamt","strinmg","chamr","booml",",",";","cimn","coumt","returmn","=","imf","elmse imf", "elmse", "whimle","int_literal","float_literal","char_literal","string_literal","trmue","falmse","<",">","<=",">=","==","!=","&","|","!","+","-", "++", "+=", "--", "-=","&&", "||", ">>", "<<", "#", "[", "]", "\"", "\'", "*","/","!", "%","ssc"};
    set <string> nonTerminals = {"S","PROGRAM","FUNCTION_LIST","FIRST_FUNCTION","FIRST_FUNCTION_PRE","FIRST_FUNCTION_POST""MORE_FUNCTIONS","MAIN","TYPE","FORMAL_PARAMS","FORMAL_PARAMS_POST","FORMAL_PARAMS_PRE","STMTS","STMT_PRE","STMT_POST","STMT","PRINT_POST","RETURN_POST","POS_3","POS_4","POS_5","ACTUAL_PARAMS","ACTUAL_PARAMS_P,RE""ACTUAL_PARAMS_POST","VARLIST_POST","CONDITION_ST","LOOP_ST","LITERAL","BOOL_LITERAL","REL_OP","LOG_OP","RELN_EXPR","RELN_EXPR'","EXPR","EXPR'","TERM","TERM'","FACTOR",};

    ParseTree() {

    }

    ParseTree(string s) {
        root -> label = s;
        
    }

    void setStart(string s) {
        root -> label = s;
    }

    void setProductions(vector <ProductionRule> productions) {
        this -> productions = productions;
    }

    void createParseTree(Node *cur, int &cnt) {
        if(cur == NULL) {
            return;
        } 
        string curLabel = cur -> label;
        if(terminals.count(cur -> label) ) {
            return;
        }
        vector <string> children = productions[cnt++].RHS;
        for(auto ch: children) {
            Node *node = new Node();
            node -> label = ch;
            cur -> children.push_back(node);
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
        if((terminals.count(curLabel))) {
            levelOrderTraversal[level].push_back(curLabel);
            return;
        }
        levelOrderTraversal[level].push_back(curLabel);
        for(auto ch: cur -> children) {
            printParseTree(ch, level + 1);
        }
        return;
    }

    // void generateThreeAdressCodes(Node *cur) {
    //     if (cur == NULL) {
    //         return;
    //     }
    //     string curLabel = cur->label;
    //     if ((terminals.count(curLabel))) {
    //         if (curLabel == "id") {
    //             operands.push(id);
    //         }
    //         return;
    //     }
    // }

};
