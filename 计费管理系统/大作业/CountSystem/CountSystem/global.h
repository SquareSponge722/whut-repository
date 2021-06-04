#pragma once

#define TIMELENGTH 20

//卡状态
#define USING 1
#define UNUSE 2
#define PAUSED 3

//开卡结果
#define SUCCESS 11
#define FAILURE 12
#define EXISTED 13

//默认语句
#define SPLITELINE "----------" 
#define ERRORLINE "！！！！！！"
#define CANCELHINT "已取消本次操作...\n"
#define REINPUTHINT "是否重新输入？（y/n）"

//默认路径
#define CARDPATH "D:\\card.txt"