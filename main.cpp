#include <iostream>
#include <exception>

#include "IdentifierGenerator.h"

int main()
{
    try
    {
        std::cout << "A1 -> " << IdentifierGenerator::GenerateNextIdentifier("A1") << std::endl;

        std::cout << "A9 -> " << IdentifierGenerator::GenerateNextIdentifier("A9") << std::endl;

        std::cout << "C9 -> " << IdentifierGenerator::GenerateNextIdentifier("C9") << std::endl;

        std::cout << "Z9 -> " << IdentifierGenerator::GenerateNextIdentifier("Z9") << std::endl;

        std::cout << "A1-Z9 -> " << IdentifierGenerator::GenerateNextIdentifier("A1-Z9") << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}