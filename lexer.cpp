/**
 * Language name - Cheems++
 * Group Number - 8
 * Jay Patel - 2019A7PS0156H
 * Kruti Baraiya - 2019A7PS1260H
 * Aman Jham - 2019A7PS0071H
 */

#include <bits/stdc++.h>
using namespace std;

#define IDENTIFIER 100 //Token number for IDENTIFIER
#define NUMERIC 101 // Token number for NUMERIC literal
#define STRING 102 // Token number for STRING literal
#define CHAR 103 // Token number for CHARACTER literal

map <string, int> operators, keywords, datatypes;  //map containing the operators, keywords and datatypes

/**
 * @brief Set the values for Tokens
 */

void setToken() {
    int c = 104;
    datatypes.insert({"inmt", c++});
    datatypes.insert({"floamt", c++});
    datatypes.insert({"chamr", c++});
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

/**
 * @brief Function for lexical analysis 
 */
void lexer() {
    
    FILE *fp;  // Declaring file pointer 
    int lineNo = 1; // Denote the current line no execution
    fp = freopen("input.txt", "r", stdin);  // Reading the file
    
    while(!feof(fp)) {  // Reading the file until the End of File
        while(true) {
            
            char ch = fgetc(fp);  // Scanning the next character in the file
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
                if(it != keywords.end()) { // Checking if the word scanned is a keyword
                    cout << "Token " << keywords[str] << ", string " << str << ", line number " << lineNo << endl; 
                    check = 1;
                }
                it = datatypes.find(str);
                if(it != datatypes.end()) { // Checking if the word scanned is a datatype
                    cout << "Token " << datatypes[str] << ", string " << str << ", line number " << lineNo << endl;  
                } else if (!check && str != "") { // Checking if the word scanned is an identifier
                    cout << "Token " << IDENTIFIER << ", string " << str << ", line number " << lineNo << endl; 
                }
                goto start;
            } 
            
            // Entry checkpoint for numericals
            else if((ch >= '0' && ch <= '9') or ch == '.') { 
                numerical:
                int count = 0;
                string str = "";
                while(((ch >= '0' && ch <= '9') or ch == '.') and count <= 1) {
                    if(ch == '.') { // Breaking the loop upon encountering a floating point
                        count++;
                        break;
                    }
                    str += ch;
                    ch = fgetc(fp);
                }
                while((ch >= '0' && ch <= '9') or ch == '.') {
                    str += ch;
                    ch = fgetc(fp);
                    if(ch == '.') { // Checking if there aren't any excess floating points
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
                    } else if(ch < '0' && ch > '9') { // Checking if there are any digits after the floating point
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
                if(ch == 'M') { // 'M' as a suffix to a numerical denotes a negative number 
                    str += 'M'; 
                }
                if(((ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z')) and ch != 'M') {
                    cout << "ERROR! : Not a numerical" << ", string " << str << ", line number " << lineNo << endl;
                    goto identifier;
                } else {
                    cout << "Token " << NUMERIC << ", string " << str << ", line number " << lineNo << endl;
                    if(ch == 'M') {
                        ch = fgetc(fp);
                    }
                    goto start;
                } 
            } 
            
            // Entry checkpoint for string literals
            else if(ch == '\"') {
                string str = "";
                int count = 0;
                ch = fgetc(fp);
                while(ch != '\"') {
                    if(ch == '\n' or ch == EOF)
                        break;
                    str += ch;
                    ch = fgetc(fp);
                }
                if(ch == '\"') {
                    cout << "Token " << STRING << ", string " << str << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not a string" << ", string " << str << ", line number " << lineNo << endl;
                }
            } 
            
            // Entry checkpoint for character
            else if(ch == '\'') {
                string str = "";
                int count = 0;
                ch = fgetc(fp);
                while(ch != '\'') {
                    if(ch == '\n' or ch == EOF)
                        break;
                    str += ch;
                    ch = fgetc(fp);
                }
                if(ch == '\'' && str.length() == 1) {
                    cout << "Token " << CHAR << ", string " << str << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not a character" << ", string " << str << ", line number " << lineNo << endl;
                } 
            } 
            
            //Entry checkpoint for comments
            else if(ch == '$') {
                string str = "$";
                ch = fgetc(fp);
                while(ch != '$') { // Checking for the comment to terminate
                    if(ch == EOF) {
                        cout << "ERROR! : Comment not terminated" << ", string " << str << ", line number " << lineNo << endl;
                        break;
                    }
                    str += ch;
                    ch = fgetc(fp);
                }
            } 
            
            //Entry checkpoint for operators
            else if(ch == '+') {
                ch = fgetc(fp);
                if(ch == '+') { // Condition for "++" operator
                    cout << "Token " << operators["++"] << ", string " << "++" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or ch == ' ') { // Condtion for '+' operator
                    cout << "Token " << operators["+"] << ", string " << "+" << ", line number " << lineNo << endl;
                    if(ch != ' ')
                    goto numerical;
                } else if(ch == '=') { // Condition for "+=" operator
                    cout << "Token " << operators["+="] << ", string " << "+=" << ", line number " << lineNo << endl;
                } else { 
                    cout << "ERROR! : Not an operator" << ", string " << "+" + ch << ", line number " << lineNo << endl;
                }
            } 
            else if(ch == '-') {
                ch = fgetc(fp);
                if(ch == '-') { // Condition for "--" operator
                    cout << "Token " << operators["--"] << ", string " << "--" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or ch == ' ') { // Condition for '-' operator
                    cout << "Token " << operators["-"] << ", string " << "-" << ", line number " << lineNo << endl;
                    goto numerical;
                } else if(ch == '=') { // Condition for "-=" operator
                    cout << "Token " << operators["-="] << ", string " << "-=" << ", line number " << lineNo << endl;
                } else { 
                    cout << "ERROR! : Not an operator" << ", string " << "-" + ch << ", line number " << lineNo << endl;
                }
            } 
            else if(ch == '*') { // Condition for '*' operator
                cout << "Token " << operators["*"] << ", string " << "*" << ", line number " << lineNo << endl;
            } 
            else if(ch == '/') { // Condition for '/' operator
                cout << "Token " << operators["/"] << ", string " << "/" << ", line number " << lineNo << endl;
            } 
            else if(ch == '%') { // Condition for '%' operator
                cout << "Token " << operators["%"] << ", string " << "%" << ", line number " << lineNo << endl;
            } 
            else if(ch == ',') { // Condition for ',' operator
                cout << "Token " << operators[","] << ", string " << "," << ", line number " << lineNo << endl;
            } 
            else if(ch == ';') { // Condition for ';' operator
                cout << "Token " << operators[";"] << ", string " << ";" << ", line number " << lineNo << endl;
            } 
            else if(ch == '(') { // Condition for '(' operator
                cout << "Token " << operators["("] << ", string " << "(" << ", line number " << lineNo << endl;
            } 
            else if(ch == ')') { // Condition for ')' operator
                cout << "Token " << operators[")"] << ", string " << ")" << ", line number " << lineNo << endl;
            } 
            else if(ch == '[') { // Condition for '[' operator
                cout << "Token " << operators["["] << ", string " << "[" << ", line number " << lineNo << endl;
            } 
            else if(ch == ']') { // Condition for ']' operator
                cout << "Token " << operators["]"] << ", string " << "]" << ", line number " << lineNo << endl;
            } 
            else if(ch == '{') { // Condition for '{' operator
                cout << "Token " << operators["{"] << ", string " << "{" << ", line number " << lineNo << endl;
            } 
            else if(ch == '}') { // Condition for '}' operator
                cout << "Token " << operators["}"] << ", string " << "}" << ", line number " << lineNo << endl;
            } 
            else if(ch == '&') {
                ch = fgetc(fp);
                if(ch == '&') { // Condition for "&&" operator
                    cout << "Token " << operators["&&"] << ", string " << "&&" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == ' ') { // Condition for '&' operator
                    cout << "Token " << operators["&"] << ", string " << "&" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "&" + ch << ", line number " << lineNo << endl;
                }
            } 
            else if(ch == '|') {
                ch = fgetc(fp);
                if(ch == '|') { // Condition for "||" operator
                    cout << "Token " << operators["||"] << ", string " << "||" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == ' ') { // Condition for '|' operator
                    cout << "Token " << operators["|"] << ", string " << "|" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "|" + ch << ", line number " << lineNo << endl;
                }
            } 
            else if(ch == '!') {
                ch = fgetc(fp);
                if(ch == '=') { // Condition for "!=" operator
                    cout << "Token " << operators["!="] << ", string " << "!=" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == ' ') { // Condition for '!' operator
                    cout << "Token " << operators["!"] << ", string " << "!" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "!" + ch << ", line number " << lineNo << endl;
                } 
            } 
            else if(ch == '<') {
                ch = fgetc(fp);
                if(ch == '<') { // Condition for "<<" operator
                    cout << "Token " << operators["<<"] << ", string " << "<<" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' or ch <= 'Z') or ch == ' ') { // Condition for '<' operator
                    cout << "Token " << operators["<"] << ", string " << "<" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else if(ch == '=') { // Condition for "<=" operator
                    cout << "Token " << operators["<="] << ", string " << "<=" << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "<" + ch << ", line number " << lineNo << endl;
                }
            }
            else if(ch == '>') {
                ch = fgetc(fp);
                if(ch == '>') { // Condition for ">>" operator
                    cout << "Token " << operators[">>"] << ", string " << ">>" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' or ch <= 'Z') or ch == ' ') { // Condition for '>' operator
                    cout << "Token " << operators[">"] << ", string " << ">" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else if(ch == '=') { // Condition for ">="" operator
                    cout << "Token " << operators[">="] << ", string " << ">=" << ", line number " << lineNo << endl;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << ">" + ch << ", line number " << lineNo << endl;
                }
            } 
            else if (ch == '=') {
                ch = fgetc(fp);
                if (ch == '=') { // Condition for "==" operator
                    cout << "Token " << operators["=="] << ", string " << "==" << ", line number " << lineNo << endl;
                } else if((ch >= '0' and ch <= '9') or (ch >= 'a' and ch <= 'z') or (ch >= 'A' or ch <= 'Z') or ch == ' ') { // Condition for "=" operator
                    cout << "Token " << operators["="] << ", string " << "=" << ", line number " << lineNo << endl;
                    if(ch >= '0' and ch <= '9')
                        goto numerical;
                    else if(ch != ' ')
                        goto identifier;
                } else {
                    cout << "ERROR! : Not an operator" << ", string " << "=" + ch << ", line number " << lineNo << endl;
                }
            }
            if (ch == '\n' or ch == EOF) // Break the loop if file pointer reaches the end of line or end of file
                break;
        }
        label:
            lineNo++; // going on to the next line  
    }    
}

int32_t main() {
    setToken(); //inilisating tokens 
    lexer(); // calling the lexer function
    return 0;
}
