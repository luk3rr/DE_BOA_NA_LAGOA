/*
* Filename: definitions.h
* Created on: October 14, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <limits>

class Defs
{
    public:
        static constexpr std::size_t INFINITY_VALUE = std::numeric_limits<std::size_t>::max();
        enum EDGE_INFO { YEAR, TIME, COST };
};
