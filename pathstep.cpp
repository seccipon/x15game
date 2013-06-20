#include "pathstep.h"


bool TablesEqual(const PathStep & lhs, const PathStep & rhs) {
   return lhs.GetTable().GetCells() == rhs.GetTable().GetCells();
}
