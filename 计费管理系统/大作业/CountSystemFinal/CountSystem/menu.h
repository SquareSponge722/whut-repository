#pragma once
#include <iostream>
#include "cardVector.h"
#include "infoVector.h"
#include "setting.h"

bool menu(cardVector& cardvector_, infoVector& infovector_, setting& setting_);
void menuInfo();
void searchInfo(infoVector& infovector_, setting& setting_);
void settingInfo(setting& setting_);