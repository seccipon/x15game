#ifndef TABLE_H
#define TABLE_H
#include "table_const.h"
class Table
{
public:
//  struct TableInversionCompareLess
//  {
//    bool operator()(const Table & lhs, const Table & rhs) const {
//      return lhs.GetInversionsNum() < rhs.GetInversionsNum();
//    }
//  };

  Table(const TableCells & tableCells);

  int GetEmptyCellIndex() const {
    return m_iEmptyCell;
  }

  int GetInversionsNum() const {
    return m_inversionsNum;
  }

  int GetWrongCnt() const {
    return m_wrongCnt;
  }

  int GetManhatanSum() const {
    return m_mahhatanSum;
  }

  const TableCells& GetCells() const {
    return m_cells;
  }

//  void SetCells(const TableCells & cells);

//  Table CloneAndMove(eMoveType moveType);
  void DoMoveEmptyCell(eMoveType moveType);

private:
  void DoSwapCells(int i1, int i2);
  void Recalc();
  TableCells m_cells;
  int m_iEmptyCell;
  int m_inversionsNum;
  int m_wrongCnt;
  int m_mahhatanSum;
};


#endif // TABLE_H
