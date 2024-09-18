#include "input.h"
#include <iostream>
#include <cstring>

/**
 * @file
 */

namespace Prog {
    /**
     * @brief Gets an integer in a given range
     * @param in input stream
     * @param out output stream
     * @param min min number allowed to be entered
     * @param max max number allowed to be entered
     * @return an entered number
     * @throws runtime_error when end of file reached 
     * @throws runtime_error when input stream has flag "bad"
     */
    int get_number(std::istream& in, std::ostream& out, int min, int max) 
    {
        int n;
        while (true) {
            in >> n;
            if (in.eof()) {
                throw std::runtime_error("EOF");
            }
            else if (in.bad()) {
                throw std::runtime_error(strerror(errno));
            }
            else if (in.fail() || n < min || n > max) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                out << "Wrong type of data. Try again: ";
            }
            else {
                return n;
            }
        }
    }
}
