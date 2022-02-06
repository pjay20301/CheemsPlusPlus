#include <bits/stdc++.h>
#include <fstream>
#include <istream>
using namespace std;

#define IDENTIFIER 100
#define NUMERIC 101
#define STRING 102
#define CHAR 103

map <string, int> operators, keywords, datatypes;

void setToken() {
    int c = 104;
    datatypes.insert({"inmt", c++});
    datatypes.insert({"floamt", c++});
    datatypes.insert({"strinmg", c++});
    datatypes.insert({"booml", c++});
    datatypes.insert({"voimd", c++}); 

    keywords.insert({"maimn", c++});
    keywords.insert({"cimn", c++});
    keywords.insert({"coumt", c++});
    keywords.insert({"whimle", c++});
    keywords.insert({"fomr", c++});
    keywords.insert({"imf", c++});
    keywords.insert({"elmse", c++});
    keywords.insert({"elmse imf", c++});
    keywords.insert({"trmue", c++});
    keywords.insert({"falmse", c++});
    keywords.insert({"endml", c++});
    keywords.insert({"breamk", c++});
    keywords.insert({"contimnue", c++});
    keywords.insert({"returmn", c++});

    operators.insert({"+", c++});
    operators.insert({"-", c++});
    operators.insert({"*", c++});
    operators.insert({"/", c++});
    operators.insert({"%", c++});
    operators.insert({"==", c++});
    operators.insert({"!=", c++});
    operators.insert({"=", c++});
    operators.insert({"&&", c++});
    operators.insert({"||", c++});
    operators.insert({"&", c++});
    operators.insert({"|", c++});
    operators.insert({"<", c++});
    operators.insert({">", c++});
    operators.insert({"<=", c++});
    operators.insert({">=", c++});
    operators.insert({"++", c++});
    operators.insert({"--", c++});
    operators.insert({"<<", c++});
    operators.insert({">>", c++});
    operators.insert({"#", c++});
    operators.insert({";", c++});
    operators.insert({",", c++});
    operators.insert({"{", c++});
    operators.insert({"}", c++});
    operators.insert({"(", c++});
    operators.insert({")", c++});
    operators.insert({"[", c++});
    operators.insert({"]", c++});
    operators.insert({"\"", c++});
    operators.insert({"\'", c++});

}
void lexer() {
    
    FILE *fp;
    int lineNo = 1;
    fp = freopen("input.txt", "r", stdin);
    while(!feof(fp)) {
        
        while(true) {
            
            char ch = fgetc(fp);
            if(ch == EOF)
                break;
            // Entry checkpoint for identifier
            if((ch >= 'A' && ch <= 'Z') or (ch >= 'a' && ch <= 'z') or (ch == '_')) {
                string str = "";
                while((ch >= 'A' && ch <= 'Z') or (ch >= 'a' && ch <= 'z') or (ch >= '0' && ch <= '9') or (ch == '_')) {
                    str += ch;
                    ch = fgetc(fp);
                } 
                auto it = keywords.find(str);
                if(it != keywords.end()) {
                    cout << "Token " << keywords[str] << ", string " << str << ", line number " << lineNo << endl;   
                }
                it = datatypes.find(str);
                if(it != datatypes.end()) {
                    cout << "Token " << datatypes[str] << ", string " << str << ", line number " << lineNo << endl;   
                } else {
                    cout << "Token " << IDENTIFIER << ", string " << str << ", line number " << lineNo << endl; 
                }

            } // Entry checkpoint for numericals
            else if((ch >= '0' && ch <= '9') or ch == '.' or ch == '+' or ch == '-') { 
                
                int count = 0;
                string str = "";
                int check = 0;
                while(((ch >= '0' && ch <= '9') or ch == '.') and count <= 1 and check <=1) {
                    if(ch == '.') {
                        count++;
                        break;
                    }
                    if(ch == '+' || ch == '-') {
                        check++;
                    }
                    str += ch;
                    ch = fgetc(fp);
                }
                while((ch >= '0' && ch <= '9') or ch == '.') {
                    str += ch;
                    ch = fgetc(fp);
                    if(ch == '.') {
                        // excess floating points
                        ch = fgetc(fp);
                        while(ch != ' ') {
                            str += ch;
                            ch = fgetc(fp);
                        }
                        cout << "ERROR! : Too many floating points" << ", string " << str << ", line number " << lineNo << endl;
                    } else if(ch < '0' && ch > '9') {
                        // no digits after floating point error
                        ch = fgetc(fp);
                        while(ch != ' ') {
                            str += ch;
                            ch = fgetc(fp);
                        }
                        cout << "ERROR! : No digit after floating point" << ", string " << str << ", line number " << lineNo << endl;
                    }
                }
                if((ch == ' ' or ch == '\n' or (ch == EOF)) and count <= 1) {
                    cout << "Token " << NUMERIC << ", string " << str << ", line number " << lineNo << endl;
                }
                else {
                    cout << "ERROR! : Not a numerical" << ", string " << str << ", line number " << lineNo << endl;
                }
            } // Entry checkpoint for string literals
            else if(ch == '\"') {
                string str = "";
                int count = 0;
                while(ch != ' ') {
                    if(ch == '\"') {
                        count++;
                    } 
                    str += ch;
                    ch = fgetc(fp);
                }
                if(count == 2 && ch == '\"') {
                    cout << "Token " << STRING << ", string " << str << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not a string" << ", string " << str << ", line number " << lineNo << endl;
                }
            } // Entry checkpoint for charachter
            else if(ch == '\'') {
                string str = "";
                int count = 0;
                while(ch != ' ') {
                    if(ch == '\'') {
                        count++;
                    } 
                    str += ch;
                    ch = fgetc(fp);
                }
                if(count == 2 && ch == '\"' && str.length() == 3) {
                    cout << "Token " << CHAR << ", string " << str << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not a character" << ", string " << str << ", line number " << lineNo << endl;
                } 
            } //Entry checkpoint for comments
            else if(ch == '$') {
                string str = "$";
                int count = 1;
                ch = fgetc(fp);
                while(ch != '$') {
                    str += ch;
                    if(ch == '$')
                        count++;
                    ch = fgetc(fp);
                }
                if(count != 2) {
                    cout << "ERROR! : lexical error" << ", string " << str << ", line number " << lineNo << endl;
                } 
            } else {
                string str = "";
                while(ch != ' ' && ch != '\n' && ch != EOF) {
                    str += ch;
                    ch = fgetc(fp);
                }
                auto itr = operators.find(str);
                if(itr != operators.end() && ch != ' ' && ch != '\n' && ch != EOF) {
                    cout << "Token " << operators[str] << ", string " << str << ", line number " << lineNo << endl;
                } else if(ch == ' ' or ch == '\n' or ch == EOF) {
                    char c = str[0];
                    str = "";
                    str += c;
                    itr = operators.find(str);
                    if(itr != operators.end()) {
                        cout << "Token " << operators[str] << ", string " << str << ", line number " << lineNo << endl;
                    } else {
                        cout << "ERROR! : Not a valid operator" << ", string " << str << ", line number " << lineNo << endl;
                    }
                } else {
                    cout << "ERROR! : Not a valid operator" << ", string " << str << ", line number " << lineNo << endl;
                }
            }
            if(ch == '\n' or ch == EOF)
                break;
        }
        lineNo++;
    }
        
    }

int32_t main() {

    setToken();
    lexer();

    return 0;
}
