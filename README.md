# C语言工程实践项目 ———— 物业费管理系统

# C Language Project ———— Propertyfee Management

---

## 简介 / Brief Introduction

【中文】

这是一个C语言工程实践项目，最大的特点是手写头文件（接口知识），有良好的项目结构。


可以将本仓库作为一个C语言知识库看待。

关于如何在 **VS Code** 里编译代码：

**[法一]**：不用配置 JSON 文件，可以在终端手敲 gcc 命令行：

#01. gcc Code/*.c -I HeadFiles -o test

#02. ./test.exe

**[法二]**：配置 JSON 文件

`````
{
    "version": "2.0.0",   
    "tasks": [
        {
            "label": "Build All C Files",
            "type": "shell",
            "command": "gcc Code/*.c -I HeadFiles -o test.exe",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
} 
`````

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

【📒飞书笔记】：https://wonderfulworld.feishu.cn/docx/D7XudwnmVoo5tKxJt3ZcdQ7Znkp?from=from_copylink

[📒Feishu note]： https://wonderfulworld.feishu.cn/docx/D7XudwnmVoo5tKxJt3ZcdQ7Znkp?from=from_copylink

