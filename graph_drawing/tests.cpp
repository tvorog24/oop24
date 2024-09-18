#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "funcs.h"
#include "input.h"
#include <sstream>
#include <limits>

using namespace Prog;

TEST_CASE( "test get_number()" ) {
    SECTION( "correct input" ) {
        std::stringstream in("2\n");
        REQUIRE(get_number(in) == 2);
    }
    SECTION( "out of range" ) {
        std::stringstream in("100\n1\n");
        std::stringstream out;
        get_number(in, out, -10, 10);
        REQUIRE(out.str() == "Wrong type of data. Try again: ");
    }
    SECTION( "wrong type of data" ) {
        std::stringstream in("lol\n999\n");
        std::stringstream out;
        get_number(in, out);
        REQUIRE(out.str() == "Wrong type of data. Try again: ");
    }
    SECTION( "empty input" ) {
        std::stringstream in("");
        REQUIRE_THROWS_AS(get_number(in), std::runtime_error);
    }  
}

TEST_CASE( "test array_input() (returns int*)" ) {
    SECTION( "correct input" ) {
        std::stringstream in("4\n0\n1\n2\n3\n");
        std::stringstream out;
        int length = 0;
        int* path = array_input(length, in, out);
        REQUIRE((length == 4 && path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3));
        delete[] path;
    }
    SECTION( "wrong type of data" ) {
        std::stringstream in("4\n0\nAAA\n1\n2\n3\n");
        std::stringstream out;
        int length = 0;
        int* path = array_input(length, in, out);
        REQUIRE((length == 4 && path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3));
        delete[] path;
    }
    SECTION( "eof" ) {
        std::stringstream in("4\n0\n1\n");
        std::stringstream out;
        int length = 0;
        REQUIRE_THROWS_AS(array_input(length, in, out), std::runtime_error);
    }
}

TEST_CASE( "test array_input() (returns vector<int>)" ) {
    SECTION( "correct input" ) {
        std::stringstream in("4\n0\n1\n2\n3\n");
        std::stringstream out;
        std::vector<int> path = array_input(in, out);
        REQUIRE((path.size() == 4 && path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3));
    }
    SECTION( "wrong type of data" ) {
        std::stringstream in("4\n0\nAAA\n1\n2\n3\n");
        std::stringstream out;
        std::vector<int> path = array_input(in, out);
        REQUIRE((path.size() == 4 && path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3));
    }
    SECTION( "eof" ) {
        std::stringstream in("4\n0\n1\n2");
        std::stringstream out;
        REQUIRE_THROWS_AS(array_input(in, out), std::runtime_error);
    }
}

TEST_CASE( "test input()" ) {
    SECTION( "correct input" ) {
        std::stringstream in("3\n1\n1\n0\n");
        std::stringstream out;
        Matrix matrix = input(in, out);
        REQUIRE((matrix.n == 3 && matrix.lines[0].arr[0] == 1 && matrix.lines[0].arr[1] == 1 && 
            matrix.lines[0].arr[2] == 1 && matrix.lines[1].arr[0] == 1 && matrix.lines[1].arr[1] == 1 &&
            matrix.lines[2].arr[0] == 1 && matrix.lines[2].arr[2] == 1 && matrix.lines[1].arr[2] == 0 &&
            matrix.lines[2].arr[1] == 0));
        erase(matrix);
    }
    SECTION( "wrong type of data" ) {
        std::stringstream in("3\n1\n1\nCRINGE\n0\n");
        std::stringstream out;
        Matrix matrix = input(in, out);
        REQUIRE((matrix.n == 3 && matrix.lines[0].arr[0] == 1 && matrix.lines[0].arr[1] == 1 && 
            matrix.lines[0].arr[2] == 1 && matrix.lines[1].arr[0] == 1 && matrix.lines[1].arr[1] == 1 &&
            matrix.lines[2].arr[0] == 1 && matrix.lines[2].arr[2] == 1 && matrix.lines[1].arr[2] == 0 &&
            matrix.lines[2].arr[1] == 0));
        erase(matrix);
    }
    SECTION( "inapproptiate value" ) {
        std::stringstream in("3\n1\n9\n1\n0\n");
        std::stringstream out;
        Matrix matrix = input(in, out);
        REQUIRE((matrix.n == 3 && matrix.lines[0].arr[0] == 1 && matrix.lines[0].arr[1] == 1 && 
            matrix.lines[0].arr[2] == 1 && matrix.lines[1].arr[0] == 1 && matrix.lines[1].arr[1] == 1 &&
            matrix.lines[2].arr[0] == 1 && matrix.lines[2].arr[2] == 1 && matrix.lines[1].arr[2] == 0 &&
            matrix.lines[2].arr[1] == 0));
        erase(matrix);
    }
    SECTION( "invalid size" ) {
        std::stringstream in("-12\n2\n0\n");
        std::stringstream out;
        Matrix matrix = input(in, out);
        REQUIRE((matrix.n == 2 && matrix.lines[0].arr[0] == 1 && matrix.lines[0].arr[1] == 0 && 
            matrix.lines[1].arr[0] == 0 && matrix.lines[1].arr[1] == 1));
        erase(matrix);
    }
    SECTION( "eof" ) {
        std::stringstream in("2\n");
        std::stringstream out;
        REQUIRE_THROWS_AS(input(in, out), std::runtime_error);
    }
}

