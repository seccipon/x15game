#ifndef TABLE_FUNC_H
#define TABLE_FUNC_H

#include "table_const.h"

namespace TableCellsFunc
{
  int FindEmptyCell(const TableCells & table);
  bool IsRightBorder(int i);
  bool IsLeftBorder(int i);
  int GetInversionCnt(const TableCells & gt);
  int GetWrongCnt(const TableCells & gt);
  bool IsCorrectIndex(char i);
  void PrintCells(const TableCells & cells);
  bool IsCorrectMove(int iCell, eMoveType moveType);
  int GetManhatanSum(const TableCells & cells);
}
#endif // TABLE_FUNC_H
