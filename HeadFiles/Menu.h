#ifndef MENU
#define MENU
#include "Linked_List.h"  //菜单功能要操作链表

/* ==================== 菜单模块 ==================== */
/*
【功能】
  - 显示主菜单
  - 根据用户选择进入物业经理模块或住户模块
  - 提供统一的退出机制
【参数】
  - list：住户链表指针，传给各功能函数使用
【返回值】
  - 无（用户选择"退出"时函数自然返回）
*/
void menu_Main(ResidentList* list);  //菜单接口

#endif


//Q1: 为什么要传【ResidentList* list】进菜单？
/*A1：菜单本身不存数据，数据在 main 里创建的链表对象里。
      将来"添加住户"、"删除住户"这些功能都要操作同一个链表，所以菜单得把链表传递下去。*/

//Q2：为什么#include "Linked_List.h"？
//A2：因为menu_Main的参数类型是ResidentList*，编译器必须知道这个类型是什么。不#include就会报"未知类型"错误。
