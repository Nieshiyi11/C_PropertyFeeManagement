/*==================== 程序入口 ====================*/
#include <stdio.h>
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
 
    //4. 读取上次生成月份
    int last_year = 0, last_month = 0;
    if(fileio_LoadLastMonth(&last_year, &last_month)){
        printf("\n[上次物业费生成记录：%d年%d月]\n", last_year, last_month);
        printf("[如需生成新月份费用，请进入【物业经理模块 → 生成物业费】]\n");
    }else{
        printf("\n[尚未生成过任何月份的物业费]\n");
        printf("[请进入【物业经理模块 → 生成物业费】开始使用]\n");
    }

    //5. 进入菜单
    menu_Main(list);
    //6. 退出前保存数据
    fileio_Save(list);
    //清理链表
    list_Destroy(list);
    return 0;
}