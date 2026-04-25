/*==================== 链表接口 ====================*/
#ifndef LINKED_LIST
#define LINKED_LIST
#include "Resident.h"  //因为Node里要用上Resident类型


/* ==================== 定义链表节点 ==================== */
typedef struct Node{   //这里也写上Node是因为内部要自引用 （可以看到内部有：struct Node* next;）
    Resident data;     //住户数据（注意此处是结构体变量！！）
    struct Node* next; //指向下一个节点
}Node;                 //外部引用，typedef出来的起个名字


/* ==================== 链表（加上哑节点） ==================== */
typedef struct{  //这里不用写结构体名字是因为内部没有引用这个结构，故不用写
    Node* head;   //永远指向哑节点
    int   size;   //不含哑节点的真数据数量
}ResidentList;

//【解释ResidentList】的功能：
/*
1. 假设现在只有Node这一个类型：
   那么链表它是一种散落在内存各处的结构：三个Node加上它们之间的next指针关系
   Eg: n1 → n2 → n3 → NULL
   这条链表里只要我们记住了开头的n1，就能顺着next访问到全部
   综上，这叫：“裸指针式链表”

2. “裸指针式链表”的麻烦之处：
    比如要得到链表的长度，每次都要用p = head; 然后用while(p!=NULL)循环计数
    要得到住户数量，就每次都要这样数一边
    此类麻烦还不限于删除或者插入节点
    那么：
    我们当然希望有个地方能够"记住"这个数，加一个就+1，删一个就-1...

3. 那么，ResidentList应运而生...
   所以，ResidentList是一个管理整条链表的结构体
*/

/* ==================== 接口函数 ==================== */
ResidentList* list_Create(void);  //创建空链表【注意C里"无参数"必须显式写void】
//【参数设计】创建全新的链表，不需要任何输入

void list_Destroy(ResidentList* list);  //销毁并释放全部内存
//void表示"不返回任何值"。销毁操作不需要告诉调用者什么，做完就完了
//【参数设计】需要知道"销毁哪个"

int list_Append(ResidentList* list, Resident r); //尾插，返回1成功/0失败
//【参数设计】需要知道"往哪个链表加"+"加什么"
//参数1表示链表，参数2表示住户r

Node* list_FindID(ResidentList* list, const char* id_number);  //按身份证查找
//【参数设计】需要知道"在哪个链表找"+"找谁"

//以下为物业管理员的功能实现：
/* 
    【按身份证号删除节点】
  - 找到身份证匹配的节点，从链表里摘除并free
  - 返回1表示成功删除，0表示找不到
*/
int list_Remove(ResidentList* list, const char* id_number);

/*
    【打印所有住户（遍历）】
  - 从第一个真数据节点开始，打印每一户的核心信息
  - 用于"查看住户列表"功能
*/
void list_Print(ResidentList* list);

#endif