TEST_CASE( "test check_way_existence() (overloaded by int*)" ) {
    SECTION( "way exists (1)" ) {
        std::stringstream in;
        in << "3\n1\n1\n1\n";
        std::stringstream out;
        Matrix matrix = input(in, out);
        int length = 0;
        in << "2\n0\n1\n";
        int* path = array_input(length, in, out);
        REQUIRE(check_way_existence(matrix, path, length) == true);
        erase(matrix);
        delete[] path;
    }
    SECTION( "way exists (2)" ) {
        std::stringstream in;
        std::stringstream out;
        in << "4\n1\n1\n1\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        int length = 0;
        in << "4\n3\n2\n0\n1\n";
        int* path = array_input(length, in, out);
        REQUIRE(check_way_existence(matrix, path, length) == true);
        erase(matrix);
        delete[] path;
    }
    SECTION( "way doesn't exist" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n0\n";
        Matrix matrix = input(in, out);
        int length = 0;
        in << "3\n1\n2\n0\n";
        int* path = array_input(length, in, out);
        REQUIRE(check_way_existence(matrix, path, length) == false);
        erase(matrix);
        delete[] path;
    }
    SECTION( "vertex doesn't exist" ) {
        std::stringstream in;
        std::stringstream out;
        in << "2\n1\n";
        Matrix matrix = input(in, out);
        int length = 0;
        in << "2\n0\n2\n";
        int* path = array_input(length, in, out);
        REQUIRE(check_way_existence(matrix, path, length) == false);
        erase(matrix);
        delete[] path;
    }
}

TEST_CASE( "test check_way_existence() (overloaded by vector<int>)" ) {
    SECTION( "way exists (1)" ) {
        std::stringstream in;
        in << "3\n1\n1\n1\n";
        std::stringstream out;
        Matrix matrix = input(in, out);
        in << "2\n0\n1\n";
        std::vector<int> path = array_input(in, out);
        REQUIRE(check_way_existence(matrix, path) == true);
        erase(matrix);
    }
    SECTION( "way exists (2)" ) {
        std::stringstream in;
        std::stringstream out;
        in << "4\n1\n1\n1\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        in << "4\n3\n2\n0\n1\n";
        std::vector<int> path = array_input(in, out);
        REQUIRE(check_way_existence(matrix, path) == true);
        erase(matrix);
    }
    SECTION( "way doesn't exist" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n0\n";
        Matrix matrix = input(in, out);
        in << "3\n1\n2\n0\n";
        std::vector<int> path = array_input(in, out);
        REQUIRE(check_way_existence(matrix, path) == false);
        erase(matrix);
    }
    SECTION( "vertex doesn't exist" ) {
        std::stringstream in;
        std::stringstream out;
        in << "2\n1\n";
        Matrix matrix = input(in, out);
        in << "2\n0\n5\n";
        std::vector<int> path = array_input(in, out);
        REQUIRE(check_way_existence(matrix, path) == false);
        erase(matrix);
    }
}

