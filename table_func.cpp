

#include "table_const.h"
#include "exc.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
namespace TableCellsFunc
{
  //only const getters/formatter here
  int FindEmptyCell(const TableCells & table)
  {
    for (int i = 0; i < kTableSize; i++) {
      if(table[i] == kEmptyCell) {
        return i;
      }
    }
    throw EEmptyCellNotFound();
  }

  bool IsRightBorder(int i)
  {
    return (i == 2) || (i == 5) || (i == 8);// | (i == 15);
  }

  bool IsLeftBorder(int i)
  {
    return (i == 0) || (i == 3) || (i == 6);// | (i == 12);
  }

  int GetInversionCnt(const TableCells & gt)
  {
    int cnt = 0;
    int iEmptyCell = FindEmptyCell(gt);

    for (int i = 0; i < kTableSize; i++) {
      if (i == iEmptyCell) {
        continue;
      }

      for (int j = i + 1; j < kTableSize; j++) {
        if (j == iEmptyCell) {
          continue;
        }
        if (gt[i] > gt[j]) {
          cnt++;
        }
      }
    }
    return cnt;
  }
  bool IsCorrectIndex(char iCell) {
    return iCell >= 0 && iCell < kTableSize;
  }

  void PrintCells(const TableCells & cells)
  {
    using std::endl;
    using std::cout;
    using std::string;
    cout << "_____" <<endl;
    for (int i = 0; i < kTableSize; i++) {
      cout << ((cells[i] == kEmptyCell) ? std::string("x") : boost::lexical_cast<string>(static_cast<int>(cells[i]))) << "  ";
      if (!((i + 1) % 3)) {
        cout << endl;
      }
    }
    cout << "_____" <<endl;
  }

  bool IsCorrectMove(int iCell, eMoveType moveType)
  {
    if (moveType == eMoveType::Right && TableCellsFunc::IsRightBorder(iCell)) {
      return false;
    }
    if (moveType == eMoveType::Left && TableCellsFunc::IsLeftBorder(iCell)) {
      return false;
    }
    return IsCorrectIndex(iCell + static_cast<int>(moveType));
  }

  int GetWrongCnt(const TableCells &gt)
  {
    int cnt = 0;
    for (int i =0; i < kTableSize; i++) {
      if (gt[i] != i + 1 && gt[i] != kEmptyCell) {
        cnt++;
      }
    }
    return cnt;
  }

  int GetManhatanSum(const TableCells &cells)
  {
    const int sideSize = 3;
    int sum = 0;
    for (int i = 0; i < kTableSize; i++) {
      if (cells[i] == kEmptyCell) {
        continue;
      }
      int iRowTarget = i / sideSize;
      int iColTarget = i % sideSize;
      int iRowReal = (cells[i] - 1) / sideSize;
      int iColReal = (cells[i] - 1) % sideSize;
      sum += abs(iRowTarget - iRowReal) + abs(iColTarget - iColReal);
    }
    return sum;
  }

}
