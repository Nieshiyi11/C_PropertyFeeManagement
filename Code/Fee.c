/*==================== 物业费模块实现 ====================*/
#include <stdio.h>
#include <string.h>
#include "../HeadFiles/Fee.h"
#include "../HeadFiles/FileIO.h"

/* ==================== 辅助：在住户记录中查找指定年月的费用索引 ==================== */
static int find_fee_index(Resident* r, int year, int month){
    for(int i = 0; i < r->fee_count; i++){
        if(r->fees[i].year == year && r->fees[i].month == month){
            return i;
        }
    }
    return -1;   //为什么返回-1？
    //因为数组下标从0开始，所以有效的索引只会是 0, 1, 2, ... 这些非负数
    //用-1作为返回值，是一个约定俗成的"哨兵值"，表示没找到。调用方收到-1就知道查无此月
    //如果用0表示没找到，就和"找到了，在第0条"混淆了，所以选一个永远不可能是合法下标的值-1来区分这两种情况
}

/* ==================== 物业经理：生成指定年月物业费 ==================== */
void fee_GenerateAll(ResidentList* list, int year, int month){
    if(list == NULL){
        printf("链表不存在!\n");
        return;
    }
    if(list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }
    
    printf("\n===== 生成 %d年%d月 物业费 =====\n", year, month);
    printf("正在为【所有住户】生成当月费用...\n\n");
    
    Node* p = list->head->next;
    int count = 0, skip = 0;
    while(p != NULL){
        //检查该月费用是否已存在
        if(find_fee_index(&p->data, year, month) >= 0){
            skip++;
            p = p->next;
            continue;
        }
        //检查是否还有空间
        if(p->data.fee_count >= MAX_FEE_RECORDS){
            printf("  [警告] %s 的费用记录已满，跳过\n", p->data.name);
            p = p->next;
            continue;
        }
        double monthly = p->data.area * p->data.pricePer;
        int index = p->data.fee_count;
        p->data.fees[index].year   = year;
        p->data.fees[index].month  = month;
        p->data.fees[index].amount = monthly;
        p->data.fees[index].paid   = 0.0;
        p->data.fee_count++;
        count++;
        printf("  [%d] %s  当月费用 %.2f 元\n", count, p->data.name, monthly);
        p = p->next;
    }

    if(skip > 0){
        printf("\n[提示] %d 户已存在%d年%d月的费用记录, 已跳过\n",
               skip, year, month);
    }
    fileio_SaveLastMonth(year, month);
    printf("\n%d年%d月物业费已生成, 共处理 %d 户\n", year, month, count);
}


/* ==================== 住户：查询指定年月应缴物业费 ==================== */
void fee_QueryOne(ResidentList* list){
    if(list == NULL || list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }
    char id_number[20];
    int year, month;

    printf("\n===== 查询应缴物业费 =====\n");
    printf("请输入您的身份证号：");
    fgets(id_number, sizeof(id_number), stdin);
    id_number[strcspn(id_number, "\n")] = '\0';

    Node* target = list_FindID(list, id_number);
    if(target == NULL){
        printf("\n未找到身份证号为 %s 的住户\n", id_number);
        return;
    }

    printf("请输入要查询的年份(例如2026): ");
    if(scanf("%d", &year) != 1 || year < 2000 || year > 2100){
        while(getchar() != '\n');
        printf("年份输入无效，操作取消\n");
        return;
    }
    printf("请输入要查询的月份(1-12): ");
    if(scanf("%d", &month) != 1 || month < 1 || month > 12){
        while(getchar() != '\n');
        printf("月份输入无效，操作取消\n");
        return;
    }
    while(getchar() != '\n');

    int idx = find_fee_index(&target->data, year, month);
    printf("\n户主: %s\n", target->data.name);
    printf("地址：%d 楼 %d 单元 %d 号\n",
           target->data.building, target->data.unit, target->data.room);

    if(idx < 0){
        printf("\n%d年%d月 尚未生成物业费记录\n", year, month);
    }else{
        FeeRecord* fr = &target->data.fees[idx];
        double unpaid = fr->amount - fr->paid;
        printf("当月费用：%.2f 元\n", fr->amount);
        printf("已缴金额：%.2f 元\n", fr->paid);
        if(unpaid > 0){
            printf("尚欠：    %.2f 元\n", unpaid);
        }else if(unpaid < 0){
            printf("预存：    %.2f 元\n", -unpaid);
        }else{
            printf("状态：    已缴清\n");
        }
    }
}


/* ==================== 住户：为指定年月自助缴费 ==================== */
void fee_PayOne(ResidentList* list){
    if(list == NULL || list->size == 0){
        printf("\n当前没有任何住户记录\n");
        return;
    }

    char id_number[20];
    int year, month;
    double amount;

    printf("\n===== 自助缴费 =====\n");
    printf("请输入您的身份证号：");
    fgets(id_number, sizeof(id_number), stdin);
    id_number[strcspn(id_number, "\n")] = '\0';

    Node* target = list_FindID(list, id_number);
    if(target == NULL){
        printf("\n未找到身份证号为 %s 的住户\n", id_number);
        return;
    }

    printf("请输入要缴纳的年月(例如: 2026 6): ");
    if(scanf("%d %d", &year, &month) != 2){
        while(getchar() != '\n');
        printf("输入格式错误，操作取消\n");
        return;
    }
    while(getchar() != '\n');

    int idx = find_fee_index(&target->data, year, month);
    if(idx < 0){
        printf("\n%d年%d月 尚未生成物业费记录，请先联系物业生成费用\n", year, month);
        return;
    }

    FeeRecord* fr = &target->data.fees[idx];
    double unpaid = fr->amount - fr->paid;

    printf("\n户主: %s\n", target->data.name);
    printf("%d年%d月 费用 %.2f 元, 已缴 %.2f 元",fr->year, fr->month, fr->amount, fr->paid);
    if(unpaid > 0){
        printf(", 尚欠 %.2f 元\n", unpaid);
    }else{
        printf(", 已缴清\n");
    }

    printf("\n请输入缴费金额: ");
    scanf("%lf", &amount);
    while(getchar() != '\n');
    if(amount <= 0){
        printf("金额必须为正数,操作取消\n");
        return;
    }

    fr->paid += amount;
    unpaid = fr->amount - fr->paid;
    printf("\n缴费成功!\n");
    if(unpaid > 0){
        printf("还需缴纳：%.2f 元\n", unpaid);
    }else if(unpaid < 0){
        printf("本次缴费后,您预存了 %.2f 元(可抵扣下月费用)\n", -unpaid);
    }else{
        printf("已付清%d年%d月所有费用\n", year, month);
    }
}