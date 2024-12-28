#include<iostream>
#include "field_arithmetic.hpp"

using namespace std;

galois_field::galois_field(){
    powers = new galois_field_element[345];
}

galois_field::~galois_field(){
    if(powers){
        delete[] powers;
    }
}

void galois_field::set_powers(){
    int i = 0;    
    galois_field_element el;
    el.element.set(0, true);
    bitset<173> max_power;
    max_power.set(0, true);
    max_power.set(1, true);
    max_power.set(2, true);
    max_power.set(10, true);
    while(i<=344){
        while(el.element[order-1]!=1){
            powers[i] = el;
            el.element<<=1;
            i++;
        }
        powers[i] = el;
        el.element<<=1;
        el.element^=max_power;
        i++;
    }
}

galois_field_element galois_field::field_mult(galois_field_element& in1, galois_field_element& in2){
    galois_field_element out;
    for(int i = 0; i < order; i++){
        if(in1.element[i]){
            for(int j = 0; j < order; j++){
                if(in2.element[j]){
                    out+=powers[i+j];
                }
            }            
        }
    }
    return out;
}

galois_field_element galois_field::field_square(galois_field_element& in){
    galois_field_element out;
    for(int i = 0; i < order; i++){
        if(in.element[i]){
            out+=powers[2*i];
        }
    }
    return out;
}

galois_field_element galois_field::field_power(galois_field_element& in, string power){
    bitset<173> pow;
    galois_field_element out;
    size_t len = power.length();
    if(len > pow.size()){
        throw invalid_argument("Power is too long");
    }
    else{
        for(int i = 0; i < len; i++){
            pow[i] = power[len-1-i]-'0';
        }
    }

    out.element.set(0, true);
    int i = order-1;
    while(pow[i] == 0){
        i--;
    }
    while(i>=0){
        if(pow[i] == 1){
            out = field_mult(out, in);
        }
        if(i!=0){
            out = field_square(out);
        }
        i--;
    }
    return out;
}

galois_field_element galois_field::invert(galois_field_element& in){
    bitset<173> power;
    power.set();
    power.set(0, false);

    galois_field_element out;
    
    out.element.set(0, true);
    int i = order-1;
    while(i>=0){
        if(power[i] == 1){
            out = field_mult(out, in);
        }
        if(i!=0){
            out = field_square(out);
        }
        i--;
    }
    return out;
}

bool galois_field::trace(galois_field_element& in){
    galois_field_element out, temp;
    temp = in;
    for(int i = 0; i < order; i++){
        out += temp;
        temp = field_square(temp);
    }
    return out.element[0];
}