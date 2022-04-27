#include<bits/stdc++.h>
#include <fstream>
#include "Lexer.cpp"
 
using namespace std;
int new_temp = 1;
 
map<pair<int,string>,pair<char,int>> populate_parse_table1() { 
    map<pair<int,string>,pair<char,int>> mp;
    mp[{0,"id"}] = {'s',1};
    mp[{2,"id"}] = {'s',6};
    mp[{4,"id"}]= {'s',6};
    mp[{5,"id"}]= {'s',6};
    mp[{7,"id"}]= {'s',6};
    mp[{8,"id"}]= {'s',6};
    mp[{9,"id"}]= {'s',6};
    mp[{10,"id"}]= {'s',6};
    /**********************/
    mp[{1,":="}]= {'s',2};
    /**********************/
    mp[{3,"+"}]= {'s',7};
    mp[{6,"+"}]= {'r',7};
    mp[{11,"+"}]= {'s',7};
    mp[{12,"+"}]= {'s',7};
    mp[{13,"+"}]= {'s',7};
    mp[{14,"+"}]= {'s',7};
    mp[{15,"+"}]= {'s',7};
    mp[{16,"+"}]= {'s',7};
    mp[{17,"+"}]= {'r',6};
    /*********************/
    mp[{2,"-"}]= {'s',4};
    mp[{3,"-"}]= {'s',8};
    mp[{4,"-"}]= {'s',4};
    mp[{5,"-"}]= {'s',4};
    mp[{6,"-"}]= {'r',7};
    mp[{7,"-"}]= {'s',4};
    mp[{8,"-"}]= {'s',4};
    mp[{9,"-"}]= {'s',4};
    mp[{10,"-"}]= {'s',4};
    mp[{11,"-"}]= {'s',8};
    mp[{12,"-"}]= {'s',8};
    mp[{13,"-"}]= {'s',8};
    mp[{14,"-"}]= {'s',8};
    mp[{15,"-"}]= {'s',8};
    mp[{16,"-"}]= {'s',8};
    mp[{17,"-"}]= {'r',6};
    /*********************/
    mp[{3,"*"}]= {'s',9};
    mp[{6,"*"}]= {'r',7};
    mp[{11,"*"}]= {'s',9};
    mp[{12,"*"}]= {'s',9};
    mp[{13,"*"}]= {'s',9};
    mp[{14,"*"}]= {'s',9};
    mp[{15,"*"}]= {'s',9};
    mp[{16,"*"}]= {'s',9};
    mp[{17,"*"}]= {'r',6};
    /*********************/
    mp[{3,"/"}]= {'s',10};
    mp[{6,"/"}]= {'r',7};
    mp[{11,"/"}]= {'s',10};
    mp[{12,"/"}]= {'s',10};
    mp[{13,"/"}]= {'s',10};
    mp[{14,"/"}]= {'s',10};
    mp[{15,"/"}]= {'s',10};
    mp[{16,"/"}]= {'s',10};
    mp[{17,"/"}]= {'r',6};
    /********************/
    mp[{2,"("}]= {'s',5};
    mp[{4,"("}]= {'s',5};
    mp[{5,"("}]= {'s',5};
    mp[{7,"("}]= {'s',5};
    mp[{8,"("}]= {'s',5};
    mp[{9,"("}]= {'s',5};
    mp[{10,"("}]= {'s',5};
    /********************/
    mp[{6,")"}] = {'r',7};
    mp[{11,")"}] = {'r',5};
    mp[{12,")"}] = {'s',17};
    mp[{13,")"}] = {'r',1};
    mp[{14,")"}] = {'r',2};
    mp[{15,")"}] = {'r',3};
    mp[{16,")"}] = {'r',4};
    mp[{17,")"}] = {'r',6};
    /*********************/
    mp[{3,"$"}] = {'a',-1}; // accept
    mp[{6,"$"}] = {'r',7};
    mp[{11,"$"}] = {'r',5};
    mp[{12,"$"}] = {'s',17};
    mp[{13,"$"}] = {'r',1};
    mp[{14,"$"}] = {'r',2};
    mp[{15,"$"}] = {'r',3};
    mp[{16,"$"}] = {'r',4};
    mp[{17,"$"}] = {'r',6};
    /*********************/
    //GOTO 
    mp[{2,"E"}]= {'n',3};
    mp[{4,"E"}]= {'n',11};
    mp[{5,"E"}]= {'n',12};
    mp[{7,"E"}]= {'n',13};
    mp[{8,"E"}]= {'n',14};
    mp[{9,"E"}]= {'n',15};
    mp[{10,"E"}]= {'n',16};
    /*********************/
    return mp;
 
}
vector<string> get_rules(){
    vector<string>rules(50);
    rules[0] = "S -> id := E";
    rules[1] = "E -> E + E";
    rules[2] = "E -> E - E";
    rules[3] = "E -> E * E";
    rules[4] = "E -> E / E";
    rules[5] = "E -> - E";
    rules[6] = "E -> ( E )";
    rules[7] = "E -> id";
    return rules;
}
 
