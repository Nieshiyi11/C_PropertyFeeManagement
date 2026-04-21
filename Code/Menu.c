/*==================== 菜单系统实现 ====================*/
#include <stdio.h>
#include "../HeadFiles/Menu.h"
//【while(1) + switch-case +break 是C语言项目中菜单的经典实现方法！！】


/* ==================== 辅助函数 ==================== */
/*
【清空stdin缓冲区】
 scanf("%d", &choice); 只会读走数字，不会读走用户按下的回车\n
 这个\n残留在缓冲区里，下次scanf/fgets会直接读到它，导致 bug
 所以每次scanf后都要手动清空缓冲区到换行符为止...
*/
static void clear_stdin(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        //把缓冲区里剩下的字符全丢掉
        //这个循环不断读字符直到遇到换行符或文件结束，相当于"清扫"缓冲区
    }
}


/*
【读取一个整数选项】
 封装scanf的逻辑，返回用户输入的数字。
 如果用户输入非数字（比如 "abc"）,scanf 返回 0,我们返回-1表示错误。
*/
static int read_choice(void){
    int choice;
    if(scanf("%d", &choice) != 1){
        /*用户输入的不是数字*/
        clear_stdin();     //清掉那些字母，否则下次scanf又读到它们
        return -1;
    }
    clear_stdin();         //清掉数字后面的 \n
    return choice;
}
//【总结！！】
/*
scanf返回成功读取的参数个数。想读1个整数，成功就返回1
如果用户输了abc，则返回0（没读到任何整数）
注意：非数字输入时，那些字母不会被scanf读走，还留在缓冲区
所以必须clear_stdin清掉，否则下次循环又读到同样的字母，死循环
*/



/* ==================== 物业经理子菜单 ==================== */
static void menu_Manager(ResidentList* list) {
    (void)list;  // 暂时不用 list，加这行避免编译警告
    while (1) {
        printf("\n===== 物业经理模块 =====\n");
        printf("1. 添加住户信息\n");
        printf("2. 修改住户信息\n");
        printf("3. 删除住户信息\n");
        printf("4. 查看住户列表\n");
        printf("5. 按楼号统计未缴费\n");
        printf("6. 按欠款排序\n");
        printf("0. 返回主菜单\n");
        printf("请选择：");
        //读取选择
        int choice = read_choice();

        switch (choice) {
            case 1:
                printf("[板块④] 添加住户功能开发中...\n");
                break;
            case 2:
                printf("[板块④] 修改住户功能开发中...\n");
                break;
            case 3:
                printf("[板块④] 删除住户功能开发中...\n");
                break;
            case 4:
                printf("[板块④] 查看住户列表功能开发中...\n");
                break;
            case 5:
                printf("[板块⑦] 按楼号统计功能开发中...\n");
                break;
            case 6:
                printf("[板块⑦] 按欠款排序功能开发中...\n");
                break;
            case 0:
                return;   //退出本函数，回到menu_Main
            default:
                printf("输入错误，请重新选择\n");
                break;
        }
    }
}

/* ==================== 住户子菜单 ==================== */
static void menu_Resident(ResidentList* list) {
    (void)list;
    while (1) {
        printf("\n===== 住户模块 =====\n");
        printf("1. 查询个人信息\n");
        printf("2. 查询应缴物业费\n");
        printf("3. 自助缴费\n");
        printf("0. 返回主菜单\n");
        printf("请选择：");

        int choice = read_choice();

        switch (choice) {
            case 1:
                printf("[板块④] 查询个人信息功能开发中...\n");
                break;
            case 2:
                printf("[板块⑤] 查询应缴物业费功能开发中...\n");
                break;
            case 3:
                printf("[板块⑥] 自助缴费功能开发中...\n");
                break;
            case 0:
                return;  //退出本函数，回到menu_Main
            default:
                printf("输入错误，请重新选择\n");
                break;
        }
    }
}

/* ==================== 主菜单 ==================== */
void menu_Main(ResidentList* list) {
    while (1) {
        printf("\n===== 主菜单 =====\n");
        printf("1. 物业经理模块\n");
        printf("2. 住户模块\n");
        printf("0. 退出系统\n");
        printf("请选择：");

        int choice = read_choice();

        switch (choice) {
            case 1:
                menu_Manager(list);
                break;
            case 2:
                menu_Resident(list);
                break;
            case 0:
                printf("\n感谢使用,再见!\n");
                return;
            default:
                printf("输入错误,请重新选择!\n");
                break;
        }
    }
}

//再次强化 ———— 【static函数】
/*
static void menu_Manager(ResidentList* list);
static void menu_Resident(ResidentList* list);
static int read_choice(void);
static void clear_stdin(void);
这些都是【本文件内部】用的，外界（main.c等）不需要知道
故加static让它们只在Menu.c里可见
对比menu_Main，就没static，因为它要被main.c调用
*/