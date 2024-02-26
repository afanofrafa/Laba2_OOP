#include "weapontypes.h"
bool Aim;
int X;
int Y;
void getXY(int & x, int & y) {
    if (!Aim) {
        x = getRandomInt(0, 600);
        y = getRandomInt(0, 600);
    }
    else {
        x = X;
        y = Y;
    }
}
QMediaPlayer *mediaPlayer = nullptr;
QVector<QPoint> Firearm::genShoot(int n) {
    double r = n;
    int x;
    int y;
    getXY(x, y);
    QVector<QPoint> small = generatePointsAroundCenter(n, r, x, y);
    QVector<QPoint> big = generatePointsAroundCenter(n, r * 2, x, y);
    QVector<QPoint> vect;
    for (int i = 0; i < n; i++) {
        vect.push_back(small.at(i));
        vect.push_back(big.at(i));
    }
    return vect;
}
QVector<QPoint> BladedWeapon::genS(int bladeThick, int bladeWidth, int a) {
    QVector<QPoint> vector;
    QPoint p;
    bladeWidth *= 2;
    bladeThick *= 2;
    float R = (((bladeWidth / 2) * (bladeWidth / 2)) + ((bladeThick / 2) * (bladeThick / 2))) / (bladeThick);
    int Cx = R - bladeThick / 2;
    int x;
    int y;
    getXY(x, y);
    p.setX(x - Cx); //Центр первого
    p.setY(y); //эллипса
    vector.push_back(p);
    p.setX(R);  //малая полуось
    p.setY(R * a); //большая полуось
    vector.push_back(p);
    p.setX(x + Cx); //Центр второго
    p.setY(y); //эллиспа
    vector.push_back(p);
    p.setX(R);  //малая полуось
    p.setY(R * a); //большая полуось
    vector.push_back(p);
    return vector;
}
void playSound(QString Url) {
    if (mediaPlayer != nullptr && mediaPlayer->isPlaying()) {
        mediaPlayer->stop();
        delete mediaPlayer;
    }
    mediaPlayer = new QMediaPlayer;
    mediaPlayer->setSource(QUrl(Url));
    mediaPlayer->setAudioOutput(new QAudioOutput);
    mediaPlayer->play();
}
Firearm::Firearm()
{
    SetInfo(93, "Flamethrower", 40, 40);
}
Firearm::Firearm(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity) {
    SetInfo(AmmoType, ModelName, PistolCapacity, CurrentPistolCapacity);
}
void Firearm::SetInfo(int AmmoType, QString ModelName, int PistolCapacity, int CurrentPistolCapacity) {
    SetAmmoType(AmmoType);
    SetModelName(ModelName);
    SetPistolCapacity(PistolCapacity);
    SetCurrentPistolCapacity(CurrentPistolCapacity);
    Info[0] = "Калибр: " + QString::number(GetAmmoType()) + "мм";
    Info[1] = GetModelName();
    Info[2] = "Вместимость магазина: " + QString::number(GetPistolCapacity());
    Info[3] = "Количество оставшихся патронов: " + QString::number(GetCurrentPistolCapacity());
    Info[4] = "Тип оружия: " + this->WeaponType;
}
QString Firearm::operator [] (int index) { //Не ипользую ссылку для лишения возможности присваивания через индекс
    if (index > infoSize)
        index = infoSize;
    if (index < 0)
        index = 0;
    return Info[index];
}
const unsigned char Firearm::GetInfoSize() {
    return infoSize;
}
int Firearm::GetAmmoType()
{
    return ammoType;
}
void Firearm::SetAmmoType(int ammoType)
{
    this->ammoType = ammoType;
}
QString Firearm::GetModelName()
{
    return modelName;
}
void Firearm::SetModelName(QString modelName)
{
    this->modelName = modelName;
}
QVector<QPoint> Firearm::Clean(QString Url) {
    playSound(Url);
    QVector<QPoint> v;
    return v;
}
QString* Firearm::GetInfo() {
    return Info;
}
void Firearm::SetPistolCapacity(int PistolsCapacity) {
    this->PistolsCapacity = PistolsCapacity;
}
int Firearm::GetPistolCapacity() {
    return PistolsCapacity;
}
void Firearm::SetCurrentPistolCapacity(int CurrentPistolsCapacity) {
    this->CurrentPistolsCapacity = CurrentPistolsCapacity;
}
int Firearm::GetCurrentPistolCapacity() {
    return CurrentPistolsCapacity;
}
QVector<QPoint> Firearm::Reload(QString Url) {
    SetCurrentPistolCapacity(GetPistolCapacity());
    playSound(Url);
    Info[3] = "Количество оставшихся патронов: " + QString::number(GetCurrentPistolCapacity());
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Firearm::Shoot(int action, QString Url) {
    QVector<QPoint> vect;
    if (GetCurrentPistolCapacity() > 0) {
        SetCurrentPistolCapacity(GetCurrentPistolCapacity() - 1);
        vect = genShoot(action);
        playSound(Url);
    }
    Info[3] = "Количество оставшихся патронов: " + QString::number(GetCurrentPistolCapacity());
    return vect;
}
QVector<QPoint> Firearm::Attack(int action) {
    switch (action) {
    case 0:
        return Shoot(action, "");

        break;
    default:
        break;
    }
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> Firearm::MakeWeaponUsable(int action) {
    switch (action) {
    case 1:
        return Reload("");

        break;
    case 2:
        return Clean("");

        break;
    default:
        break;
    }
    QVector<QPoint> v;
    return v;
}
Firearm::~Firearm()
{
}
BladedWeapon::BladedWeapon()
{
    SetInfo("Steel", true, 10, 0, 5, 50);
}

BladedWeapon::BladedWeapon(QString material, bool isSharp, int durability, int currSlashNum, int bladeThick, int bladeWidth)
{
    SetInfo(material, isSharp, durability, currSlashNum, bladeThick, bladeWidth);
}
void BladedWeapon::SetInfo(QString material, bool isSharp, int durability, int currSlashNum, int bladeThick, int bladeWidth) {
    SetMaterial(material);
    SetSharp(isSharp);
    SetDurability(durability);
    SetSlashNum(currSlashNum);
    SetBladeThick(bladeThick);
    SetBladeWidth(bladeWidth);
    Info[0] = "Материал: " + GetMaterial();
    Info[1] = GetSharp() ? "Заточено" : "Не заточено";
    Info[2] = "Прочность: " + QString::number(GetDurability()) + " ударов";
    Info[3] = "Текущее количество ударов: " + QString::number(GetSlashNum());
    Info[4] = "Толщина лезвия: " + QString::number(GetBladeThick()) + "мм";
    Info[5] = "Ширина лезвия: " + QString::number(GetBladeWidth()) + "мм";
    Info[6] = "Тип оружия: " + this->WeaponType;
}
QString BladedWeapon::operator [] (int index) { //Не ипользую ссылку для лишения возможности присваивания через индекс
    if (index > infoSize)
        index = infoSize;
    if (index < 0)
        index = 0;
    return Info[index];
}
QString* BladedWeapon::GetInfo() {
    return Info;
}
const unsigned char BladedWeapon::GetInfoSize() {
    return infoSize;
}
int BladedWeapon::GetBladeThick() {
    return bladeThick;
}
void BladedWeapon::SetBladeThick(int bladeThick) {
    this->bladeThick = bladeThick;
}
int BladedWeapon::GetBladeWidth() {
    return bladeWidth;
}
void BladedWeapon::SetBladeWidth(int bladeWidth) {
    this->bladeWidth = bladeWidth;
}
int BladedWeapon::GetDurability() {
    return durability;
}
QVector<QPoint> BladedWeapon::Attack(int action) {
    switch (action) {
    case 0:
        return Slash(action, action, "", 3);

        break;
    case 1:
        return Stab(action, action, "", 1);

        break;
    default:
        break;
    }
    QVector<QPoint> v;
    return v;
}
QVector<QPoint> BladedWeapon::MakeWeaponUsable(int action) {
    switch (action) {
    case 2:
        return Sharpen("");

        break;
    default:
        break;
    }
    QVector<QPoint> v;
    return v;

}
QVector<QPoint> BladedWeapon::Sharpen(QString Url) {
    currSlashNum = 0;
    isSharp = true;
    playSound(Url);
    Info[1] = GetSharp() ? "Заточено" : "Не заточено";
    Info[3] = "Текущее количество ударов: " + QString::number(GetSlashNum());
    QVector<QPoint> v;
    return v;
}
QString BladedWeapon::GetMaterial()
{
    return material;
}
void BladedWeapon::SetMaterial(QString material)
{
    this->material = material;
}
bool BladedWeapon::GetSharp() {
    return isSharp;
}
void BladedWeapon::SetSharp(bool isSharp) {
    this->isSharp = isSharp;
}
void BladedWeapon::SetDurability(int durability) {
    this->durability = durability;
}
int BladedWeapon::GetSlashNum() {
    return currSlashNum;
}
void BladedWeapon::SetSlashNum(int currSlashNum) {
    this->currSlashNum =  currSlashNum;
}
QVector<QPoint> BladedWeapon::Slash(int bladeThick, int bladeWidth, QString Url, int b) {
    QVector<QPoint> vector;
    if (GetSlashNum() < GetDurability()) {
        currSlashNum++;
        vector = genS(bladeThick, bladeWidth, b);
        playSound(Url);
    }
    else
        isSharp = false;
    Info[1] = GetSharp() ? "Заточено" : "Не заточено";
    Info[3] = "Текущее количество ударов: " + QString::number(GetSlashNum());
    return vector;
}
QVector<QPoint> BladedWeapon::Stab(int bladeThick, int bladeWidth, QString Url, int b) {
    return BladedWeapon::Slash(bladeThick, bladeWidth, Url, b);
}
BladedWeapon::~BladedWeapon()
{
}
