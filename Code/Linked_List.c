#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HeadFiles/Linked_List.h"

/* ---------- 创建空链表 ---------- */
ResidentList* list_Create(void) {
    // 1. malloc 一个 ResidentList
    // 2. 检查 NULL
    // 3. malloc 哑节点
    // 4. 检查 NULL（失败要 free 第一步）
    // 5. 哑节点 next = NULL
    // 6. size = 0
    // 7. 返回 list
}

/* ---------- 销毁链表 ---------- */
void list_Destroy(ResidentList* list) {
    // 1. 判 list == NULL 直接 return
    // 2. 从 list->head 开始遍历
    // 3. 三步法释放：next = p->next → free(p) → p = next
    // 4. 最后 free(list)
}

/* ---------- 尾部添加 ---------- */
int list_Append(ResidentList* list, Resident r) {
    // 1. 判 list == NULL 返回 0
    // 2. malloc 新节点
    // 3. 失败返回 0
    // 4. new_node->data = r
    // 5. new_node->next = NULL
    // 6. 从 list->head 走到末尾
    // 7. tail->next = new_node
    // 8. list->size++
    // 9. 返回 1
}

/* ---------- 按身份证查找 ---------- */
Node* list_FindID(ResidentList* list, const char* id_number) {
    // 1. 判两个参数的 NULL
    // 2. p = list->head->next（跳过哑节点）
    // 3. while p != NULL
    // 4. strcmp 比较，相等返回 p
    // 5. 循环结束返回 NULL
}