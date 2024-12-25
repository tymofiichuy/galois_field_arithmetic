#pragma once

#include<bitset>
#include<string>

class char_2_galois_field{

};

class field_element{
private:
    std::bitset<173> element;
public:
    void read_element(std::string& in);
    void print_element();
};