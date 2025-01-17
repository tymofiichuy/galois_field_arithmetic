#include<iostream>
#include "field_arithmetic.hpp"

using namespace std;

int main(){
    string pow = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    galois_field_element el1, el2, el3, out1, out2;
    galois_field_poly F_poly;
    F_poly.set_powers();
    galois_field_norm F_norm;
    F_norm.set_matrix();

    el1.read_element("10111111111011011001101010010011010010110010110110100011011000011101110101110110100000110001011010111111101000001000101110101101001001010110001101111001000000001010111011011");
    el2.read_element("11111010011001000111100100111110101001010001101000100100101010011011110011000111111111100111011111110110111100101010100110001010001110011100111101111111010000101010101011110");
    el3.read_element("01110110001010001110011111011110111110111011110000011001001110110000111011011110110111000010100011011001110011110111100010000000111001100001111111111010001011011001100010001");

    //equalty 1, polynomial basis
    out1 = F_poly.field_mult(el1+el2, el3);
    out2 = F_poly.field_mult(el1, el3);
    out2 += F_poly.field_mult(el2, el3);
    cout << "Equalty 1, polynomial basis:\n";
    out1.print_element();
    out2.print_element();
    cout << "\n";

    //equalty 1, normal basis
    out1 = F_norm.field_mult(el1+el2, el3);
    out2 = F_norm.field_mult(el1, el3);
    out2 += F_norm.field_mult(el2, el3);
    cout << "Equalty 1, normal basis:\n";
    out1.print_element();
    out2.print_element();
    cout << "\n";

    //equalty 2, polynomial basis
    out1 = F_poly.field_power(el1, pow);
    cout << "Equalty 2, polynomial basis:\n";
    out1.print_element();
    cout << "\n";

    //equalty 2, normal basis
    out1 = F_norm.field_power(el1, pow);
    cout << "Equalty 2, normal basis:\n";
    out1.print_element();

    return 0;
}
