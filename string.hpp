//
// Created by slaventy on 22.11.2020.
//

#ifndef CLASS_STRING_STRING_HPP
#define CLASS_STRING_STRING_HPP
#include <iostream>
#include <cstring>


class String : public std::error_code {
    char *line;
    int len;
public:
    explicit String(const char* s);
    explicit String(int l = 80);
    String(String & s);
    ~String(){delete [] line;}
    int Len(){return len;}
    char & operator [](int i);
    String & operator = (const String & s);
    String & operator += (String & s);
    String operator + (String &);
    friend std::ostream & operator << (std::ostream & out, String & s);
    int BMH_search(String & s);
    int KMP_search(String & s);
    String delete_substr(String & s);

};
#endif //CLASS_STRING_STRING_HPP
