#include <iostream>
#include <array>
#include <limits>
#include <exception>
#include <algorithm>
#include <initializer_list>
#include <random>
#include <assert.h>
#include <unistd.h>
#include <stack>
#include <queue>
#include <set>
#include <functional>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "table_const.h"
#include "table_func.h"
#include "exc.h"
#include "table.h"
#include "pathstep.h"



eMoveType GetRandomMove()
{
  static std::default_random_engine generator;
  static std::uniform_int_distribution<int> distribution(0,3);
  int dice_roll = distribution(generator);
  switch(dice_roll) {
  case 0 :
    return eMoveType::Up;
  case 1:
    return eMoveType::Down;
  case 2:
    return eMoveType::Right;
  case 3:
    return eMoveType::Left;
  default:
    assert(0);
  }
}

PathStep::CompareHeuristicLess sorter;
using std::cout;
using std::endl;
using std::cin;


void ShowHistory(PathStep & result)
{
  if (result.prev) {
    ShowHistory((*result.prev));
  }
  TableCellsFunc::PrintCells(result.GetTable().GetCells());


}

int main()
{
  TableCells cells;
  for (int i = 0; i < kTableSize; i++) {
    std::string str;
    cin >> str;
    cells[i] = boost::lexical_cast<int>(str);
    if (!cells[i]) {
      cells[i] = kEmptyCell;
    }
  }

  TableCellsFunc::PrintCells(cells);

  if ((TableCellsFunc::GetInversionCnt(cells) + TableCellsFunc::FindEmptyCell(cells) / 4 + 1) %2) {
    cout << "no solution" << endl;
    return -1;
  }
  Table tbl(cells);

  std::vector<eMoveType> possibleMoves = {eMoveType::Up, eMoveType::Down, eMoveType::Right, eMoveType::Left};



  std::vector<PathStep> openCells;
  std::vector<PathStep> closedSet;


  PathStep startPos(tbl, 0);

  openCells.push_back(startPos);

  while(!openCells.empty()) {
    PathStep currentStep = openCells.back();
    const Table & currentTable (currentStep.GetTable());

    openCells.pop_back();
    TableCellsFunc::PrintCells(currentStep.GetTable().GetCells());
//    cout << "Inversions: " << currentStep.GetInversions() << endl;
    cout << "Wrongs: " << currentStep.GetWrongCnt() << endl;
    cout << "Len: " << currentStep.GetPathLength() << endl;
    cout << "Heu" << currentStep.GetHeuristic() << endl;
    cout << "INV" << currentStep.GetInversions() << endl;
    cout << "MAH" << currentStep.GetManhatanSum() <<endl;

    closedSet.push_back(currentStep);
    if (!currentTable.GetInversionsNum() && currentTable.GetEmptyCellIndex() == 8) {
      std::cout << "FOUND!" << std::endl;

      ShowHistory(currentStep);
      break;
    }

//    cout << "OPENSET : " << endl;
//    for (auto &x : openCells) {
//      cout << x.GetHeuristic() << endl;
//    }
//    cout << "__________________" << endl;

    for (auto i = possibleMoves.begin(); i != possibleMoves.end(); ++i) {
      const eMoveType & moveType = *i;
      if (TableCellsFunc::IsCorrectMove(currentTable.GetEmptyCellIndex(), moveType)) {

        Table movedTable(currentTable);
        movedTable.DoMoveEmptyCell(moveType);
        if (currentStep.GetTable().GetCells() == movedTable.GetCells()) {
          //назад не идем
          continue;
        }
        PathStep moveStep(movedTable, currentStep.GetPathLength() + 1);
//        if (moveStep.GetPathLength() > 10) {
//          continue;
//        }
        moveStep.prev.reset(new PathStep(currentStep));
        if (std::find_if(closedSet.begin(), closedSet.end(), boost::bind(TablesEqual, moveStep, _1)) != closedSet.end()) {

          //Сосед в закрытом списке, игнорируем его
//          cout << "closed" << endl;
          continue;
        }
        auto foundOpen = std::find_if(openCells.begin(), openCells.end(), boost::bind(TablesEqual, moveStep, _1));
        if (foundOpen ==  openCells.end()) {
          //Сосед не в открытом списке, надо добавить
          openCells.push_back(moveStep);
          std::sort(openCells.begin(), openCells.end(), sorter);
//          cout << "opened" << endl;

        } else {
          //Сосед в открытом списке, проверяем, лучше ли этот путь
          PathStep & step = *foundOpen;
          if (moveStep.GetHeuristic() < step.GetHeuristic()) {
            //Мы пришли сюда лучшим путем, чем раньше
            cout << "changedd : " << step.GetHeuristic() << " " << moveStep.GetHeuristic() << endl;
            step = moveStep;
            std::sort(openCells.begin(), openCells.end(), sorter);
//            cout << "changed" << endl;
          }
        }
      }
    }

  }

//  open



//  openCells
//  int nInversions = 0;
//  while(nInversions = tbl.GetInversionsNum()) {





//  }


//  std::cout << "DONE" << endl;



//  std::stack<TableCells> tableCellsStack;
//  int nInversions = 0;
//  if (!(TableCellsFunc::GetInversionCnt(tbl.GetCells()) % 2))  {
//    std::cout << "No solution" << std::endl;
//    return 0;
//  }

//  while(nInversions = TableCellsFunc::GetInversionCnt(tbl.GetCells())) {
//    eMoveType move;
//    for (auto i = moves.begin(); i != moves.end(); ++i) {
//      if (TableCellsFunc::IsCorrectMove(tbl.GetEmptyCellIndex(), *i)) {
//        tbl.
//      }
//    }
//  };

//    tableCellsStack.push(tbl.GetCells());
//    tbl.MoveEmptyCell(move);


//    if (TableCellsFunc::GetInversionCnt(tbl.GetCells()) > nInversions) {
//      tbl.SetCells(tableCellsStack.top());
//      tableCellsStack.pop();
//    }
////    TableCellsFunc::PrintCells(tbl.GetCells());
//    std::cout << "INVERSION : " << tbl.GetInversionsNum() << std::endl;
////    ::sleep(1);
//  }

//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;
//  tbl.MoveEmptyCell(eMoveType::Up);
//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;
//  tbl.MoveEmptyCell(eMoveType::Up);
//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;
//  tbl.MoveEmptyCell(eMoveType::Right);
//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;
//  tbl.MoveEmptyCell(eMoveType::Left);
//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;
//  tbl.MoveEmptyCell(eMoveType::Left);
//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;
//  tbl.MoveEmptyCell(eMoveType::Left);
//  TableCellsFunc::PrintCells(tbl.GetCells());
//  std::cout << TableCellsFunc::GetInversionCnt(tbl.GetCells()) << std::endl;



  return 0;
}

