#ifndef TABLE_CONST_H
#define TABLE_CONST_H
#include <array>
#include <limits>


enum class eMoveType {
  Up = -3,
  Down = 3,
  Right = 1,
  Left = -1
};



const int kTableSize = 9;
typedef std::array<char, kTableSize> TableCells;
const char kEmptyCell = std::numeric_limits<char>::max();



#endif // TABLE_CONST_H
