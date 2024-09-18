#ifndef FUNCS_H
#define FUNCS_H

#include <string>
#include <vector>
#include <iostream>

/**
 * @file
 */

namespace Prog {
    /**
     * @brief Row of an adjacency table
     * @details To be filled with 0 and 1
     */
    struct Line {
        int* arr = nullptr;
    };
    /**
     * @brief An adjacency table
     * @details Describes connections between vertices: 1 -- connection exists, 0 -- no connection
     */
    struct Matrix {  // adjacency table
        int n = 0;
        Line* lines = nullptr;
    };
    Matrix input(std::istream& in = std::cin, std::ostream& out = std::cout);
    void output(const Matrix& matrix, std::string message = "Adjacency matrix", std::ostream& out = std::cout);
    void erase(Matrix& matrix);
    bool check_way_existence(const Matrix& matrix, const int* path, const int length);
    bool check_way_existence(const Matrix& matrix, const std::vector<int>& path);
    void create_dot_file(const Matrix& matrix, std::string filename = "graph.txt");
    void create_dot_file(const Matrix& matrix, const int* path, const int length, std::string filename = "graph.txt");
    void create_dot_file(const Matrix& matrix, const std::vector<int>& path, std::string filename = "graph.txt");
    void draw_graph(std::string filename = "graph.txt");
    int* array_input(int& length, std::istream& in = std::cin, std::ostream& out = std::cout);
    std::vector<int> array_input(std::istream& in = std::cin, std::ostream& out = std::cout);
    void path_input_options(const Matrix& matrix);
}

#endif