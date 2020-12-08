#include <iostream>
#include "string.hpp"

int main() {
    String str("Long cards are bad");
    String car("cards");
    std::cout << str << '\n';
    std::cout << car << '\n';
    std::cout << str.BMH_search(car) << '\n';
    str.delete_substr(car);
    std::cout << str << '\n';
    return 0;
}
