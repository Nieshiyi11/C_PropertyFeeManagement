/*==================== 登录系统实现 ====================*/
#include <stdio.h>
#include <string.h>
#include "../HeadFiles/Login.h"


/* ---------- 先设置用户名和密码（之后会改为从文件读取） ---------- */
#define CORRECT_USERNAME "admin"
#define CORRECT_PASSWORD "123456"
#define MAX_ATTEMPTS 3


/* ---------- 辅助函数：去除字符串末尾的换行符 ---------- */
/*
【需知】
  fgets(str,sizeof(str),stdin);
  stdin表示的是输入流（键盘区）;
  fgets会把用户按下的回车\n也读进字符串;
  比如用户输入"admin"以后按回车，那么实际存的是"admin\n";
  和"admin"比较就会不相等，所以必须去掉末尾的\n。

【strcspn用法】
  strcspn(s, "\n") 返回：str中第一次出现任何"\n"字符【之前】的字符数
  换句话说:它返回\n的位置索引（如果str里没有\n，则返回strlen(str)）
  把那个位置设成'\0'，就截断了换行符！！
*/

static void strip_newline(char* str){
    str[strcspn(str, "\n")] = '\0';
}
//【static】表示"只能在本文件（Login.c）内部调用"，对外（Login.h）不暴露。这是"模块内部辅助函数"的标准写法。
//这一段strcspn等价于：
/*
for(int i = 0; s[i] != '\0'; i++){
    if (s[i] == '\n'){
        s[i] = '\0';
        break;
    }
}
*/


/* ---------- 登录函数 ---------- */
int login(void){
    char username[32];
    char password[32];
    printf("============================\n");
    printf("    物业费管理用户登录系统\n");
    printf("============================\n");
    //给用户3次机会
    for(int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++){
        printf("\n【您的第%d / %d次尝试】\n", attempt, MAX_ATTEMPTS);
        //读用户名
        printf("请输入用户名：");
        fgets(username, sizeof(username), stdin);
        strip_newline(username);  //吃掉用户按入的回车
        
        //读密码
        printf("请输入您的密码：");
        fgets(password, sizeof(password), stdin);
        strip_newline(password);  //吃掉用户按入的回车
        
        //验证登录
        if(strcmp(username,CORRECT_USERNAME) == 0 && strcmp(password,CORRECT_PASSWORD) == 0){
            printf("\n登录成功,欢迎进入物业费管理系统!\n");
            return 1;
        }else{
            int remaining = MAX_ATTEMPTS - attempt;
            if (remaining > 0){
                printf("用户名或密码错误,还剩 %d 次机会\n", remaining);
            }
        }
    }
    //*3次都失败
    printf("用户名或密码错误,系统已自动退出\n");
    return 0;
}

/*
**体会“为什么main.c里只是#include了Login.h 但是没有和Login.c建立联系，那Login函数是怎么能够被使用了呢？”
1.【编译阶段】
main.c打电话时，电话本上没号码，编译器说："先记下'要打给login'，号码等我查到再填。"
Login.c本身是独立的，告诉系统："我的地址是 0x1234"。
2.【链接阶段】
链接器拿着所有信息对接："main要找login？好，我知道login在 0x1234，填进去。"
最终test.exe里main调用login时，直接跳到 0x1234 执行。
*/


/*
关键：链接器怎么知道要找Login？
回答：早就在tasks.json里告诉它的了！！
"args": [
    ...
    "${workspaceFolder}/Code/InterfaceFunction.c",
    "${workspaceFolder}/Code/Login.c",
    "${workspaceFolder}/Code/Menu.c",
    "${workspaceFolder}/Code/main.c",
    "-o",
    "${workspaceFolder}/test.exe"
]
这像是在告诉gcc：把这些.c文件一起编译链接成test.exe
那么，gcc的内部流程即为：
Step1. 编译每个.c → 各自的.o
Step2. 链接所有.o → test.exe

*/