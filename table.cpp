#include "table.h"
#include "table_func.h"
#include "exc.h"
Table::Table(const TableCells & tableCells) :
  m_cells(tableCells)
{
  Recalc();

}
void Table::DoMoveEmptyCell(eMoveType moveType)
{
  int iEmptyCell = GetEmptyCellIndex();

  if (!TableCellsFunc::IsCorrectMove(iEmptyCell, moveType)) {
    throw EInvalidMove();
  }

  int iSwap = iEmptyCell + static_cast<int>(moveType);
  DoSwapCells(iEmptyCell, iSwap);
  Recalc();
}


void Table::DoSwapCells(int i1, int i2)
{
  char t = m_cells[i1];
  m_cells[i1] = m_cells[i2];
  m_cells[i2] = t;
}

void Table::Recalc()
{
  m_iEmptyCell = TableCellsFunc::FindEmptyCell(m_cells);
  m_inversionsNum = TableCellsFunc::GetInversionCnt(m_cells);
  m_wrongCnt =TableCellsFunc::GetWrongCnt(m_cells);
  m_mahhatanSum = TableCellsFunc::GetManhatanSum(m_cells);
}


//void Table::SetCells(const TableCells & cells) {
//  m_cells = cells;
//  Recalc();
//}
