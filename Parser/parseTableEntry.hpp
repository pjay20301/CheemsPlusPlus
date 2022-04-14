#include <bits/stdc++.h>
using namespace std;

class ParseTableEntry {
    
public:
    string nonTerminal;
    string terminal;

    ParseTableEntry() {

    }
    ParseTableEntry(string row, string col) {
        this -> nonTerminal = row;
        this -> terminal = col;
    }
};