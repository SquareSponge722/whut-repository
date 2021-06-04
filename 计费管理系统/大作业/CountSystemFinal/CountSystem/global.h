#pragma once

constexpr auto TIMELENGTH = 20;
constexpr auto WRITEFILE = false;

//卡状态
constexpr auto USING = 1; //上机
constexpr auto UNUSE = 2; //下机
constexpr auto PAUSED = 3; //注销

//开卡结果
constexpr auto SUCCESS = 11;
constexpr auto FAILURE = 12;
constexpr auto EXISTED = 13;

//INFO常量标识
constexpr auto INFO_NEW = 21; //创卡
constexpr auto INFO_PAUSE = 22; //销卡
constexpr auto INFO_CHARGE = 23; //充值
constexpr auto INFO_FEEBACK = 24; //退费
constexpr auto INFO_CUNSUME = 25; //消费

//费用常量
constexpr auto UNIT = 5; //最小收费单元(分钟)
constexpr auto FEE = 500; //每收费单元费用(元)
constexpr auto LIMIT = 0.5; //卡余额下限(元)

//默认语句
constexpr auto SPLITELINE = "----------" ;
constexpr auto ERRORLINE = "！！！！！！";
constexpr auto DOWNLINE = "____";
constexpr auto HINT_CANCEL = "已取消本次操作...\n";
constexpr auto HINT_REINPUT = "是否重新输入？（y/n）";
constexpr auto HINT_REWRITE = "是否更改？（y/n）";
constexpr auto HINT_PAUSED = "卡号已注销！\n";
constexpr auto HINT_USING = "本卡已上机！\n";
constexpr auto HINT_UNUSED = "本卡已下机！\n";
constexpr auto HINT_ASK_UNUSE = "请将卡下机后再操作！\n";
constexpr auto HINT_ASK_USING = "请将卡上机后再操作！\n";
constexpr auto HINT_ASK_QUIT = "请退出本系统以应用新设置！\n";
constexpr auto HINT_ASK_PATH = "请输入新路径：";
constexpr auto HINT_ASK_VALUE = "请输入新值：";
constexpr auto HINT_BALANCE_SHORTAGE = "卡余额不足！\n";
constexpr auto HINT_SUCCESS = "操作成功！\n";
constexpr auto HINT_NULL_RESAULT = "查询结果为空！\n";

//默认路径
constexpr auto CARDPATH = "D:\\card.txt";
constexpr auto INFOPATH = "D:\\info.txt";
constexpr auto LOGPATH = "D:\\log.txt";
constexpr auto SETTINGPATH = "D:\\setting.txt";