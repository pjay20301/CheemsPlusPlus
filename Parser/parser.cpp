#include "lexer.hpp"
#include "parseTableEntry.hpp"
#include "productionRule.hpp"
#include "parseTree.hpp"

struct compare {
    bool operator()(const ParseTableEntry& a, const ParseTableEntry& b) const {
        return a.nonTerminal < b.nonTerminal;
    }
};

map < ParseTableEntry, ProductionRule, compare> parseTable;
vector <string> parserInput;
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

    tokenToLexeme.insert({100, "id"});
    tokenToLexeme.insert({});
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
        currentStackContents.emplace_back(revStr);
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
                productions.emplace_back(parseTable[key]);
                st.pop();
                continue;
            }

            productions.emplace_back(parseTable[key]);
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
    for(auto &[x, y]: tokenList) {
        parserInput.emplace_back(parseTable[y]);
    }
    cout << endl;
    parserInput.emplace_back("$");

    for (int i = parserInput.size() - 1; i >= 0; i--) {
        input.push(parserInput[0]);
    }

    stack <string> st;
    st.push("$");
    st.push("PROGRAM");

    if(parser(st, input)) {
        int cnt = 0;
        tree.setProductions(productions);
        tree.createParseTree(tree.root, cnt);
        tree.printParseTree(tree.root, 0);
        for(auto [level, nodes]: tree.levelOrderTraversal) {
            cout << "Level " << level << " ";
            for(auto node: nodes) {
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