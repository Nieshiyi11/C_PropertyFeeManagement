#ifndef FEE
#define FEE
#include "Linked_List.h"

/* ==================== 物业费模块 ==================== */
/*
【模块说明】
  fee_due 字段同时表达三种状态：
  1). fee_due > 0：欠费金额
  2). fee_due = 0：已付清
  3). fee_due < 0：预存余额（绝对值表示预存了多少）
  "生成本月物业费"由物业经理手动触发,输入要生成x月的物业费
  每户的fee_due加上 (面积×单价)
*/

//物业经理：给所有住户生成指定年月的物业费
void fee_GenerateAll(ResidentList* list, int year, int month);

//住户：查询指定年月的应缴物业费
void fee_QueryOne(ResidentList* list);

//住户：为指定年月自助缴费
void fee_PayOne(ResidentList* list);

#endif