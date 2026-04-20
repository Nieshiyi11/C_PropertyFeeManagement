#ifndef RESIDENT   //头文件守卫: 防止同一个头文件被多次#include导致"重复定义"错误
#define RESIDENT   //定于这个头文件

/* ==================== 住户信息结构体 ==================== */
typedef struct{
    char   name[32];         //户主姓名
    char   gender[8];        //性别
    char   id_number[20];    //身份证号
    char   phone[16];        //联系电话
    int    building;         //楼号
    int    unit;             //单元号
    int    room;             //房号
    double area;             //平米数
    double pricePer;         //每平米物业价格
    double fee_due;          //应缴纳物业费
    char   remark[128];      //备注信息
}Resident;

#endif  //结束 #ifndef