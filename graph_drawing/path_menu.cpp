#include "path_menu.h"
#include "input.h"

/**
 * @file
 */

namespace Prog {
    /**
     * @brief Provides a choice of which type of vertices succession to use or not to use it at all
     * @param matrix adjacency table
     * @throws runtime_error check get_number() throws
     * @throws runtime_error check create_dot_file() throws
     * @throws bad_alloc check array_input() throws
     */
    void path_input_options(const Matrix& matrix) 
    {
        std::cout << "No path (0), int* (1), vector<int> (2): ";
        switch (get_number(std::cin, std::cout, 0, 2)) {
            case 0: {
                create_dot_file(matrix);
                break;
            }
            case 1: {
                int length = 0;
                const int* path = array_input(length);
                try {
                    create_dot_file(matrix, path, length);
                }
                catch(...) {
                    delete[] path;
                    throw;
                }  
                delete[] path;
                break;
            }
            case 2: {
                std::vector<int> path = array_input();
                create_dot_file(matrix, path);
                break;
            }
        }
    }    
}
