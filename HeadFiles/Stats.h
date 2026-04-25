#ifndef STATS
#define STATS
#include "Linked_List.h"

/* ==================== 统计模块 ==================== */

/* 按楼号统计：列出指定楼号所有欠费(fee_due > 0)的住户 */
void stats_Building(ResidentList* list);

/* 按欠款从大到小排序后打印 */
void stats_Sort(ResidentList* list);

#endif