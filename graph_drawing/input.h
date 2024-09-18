#ifndef INPUT_H
#define INPUT_H

#include <limits>
#include <iostream>

namespace Prog {
    int get_number(std::istream& in = std::cin, std::ostream& out = std::cout,
     int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
}

#endif