#include "IdentifierGenerator.h"

#include <vector>
#include <stdexcept>

namespace
{
    const char LETTERS[] =
        "ABCEHIKLNOPRSTUWXYZ";

    const int LETTER_COUNT = 19;
    const int DIGIT_COUNT = 9;
    const int GROUP_BASE = LETTER_COUNT * DIGIT_COUNT;
    const int MAX_GROUPS = 10;

    bool IsValidLetter(char c)
    {
        for (int i = 0; i < LETTER_COUNT; ++i)
        {
            if (LETTERS[i] == c)
            {
                return true;
            }
        }

        return false;
    }

    int LetterIndex(char c)
    {
        for (int i = 0; i < LETTER_COUNT; ++i)
        {
            if (LETTERS[i] == c)
            {
                return i;
            }
        }

        throw std::invalid_argument("Invalid letter");
    }

    int GroupToValue(char letter, char digit)
    {
        if (!IsValidLetter(letter))
        {
            throw std::invalid_argument("Invalid letter");
        }

        if (digit < '1' || digit > '9')
        {
            throw std::invalid_argument("Invalid digit");
        }

        return LetterIndex(letter) * DIGIT_COUNT + (digit - '1');
    }

    void ValueToGroup(int value, char& letter, char& digit)
    {
        letter = LETTERS[value / DIGIT_COUNT];
        digit = static_cast<char>('1' + (value % DIGIT_COUNT));
    }

    std::vector<int> Parse(const std::string& identifier)
    {
        if (identifier.empty())
        {
            throw std::invalid_argument("Identifier is empty");
        }

        std::vector<int> groups;

        std::size_t pos = 0;

        while (pos < identifier.size())
        {
            if (pos + 1 >= identifier.size())
            {
                throw std::invalid_argument("Invalid identifier format");
            }

            groups.push_back(GroupToValue(identifier[pos],identifier[pos + 1]));

            pos += 2;

            if (pos == identifier.size())
            {
                break;
            }

            if (identifier[pos] != '-')
            {
                throw std::invalid_argument("Invalid separator");
            }

            ++pos;
        }

        if (groups.size() > MAX_GROUPS)
        {
            throw std::invalid_argument("Too many groups");
        }

        return groups;
    }

    std::string Format(const std::vector<int>& groups)
    {
        std::string result;

        for (std::size_t i = 0; i < groups.size(); ++i)
        {
            if (i > 0)
            {
                result += '-';
            }

            char letter;
            char digit;

            ValueToGroup(groups[i], letter, digit);

            result += letter;
            result += digit;
        }

        return result;
    }
}

std::string IdentifierGenerator::GenerateNextIdentifier(const std::string& identifier)
{
    std::vector<int> groups = Parse(identifier);

    int carry = 1;

    for (int i = static_cast<int>(groups.size()) - 1; i >= 0 && carry; --i)
    {
        ++groups[i];

        if (groups[i] == GROUP_BASE)
        {
            groups[i] = 0;
        }
        else
        {
            carry = 0;
        }
    }

    if (carry)
    {
        if (groups.size() >= MAX_GROUPS)
        {
            throw std::overflow_error("Maximum identifier reached");
        }

        groups.insert(groups.begin(), 0);
    }

    return Format(groups);
}