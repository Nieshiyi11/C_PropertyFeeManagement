/*
【文件四大操作】
- FILE* fp = fopen("data.txt", "r");   // 打开文件
- fread/fscanf/fgets(...);             // 读  fscanf(); 遇到空格就停!!
- fwrite/fprintf(...);                 // 写
- fclose(fp);                          // 关闭
*/
#ifndef FILEIO
#define FILEIO
#include "Linked_List.h"
#define DATA_FILE "data.txt" //含义: 在编译前把所有 DATA_FILE 替换成 "data.txt"
#define MONTH_FILE "last_month.txt" //记录上次生成费用的年月

/* ==================== 文件读写模块 ==================== */

/* 从文件加载住户数据到链表(覆盖原有数据) */
int fileio_Load(ResidentList* list);
/* 把链表数据保存到文件(覆盖原有文件) */
int fileio_Save(ResidentList* list);

/* 读取上次生成月份，读不到则返回0 */
// 用int* 指针传参是因为C语言函数没法直接返回两个值，所以用指针把年和月"带出来"
int fileio_LoadLastMonth(int* year, int* month);
/* 保存本次生成的年月 */
int fileio_SaveLastMonth(int year, int month);

#endif

/*
【#define DATA_FILE "data.txt"】
- 你在 FileIO.c 里看见的：
  FILE* fp = fopen(DATA_FILE, "w");
- 编译器实际上看到的：
  FILE* fp = fopen("data.txt","w");
*/