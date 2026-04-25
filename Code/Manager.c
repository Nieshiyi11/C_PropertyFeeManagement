/*==================== 物业经理模块实现 ====================*/
#include <stdio.h>
#include <string.h>
#include "../HeadFiles/Manager.h"

/* ==================== 添加住户 ==================== */
/*
添加住户其实做3件事：
1. 读【字符串字段】（姓名、性别、身份证、电话、备注）→ 用fgets
2. 读【数字字段】（楼号、单元号、房号、面积、单价）→ 用scanf
3. 加进链表
*/
void manager_AddResident(ResidentList* list){
    if(list == NULL){
        printf("链表不存在！\n");
        return ;
    }
    /* 创建一个空白住户，所有字段初始化为 0 */
    /* 时刻注意：r是结构体变量 访问内容要用. */
    Resident r = {0};
    printf("\n===== 添加新住户 =====\n");


    /* ----------第一部分：读5个【字符串字段】---------- */
    /* 姓名 */
    printf("住户姓名：");
    fgets(r.name, sizeof(r.name), stdin);    //把用户输入读到 r.name
    r.name[strcspn(r.name, "\n")] = '\0';    //重要！！去掉末尾的换行符 \n
    /* 性别 */
    printf("性别（男/女）：");
    fgets(r.gender, sizeof(r.gender), stdin);
    r.gender[strcspn(r.gender, "\n")] = '\0';
    /* 身份证号 */
    printf("身份证号：");
    fgets(r.id_number, sizeof(r.id_number), stdin);
    r.id_number[strcspn(r.id_number, "\n")] = '\0';
    /* 身份证查重 */
    if(list_FindID(list,r.id_number) != NULL){
        printf("该住户已存在！\n");
        return ;
    }
    /*
      Q：我们没有#include Linked_List.h ,但是为什么能用这个list_FindID函数呢？
      A: 因为Manager.h里#include了Linked_List.h ;
         include是传递的！！
    */
    /* 联系电话 */
    printf("联系电话：");
    fgets(r.phone, sizeof(r.phone), stdin);
    r.phone[strcspn(r.phone, "\n")] = '\0';


    /* ----------第二部分：读5个【数字字段】---------- */
    /* 楼号 */
    printf("楼号：");
    scanf("%d", &r.building);
    /* 单元号 */
    printf("单元号：");
    scanf("%d", &r.unit);
    /* 房号 */
    printf("房号：");
    scanf("%d", &r.room);
    /* 平米数 */
    printf("平米数：");
    scanf("%lf", &r.area);  // %lf表示读入double类型数据
    /* 价格 */
    printf("每平米物业价格：");
    scanf("%lf", &r.pricePer);
    /* scanf用完后,缓冲区里残留一个\n,要把它清掉 */
    /* 否则下面的fgets会直接读到这个\n,跳过用户输入*/
    while (getchar() != '\n');

    /*
    【while (getchar() != '\n');】
    用户输完最后一个数字2.5，按下回车：
    用户输入：    2.5\n
    scanf("%lf", &r.pricePer)只读走2.5，留下\n在缓冲区
    接下来执行：
    fgets(r.remark, sizeof(r.remark), stdin);
    fgets看到缓冲区里残留的\n，就会立刻返回！！
    它会以为用户已经输入完一行了（其实是空行）
    结果：用户根本没机会输入备注
    解决：用 while (getchar() != '\n'); 手动吃掉残留的 \n
    */

    /* ----------第三部分：再读1个【字符串字段】(备注信息) ---------- */
    printf("备注信息：");
    fgets(r.remark, sizeof(r.remark), stdin);
    r.remark[strcspn(r.remark, "\n")] = '\0';
    /* 应缴物业费暂时为0(板块⑤会自动计算) */
    r.fee_due = 0.0;


    /* ---------- 第四部分：添加到链表 ---------- */
    if (list_Append(list, r)){
        printf("\n 添加成功！当前共 %d 户\n", list->size);
    }else{
        printf("\n 添加失败 \n");
    }
}


/* ==================== 查看所有住户 ==================== */
void manager_ViewAll(ResidentList* list) {
    list_Print(list);   // 直接调用链表层的打印函数
}
/*   
    【以上知识点总结 ———— fgets（读入字符串）】
     - fgets(目标, 最多读多少, 从哪里读)
     - r.name是 char[32]数组，fgets把用户输入的字符填进去
     - sizeof(r.name) = 32，告诉fgets最多读31个字符 + 1个'\0'
     - stdin则表示从键盘读
*/