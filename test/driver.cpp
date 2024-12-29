#include<iostream>
#include "field_arithmetic.hpp"

using namespace std;

int main(){
    galois_field_poly F_poly;
    F_poly.set_powers();
    galois_field_norm F_norm;
    F_norm.set_matrix();

    bool tr;
    galois_field_element el1, el2, out;
    el1.read_element("10111111111011011001101010010011010010110010110110100011011000011101110101110110100000110001011010111111101000001000101110101101001001010110001101111001000000001010111011011");
    el2.read_element("11111010011001000111100100111110101001010001101000100100101010011011110011000111111111100111011111110110111100101010100110001010001110011100111101111111010000101010101011110");
    string power = "01110110001010001110011111011110111110111011110000011001001110110000111011011110110111000010100011011001110011110111100010000000111001100001111111111010001011011001100010001";
    
    cout << "A: ";
    el1.print_element();
    cout << "B: ";
    el2.print_element();
    cout << "N: " << power << "\n\n";

    out = el1 + el2;
    cout << "Polynomial basis:\nA+B: ";
    out.print_element();
    out = F_poly.field_mult(el1, el2);
    cout << "A*B: ";
    out.print_element();
    out = F_poly.field_square(el1);
    cout << "A^2: ";
    out.print_element();
    out = F_poly.invert(el1);
    cout << "1/A: ";
    out.print_element();
    out = F_poly.field_power(el1, power);
    cout << "A^N: ";
    out.print_element();
    tr = F_poly.trace(el1);
    cout << "TrA: " << tr;

    out = el1 + el2;
    cout << "\n\nNormal basis:\nA+B: ";
    out.print_element();
    out = F_norm.field_mult(el1, el2);
    cout << "A*B: ";
    out.print_element();
    out = F_norm.field_square(el1);
    cout << "A^2: ";
    out.print_element();
    out = F_norm.invert(el1);
    cout << "1/A: ";
    out.print_element();
    out = F_norm.field_power(el1, power);
    cout << "A^N: ";
    out.print_element();
    tr = F_norm.trace(el1);
    cout << "TrA: " << tr;

    return 0;
}