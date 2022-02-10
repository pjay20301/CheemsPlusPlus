#include <bits/stdc++.h>
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
    operators.insert({"!", c++});
    operators.insert({"&", c++});
    operators.insert({"|", c++});
    operators.insert({"<", c++});
    operators.insert({">", c++});
    operators.insert({"<=", c++});
    operators.insert({">=", c++});
    operators.insert({"++", c++});
    operators.insert({"--", c++});
    operators.insert({"+=", c++});
    operators.insert({"-=", c++});
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
                start:
            // Entry checkpoint for identifier
            if((ch >= 'A' && ch <= 'Z') or (ch >= 'a' && ch <= 'z') or (ch == '_')) {
                identifier:
                string str = "";
                while((ch >= 'A' && ch <= 'Z') or (ch >= 'a' && ch <= 'z') or (ch >= '0' && ch <= '9') or (ch == '_')) {
                    str += ch;
                    ch = fgetc(fp);
                } 
                auto it = keywords.find(str);
                int check = 0;
                if(it != keywords.end()) {
                    cout << "Token " << keywords[str] << ", string " << str << ", line number " << lineNo << endl; 
                    check = 1;
                }
                it = datatypes.find(str);
                if(it != datatypes.end()) {
                    cout << "Token " << datatypes[str] << ", string " << str << ", line number " << lineNo << endl;  
                } else if (!check && str != "") {
                    cout << "Token " << IDENTIFIER << ", string " << str << ", line number " << lineNo << endl; 
                }

            } // Entry checkpoint for numericals
            else if((ch >= '0' && ch <= '9') or ch == '.') { 
                numerical:
                int count = 0;
                string str = "";
                while(((ch >= '0' && ch <= '9') or ch == '.') and count <= 1) {
                    if(ch == '.') {
                        count++;
                        break;
                    }
                    str += ch;
                    ch = fgetc(fp);
                }
                while((ch >= '0' && ch <= '9') or ch == '.') {
                    str += ch;
                    ch = fgetc(fp);
                    if(ch == '.') {
                        // excess floating points
                        str += ch;
                        ch = fgetc(fp);
                        while(true) {
                            if(ch == ' ' or ch == '\n' or ch == EOF)
                                break;
                            str += ch;
                            ch = fgetc(fp);
                        }
                        cout << "ERROR! : Too many floating points" << ", string "  << str << ", line number " << lineNo << endl;
                        goto label;
                    } else if(ch < '0' && ch > '9') {
                        // no digits after floating point error
                        str += ch;
                        ch = fgetc(fp);
                        while(true) {
                            if(ch == ' ' or ch == '\n' or ch == EOF)
                                break;
                            str += ch;
                            ch = fgetc(fp);
                        }
                        cout << "ERROR! : No digit after floating point" << ", string " << str << ", line number " << lineNo << endl;
                        goto label;
                    }
                }
                if((ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z')) {
                    cout << "ERROR! : Not a numerical" << ", string " << str << ", line number " << lineNo << endl;
                    goto identifier;
                } else {
                    cout << "Token " << NUMERIC << ", string " << str << ", line number " << lineNo << endl;
                    goto start;
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
            } else if(ch == '+') {
                ch = fgetc(fp);
                if(ch == '+') {
                    cout << "Token " << operators["++"] << ", string " << "++" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or ch == ' ') {
                    cout << "Token " << operators["+"] << ", string " << "+" << ", line number " << lineNo << endl;
                    if(ch != ' ')
                    goto numerical;
                } else if(ch == '=') {
                    cout << "Token " << operators["+="] << ", string " << "+=" << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "+" + ch << ", line number " << lineNo << endl;
                }
            } else if(ch == '-') {
                ch = fgetc(fp);
                if(ch == '-') {
                    cout << "Token " << operators["--"] << ", string " << "--" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or ch == ' ') {
                    cout << "Token " << operators["-"] << ", string " << "-" << ", line number " << lineNo << endl;
                    goto numerical;
                } else if(ch == '=') {
                    cout << "Token " << operators["-="] << ", string " << "-=" << ", line number " << lineNo << endl;
                } else {
                    cout << "Token " << operators["-"] << ", string " << "-" << ", line number " << lineNo << endl;
                }
            } else if(ch == '*') {
                cout << "Token " << operators["*"] << ", string " << "*" << ", line number " << lineNo << endl;
            } else if(ch == '/') {
                cout << "Token " << operators["/"] << ", string " << "/" << ", line number " << lineNo << endl;
            } else if(ch == '%') {
                cout << "Token " << operators["%"] << ", string " << "%" << ", line number " << lineNo << endl;
            } else if(ch == ',') {
                cout << "Token " << operators[","] << ", string " << "," << ", line number " << lineNo << endl;
            } else if(ch == ';') {
                cout << "Token " << operators[";"] << ", string " << ";" << ", line number " << lineNo << endl;
            } else if(ch == '(') {
                cout << "Token " << operators["("] << ", string " << "(" << ", line number " << lineNo << endl;
            } else if(ch == ')') {
                cout << "Token " << operators[")"] << ", string " << ")" << ", line number " << lineNo << endl;
            } else if(ch == '[') {
                cout << "Token " << operators["["] << ", string " << "[" << ", line number " << lineNo << endl;
            } else if(ch == ']') {
                cout << "Token " << operators["]"] << ", string " << "]" << ", line number " << lineNo << endl;
            } else if(ch == '{') {
                cout << "Token " << operators["{"] << ", string " << "{" << ", line number " << lineNo << endl;
            } else if(ch == '}') {
                cout << "Token " << operators["}"] << ", string " << "}" << ", line number " << lineNo << endl;
            } else if(ch == '&') {
                ch = fgetc(fp);
                if(ch == '&') {
                    cout << "Token " << operators["&&"] << ", string " << "&&" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == ' ') {
                    cout << "Token " << operators["&"] << ", string " << "&" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "&" + ch << ", line number " << lineNo << endl;
                }
            } else if(ch == '|') {
                ch = fgetc(fp);
                if(ch == '|') {
                    cout << "Token " << operators["||"] << ", string " << "||" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == ' ') {
                    cout << "Token " << operators["|"] << ", string " << "|" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "|" + ch << ", line number " << lineNo << endl;
                }
            } else if(ch == '!') {
                ch = fgetc(fp);
                if(ch == '=') {
                    cout << "Token " << operators["!="] << ", string " << "!=" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == ' ') {
                    cout << "Token " << operators["!"] << ", string " << "!" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "!" + ch << ", line number " << lineNo << endl;
                } 
            } else if(ch == '<') {
                ch = fgetc(fp);
                if(ch == '<') {
                    cout << "Token " << operators["<<"] << ", string " << "<<" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' or ch <= 'Z') or ch == ' ') {
                    cout << "Token " << operators["<"] << ", string " << "<" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else if(ch == '=') {
                    cout << "Token " << operators["<="] << ", string " << "<=" << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "<" + ch << ", line number " << lineNo << endl;
                }
            } else if(ch == '>') {
                ch = fgetc(fp);
                if(ch == '>') {
                    cout << "Token " << operators[">>"] << ", string " << ">>" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' or ch <= 'Z') or ch == ' ') {
                    cout << "Token " << operators[">"] << ", string " << ">" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else if(ch == '=') {
                    cout << "Token " << operators[">="] << ", string " << ">=" << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << ">" + ch << ", line number " << lineNo << endl;
                }
            } else if(ch == '=') {
                ch = fgetc(fp);
                if(ch == '=') {
                    cout << "Token " << operators["=="] << ", string " << "==" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' or ch <= 'Z') or ch == ' ') {
                    cout << "Token " << operators["="] << ", string " << "=" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "=" + ch << ", line number " << lineNo << endl;
                }
            }
            if(ch == '\n' or ch == EOF)
                break;
        }
        label:
            lineNo++;
        
    }
        
    }

int32_t main() {

    setToken();
    lexer();

    return 0;
}
