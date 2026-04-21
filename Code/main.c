/*==================== 程序入口 ====================*/
#include <stdio.h>
#include "../HeadFiles/Linked_List.h"
#include "../HeadFiles/Login.h"
#include "../HeadFiles/Menu.h"

int main(void) {
    //1.登录
    if (!login()) {
        return 1;
    }
    //2. 创建链表
    ResidentList* list = list_Create();
    if (list == NULL) {
        printf("内存分配失败，程序退出\n");
        return 1;
    }
    //3. 从文件加载已有数据
    //4. 进入菜单
    menu_Main(list);
    //清理链表
    list_Destroy(list);
    return 0;
}