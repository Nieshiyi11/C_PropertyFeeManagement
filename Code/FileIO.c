/*==================== 文件读写模块实现 ====================*/
#include <stdio.h>
#include <string.h>
#include "../HeadFiles/FileIO.h"

/* ==================== 保存到文件 ==================== */
int fileio_Save(ResidentList* list){
    if(list == NULL){
        return 0;
    }

    FILE* fp = fopen(DATA_FILE, "w");
    if(fp == NULL){
        printf("\n无法打开文件 %s 进行写入\n", DATA_FILE);
        return 0;
    }

    Node* p = list->head->next;
    int count = 0;
    while(p != NULL){
        fprintf(fp, "%s %s %s %s %d %d %d %.2f %.2f %.2f %s\n",
                p->data.name,
                p->data.gender,
                p->data.id_number,
                p->data.phone,
                p->data.building,
                p->data.unit,
                p->data.room,
                p->data.area,
                p->data.pricePer,
                p->data.fee_due,
                p->data.remark);
        count++;
        p = p->next;
    }
    fclose(fp);
    printf("\n[已保存 %d 户到文件 %s]\n", count, DATA_FILE);
    return 1;
}


/* ==================== 从文件加载 ==================== */
int fileio_Load(ResidentList* list){
    if(list == NULL){
        return 0;
    }

    FILE* fp = fopen(DATA_FILE, "r");
    if(fp == NULL){
        printf("\n[未找到数据文件,从空链表开始]\n");
        return 0;
    }
    //【逻辑】
    //用fscanf循环读,每次读一户的所有字段;
    //fscanf的返回值：成功读到的字段数,应该是11;
    //当读到EOF(文件末尾)时返回值就不是 11,循环结束。
    int count = 0;
    while(1){
        Resident r = {0};   //创建一个空结构体变量，里面所有字段初始置0
        int fields = fscanf(fp, "%s %s %s %s %d %d %d %lf %lf %lf %s",
                            r.name,
                            r.gender,
                            r.id_number,
                            r.phone,
                            &r.building,
                            &r.unit,
                            &r.room,
                            &r.area,
                            &r.pricePer,
                            &r.fee_due,
                            r.remark);
        if(fields != 11){   //读不到11个字段就退出循环
            break;
        }
        list_Append(list, r);
        count++;
    }

    fclose(fp);
    printf("\n[已从文件 %s 加载 %d 户]\n", DATA_FILE, count);
    return 1;
}

/* ==================== 读取上次生成月份 ==================== */
int fileio_LoadLastMonth(int* year, int* month){
    FILE* fp = fopen(MONTH_FILE, "r");
    if(fp == NULL){
        return 0;   //文件不存在，说明从未生成过
    }
    int ok = (fscanf(fp, "%d %d", year, month) == 2);
    fclose(fp);
    return ok;
}

/* ==================== 保存本次生成的年月 ==================== */
int fileio_SaveLastMonth(int year, int month){
    FILE* fp = fopen(MONTH_FILE, "w");
    if(fp == NULL){
        return 0;
    }
    fprintf(fp, "%d %d\n", year, month);
    fclose(fp);
    return 1;
}