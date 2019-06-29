#include "datalist.h"

bool allRead=false;
int intRow;//行数
int Begin_Row=1;//起始行
int End_Row=-1;
STATE current_STATE=EXECL_START;

QString execl_Name;
QString word_Name;
QString new_Route;
QString Path=".";

Cells_template Cells;
Bookmarks_template Bookmarks;

dataList::dataList()
{

}
