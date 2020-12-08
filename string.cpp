//
// Created by slaventy on 22.11.2020.
//
#include "string.hpp"
String ::String(const char* s){
    line = new char[strlen(s) +1];
    for(len = 0; s[len] != '\0'; line[len] = s[len], len++);
    line[len] = '\0';
}
String ::String(int l){
    line = new char[l];
    len = 0;
    line[0] = '\0';
}


String ::String(String & s){
    line = new char[s.len +1];
    for(len = 0; line[len] != '\0'; line[len] = s[len], len++);
    line[len] = '\0';
}
char & String::operator [](int i){
    if(i < 0 || i >= len){
        std::cout << "Out of bounds\n";
        return line[0];
    }
    return line[i];
}

String & String::operator += (String &s){
    char *t = new char[len +1];
    strcpy(t, line);
    delete [] line;
    len += s.len;
    line = new char [len +1];
    strcpy(line, t);
    strcat(line, s.line);
    delete [] t;
    return *this;
}

String & String::operator = (const String &s){
    if(this->line != s.line){
        delete [] line;
        len = s.len +1;
        line = new char[len];
        strcpy(line, s.line);
    }
    return *this;
}
String String::operator + (String & s){
    String z(len + s.len +1);
    strcpy(z.line, line);
    strcat(z.line, s.line);
    z.len = strlen(z.line);
    return z;
}

std::ostream & operator << (std::ostream & out, String & s){
    out << s.line;
    return out;
}

int String::KMP_search(String & s){
    int j = 0, k = -1, NewJ[s.len];
    NewJ[0] = -1;
    while(j < s.len - 1){
        if((k >= 0) && (s[j] != s[k])){
            k = NewJ[k];
        } else {
            k++;
            j++;
            if(s[j] == s[k]){
                NewJ[j] = NewJ[k];
            } else {
                NewJ[j] = k;
            }
        }
    }

    int i = 0;
    j = 0;

    while(j < s.len){
        if(i >= len)return -1;
        while(j >= 0 && line[i] != s[j]){
            j = NewJ[j];
        }
        i++;
        j++;
    }
    return i - s.len;
}

int String::BMH_search(String &s){
    int P[256];
    for(int i = 0; i < 256; i++){
        P[i] = s.len;
    }
    for(int i = 0; i < s.len - 1; i++){
        P[(int)s[i]] = s.len - 1 - i;
    }

    int i = s.len - 1, j = s.len - 1;
    while(i <= len){
        if(line[i] == s[j]){
            if(j == 0)return i;
            i--; j--;
        } else {
            i+=P[(int)line[i]];
            if(i > len){
                std::cout<< "No match" << '\n';
                return -1;}
            j = s.len - 1;
        }
    }
}

String String::delete_substr(String & s){
    int a = BMH_search(s);
    String one;
    one.line = new char[a +1];
    for(one.len = 0; one.len != a; one.line[one.len] = line[one.len], one.len++);
    one.line[one.len] = '\0';
    String two;
    two.line = new char[len-a-s.len +1];
    int beg = a + s.len;
    for(two.len = 0; line[beg + two.len] != '\0'; two.line[two.len] = line[beg + two.len], two.len++);
    two.line[two.len] = '\0';
    *this = one + two;
    return *this;
}