TEST_CASE( "test output()" ) {
    std::stringstream in;
    std::stringstream iout;
    in << "2\n1\n";
    Matrix matrix = input(in, iout);
    std::stringstream out;
    output(matrix, "Adjacency matrix", out);
    REQUIRE(out.str() == "Adjacency matrix\n1 1 \n1 1 \n");
    erase(matrix);
}

TEST_CASE( "test create_dot_file() (overload by int*)" ) {
    SECTION( "way doesn't exist" ) {
        std::stringstream in;
        std::stringstream out;
        in << "2\n0\n";
        Matrix matrix = input(in, out);
        int length = 0;
        in << "2\n0\n1\n";
        int* path = array_input(length, in, out);
        REQUIRE_THROWS_AS(create_dot_file(matrix, path, length), std::runtime_error);
        erase(matrix);
        delete[] path;
    }
    SECTION( "way exists" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        int length = 0;
        in << "3\n0\n2\n1\n";
        int* path = array_input(length, in, out);
        create_dot_file(matrix, path, length);
        std::ifstream file("graph.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        REQUIRE(buffer.str() == "graph {\n\trankdir=LR;\n\t0 -- 2 [color=\"green\",penwidth=3.0];\n\t2 -- 1 [color=\"green\",penwidth=3.0];\n\t0 -- 1;\n\t0 [color=\"green\"];\n\t1 [color=\"green\"];\n\t2 [color=\"green\"];\n}");
        file.close();
        erase(matrix);
        delete[] path;
    } 
    SECTION( "can't open file" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        int length = 0;
        in << "3\n0\n2\n1\n";
        int* path = array_input(length, in, out);
        REQUIRE_THROWS(create_dot_file(matrix, path, length, ""));
        erase(matrix);
        delete[] path;
    } 
}

TEST_CASE( "test create_dot_file() (overload by vector<int>)" ) {
    SECTION( "way doesn't exist" ) {
        std::stringstream in;
        std::stringstream out;
        in << "2\n0\n";
        Matrix matrix = input(in, out);
        in << "2\n0\n1\n";
        std::vector<int> path = array_input(in, out);
        REQUIRE_THROWS_AS(create_dot_file(matrix, path), std::runtime_error);
        erase(matrix);
    }
    SECTION( "way exists" ) {
        std::stringstream in;
        std::stringstream out;
         in << "3\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        in << "3\n0\n2\n1\n";
        std::vector<int> path = array_input(in, out);
        create_dot_file(matrix, path);
        std::ifstream file("graph.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        REQUIRE(buffer.str() == "graph {\n\trankdir=LR;\n\t0 -- 2 [color=\"green\",penwidth=3.0];\n\t2 -- 1 [color=\"green\",penwidth=3.0];\n\t0 -- 1;\n\t0 [color=\"green\"];\n\t1 [color=\"green\"];\n\t2 [color=\"green\"];\n}");
        file.close();
        erase(matrix);
    } 
    SECTION( "can't open file" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        in << "3\n0\n2\n1\n";
        std::vector<int> path = array_input(in, out);
        REQUIRE_THROWS(create_dot_file(matrix, path, ""));
        erase(matrix);
    } 
}

TEST_CASE( "test create_dot_file()" ) {
    SECTION( "all right" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        create_dot_file(matrix);
        std::ifstream file("graph.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        REQUIRE(buffer.str() == "graph {\n\trankdir=LR;\n\t0 -- 1;\n\t0 -- 2;\n\t0;\n\t1 -- 2;\n\t1;\n\t2;\n}");
        file.close();
        erase(matrix);
    }
     SECTION( "can't open file" ) {
        std::stringstream in;
        std::stringstream out;
        in << "3\n1\n1\n1\n";
        Matrix matrix = input(in, out);
        REQUIRE_THROWS(create_dot_file(matrix, ""));
        erase(matrix);
    } 
}

TEST_CASE( "test draw_graph()" ) {
    REQUIRE_NOTHROW(draw_graph());
}
