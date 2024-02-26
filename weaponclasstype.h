#ifndef WEAPONCLASSTYPE_H
#define WEAPONCLASSTYPE_H
#pragma once
#include "weapontypes.h"
class Gun : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    Gun();
    ~Gun() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class MachineGun : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    MachineGun();
    ~MachineGun() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class Rifle : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    Rifle();
    ~Rifle() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class ShotGun : public Firearm {
private:
    QVector<QPoint> Shoot(int action, QString Url) override;
    QVector<QPoint> Reload(QString Url) override;
    QVector<QPoint> Clean(QString Url) override;
public:
    ShotGun();
    ~ShotGun() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class Knife : public BladedWeapon {
private:
    QVector<QPoint> Stab(int bladeThick, int bladeWidth, QString Url, int b) override;
    QVector<QPoint> Sharpen(QString Url) override;
    QVector<QPoint> Slash(int bladeThick, int bladeWidth, QString Url, int b) override;
public:
    Knife();
    ~Knife() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class Katana : public BladedWeapon {
private:
    QVector<QPoint> Stab(int bladeThick, int bladeWidth, QString Url, int b) override;
    QVector<QPoint> Sharpen(QString Url) override;
    QVector<QPoint> Slash(int bladeThick, int bladeWidth, QString Url, int b) override;
public:
    Katana();
    ~Katana() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class Sword : public BladedWeapon {
private:
    QVector<QPoint> Stab(int bladeThick, int bladeWidth, QString Url, int b) override;
    QVector<QPoint> Sharpen(QString Url) override;
    QVector<QPoint> Slash(int bladeThick, int bladeWidth, QString Url, int b) override;
public:
    Sword();
    ~Sword() override;
    void accept(Visitor* visitor, QString actionName) override;
};
class Blade : public BladedWeapon {
private:
    QVector<QPoint> Stab(int bladeThick, int bladeWidth, QString Url, int b) override;
    QVector<QPoint> Sharpen(QString Url) override;
    QVector<QPoint> Slash(int bladeThick, int bladeWidth, QString Url, int b) override;
public:
    Blade();
    ~Blade() override;
    void accept(Visitor* visitor, QString actionName) override;
};
#endif // WEAPONCLASSTYPE_H
