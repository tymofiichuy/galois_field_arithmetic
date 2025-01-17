#include<iostream>
#include "field_arithmetic.hpp"
#include "long_arithmetic.hpp"

using namespace std;

galois_field_poly::galois_field_poly(){
    powers = new galois_field_element[345];
}

galois_field_poly::~galois_field_poly(){
    if(powers){
        delete[] powers;
    }
}

void galois_field_poly::set_powers(){
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

galois_field_element galois_field_poly::field_mult(galois_field_element& in1, galois_field_element& in2){
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

galois_field_element galois_field_poly::field_square(galois_field_element& in){
    galois_field_element out;
    for(int i = 0; i < order; i++){
        if(in.element[i]){
            out+=powers[2*i];
        }
    }
    return out;
}

galois_field_element galois_field_poly::field_power(galois_field_element& in, string power){
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

galois_field_element galois_field_poly::invert(galois_field_element& in){
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

bool galois_field_poly::trace(galois_field_element& in){
    galois_field_element out, temp;
    temp = in;
    for(int i = 0; i < order; i++){
        out += temp;
        temp = field_square(temp);
    }
    return out.element[0];
}

galois_field_element galois_field_poly::get_0(){
    galois_field_element out;
    return out;
}

galois_field_element galois_field_poly::get_1(){
    galois_field_element out;
    out.element.set(0, true);
    return out;
}

galois_field_norm::galois_field_norm(){
    mult_matrix = new bool*[order];
    for(int i = 0; i < order; i++){
        mult_matrix[i] = new bool[order]();
    }
}

galois_field_norm::~galois_field_norm(){
    if(mult_matrix){
        for(int i = 0; i < order; i++){
            delete[] mult_matrix[i];
        }
        delete[] mult_matrix;
        mult_matrix = nullptr;
    }
}

void galois_field_norm::set_matrix(){
    long_int reduc(0, 3), pow(0, 3), modulo(347, 3), temp(0, 3), exp1(346, 3), exp2(1, 3);
    for(int i = 0; i < order; i++){
        for(int j = i; j < order; j++){
            pow.reset();
            if(i != j){
                pow.set_bit(1, i);
                pow.set_bit(1, j);                
            }
            else{
                pow.set_bit(1, i+1);
            }
            long_arithmetic::long_divide(pow, modulo, reduc, pow);
            if(reduc == exp1 || reduc == exp2){
                mult_matrix[i][j] = true;
                mult_matrix[j][i] = true;
            }
            else{
                pow.reset();
                pow.set_bit(1, j);
                temp.set_bit(1, i);
                long_arithmetic::long_sub(pow, temp, pow);
                temp.set_bit(0, i);
                long_arithmetic::long_divide(pow, modulo, reduc, pow);
                if(reduc == exp1 || reduc == exp2){
                    mult_matrix[i][j] = true;
                    mult_matrix[j][i] = true;
                }
                else{
                    mult_matrix[i][j] = false;
                    mult_matrix[j][i] = false;
                }
            }
        }
    }
}

galois_field_element galois_field_norm::field_mult(galois_field_element in1, galois_field_element in2){
    galois_field_element out, temp;
    bool c_temp;

    for(int i = 0; i < order; i++){
        if(i!=0){
            in1.cycl_shift_1_to_high();
            in2.cycl_shift_1_to_high();
        }

        for(int j = 0; j < order; j++){
            c_temp = false;
            for(int k = 0; k < order; k++){
                if(mult_matrix[order-j-1][order-k-1]){
                    c_temp^=in1.element[k];
                }
            }
            temp.element[j] = c_temp;
        }

        c_temp = false;
        for(int j = 0; j < order; j++){
            if(temp.element[j]){
                c_temp^=in2.element[j];
            }
        }
        out.element[order-i-1] = c_temp;
    }

    return out;
}

galois_field_element galois_field_norm::field_square(galois_field_element& in){
    galois_field_element out(in);
    out.cycl_shift_1_to_low();
    return out;
}

galois_field_element galois_field_norm::field_power(galois_field_element& in, string power){
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

    out.element.set();
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

// galois_field_element galois_field_norm::invert(galois_field_element& in){
//     galois_field_element temp, inverted(in);
//     int power = order - 1, index = 1, iter = 0;
//     while((power>>iter)!=0){
//         iter++;
//     }
//     iter--;
//     while(iter>=0){
//         temp = inverted.cycl_shift_to_low(index);
//         inverted = field_mult(inverted, temp);
//         index<<=1;
//         if((power&(1<<iter))!=0){
//             inverted.cycl_shift_1_to_low();
//             inverted = field_mult(inverted, in);
//             index++;
//         }
//         iter--;
//     }
//     inverted.cycl_shift_1_to_low();
//     return inverted;
// }

galois_field_element galois_field_norm::invert(galois_field_element& in){
    bitset<173> power;
    power.set();
    power.set(0, false);

    galois_field_element out;
    
    out.element.set();
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

bool galois_field_norm::trace(galois_field_element& in){
    bool out = false;
    for(int i = 0; i < order; i++){
        out^=in.element[i];
    }
    return out;
}

galois_field_element galois_field_norm::get_0(){
    galois_field_element out;
    return out;
}

galois_field_element galois_field_norm::get_1(){
    galois_field_element out;
    out.element.set();
    return out;
}