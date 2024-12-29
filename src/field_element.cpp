#include<iostream>
#include "field_arithmetic.hpp"

using namespace std;

void galois_field_element::read_element(string in){
    element.reset();
    size_t len = in.length();
    if(len > element.size()){
        throw invalid_argument("Input is too long");
    }
    else{
        for(int i = 0; i < len; i++){
            element[i] = in[len-1-i]-'0';
        }
    }
}

void galois_field_element::print_element(){
    cout << element << "\n";
    // for(size_t i = element.size()-1; i >=0; i--){
    //     cout << element[i];
    // }
    // cout << "\n";
}

galois_field_element galois_field_element::operator+(galois_field_element& in){
    galois_field_element out;
    out.element = element^in.element;
    return out;
}

void galois_field_element::operator+=(galois_field_element& in){
    element^=in.element;
}

galois_field_element::galois_field_element(){}

galois_field_element::galois_field_element(const galois_field_element& obj){
    element = obj.element;
}

galois_field_element& galois_field_element::operator=(const galois_field_element& obj){
    if(this == &obj){
        return *this;
    }
    element = obj.element;
    return *this;
}

void galois_field_element::cycl_shift_1_to_low(){
    bool temp = element[0];
    element>>=1;
    element[172] = temp;
}

void galois_field_element::cycl_shift_1_to_high(){
    bool temp = element[172];
    element<<=1;
    element[0] = temp;
}

galois_field_element galois_field_element::cycl_shift_to_low(int shift){
    galois_field_element out;
    out.element.reset();
    out.element = (element>>shift)|(element<<(173-shift));
    return out;
}

galois_field_element galois_field_element::cycl_shift_to_high(int shift){
    galois_field_element out;
    out.element = (element<<shift)|(element>>(173-shift));
    return out;
}