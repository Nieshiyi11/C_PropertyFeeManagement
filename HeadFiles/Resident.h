#ifndef RESIDENT   //头文件守卫: 防止同一个头文件被多次#include导致"重复定义"错误
#define RESIDENT   //定义这个头文件

//单月费用记录
#define MAX_FEE_RECORDS 36
typedef struct{
    int    year;
    int    month;
    double amount;    //当月费用（面积*单价）
    double paid;      //已缴金额（0=未缴费 amount=已缴清）
}FeeRecord;

//住户信息结构体
typedef struct{
    char   name[32];                 //住户姓名
    char   gender[8];                //性别
    char   id_number[20];            //身份证号
    char   phone[16];                //联系电话
    int    building;                 //楼号
    int    unit;                     //单元号
    int    room;                     //房号
    double area;                     //平米数
    double pricePer;                 //每平米物业价格
    char   remark[128];              //备注信息
    FeeRecord fees[MAX_FEE_RECORDS]; //按月费用记录
    int    fee_count;                //已有费用记录条数
}Resident;

#endif  //结束 #ifndef



/*
单个.c文件中怎么会发生“重复定义”问题呢？？
举例：

#include "Resident.h"     //第一次包含Resident.h
#include "Linked_List.h"  //这里面又包含了Resident.h

#include 的本质就是文本粘贴！！
*/