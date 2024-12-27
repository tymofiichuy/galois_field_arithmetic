#pragma once

#include<bitset>
#include<string>

class galois_field_element{
private:
    std::bitset<173> element;
public:
    void read_element(std::string in);
    void print_element();

    galois_field_element operator+ (galois_field_element& in);
    void operator+= (galois_field_element& in);

    friend class galois_field;
};

class galois_field{
private:
    int order = 173;
    galois_field_element* powers;
public:
    void set_powers();

    galois_field_element field_mult(galois_field_element& in1, galois_field_element& in2);

    galois_field();
    ~galois_field();
};