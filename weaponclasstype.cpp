#include "weaponclasstype.h"
#include <QTimer>
QTimer *timerA = nullptr;
QTimer *timerB = nullptr;
Gun::Gun() : Firearm(9, "Пистолет", 9, 9)
{
}
Gun::~Gun()
{
}
QVector<QPoint> Gun::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/DeagleShot.mp3");
    timerA->start(190);
    return v;
}
QVector<QPoint> Gun::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/DeagleReload.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Gun::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/DeagleClean.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
void Gun::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
MachineGun::MachineGun() : Firearm(7, "Автомат", 100, 100)
{
}
MachineGun::~MachineGun()
{
}
void MachineGun::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> MachineGun::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/MachineGunShot.mp3");
    timerA->start(100);
    return v;
}
QVector<QPoint> MachineGun::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/MachineGunReload.mp3");
    timerB->start(3000);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> MachineGun::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/MachineGunClean.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
Rifle::Rifle() :  Firearm(12, "Винтовка", 9, 9)
{
}
Rifle::~Rifle()
{
}
void Rifle::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> Rifle::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/VintovkaShot.mp3");
    timerA->start(1500);
    return v;
}
QVector<QPoint> Rifle::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/RifleReload.mp3");
    timerB->start(5000);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Rifle::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/RifleClean.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
ShotGun::ShotGun() : Firearm(20, "Дробовик", 7, 7)
{
}

ShotGun::~ShotGun()
{
}
void ShotGun::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> ShotGun::Shoot(int action, QString Url) {
    QVector<QPoint> v = Firearm::Shoot(GetAmmoType(), "qrc:/sounds/ShotGunShot.mp3");
    timerA->start(1950);
    return v;
}
QVector<QPoint> ShotGun::Reload(QString Url) {
    Firearm::Reload("qrc:/sounds/ShotGunReload.mp3");
    timerB->start(5000);
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> ShotGun::Clean(QString Url) {
    Firearm::Clean("qrc:/sounds/ShotGunClean.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
Knife::Knife() : BladedWeapon("Damascus steel", true, 10 , 0, 3, 30)
{
}

Knife::~Knife()
{
}
QVector<QPoint> Knife::Slash(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Slash(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/KnifeSlash.mp3", b);
        timerA->start(400);
    }
    return v;
}
void Knife::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> Knife::Stab(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Stab(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/KnifeStab.mp3", b);
        timerA->start(300);
    }
    return v;
}
QVector<QPoint> Knife::Sharpen(QString Url) {
    BladedWeapon::Sharpen("qrc:/sounds/KnifeSharpen.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
Katana::Katana() : BladedWeapon("High-carbon layers steel", true, 30 , 0, 7, 30)
{
}
QVector<QPoint> Katana::Slash(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Slash(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/KatanaSlash.mp3", b);
        timerA->start(500);
    }
    return v;
}
QVector<QPoint> Katana::Stab(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Stab(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/KatanaStab.mp3", b);
        timerA->start(500);
    }
    return v;
}
QVector<QPoint> Katana::Sharpen(QString Url) {
    BladedWeapon::Sharpen("qrc:/sounds/KatanaSharpen.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
void Katana::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
Katana::~Katana()
{
}
Sword::Sword() : BladedWeapon("Stainless steel", true, 30 , 0, 5, 40)
{
}
Sword::~Sword()
{
}
QVector<QPoint> Sword::Slash(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Slash(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/SwordSlash.mp3", b);
        timerA->start(800);
    }
    return v;
}
void Sword::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> Sword::Stab(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Stab(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/SwordStab.mp3", b);
        timerA->start(800);
    }
    return v;
}
QVector<QPoint> Sword::Sharpen(QString Url) {
    BladedWeapon::Sharpen("qrc:/sounds/SwordSharpen.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
Blade::Blade() : BladedWeapon("High-carbon steel", true, 15 , 0, 5, 35)
{
}

Blade::~Blade()
{
}
QVector<QPoint> Blade::Slash(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Slash(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/BladeSlash.mp3", b);
        timerA->start(500);
    }
    return v;
}
void Blade::accept(Visitor* visitor, QString actionName) {
    visitor->visit(this, actionName);
}
QVector<QPoint> Blade::Stab(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> v;
    if (GetSharp()) {
        v = BladedWeapon::Stab(GetBladeThick(), GetBladeWidth(), "qrc:/sounds/BladeStab.mp3", b);
        timerA->start(500);
    }
    return v;
}
QVector<QPoint> Blade::Sharpen(QString Url) {
    BladedWeapon::Sharpen("qrc:/sounds/BladeSharpen.mp3");
    timerB->start(2500);
    QVector<QPoint> v;
    return v;
}
