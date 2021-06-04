#pragma once

#include <string>
#include "cardVector.h"
#include "infoVector.h"
#include "setting.h"

void addCard(cardVector& cardV, infoVector& infoV, setting& settings);
void displayCard(cardVector& cardV, setting& settings);
void pauseCard(cardVector& cardV, infoVector& infoV, setting& settings);
void cardSetUse(cardVector& cardV, setting& settings);
void cardSetUnuse(cardVector& cardV, infoVector& infoV, setting& settings);
void chargeCard(cardVector& cardV, infoVector& infoV, setting& settings);
void feeBack(cardVector& cardV, infoVector& infoV, setting& settings);
void searchCount(infoVector& infoV, const char id, setting& settings);
void searchCount1(infoVector& infoV, setting& settings);
void searchCount2(infoVector& infoV, setting& settings);
void searchCount3(infoVector& infoV, setting& settings);
void settings(setting& settings, const char id);