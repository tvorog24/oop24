#include "funcs.h"
#include "input.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>

/**
 * @file
 */

namespace Prog {
    /**
     * @brief Gets an adjacency table
     * @param in input stream
     * @param out output stream
     * @return an adjacency table
     * @throw runtime_error check get_number() throws
     * @throw bad_alloc when impossible to allocate memory with operator new
     */
    Matrix input(std::istream& in, std::ostream& out) 
    {
        Matrix matrix;
        try {
            out << "Enter the number of elements: ";
            matrix.n = get_number(in, out, 1);
            try {
                matrix.lines = new Line[matrix.n];
            }
            catch(const std::bad_alloc& ba) {
                matrix.lines = nullptr;
                throw;
            }
            for (int i=0; i<matrix.n; i++) {
                Line& line = matrix.lines[i];
                try {
                    line.arr = new int[matrix.n];
                }
                catch(const std::bad_alloc& ba) {
                    line.arr = nullptr;
                    erase(matrix);
                    throw;
                }
                for (int j = i + 1; j < matrix.n; j++) {
                    out << "Connection between " << i << " and " << j << ": ";
                    line.arr[j] = get_number(in, out, 0, 1);
                }
            } 
            for (int i=0; i<matrix.n; i++) {
                for (int j = 0; j < i; j++) {
                    matrix.lines[i].arr[j] = matrix.lines[j].arr[i];
                }
                matrix.lines[i].arr[i] = 1;
            }
        }
        catch(...) {
            erase(matrix);
            throw;
        }
        return matrix;
    }
    /**
     * @brief Prints an adjacency table
     * @param matrix adjacency table
     * @param message caption
     * @param out output stream
     */
    void output(const Matrix& matrix, std::string message, std::ostream& out) 
    {
        out << message << std::endl;
        for (int i=0;i<matrix.n;i++) {
            for (int j=0;j<matrix.n;j++) {
                out << matrix.lines[i].arr[j] << " ";
            }
            out << std::endl;
        }
    }
    /**
     * @brief Free memory allocated for table
     * @param matrix adjacency table
     */
    void erase(Matrix& matrix) 
    {
        if (matrix.lines != nullptr) {
            for (int i=0; i<matrix.n; i++) {
                delete[] matrix.lines[i].arr;
            }
        }
        delete[] matrix.lines;
        matrix.lines = nullptr;
        matrix.n = 0;
    }
    /**
     * @brief Checks way existence. Overloaded by "path" and "length"
     * @param matrix adjacency table
     * @param path succession of vertices
     * @param length amount of vertices
     * @return true, if way exists
     * @return false, otherwise
     */
    bool check_way_existence(const Matrix& matrix, const int* path, const int length) 
    {
        if (!std::all_of(path, path + length, [&matrix](int x){return x >= 0 && x < matrix.n;})) {
            return false;
        }
        for (int i=0; i<length-1; i++) {
            if (matrix.lines[path[i]].arr[path[i+1]] == 0) {return false;}
        }
        return true;
    } 
    /**
     * @brief Creates file in dot format
     * @param matrix adjacency table
     * @param filename name of result file 
     * @throws runtime_error when impossible to open file
     */
    void create_dot_file(const Matrix& matrix, std::string filename) 
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Can't open file");
        }
        file << "graph {\n";
        file << "\trankdir=LR;\n";
        for (int i=0; i<matrix.n; i++) {
            for (int j=i+1; j<matrix.n; j++) {
                if (matrix.lines[i].arr[j] == 1) {
                    file << '\t' << i << " -- " << j << ";\n";
                }
            }
            file << '\t' << i << ";\n";
        }
        file << "}";
        file.close();
    }
    /**
     * @brief Creates picture of a graph
     * @param filename name of source file 
     */
    void draw_graph(std::string filename) 
    {
        std::string prompt = "dot -T png -O " + filename;
        system(prompt.c_str()); 
        std::cout << "Check out \"" << filename << ".png\"!" << std::endl;
    }
    /**
     * @brief Gets a succession of vertices. Overloaded by "length"
     * @param length amount of numbers in array
     * @param in input stream 
     * @param out output stream 
     * @return succession of vertices
     * @throws runtime_error check get_number() throws
     * @throws bad_alloc when impossible to alloc memory with operator new
     */
    int* array_input(int& length, std::istream& in, std::ostream& out) 
    {
        int* path = nullptr;
        try {
            out << "Enter the length of a path: ";
            length = get_number(in, out, 1);
            try {
                path = new int[length];
            }
            catch(const std::bad_alloc& ba) {
                path = nullptr;
                throw;
            }
            for (int i=0;i<length;i++) {
                out << "path[" << i << "] = ";
                path[i] = get_number(in, out);
            }
        }
        catch(...) {
            delete[] path;
            throw;
        }
        return path;
    }
    /**
     * @brief Creates file in dot format. Overloaded by "path" and "length"
     * @param matrix adjacency table
     * @param path succession of vertices
     * @param length amount of vertices
     * @param filename name of result file
     * @throws runtime_error when impossible to open file
     * @throws runtime_error when path doesn't exist
     */
    void create_dot_file(const Matrix& matrix, const int* path, const int length, std::string filename) 
    {
        if (!check_way_existence(matrix, path, length)) {
            throw std::runtime_error("Path doesn't exist");
        }
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Can't open file");
        }
        file << "graph {\n";
        file << "\trankdir=LR;\n";
        for (int i=0; i<length-1; i++) {
             file << '\t' << path[i] << " -- " << path[i+1] << " [color=\"green\",penwidth=3.0];\n";
        }
        for (int i=0; i<matrix.n; i++) {
            const int* ptr = std::find(path, path + length, i);
            for (int j=i+1; j<matrix.n; j++) {
                if (matrix.lines[i].arr[j] == 1) {
                    if (length == 1 || ptr == path + length || ptr == path + length - 1 && j != *(ptr - 1) 
                    || ptr == path && j != *(ptr+1) || ptr > path && ptr < path + length && j != *(ptr - 1) && j != *(ptr + 1)) {
                        file << '\t' << i << " -- " << j << ";\n";
                    }
                }
            }
            file << '\t' << i;
            if (ptr != path + length) {
                file << " [color=\"green\"]";
            }
            file << ";\n";     
        }
        file << "}";
        file.close();
    }
    /**
     * @brief Gets a succession of vertices
     * @param in input stream 
     * @param out output stream 
     * @return succession of vertices
     * @throws runtime_error check get_number() throws
     */
    std::vector<int> array_input(std::istream& in, std::ostream& out) 
    {
        out << "Enter the length of a path: ";
        int length = get_number(in, out, 1);
        std::vector<int> path(length);
        int counter = 0;
        for (int& vertex : path) {
            out << "path[" << counter++ << "] = ";
            vertex = get_number(in, out);
        }
        return path;
    }
    /**
     * @brief Checks way existence. Overloaded by "path"
     * @param matrix adjacency table
     * @param path succession of vertices
     * @return true, if way exists
     * @return false, otherwise
     */
    bool check_way_existence(const Matrix& matrix, const std::vector<int>& path) 
    {
        if (!std::all_of(path.begin(), path.end(), [&matrix](int x){return x >= 0 && x < matrix.n;})) {
            return false;
        }
        for (int i=0; i<path.size()-1; i++) {
            if (matrix.lines[path[i]].arr[path[i+1]] == 0) {return false;}
        }
        return true;
    }
    /**
     * @brief Creates file in dot format. Overloaded by "path"
     * @param matrix adjacency table
     * @param path succession of vertices
     * @param filename name of result file
     * @throws runtime_error when impossible to open file
     * @throws runtime_error when path doesn't exist
     */
    void create_dot_file(const Matrix& matrix, const std::vector<int>& path, std::string filename) 
    {
        int length = path.size();
        if (!check_way_existence(matrix, path)) {
            throw std::runtime_error("Path doesn't exist");
        }
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Can't open file");
        }
        file << "graph {\n";
        file << "\trankdir=LR;\n";
        for (int i=0; i<length-1; i++) {
             file << '\t' << path[i] << " -- " << path[i+1] << " [color=\"green\",penwidth=3.0];\n";
        }
        for (int i=0; i<matrix.n; i++) {
            auto ptr = std::find(path.begin(), path.end(), i);
            for (int j=i+1; j<matrix.n; j++) {
                if (matrix.lines[i].arr[j] == 1) { 
                    if (length == 1 || ptr == path.end() || ptr == path.end() - 1 && j != *(ptr-1) || ptr == path.begin() 
                    && j != *(ptr+1) || ptr > path.begin() && ptr < path.end() - 1 && j != *(ptr+1) && j != *(ptr-1)) {
                        file << '\t' << i << " -- " << j << ";\n";
                    }
                }
            }
            file << '\t' << i;
            if (ptr != path.end()) {
                file << " [color=\"green\"]";
            }
            file << ";\n";     
        }
        file << "}";
        file.close();
    }
}
