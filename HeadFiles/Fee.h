#ifndef FEE
#define FEE
#include "Linked_List.h"

/* ==================== 物业费模块 ==================== */
/*
【模块说明】
  fee_due 字段同时表达两种状态：
  1). fee_due > 0：欠费金额
  2). fee_due = 0：已付清
  3). fee_due < 0：预存余额（绝对值表示预存了多少）
  "生成本月物业费"由物业经理手动触发,每点一次相当于过了一个月
  每户的fee_due加上 (面积×单价)
*/

/* 物业经理：给所有住户生成本月物业费,自动累加 */
void fee_GenerateAll(ResidentList* list,int year,int month);

/* 住户：查询自己的指定年月的应缴物业费 */
void fee_QueryOne(ResidentList* list);

/* 住户：自助缴费(可预存) */
void fee_PayOne(ResidentList* list);

#endif