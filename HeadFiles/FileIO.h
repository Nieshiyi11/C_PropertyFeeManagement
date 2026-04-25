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
#define DATA_FILE "data.txt" //含义: 在编译前把所有 DATA_FILE 替换成 "data.txt"。

/* ==================== 文件读写模块 ==================== */

/* 从文件加载住户数据到链表(覆盖原有数据) */
int fileio_Load(ResidentList* list);

/* 把链表数据保存到文件(覆盖原有文件) */
int fileio_Save(ResidentList* list);

#endif

/*
【#define DATA_FILE "data.txt"】
- 你在 FileIO.c 里看见的：
  FILE* fp = fopen(DATA_FILE, "w");
- 编译器实际上看到的：
  FILE* fp = fopen("data.txt","w");
*/