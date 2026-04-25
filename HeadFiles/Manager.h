#ifndef MANAGER
#define MANAGER
#include "Linked_List.h"

/* ==================== 物业经理模块 ==================== */
/*
【设计】
    - 此头文件封装物业经理能做的所有操作
    - 每个函数都能接收list指针，对链表进行操作
*/

/*添加新住户*/
void manager_AddResident(ResidentList* list);
/*查看所有住户列表*/
void manager_ViewAll(ResidentList* list);
/*修改住户*/

/*删除住户*/
#endif