#include "lexer.hpp"
#include "parseTableEntry.hpp"
#include "parseTree.hpp"

struct compare {
    bool operator()(const ParseTableEntry& a, const ParseTableEntry& b) const {
        return a.nonTerminal < b.nonTerminal;
    }
};

map < ParseTableEntry, ProductionRule, compare> parseTable;
vector <string> inputToParser;
map <int, string> tokenToLexeme;
stack <string> input;
vector < vector <string> > currentStackContents;
vector < ProductionRule > productions;
ParseTree tree("PROGRAM");

void populateParseTable() {
    fstream fp;
    fp.open("parser_table", ios::in);
    
    if(fp.is_open()) {
        string cur;

        while(getline(fp, cur)) {
            istringstream iss(cur);
            ParseTableEntry entry;

            for (string s; iss >> cur; ) {
                entry.nonTerminal = s;
                iss >> cur;

                entry.terminal = s;
                iss >> cur;

                ProductionRule rule;
                rule.LHS = s;

                for(; iss >> cur; ) {
                    rule.RHS.push_back(s);
                }
                parseTable[entry] = rule;
            }
        }
        fp.close();
    }
    return;
}
void tokenNumberToLexeme() {
    int c = 104;
    tokenToLexeme.insert({100, "id"});
    tokenToLexeme.insert({101, "int_literal"});
    tokenToLexeme.insert({102, "string_literal"});
    tokenToLexeme.insert({103, "char_literal"});
    tokenToLexeme.insert({c++, "inmt"});
    tokenToLexeme.insert({c++, "floamt"});
    tokenToLexeme.insert({c++, "chamr"});
    tokenToLexeme.insert({c++, "strinmg"});
    tokenToLexeme.insert({c++, "booml"});
    tokenToLexeme.insert({c++, "voimd"});
    tokenToLexeme.insert({c++, "maimn"});
    tokenToLexeme.insert({c++, "cimn"});
    tokenToLexeme.insert({c++, "coumt"});
    tokenToLexeme.insert({c++, "whimle"});
    tokenToLexeme.insert({c++, "fomr"});
    tokenToLexeme.insert({c++, "imf"});
    tokenToLexeme.insert({c++, "elmse"});
    tokenToLexeme.insert({c++, "elmse imf"});
    tokenToLexeme.insert({c++, "trmue"});
    tokenToLexeme.insert({c++, "falmse"});
    tokenToLexeme.insert({c++, "endml"});
    tokenToLexeme.insert({c++, "breamk"});
    tokenToLexeme.insert({c++, "contimnue"});
    tokenToLexeme.insert({c++, "returmn"});
    tokenToLexeme.insert({c++, "+"});
    tokenToLexeme.insert({c++, "-"});
    tokenToLexeme.insert({c++, "*"});
    tokenToLexeme.insert({c++, "/"});
    tokenToLexeme.insert({c++, "%"});
    tokenToLexeme.insert({c++, "=="});
    tokenToLexeme.insert({c++, "!="});
    tokenToLexeme.insert({c++, "="});
    tokenToLexeme.insert({c++, "&&"});
    tokenToLexeme.insert({c++, "||"});
    tokenToLexeme.insert({c++, "!"});
    tokenToLexeme.insert({c++, "&"});
    tokenToLexeme.insert({c++, "|"});
    tokenToLexeme.insert({c++, "<"});
    tokenToLexeme.insert({c++, ">"});
    tokenToLexeme.insert({c++, "<="});
    tokenToLexeme.insert({c++, ">="});
    tokenToLexeme.insert({c++, "++"});
    tokenToLexeme.insert({c++, "--"});
    tokenToLexeme.insert({c++, "+="});
    tokenToLexeme.insert({c++, "-="});
    tokenToLexeme.insert({c++, "<<"});
    tokenToLexeme.insert({c++, ">>"});
    tokenToLexeme.insert({c++, "#"});
    tokenToLexeme.insert({c++, ";"});
    tokenToLexeme.insert({c++, ","});
    tokenToLexeme.insert({c++, "{"});
    tokenToLexeme.insert({c++, "}"});
    tokenToLexeme.insert({c++, "("});
    tokenToLexeme.insert({c++, ")"});
    tokenToLexeme.insert({c++, "["});
    tokenToLexeme.insert({c++, "]"});
    tokenToLexeme.insert({c++, "\""});
    tokenToLexeme.insert({c++, "\'"});
    return;
}
int parser(stack <string> st, stack < string> remInput) {
    int correctSyntax = 1;
    int needParseTree = 0;
    while(true) {
        if(st.empty() and remInput.empty()) {
            needParseTree = 1;
            break;
        } else if(st.empty()) {
            cout << "Parsing was completed but input string is not completely consumed and all non terminals are exhausted" << endl;
            break;
        } else if(remInput.empty()) {
            cout << "Parsing was completed but the input string is completely consumed and the stack is not empty" << endl;
            break;
        }
        stack <string> stCopy(st);
        vector < string > revStr;
        while(!stCopy.empty()) {
            revStr.push_back(stCopy.top());
            stCopy.pop();
        }
        currentStackContents.push_back(revStr);
        string stackTop = st.top();
        string curInput = remInput.top();

        if(!(tree.terminals.count(stackTop))) {
            if(stackTop == curInput) {
                remInput.pop();
                st.pop();
            } else {
                correctSyntax = 0;
                cout << "Terminals do not match : - Expected :" << stackTop << " || Found : " << curInput << endl;
                remInput.pop();
            }
        } else {
            ParseTableEntry key(stackTop, curInput);
            string LHS = parseTable[key].LHS;
            vector <string> RHS = parseTable[key].RHS;

            if(LHS == "SYNCH") {
                correctSyntax = 0;
                cout << "SYNCH was encountered in Parse table entry and " << stackTop << " was omitted." << endl;
                st.pop();
                continue;
            } else if(LHS == "SKIP") {
                correctSyntax = 0;
                cout << "SKIP was encountered in Parse Table entry and current input symbol " << curInput << " was omitted." << endl;
                remInput.pop();
                continue;
            }
            
            if(RHS[0] == "ssc") {
                productions.push_back(parseTable[key]);
                st.pop();
                continue;
            }

            productions.push_back(parseTable[key]);
            st.pop();
            for(int i = RHS.size()-1; i >= 0; i--) {
                st.push(RHS[i]);
            }
            
        }
    }
    if(correctSyntax == 0) {
        cout << "Parsing was completed but either terminals did not match, SKIP was used or SYNCH was used" << endl;
        return 0;
    } else if(needParseTree == 1)  {
        cout << "Parsing was successful and the level order traversal for the parse tree is generated as follows:-" << endl;
        return 1;
    }
    return 0;
}
int32_t main() {

    populateParseTable();
    tokenNumberToLexeme();

    vector< pair <string, int> > tokenList = lexer();
    for(auto token: tokenList) {
        inputToParser.push_back(tokenToLexeme[token.second]);
    }
    cout << endl;
    inputToParser.push_back("$");

    for (int i = inputToParser.size() - 1; i >= 0; i--) {
        input.push(inputToParser[i]);
    }

    stack <string> st;
    st.push("$");
    st.push("PROGRAM");

    if(parser(st, input)) {
        int cnt = 0;
        tree.setProductions(productions);
        tree.createParseTree(tree.root, cnt);
        tree.printParseTree(tree.root, cnt);
        for(auto level: tree.levelOrderTraversal) {
            cout << "Level " << level.first << " ";
            for(auto node: level.second) {
                cout << node << " ";
            }
            cout << endl;
        }
    } else {
        cout << endl;
        cout << "Input is not valid according to the CheemsPlusPlus" << endl;
        cout << "The contents of the stack at the each step are as follows :" << endl;
        int step = 1;
        for (auto it: currentStackContents) {
            cout << "Step: " << step++ << ": ";
            for(auto i: it) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
    return 0;
}