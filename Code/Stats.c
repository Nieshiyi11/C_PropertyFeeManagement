/*==================== 统计模块实现 ====================*/
#include <stdio.h>
#include "../HeadFiles/Stats.h"


/* ==================== 功能 1：按楼号统计未缴费 ==================== */
void stats_Building(ResidentList* list){
    if(list == NULL || list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }

    int target_building;
    printf("\n===== 按楼号统计未缴费 =====\n");
    printf("请输入楼号：");
    scanf("%d", &target_building);

    Node* p = list->head->next;  //跳过哑节点
    int count = 0;
    double total_debt = 0.0;

    printf("\n%d 号楼欠费住户：\n", target_building);
    printf("--------------------------------------------------\n");
    while(p != NULL){
        /* 楼号匹配并且欠费 */
        if(p->data.building == target_building && p->data.fee_due > 0){
            count++;
            total_debt += p->data.fee_due;
            printf("  %s  %d-%d-%d  欠费 %.2f 元\n",p->data.name,p->data.building, p->data.unit, p->data.room,p->data.fee_due);
        }
        p = p->next;
    }
    printf("--------------------------------------------------\n");

    if(count == 0){
        printf("%d 号楼无人欠费,或该楼号不存在\n", target_building);
    }else{
        printf("共 %d 户欠费,合计 %.2f 元\n", count, total_debt);
    }
}


/* ==================== 功能 2：按欠款从大到小排序 ==================== */
void stats_Sort(ResidentList* list){
    if(list == NULL || list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }

    //冒泡排序的链表实现
    int n = list->size;              // n 表示循环的次数
    for(int i = 0; i < n - 1; i++){  //【外层】：n - 1 轮就够
        Node* a = list->head->next;  //跳过哑节点
        Node* b = a->next;
        for(int j = 0; j < n - 1 - i; j++){ //【内层】；每轮少扫 i 个(后面 i 个已经排好)
            if(a->data.fee_due < b->data.fee_due){ //前面的更小 → 交换两个节点的data
                Resident temp = a->data;
                a->data = b->data;
                b->data = temp;
            }
            a = b;       //更新成下一个
            b = b->next; //更新成下一个
        }
    }

    //排序完毕,直接遍历打印
    printf("\n===== 欠款从大到小排序 =====\n");
    printf("%-4s %-10s %-13s %-10s\n", "序号", "姓名", "楼-单元-房", "欠款(元)");
    printf("--------------------------------------------------\n");
    Node* p = list->head->next;
    int idx = 1;
    while(p != NULL){
        printf("%-4d %-10s %d-%d-%-4d %-10.2f\n",idx++,p->data.name,p->data.building, p->data.unit, p->data.room,p->data.fee_due);
        p = p->next;
    }
    printf("--------------------------------------------------\n");
}
