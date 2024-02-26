#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <functional>
#include <map>
#include <QMainWindow>
#include "weaponclasstype.h"
#include <QScreen>
#include <QSize>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#define WeaponTypesCount 8
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Soldier {
private:
    unordered_map<QString, pair<QVector<QPoint> (Firearm::*)(int), QString>> fireMap;
    unordered_map<QString, pair<QVector<QPoint> (BladedWeapon::*)(int), QString>> bladedMap;
    vector<Weapon*> weapons;
public:
    Soldier() {
        QString Attack = "Attack";
        QString MakeWeaponUsable = "MakeWeaponUsable";
        fireMap["Стрелять"] = {&Firearm::Attack, "Attack"};
        fireMap["Перезарядить"] = {&Firearm::MakeWeaponUsable, "MakeWeaponUsable"};
        fireMap["Почистить"] = {&Firearm::MakeWeaponUsable, "MakeWeaponUsable"};

        bladedMap["Рубить"] = {&BladedWeapon::Attack, "Attack"};
        bladedMap["Колоть"] = {&BladedWeapon::Attack, "Attack"};
        bladedMap["Заточить"] = {&BladedWeapon::MakeWeaponUsable, "MakeWeaponUsable"};

    }

    void useWeapon(Firearm* weapo, QString actionName);
    void useWeapon(BladedWeapon* weapon, QString actionName);
    template<typename WeaponType>
    QVector<QPoint> useWeapon(WeaponType* weapon, QString actionName, unordered_map<QString, pair<QVector<QPoint> (WeaponType::*)(int), QString>>& actionMap);

};
class DrawVisitor : public Visitor {
public:
    DrawVisitor() {};
    ~DrawVisitor() {};
    void visit(Firearm* firearm, QString actionName) override;
    void visit(BladedWeapon* bladedweapon, QString actionName) override;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    QPixmap pixmap;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void doAfterAction();

    void doAction();

    void on_pushButton_Buy_clicked();

    void on_pushButton_Throw_clicked();

    void on_comboBox_WeaponList_currentIndexChanged(int index);

    void on_pushButton_Meth_1_clicked();

    void on_pushButton_Meth_2_clicked();

    void on_pushButton_Aim_clicked();

    void on_spinBox_X_valueChanged(int arg1);

    void on_spinBox_Y_valueChanged(int arg1);

    void on_pushButton_Meth_3_clicked();

    void on_pushButton_Meth_1_pressed();

    void on_pushButton_Meth_1_released();

    void on_pushButton_Meth_2_released();

    void on_pushButton_Meth_2_pressed();

    void on_pushButton_Meth_3_pressed();

    void on_pushButton_Meth_3_released();

private:
    int const iconSize = 150;
    struct wepData {
        QString wepName;
        QString wepImgPath;
        function<Weapon*()> wepType;
    };
    map<int, wepData> wepMap;
    vector<Weapon*> weapon_vect;
    DrawVisitor drawVisitor;
};
#endif // MAINWINDOW_H
