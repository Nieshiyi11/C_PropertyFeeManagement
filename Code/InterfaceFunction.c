/*==================== 完成接口函数 ====================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HeadFiles/Linked_List.h"

/* ---------- 创建空链表 ---------- */
ResidentList* list_Create(void){
    //1. malloc一个ResidentList
    ResidentList* list = (ResidentList*)malloc(sizeof(ResidentList));
    //2. 检查NULL
    if(list == NULL){
        return NULL;
    }
    //3. malloc哑节点
    Node* dummy = (Node*)malloc(sizeof(Node));
    //4. 检查NULL（p.s: 失败要free第一步）
    if(dummy == NULL){
        free(list);
        return NULL;
    }
    //5. 哑节点next = NULL
    dummy->next = NULL;
    //6. 令size=0
    list->head = dummy;
    list->size = 0;
    //7. 返回 list
    return list;
}

/* ---------- 销毁链表 ---------- */
void list_Destroy(ResidentList* list){
    // 1. 判list==NULL时直接return
    if(list == NULL){
        return ;
    }
    // 2. 从 list->head 开始遍历
    Node* p = list->head;
    // 3. 释放free
    while(p != NULL){
        Node* next = p->next;  //先保存下一个节点
        free(p);
        p=next;
    }
    // 4. 最后 free(list)
    free(list);
}

/* ---------- 尾插法 ---------- */
int list_Append(ResidentList* list, Resident r){
    //1. 判 list == NULL 返回 0
    if(list == NULL){
        return 0;
    }
    //2. malloc新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    //3. 失败返回 0
    if(newNode == NULL){
        return 0;
    }
    //4. 填充新节点
    newNode->data = r;
    newNode->next = NULL;
    //5. 从head走到末尾
    Node* tail = list->head; //从头开始
    while(tail->next != NULL){ //走到最后一个节点
        tail = tail->next;
    }
    //循环接受以后tail就是最后一个节点
    //6. 尾插
    tail->next = newNode;
    list->size++; //别忘记添加好节点后 真实节点数＋1
    return 1;
}

/* ---------- 按身份证查找 ---------- */
Node* list_FindID(ResidentList* list, const char* id_number){
    //1. 判两个参数的NULL
    if(list == NULL || id_number == NULL){
        return NULL;
    }
    //2. p = list->head->next（跳过哑节点）
    Node* p = list->head->next;
    //3. while(p != NULL)
    while(p != NULL){
    //4. C语言中字符串要用strcmp比较，而不是==，若相等就返回p
    //【strcmp的规则】：相等返回0，不相等返回非0
    //【错误写法：strcmp(p->data,id_number)】
    if(strcmp(p->data.id_number,id_number) == 0){  //【易错：p->data是整个Resident结构体，但strcmp需要的是字符串！！】
        return p;
    }else{
        p = p->next;
    }
}
    //5. 循环结束返回 NULL
    return NULL;
}

/* ---------- 按身份证删除节点 ---------- */
int list_Remove(ResidentList* list, const char* id_number){
    if(list == NULL && id_number == NULL){
        return 0;
    }
    Node* prev = list->head;  //哑节点是最完美的节点
    Node* curr = prev->next;  //第一个真数据节点
    while(curr != NULL){
        if(strcmp(curr->data.id_number , id_number)==0){
            prev->next = curr->next;
            free(curr);
            list->size--;
            return 1;
        }
        //没找到该住户的话，两个指针一起往后走
        prev = prev->next;  //或：prev = curr;
        curr = curr->next;
    }
    //遍历完了还没找到:
    return 0;
}

/* ---------- 遍历打印所有住户 ---------- */
void list_Print(ResidentList* list){
    if(list == NULL){
        printf("链表不存在\n");
        return ;
    }
    if(list->size == 0){
        printf("\n当前没有任何住户记录!\n");
        return ;
    }
    //因为是void函数 所以return ;即可
    //如果是指针函数那样 return NULL; (详情见上文)

    printf("\n===== 住户列表（共 %d 户）=====\n", list->size);
    printf("%-4s %-10s %-4s %-20s %-13s %-8s %-8s %-10s\n", "序号", "姓名", "性别", "身份证号", "电话", "楼-单元-房", "面积㎡", "应缴(元)");
    printf("--------------------------------------------------------------------------------\n");
    // %-4s的意思是：字符串至少4个字符宽度，不够用空格补齐，符号表示左对齐。输出字符串  序号

    Node* p = list->head->next;  //跳过哑节点
    int idx = 1;
    while(p != NULL){
        printf("%-4d %-10s %-4s %-20s %-13s %d-%d-%-4d %-8.1f %-10.2f\n",
               idx++,
               p->data.name,
               p->data.gender,
               p->data.id_number,
               p->data.phone,
               p->data.building, p->data.unit, p->data.room,
               p->data.area,
               p->data.fee_due);
        //记得更新指针p
        p = p->next;
    }
    printf("--------------------------------------------------------------------------------\n");
}
