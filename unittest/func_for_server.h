#ifndef FUNC_FOR_SERVER_H
#define FUNC_FOR_SERVER_H
#include<QByteArray>
#include <iostream>
#include <QString>
#include "SingletonDB.h"
QByteArray parsing(QString str,long desc);
QByteArray auth(QString log, QString pas,long desc);
QByteArray reg(QString log, QString pas,long desc);
QByteArray checktask(QString numb,QString var,QString otvet,long desc);
QByteArray get_var_task_1(QString var, QString otvet, long desc, QByteArray& stats);
bool check_task_1(QString variant, QString answer);
QByteArray mlta(QString ansv);
void sokr(int*& massive, int o, int*& s);
QByteArray stat(long desc, QByteArray& stats);
#endif