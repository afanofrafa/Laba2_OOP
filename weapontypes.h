#ifndef WEAPONTYPES_H
#define WEAPONTYPES_H
#pragma once
#include "weapon.h"
class Firearm : public Weapon {
private:
    int ammoType;
    QString modelName;
    const QString WeaponType = "огнестрельное оружие";
    int PistolsCapacity;
    int CurrentPistolsCapacity;
    QVector<QPoint> genShoot(int i);
    const unsigned char infoSize = 5;
    QString Info[5];
public:
    Firearm();
    Firearm(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity);

    QString operator [] (int index) override;

    void SetPistolCapacity(int PistolsCapacity);
    int GetPistolCapacity();

    void SetCurrentPistolCapacity(int CurrentPistolsCapacity);
    int GetCurrentPistolCapacity();

    int GetAmmoType();
    void SetAmmoType(int ammoType);

    QString GetModelName();
    void SetModelName(QString modelName);

    QString* GetInfo() override;
    void SetInfo(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity);

    const unsigned char GetInfoSize();

    virtual void accept(Visitor* visitor, QString actionName) override = 0;
    virtual QVector<QPoint> Attack(int action) override;
    virtual QVector<QPoint> MakeWeaponUsable(int action) override;
    virtual QVector<QPoint> Shoot(int action, QString Url);
    virtual QVector<QPoint> Reload(QString Url);
    virtual QVector<QPoint> Clean(QString Url);

    ~Firearm() override;
};
class BladedWeapon : public Weapon {
private:
    QString material;
    const QString WeaponType = "холодное оружие";
    bool isSharp;
    int durability;
    int currSlashNum;
    int bladeThick;
    int bladeWidth;
    const unsigned char infoSize = 7;
    QString Info[7];
    QVector<QPoint> genS(int bladeThick, int bladeWidth, int a);
public:
    BladedWeapon();
    BladedWeapon(QString material, bool isSharp, int durability, int currSlashNum, int bladeThick, int bladeWidth);

    QString operator [] (int index) override;

    QString GetMaterial();
    void SetMaterial(QString material);

    bool GetSharp();
    void SetSharp(bool isSharp);

    int GetBladeThick();
    void SetBladeThick(int bladeThick);

    int GetBladeWidth();
    void SetBladeWidth(int bladeWidth);

    int GetDurability();
    void SetDurability(int durability);

    int GetSlashNum();
    void SetSlashNum(int currSlashNum);

    QString* GetInfo() override;
    void SetInfo(QString material, bool isSharp, int durability, int currSlashNum, int bladeThick, int bladeWidth);

    const unsigned char GetInfoSize();

    virtual void accept(Visitor* visitor, QString actionName) override = 0;
    virtual QVector<QPoint> Attack(int action) override;
    virtual QVector<QPoint> MakeWeaponUsable(int action) override;
    virtual QVector<QPoint> Sharpen(QString Url);
    virtual QVector<QPoint> Slash(int bladeThick, int bladeWidth, QString Url, int b);
    virtual QVector<QPoint> Stab(int bladeThick, int bladeWidth, QString Url, int b);

    ~BladedWeapon() override;
};

#endif // WEAPONTYPES_H
