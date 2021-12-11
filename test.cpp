#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "4 11\n"
                "802\n"
                "743\n"
                "457\n"
                "539\n"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "200"
    );
}

TEST_CASE("0 length", ""){
    std::stringstream input(
            "4 11\n"
            "1\n"
            "2\n"
            "3\n"
            "4\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "0"
    );
}

TEST_CASE("1 length", ""){
    std::stringstream input(
            "4 10\n"
            "1\n"
            "2\n"
            "3\n"
            "4\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() == "1"
    );
}
