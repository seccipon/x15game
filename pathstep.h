#ifndef PATHSTEP_H
#define PATHSTEP_H

#include "table.h"

#include <memory>
class PathStep
{

public:
  PathStep(const Table & table, int cost) :
    m_table(table),
    m_cost(cost)
  {}


  const Table & GetTable() const {
    return m_table;
  }

  int GetPathLength() const {
    return m_cost;
  }

  int GetInversions() const {
    return m_table.GetInversionsNum();
  }

  int GetWrongCnt() const {
    return m_table.GetWrongCnt();
  }

  int GetHeuristic() const {
    return  GetPathLength() + m_table.GetManhatanSum() * m_table.GetManhatanSum();
  }

  int GetManhatanSum() const {
    return m_table.GetManhatanSum();
  }

  void SetPathlength(int pathLength) {
    m_cost = pathLength;
  }

  struct CompareHeuristicLess
  {
    bool operator()(const PathStep & lhs, const PathStep & rhs) {
      return lhs.GetHeuristic() > rhs.GetHeuristic();
    }
  };

  struct CompareCellsLexLess
  {
    bool operator()(const PathStep & lhs, const PathStep & rhs) {
      return lhs.GetTable().GetCells() < rhs.GetTable().GetCells();
    }

  };

  struct EqualTables
  {
    bool operator()(const PathStep & lhs, const PathStep & rhs)
    {
      return lhs.GetTable().GetCells() == rhs.GetTable().GetCells();
    }
  };

  std::shared_ptr<PathStep> prev;

private:
  Table m_table;
  int m_cost;
};

bool TablesEqual(const PathStep & lhs, const PathStep & rhs);
#endif // PATHSTEP_H
