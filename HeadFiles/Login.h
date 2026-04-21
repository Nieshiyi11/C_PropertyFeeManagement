#ifndef LOGIN
#define LOGIN
/* ==================== 登录模块 ==================== */
/*
【功能如下】
  - 要求用户输入用户名和密码
  - 用户名和密码是否输入正确（admin / 123456）
  - 最多允许3次尝试
  - 3次都失败则返回0（登录失败）
  - 成功则返回1
*/
int login(void);  //只暴露一个【用户登录接口】调用方（main函数）只需要知道：返回1则进系统，返回0就退出。
#endif


// Q1：为什么不在这个头文件里就实现Login函数，而要在Login.c里单独实现函数？
/* A1：回忆一下每次#include都在做什么 ———— 文本粘贴
      既然如此，假设两个文件都用到了Login.c
    【main.c】:
    #include "Login.h"     // 把Login.h内容粘过来
    int main() { login(); return 0; }
    【other.c】
    #include "Login.h"     // 又把Login.h内容粘过来
    void foo() { login(); }
    ---
    那么，预处理之后，编译器看到的就是Login()被定义了两次 ———— 重复定义
    编译器会报错:"multiple definition of `login'"
*/

// Q2：那么不是还有头文件守卫 #ifndef 吗？我们知道 #ifndef就是用来解决被#include多次而出现重复定义问题的。
// A2：守卫只在单个.c内部防重复，对跨文件无效。【详情请见../HeadFiles/Resident.h】
