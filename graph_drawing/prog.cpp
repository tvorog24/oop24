#include "funcs.h"
#include "path_menu.h"
#include <iostream>

using namespace Prog;
/**
 * @mainpage Basic information
 * 
 * This is the main page of documentation.<br>Listing of project files with short descriptions of their content:
 * 
 *  - @ref prog.cpp -- contains only main()
 * 
 *  - @ref funcs.cpp -- contains processing functions
 * 
 *  - @ref input.cpp -- contains input functions
 * 
 *  - @ref path_menu.cpp -- contains dialogue function
 * 
 *  - @ref funcs.h -- describes structures
 * 
 */
/**
 * @file
 */
/**
 * @brief Draws graph and highlights path according adjacency table
 * @return 0, in case of success
 * @return 1, in case of exception 
 */
int main() 
{
    Matrix matrix;
    try {
        matrix = input();
        output(matrix);
        path_input_options(matrix);
        draw_graph();
        erase(matrix);
    }
    catch(const std::bad_alloc& ba) {
        std::cerr << "Not enough memory" << std::endl;
        erase(matrix);
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        erase(matrix);
        return 1;
    }
    return 0;
}