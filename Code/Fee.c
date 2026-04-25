/*==================== 物业费模块实现 ====================*/
#include <stdio.h>
#include <string.h>
#include "../HeadFiles/Fee.h"


/* ==================== 物业经理：生成本月物业费 ==================== */
void fee_GenerateAll(ResidentList* list){
    if(list == NULL){
        printf("链表不存在!\n");
        return;
    }
    if(list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }
    printf("\n===== 生成本月物业费 =====\n");
    printf("正在为【所有住户】生成本月费用...\n\n");

    /* 遍历每户,累加本月费用 */
    Node* p = list->head->next;   //跳过哑节点
    int count = 0;
    while(p != NULL){
        double monthly = p->data.area * p->data.pricePer;   //月费=面积×单价
        p->data.fee_due += monthly;    //累加到应缴
        count++;
        printf("  [%d] %s  本月费用 %.2f 元,累计应缴 %.2f 元\n",count, p->data.name, monthly, p->data.fee_due);
        p = p->next;
    }
    printf("\n本月物业费已生成,共处理 %d 户\n", count);
}


/* ==================== 住户：查询应缴物业费 ==================== */
void fee_QueryOne(ResidentList* list){
    if(list == NULL || list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }
    char id_number[20];

    /* 输入身份证号 */
    printf("\n===== 查询应缴物业费 =====\n");
    printf("请输入您的身份证号：");
    fgets(id_number, sizeof(id_number), stdin);
    id_number[strcspn(id_number, "\n")] = '\0';

    /* 查找用户是否存在 */
    Node* target = list_FindID(list, id_number);
    if(target == NULL){
        printf("\n未找到身份证号为 %s 的住户\n", id_number);
        return;
    }
    printf("\n户主: %s\n", target->data.name);
    printf("地址：%d 楼 %d 单元 %d 号\n",target->data.building, target->data.unit, target->data.room);
    printf("面积：%.1f ㎡,单价：%.2f 元/㎡\n",target->data.area, target->data.pricePer);

    /* 显示费用情况(三种状态) */
    if(target->data.fee_due > 0){
        printf("\n您当前【欠费】%.2f 元\n", target->data.fee_due);
    }else if(target->data.fee_due < 0){
        printf("\n您当前已【预存】%.2f 元\n", -target->data.fee_due); //注意：fee_due是负的,加个负号让显示成正数
    }else{
        printf("\n您当前【已付清】所有费用\n");
    }
}


/* ==================== 住户：自助缴费 ==================== */
void fee_PayOne(ResidentList* list){
    if(list == NULL || list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }

    char id_number[20];
    double amount;  //缴费金额
    printf("\n===== 自助缴费 =====\n");
    printf("请输入您的身份证号：");
    fgets(id_number, sizeof(id_number), stdin);
    id_number[strcspn(id_number, "\n")] = '\0';

    Node* target = list_FindID(list, id_number);
    if(target == NULL){
        printf("\n未找到身份证号为 %s 的住户\n", id_number);
        return;
    }

    /* 显示当前费用情况 */
    printf("\n户主: %s\n", target->data.name);
    if(target->data.fee_due > 0){
        printf("当前应缴：%.2f 元\n", target->data.fee_due);
    }else if(target->data.fee_due < 0){
        printf("当前已预存：%.2f 元\n", -target->data.fee_due);
    }else{
        printf("当前已付清\n");
    }

    /* 读缴费金额 */
    printf("\n请输入缴费金额: ");
    scanf("%lf", &amount);
    if(amount <= 0){
        printf("\n金额必须为正数,操作取消\n");
        return;
    }
    /* 缴费:从应缴里减掉 */
    target->data.fee_due = target->data.fee_due - amount;
    /* 反馈结果(三种情况) */
    printf("\n缴费成功!\n");
    if(target->data.fee_due > 0){
        printf("还需缴纳：%.2f 元\n", target->data.fee_due);
    }else if(target->data.fee_due < 0){
        printf("本次缴费后,您预存了 %.2f 元(可抵扣下月费用)\n", -target->data.fee_due);
    }else{
        printf("已付清所有费用\n");
    }
}