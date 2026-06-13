#include "IdentifierGenerator.h"

#include <vector>

namespace
{
    const char LETTERS[] =
        "ABCEHIKLNOPRSTUWXYZ";

    const int LETTER_COUNT = 19;
    const int DIGIT_COUNT = 9;
    const int GROUP_BASE = LETTER_COUNT * DIGIT_COUNT;

    int LetterIndex(char c)
    {
        for (int i = 0; i < LETTER_COUNT; ++i)
        {
            if (LETTERS[i] == c)
            {
                return i;
            }
        }

        return -1;
    }

    int GroupToValue(char letter, char digit)
    {
        return LetterIndex(letter) * DIGIT_COUNT +
            (digit - '1');
    }

    void ValueToGroup(
        int value,
        char& letter,
        char& digit)
    {
        letter = LETTERS[value / DIGIT_COUNT];
        digit = static_cast<char>(
            '1' + value % DIGIT_COUNT);
    }

    std::vector<int> Parse(
        const std::string& identifier)
    {
        std::vector<int> groups;

        std::size_t pos = 0;

        while (pos < identifier.size())
        {
            groups.push_back(
                GroupToValue(
                    identifier[pos],
                    identifier[pos + 1]));

            pos += 2;

            if (pos < identifier.size())
            {
                ++pos;
            }
        }

        return groups;
    }

    std::string Format(
        const std::vector<int>& groups)
    {
        std::string result;

        for (std::size_t i = 0;
            i < groups.size();
            ++i)
        {
            if (i > 0)
            {
                result += '-';
            }

            char letter;
            char digit;

            ValueToGroup(
                groups[i],
                letter,
                digit);

            result += letter;
            result += digit;
        }

        return result;
    }
}

std::string IdentifierGenerator::GenerateNextIdentifier(
    const std::string& identifier)
{
    std::vector<int> groups =
        Parse(identifier);

    int carry = 1;

    for (int i =
        static_cast<int>(groups.size()) - 1;
        i >= 0 && carry;
        --i)
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
        groups.insert(groups.begin(), 0);
    }

    return Format(groups);
}