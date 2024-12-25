#include<iostream>
#include "field_arithmetic.hpp"

using namespace std;

void field_element::read_element(string& in){
    element.reset();
    int len = in.length();
    if(len > element.size()){
        throw invalid_argument("Input is too long");
    }
    else{
        for(int i = 0; i < len; i++){
            element[i] = in[len-1-i]-'0';
        }
    }
}

void field_element::print_element(){
    for(int i = element.size()-1; i >=0; i--){
        cout << element[i];
    }
    cout << "\n";
}