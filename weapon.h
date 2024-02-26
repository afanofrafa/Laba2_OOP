#ifndef WEAPON_H
#define WEAPON_H
#pragma once
#include <iostream>
#include <QPushButton>
#include <QtMultimedia>
using namespace std;
int getRandomInt(int min_value, int max_value);
QVector<QPoint> generatePointsAroundCenter(int n, double radius, double centerX, double centerY);
class Firearm;
class BladedWeapon;
class Visitor {
public:
    virtual void visit(Firearm* firearm, QString actionName) = 0;
    virtual void visit(BladedWeapon* bladedweapon, QString actionName) = 0;
};
class Weapon {
private:
    static int count;
    static int createNum;
    int id;
public:
    Weapon();
    virtual ~Weapon();
    int GetID();
    static int GetCount();
    virtual QString* GetInfo() = 0;
    virtual QString operator [] (int index) = 0;
    virtual QVector<QPoint> Attack(int action) = 0;
    virtual QVector<QPoint> MakeWeaponUsable(int action) = 0;
    virtual void accept(Visitor* visitor, QString actionName) = 0;
};
#endif // WEAPON_H
