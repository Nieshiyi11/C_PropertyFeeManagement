# C语言工程实践项目 ———— 物业费管理系统

# C Language Project ———— Propertyfee Management

---

## 简介 / Brief Introduction

【中文】

这是一个C语言工程实践项目，最大的特点是手写头文件（接口知识），有良好的项目结构。


可以将本仓库作为一个C语言知识库看待。


:)

[English]

This is a C Language Project,the greatest feature is writing a headfile(a knowledge about Interface) and having a better project structure.

You can regard it as a C Language knowledge base.

:)

---

## 【注】关于VS Code中文乱码问题的解决

Step1. 电脑配置GCC编译器以及环境配置PATH

Step2. 配置powershell编码

Step3. 配置json文件

Step4. VS Code里设置调整默认文字编码为UTF-8

---

## [P.S.] Solving Chinese Encodng in VS Code

Step1. Install GCC compiler and configure environment variable PATH

Step2. Configure powershell encoding

Step3. Configure the tasks.json file

Step4. Set VS Code default file encoding to UTF-8

---

## 📁 项目结构 (Project Structure)

```
C_PropertyFeeManagement/
├── .vscode/
│   └── tasks.json              # 编译配置（UTF-8 全链路）
│
├── HeadFiles/                  # 头文件 / 接口声明
│   ├── Resident.h              # 住户结构体
│   ├── Linked_List.h           # 链表接口
│   ├── Login.h                 # 登录接口
│   ├── Menu.h                  # 菜单接口
│   ├── Manager.h               # 物业经理接口
│   ├── Fee.h                   # 物业费接口
│   ├── Stats.h                 # 统计接口
│   └── FileIO.h                # 文件读写接口
│
├── Code/                       # 源文件 / 实现
│   ├── InterfaceFunction.c     # 链表实现（增删改查）
│   ├── Login.c                 # 登录验证
│   ├── Menu.c                  # 三层菜单
│   ├── Manager.c               # 物业经理模块
│   ├── Fee.c                   # 费用计算 + 缴费
│   ├── Stats.c                 # 统计 + 排序
│   ├── FileIO.c                # 数据持久化
│   └── main.c                  # 程序入口
│
├── Images/
│   └── 项目要求.jpg
│
├── data.txt                    # 数据持久化文件（运行时生成）
└── test.exe                    # 编译产物（运行时生成）
```
---
