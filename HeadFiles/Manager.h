#ifndef MANAGER
#define MANAGER
#include "Linked_List.h"

/* ==================== 物业经理模块 ==================== */
/*
【设计】
    - 此头文件封装物业经理能做的所有操作
    - 每个函数都能接收list指针，对链表进行操作
*/

//添加新住户
void manager_AddResident(ResidentList* list);
//查看所有住户列表
void manager_ViewAll(ResidentList* list);
//修改住户：输入身份证 → 找到 → 显示当前信息 → 选要改的字段 → 修改
void manager_ModifyResident(ResidentList* list);
//删除住户：输入身份证 → 确认 → 删除
void manager_DeleteResident(ResidentList* list);
//用户自己查询个人信息（不属于物业经理的功能）
void resident_QueryInfo(ResidentList* list);
#endif