#pragma once

#include <string>
#include "cardVector.h"

void addCard(cardVector& cardV);
bool inputName(string& name);
bool inputPwd(string& pwd);
bool inputBalance(double& balance);
bool confirmBalance(double balance);
void displayCard(cardVector& cardV);
void pauseCard(cardVector& cardV);