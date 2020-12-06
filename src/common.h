/*
 * 作者：幽弥狂
 * 日期：2020-12-6
 * 功能：通用全局变量
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QString>
#include <QThread>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include <iostream>

struct pkgPacket{
    int signal;

    int delta;
    int theta;
    int lowAlpha;
    int highAlpha;
    int lowBeta;
    int highBeta;
    int lowGamma;
    int midGamma;
    int attention;//0-100
    int meditation;//0-100
    int rawdata;
    int blink;

    bool valid;//此包数据是否有效
}pkgPacket;//一个数据包包含的所有值

#endif // COMMON_H