map<string,string> legit_T() {
    map<string,string> match;
    match["S"]="$";
    match["E"]="$";
    return match;
}
 
string newTemp(){
    string res = "t" + to_string(new_temp);
    new_temp++;
    return res;
}

int32_t main(){
	ofstream fout; // output file stream
    fout.open("output_for_immediate_code.txt");
    scanTokens("input_for_immediate_code.txt", "output_for_immediate_code.txt");
    map<pair<int,string>,pair<char,int>> parse_table = populate_parse_table1();
    stack<string>st;
    vector<string> rules = get_rules();
    st.push("0");
    int ptr = 0;
    vector<string> NT = {"S","E"};
    map<string,string>match = legit_T();
    stack<pair<string,string>> attribute_stk;
    while(ptr < token_list.size()) {
        stack<string> tmp = st;
        token tk = token_list[ptr];
        int token_num = tk.token_num;
        string input = symbol_table[token_num];
        if(parse_table.find({stoi(st.top()),input}) == parse_table.end()){
            // Error detected when parse table has empty entry
            cout<<"***************"<<endl;
            cout<<"* PARSE ERROR *"<<endl;
            cout<<"***************"<<endl;
            cout<<"================================================================="<<endl;
            string match_NT,match_terminal;
            int state;
            int matched=0;
            while(1){
                string t1 = st.top();
                st.pop();
                if(t1[0]<'0' || t1[0]>'9'){
                    continue;
                }
                int flg=0;
                for(auto i:NT){
                    if(parse_table.find({stoi(t1),i})!=parse_table.end()){
                        match_NT=i; 
                        state = stoi(t1);
                        st.push(t1);
                        st.push(match_NT);
                        flg=1;
                        break;
                    }
                }
                if(flg){
                    matched=1;
                    break;
                }
            }
            if(matched){
            match_terminal = match[match_NT];
            while(symbol_table[token_list[ptr].token_num]!=match_terminal){
                ptr++;
            }
            st.push(to_string(parse_table[{state,match_NT}].second));
            continue;}
 
        }
        pair<char,int> action = parse_table[{stoi(st.top()),input}];
        cout << "Input token : " << tk.lexeme << endl;
        cout << "Stack state : ";
        while(!tmp.empty()){
            cout<<tmp.top()<<" ";
            tmp.pop();
        }
        cout<<endl;
        if(action.first!='a'){
        cout << "Action : " << action.first << action.second<<endl;}
 
        if(action.first=='a'){
            cout << "Action : " << "acc" <<endl;
            cout<<"ACCEPTED"<<endl;
            string E_code = attribute_stk.top().second;
            string E_temp = attribute_stk.top().first;
            attribute_stk.pop();
            attribute_stk.pop();
            string id_tmp = attribute_stk.top().first;
            attribute_stk.pop();
            string S_code = E_code + id_tmp + ":="+E_temp + "\n";
            attribute_stk.push({"",S_code});
            break;
        }
        cout << "=================================================================" <<endl;
        if(action.first == 's'){
           st.push(input);
           st.push(to_string(action.second));  
           attribute_stk.push({tk.lexeme,""}); 
           ptr++;
        }
        if(action.first=='r'){
            string rule = rules[action.second];
            vector<string> v;
            stringstream ss(rule);
            string word;
            int cou=0;
            while(ss>>word){
                v.push_back(word);
                if(word!="''"){
                    cou++;
                }
            }
            int attr = cou-2;
            int tmp = 2 * (cou-2);
            while(tmp--){
                st.pop();
            }
            int nm = stoi(st.top());
            st.push(v[0]);
            pair<char,int> nxt_action = parse_table[{nm,v[0]}];
            st.push(to_string(nxt_action.second));
            if(action.second==7){
                string id_tmp = attribute_stk.top().first;
                while(attr--){
                attribute_stk.pop();
                }
                attribute_stk.push({id_tmp,""});
            } else if(action.second==6){
                attribute_stk.pop();
                attr--;
                string E1_tmp = attribute_stk.top().first;
                string E1_code = attribute_stk.top().second;
                while(attr--){
                attribute_stk.pop();
                }
                attribute_stk.push({E1_tmp,E1_code});
            } else if(action.second==5){
                string E_tmp = newTemp();
                string E_code = attribute_stk.top().second  + E_tmp + ":=" + "uminus " + attribute_stk.top().first + "\n";
                while(attr--){
                    attribute_stk.pop();
                }
                attribute_stk.push({E_tmp,E_code});
            } else if(action.second==1){
                string E_tmp = newTemp();
                string E2_temp = attribute_stk.top().first;
                string E2_code = attribute_stk.top().second;
                attribute_stk.pop();
                attr--;
                attribute_stk.pop();
                attr--;
                string E1_temp = attribute_stk.top().first;
                string E1_code = attribute_stk.top().second;
                string E_code = E1_code + E2_code + E_tmp + ":=" + E1_temp + "+" + E2_temp + "\n";
                while(attr--){
                    attribute_stk.pop();
                }
                attribute_stk.push({E_tmp,E_code});
            } else if(action.second==2){
                string E_tmp = newTemp();
                string E2_temp = attribute_stk.top().first;
                string E2_code = attribute_stk.top().second;
                attribute_stk.pop();
                attr--;
                attribute_stk.pop();
                attr--;
                string E1_temp = attribute_stk.top().first;
                string E1_code = attribute_stk.top().second;
                string E_code = E1_code + E2_code + E_tmp + ":=" + E1_temp + "-" + E2_temp + "\n";
                while(attr--){
                    attribute_stk.pop();
                }
                attribute_stk.push({E_tmp,E_code});
            } else if(action.second==3){
                string E_tmp = newTemp();
                string E2_temp = attribute_stk.top().first;
                string E2_code = attribute_stk.top().second;
                attribute_stk.pop();
                attr--;
                attribute_stk.pop();
                attr--;
                string E1_temp = attribute_stk.top().first;
                string E1_code = attribute_stk.top().second;
                string E_code = E1_code + E2_code + E_tmp + ":=" + E1_temp + "*" + E2_temp + "\n";
                while(attr--) {
                    attribute_stk.pop();
                }
                attribute_stk.push({E_tmp,E_code});
            } else if(action.second==4){
                string E_tmp = newTemp();
                string E2_temp = attribute_stk.top().first;
                string E2_code = attribute_stk.top().second;
                attribute_stk.pop();
                attr--;
                attribute_stk.pop();
                attr--;
                string E1_temp = attribute_stk.top().first;
                string E1_code = attribute_stk.top().second;
                string E_code = E1_code + E2_code + E_tmp + ":=" + E1_temp + "/" + E2_temp + "\n";
                while(attr--){
                    attribute_stk.pop();
                }
                attribute_stk.push({E_tmp,E_code});
            }
        }
    }
    string intermediate_code = attribute_stk.top().second;
    cout << endl;
    cout << "---------------------"<<endl;
    cout << "Intermediate code for arithmetic_expression"<<endl;
    cout << endl;
    cout << intermediate_code;
    cout << "---------------------"<<endl;
    fout << "---------------------"<<endl;
    fout << "Intermediate code for arithmetic_expression : "<<endl;
    fout << endl;
    fout << intermediate_code;
    fout << "---------------------"<<endl;
	return 0;
}