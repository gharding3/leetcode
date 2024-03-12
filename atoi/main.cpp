#include <iostream>
#include <string>
#include <cassert>

enum ParserState
{
    Trimming,   // searching for first digit
    FirstToken, // found first non-whitespace token
    Parsing,    // parsing digits
    Finished    // all digits parsed
};

int myAtoi(std::string str)
{
    long long parsed = 0;
    bool negate = false;
    bool signable = true;
    ::ParserState state = ParserState::Trimming;

    static const long long max_positive_int32 = 2147483647L;
    static const long long max_negative_int32 = 2147483648L;

    for(auto& c : str)
    {
        if(state == ParserState::Trimming)
        {
            if(c == ' ')
                continue;
            else
                state = FirstToken;
        }

        if(state == ParserState::FirstToken)
        {
            if(c == '-' && signable)
            {
                negate = true;
                signable = false; // only allow sign to appear once
                continue;
            }
            else if(c == '+' && signable)
            {
                negate = false;
                signable = false; // only allow sign to appear once
                continue;
            }
            else if(c == '0')
            {
                // trim leading zeroes
                signable = false;
                continue;
            }
            else if(c >= '1' && c <= '9')
            {
                state = ParserState::Parsing;
            }
            else
            {
                // invalid first character
                return 0;
            }
        }

        if(state == ParserState::Parsing)
        {
            if(c >= '0' && c <= '9')
            {
                parsed *= 10;
                parsed += (c - '0');
                if(!negate && parsed > max_positive_int32)
                {
                    parsed = max_positive_int32;
                    break;
                }
                else if(negate && parsed > max_negative_int32)
                {
                    parsed = max_negative_int32;
                    break;
                }
            }
            else
            {
                state = ParserState::Finished;
                break;
            }
        }
    }

    int parsed32 = parsed & 0xFFFFFFFFFFFFFFFF;
    return negate ? -parsed : parsed;
}

int main(int argc, char *argv[])
{
    int passed = 0;

    // given empty string, ensure result is zero.
    {
        int actual = myAtoi("asdf");
        assert(actual == 0);
        ++passed;    
    }

    {
        int actual = myAtoi("12");
        assert(actual == 12);
        ++passed;
    }

    {
        int actual = myAtoi(" +125.00");
        assert(actual == 125);
        ++passed;
    }

    {
        int actual = myAtoi("    -6342");
        assert(actual == -6342);
        ++passed;
    }

    {
        int actual = myAtoi("-001200");
        assert(actual == -1200);
        ++passed;
    }

    {
        int actual = myAtoi("+0.123 ");
        assert(actual == 0);
        ++passed;
    }

    {
        int actual = myAtoi("    fff 023");
        assert(actual == 0);
        ++passed;
    }

    {
        int actual = myAtoi("+-3");
        assert(actual == 0);
        ++passed;
    }

    {
        int actual = myAtoi(" --5");
        assert(actual == 0);
        ++passed;
    }

    {
        int actual = myAtoi("00-3");
        assert(actual == 0);
        ++passed;
    }

    {
        int actual = myAtoi("  2147483647");
        assert(actual == 2147483647);
        ++passed;
    }

    {
        int actual = myAtoi("  -2147483648");
        assert(actual == -2147483648);
        ++passed;
    }

    {
        int actual = myAtoi("  -2147483649");
        assert(actual == -2147483648);
        ++passed;
    }

    {
        int actual = myAtoi("  2147483648");
        assert(actual == 2147483647);
        ++passed;
    }

    {
        int actual = myAtoi("  -99999999999999");
        assert(actual == -2147483648);
        ++passed;
    }

    {
        int actual = myAtoi("  8888888888888");
        assert(actual == 2147483647);
        ++passed;
    }

    std::cout << "PASSED " << passed << " tests." << std::endl;

    return 0;
}
