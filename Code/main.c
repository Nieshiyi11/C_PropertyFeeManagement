/*==================== 程序入口 ====================*/
#include <stdio.h>
#include <time.h> //用C标准库的time.h获取系统当前时间
#include "../HeadFiles/Linked_List.h"
#include "../HeadFiles/Login.h"
#include "../HeadFiles/Menu.h"
#include "../HeadFiles/FileIO.h"

int main(void){
    //1.登录
    if (!login()){
        return 1;
    }
    //2. 创建链表
    ResidentList* list = list_Create();
    if (list == NULL){
        printf("内存分配失败，程序退出\n");
        return 1;
    }
    //3. 从文件加载已有数据
    fileio_Load(list); 

    //4. 获取系统当前年月
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    int cur_year  = t->tm_year + 1900;  //注意 tm_year 是从1900年开始算的所以要+1900
    int cur_month = t->tm_mon + 1;  //tm_mon 是从0开始算的（0=1月）所以要+1
 
    //5. 读取上次生成月份，判断是否需要自动生成本月费用
    int last_year = 0, last_month = 0;
    int has_record = fileio_LoadLastMonth(&last_year, &last_month);

    if (!has_record || cur_year > last_year || (cur_year == last_year && cur_month > last_month)){
        //跨月了（或从未生成过），自动生成本月物业费
        printf("\n========================================\n");
        printf("  检测到新月份：%d年%d月\n", cur_year, cur_month);
        printf("  正在自动生成本月物业费...\n");
        printf("========================================\n");

        fee_GenerateAll(list);              //生成费用
        fileio_SaveLastMonth(cur_year, cur_month);  //记录本月已生成
        fileio_Save(list);                  //立即保存，防止意外丢失
    }else{
        printf("\n[本月(%d年%d月)物业费已生成，无需重复生成]\n",cur_year, cur_month);
    }

    //6. 进入菜单
    menu_Main(list);
    //7. 退出前保存数据
     fileio_Save(list);
    //清理链表
    list_Destroy(list);
    return 0;
}