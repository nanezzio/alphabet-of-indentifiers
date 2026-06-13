#ifndef IDENTIFIER_GENERATOR_H
#define IDENTIFIER_GENERATOR_H

#include <string>

class IdentifierGenerator
{
public:
    static std::string GenerateNextIdentifier(
        const std::string& identifier);
};

#endif