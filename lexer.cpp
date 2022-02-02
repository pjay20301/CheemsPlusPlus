#include <bits/stdc++.h>
using namespace std;

map <string, int> operators, keywords, datatypes;

void setToken() {
    int c = 0;
    operators.insert({"inmt", c++});
    operators.insert({"floamt", c++});
    operators.insert({"strinmg", c++});
    operators.insert({"booml", c++});

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
}

int32_t main() {


    return 0;
}
