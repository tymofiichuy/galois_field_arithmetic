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
    galois_field_element& operator=(const galois_field_element& obj);
    void cycl_shift_1_to_low();
    void cycl_shift_1_to_high();

    galois_field_element();
    galois_field_element(const galois_field_element& obj);

    friend class galois_field_poly;
    friend class galois_field_norm;
};

class galois_field_poly{
private:
    int order = 173;
    galois_field_element* powers;
public:
    void set_powers();

    galois_field_element get_0();
    galois_field_element get_1();

    galois_field_element field_mult(galois_field_element& in1, galois_field_element& in2);
    galois_field_element field_square(galois_field_element& in);
    galois_field_element field_power(galois_field_element& in, std::string power);
    galois_field_element invert(galois_field_element& in);
    bool trace(galois_field_element& in);

    galois_field_poly();
    ~galois_field_poly();
};

class galois_field_norm{
// private:
public:
    int order = 173;
    bool** mult_matrix = nullptr;
// public:
    void set_matrix();

    galois_field_element get_0();
    galois_field_element get_1();

    galois_field_element field_mult(galois_field_element in1, galois_field_element in2);

    galois_field_norm();
    ~galois_field_norm();
};