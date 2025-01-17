#include<iostream>
#include<random>
#include<chrono>
#include "field_arithmetic.hpp"

using namespace std;

string random_string_173(mt19937& mt){
    string out;
    out.reserve(173);
    bernoulli_distribution bit_dist(0.5);
    for(int i = 0; i < 173; i++){
        out.push_back(bit_dist(mt)?'1':'0');
    }
    return out;
}

int main(){
    random_device rd;
    mt19937 mt(rd());

    galois_field_element el1, el2;
    string str;
    galois_field_poly F_poly;
    F_poly.set_powers();
    galois_field_norm F_norm;
    F_norm.set_matrix();

    chrono::microseconds p_mult_total(0);
    chrono::microseconds p_trace_total(0);
    chrono::microseconds p_sq_total(0);
    chrono::microseconds p_pow_total(0);
    chrono::microseconds p_inv_total(0);

    chrono::microseconds n_mult_total(0);
    chrono::microseconds n_trace_total(0);
    chrono::microseconds n_sq_total(0);
    chrono::microseconds n_pow_total(0);
    chrono::microseconds n_inv_total(0);

    for(int i = 0; i < 250; i++){
        str = random_string_173(mt);
        el1.read_element(str);
        str = random_string_173(mt);
        el2.read_element(str);
        str = random_string_173(mt);

        auto start = chrono::high_resolution_clock::now();
        F_poly.field_mult(el1, el2);
        auto end = chrono::high_resolution_clock::now();
        p_mult_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_poly.trace(el1);
        end = chrono::high_resolution_clock::now();
        p_trace_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_poly.field_square(el1);
        end = chrono::high_resolution_clock::now();
        p_sq_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_poly.field_power(el1, str);
        end = chrono::high_resolution_clock::now();
        p_pow_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_poly.invert(el1);
        end = chrono::high_resolution_clock::now();
        p_inv_total+=chrono::duration_cast<chrono::microseconds>(end - start);


        start = chrono::high_resolution_clock::now();
        F_norm.field_mult(el1, el2);
        end = chrono::high_resolution_clock::now();
        n_mult_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_norm.trace(el1);
        end = chrono::high_resolution_clock::now();
        n_trace_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_norm.field_square(el1);
        end = chrono::high_resolution_clock::now();
        n_sq_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_norm.field_power(el1, str);
        end = chrono::high_resolution_clock::now();
        n_pow_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        start = chrono::high_resolution_clock::now();
        F_norm.invert(el1);
        end = chrono::high_resolution_clock::now();
        n_inv_total+=chrono::duration_cast<chrono::microseconds>(end - start);

        if(i%25 == 0){
            cout << (i/25)*10 << "% ";
        }
    }
    cout << "100%\n\n";
    cout << "Polynomial basis: mult - " << p_mult_total.count()/1000 << ", trace - " << p_trace_total.count()/1000 
    << ", square - " << p_sq_total.count()/1000 << ", pow - " << p_pow_total.count()/1000 << ", invert - " 
    << p_inv_total.count()/1000
    << ".\nNormal basis: mult - " << n_mult_total.count()/1000 << ", trace - " << n_trace_total.count()/1000 
    << ", square - " << n_sq_total.count()/1000 << ", pow - " << n_pow_total.count()/1000 << ", invert - " 
    << n_inv_total.count()/1000 << ".";

    return 0;
}