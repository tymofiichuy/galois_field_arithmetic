#include "field_arithmetic.hpp"

using namespace std;

galois_field::galois_field(){
    powers = new galois_field_element[345];
}

galois_field::~galois_field(){
    if(powers){
        delete powers;
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
}