#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QTimer>
Ui::MainWindow *u;
Soldier soldier;
extern QTimer *timerA;
extern QTimer *timerB;
QTimer *timerZ;
extern QMediaPlayer *mediaPlayer;
extern bool Aim;
extern int X;
extern int Y;
bool isAttack;
bool fl;
QPushButton *button;
unordered_map<QString, int> actNum;
list<QPushButton*> listButtons;
void SetButtonsEnabled() {
    if (u->pushButton_Meth_2->isEnabled() != fl) {
        u->pushButton_Meth_1->setEnabled(fl);
        u->pushButton_Meth_2->setEnabled(fl);
        u->pushButton_Meth_3->setEnabled(fl);
        u->pushButton_Aim->setEnabled(fl);
        u->listWidget_Info->setEnabled(fl);
        u->label_Info->setEnabled(fl);
    }
}
void SetButtonsVisible() {
    if (u->pushButton_Meth_2->isEnabled() != fl) {
        u->pushButton_Meth_1->setVisible(fl);
        u->pushButton_Meth_2->setVisible(fl);
        u->pushButton_Meth_3->setVisible(fl);
        u->pushButton_Aim->setVisible(fl);
        u->listWidget_Info->setVisible(fl);
        u->label_Info->setVisible(fl);
    }
}
void SetTarget() {
    Aim = fl;
    u->label_X->setVisible(fl);
    u->label_X->setEnabled(fl);
    u->label_Y->setVisible(fl);
    u->label_Y->setEnabled(fl);
    u->spinBox_X->setVisible(fl);
    u->spinBox_X->setEnabled(fl);
    u->spinBox_Y->setVisible(fl);
    u->spinBox_Y->setEnabled(fl);
}

void drawFigureFire(QPixmap& pixmap, QVector<QPoint>& points) {
    QPainter painter(&pixmap);
    int count = points.size();
    painter.setRenderHint(QPainter::Antialiasing); // Устанавливаем сглаживание для лучшего качества рисунка
    painter.setPen(Qt::black); // Устанавливаем цвет линии
    painter.drawRect(0, 0, pixmap.width() - 1, pixmap.height() - 1);
    // Создаем путь, используя переданные точки
    QPainterPath path;
    path.moveTo(points.at(0));
    for (int i = 1; i < count; ++i)
        path.lineTo(points.at(i));
    path.closeSubpath();
    // Закрашиваем область, ограниченную путем, в белый цвет
    painter.fillPath(path, Qt::white);
    // Рисуем линии
    for (int i = 0; i < count - 1; ++i)
        painter.drawLine(points.at(i), points.at(i + 1));
    painter.drawLine(points.last(), points.first());
    painter.end();
}

void drawFigureBlade(QPixmap& pixmap, QVector<QPoint>& points)  {
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawRect(0, 0, pixmap.width() - 1, pixmap.height() - 1);
    QPainterPath circle1, circle2;
    circle1.addEllipse(points.at(0), points.at(1).x(), points.at(1).y());
    circle2.addEllipse(points.at(2), points.at(3).x(), points.at(3).y());
    // Получаем область пересечения кругов
    QPainterPath intersection = circle1.intersected(circle2);
    int angle = rand() % 360; // Генерация случайного угла
    QPointF center = intersection.boundingRect().center();
    // Применяем трансформацию для центрирования объекта в начале координат
    QTransform transform;
    transform.translate(-center.x(), -center.y());
    intersection = transform.map(intersection);
    // Применяем поворот
    transform.reset(); // Сбрасываем трансформацию
    transform.rotate(angle); // Поворачиваем на нужный угол
    intersection = transform.map(intersection); // Применяем поворот
    // Применяем трансформацию для возврата объекта в исходное положение
    transform.reset();
    transform.translate(center.x(), center.y());
    intersection = transform.map(intersection);
    // Применяем смещение к QPainterPath
    painter.drawPath(intersection);
    painter.fillPath(intersection, Qt::white);
}
void drawFigure(void (*drawFunc)(QPixmap& pixmap, QVector<QPoint>& points), QVector<QPoint> figure) {
    if (!figure.empty()) {
        QPixmap pixmap(":/img/target.png");
        pixmap = pixmap.scaled(600, 600, Qt::KeepAspectRatio);
        drawFunc(pixmap, figure);
        u->label_target->setPixmap(pixmap);
    }
}
template<typename WeaponType>
void getButtonNames(unordered_map<QString, pair<QVector<QPoint> (WeaponType::*)(int), QString>>& actionMap) {
    auto actionIter = actionMap.begin();
    auto buttonIter = listButtons.begin();
    for (; (buttonIter != listButtons.end()) && (actionIter != actionMap.end()); buttonIter++, actionIter++) {
        (*buttonIter)->setText(actionIter->first);
    }
}
template<typename WeaponType>
QVector<QPoint> Soldier::useWeapon(WeaponType* weapon, QString actionName, unordered_map<QString, pair<QVector<QPoint> (WeaponType::*)(int), QString>>& actionMap) {
    fl = true;
    SetButtonsVisible();
    SetButtonsEnabled();
    getButtonNames(actionMap);
    QVector<QPoint> figure;
    auto it = actionMap.find(actionName);
    if (it != actionMap.end()) {
        if (it->second.second == "Attack")
            isAttack = true;
        else
            isAttack = false;
        figure = (weapon->*(it->second.first))(actNum[actionName]);
    }
    int len = weapon->GetInfoSize();
    u->listWidget_Info->clear();
    for (int i = 0; i < len; i++) {
        QListWidgetItem *listItem = new QListWidgetItem;
        listItem->setText((*weapon)[i]);
        u->listWidget_Info->addItem(listItem);
    }
    return figure;
}
void Soldier::useWeapon(Firearm* weapon, QString actionName) {
    drawFigure(drawFigureFire, useWeapon(weapon, actionName, fireMap));
};


void Soldier::useWeapon(BladedWeapon* weapon, QString actionName) {
    drawFigure(drawFigureBlade, useWeapon(weapon, actionName, bladedMap));
};
void DrawVisitor::visit(Firearm* firearm, QString actionName) {
    soldier.useWeapon(firearm, actionName);
};

void DrawVisitor::visit(BladedWeapon* bladedweapon, QString actionName) {
    soldier.useWeapon(bladedweapon, actionName);
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    u = ui;
    QPixmap pixmap(":/img/target.png");
    pixmap = pixmap.scaled(600, 600, Qt::KeepAspectRatio);
    ui->label_target->setPixmap(pixmap);
    timerA = new QTimer(this);
    timerB = new QTimer(this);
    timerZ = new QTimer(this);
    listButtons.push_back(ui->pushButton_Meth_1);
    listButtons.push_back(ui->pushButton_Meth_2);
    listButtons.push_back(ui->pushButton_Meth_3);
    connect(timerA, SIGNAL(timeout()), this, SLOT(doAction()));
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    this->setFixedSize(screenSize);
    ui->spinBox_X->setMaximum(600);
    ui->spinBox_Y->setMaximum(600);
    ui->spinBox_X->setMinimum(0);
    ui->spinBox_Y->setMinimum(0);
    this->move(0, 0);
    actNum["Рубить"] = 0;
    actNum["Колоть"] = 1;
    actNum["Заточить"] = 2;
    actNum["Стрелять"] = 0;
    actNum["Перезарядить"] = 1;
    actNum["Почистить"] = 2;

    ui->label_BuyNum->setText("0");
    wepMap[0] = {"Автомат", ":/img/AKM.png", []() { return new MachineGun; }};
    wepMap[1] = {"Пистолет", ":/img/Deagle.jpg", []() { return new Gun; }};
    wepMap[2] = {"Дробовик", ":/img/Drobovik.png", []() { return new ShotGun; }};
    wepMap[3] = {"Винтовка", ":/img/Vintovka.jpg", []() { return new Rifle; }};
    wepMap[4] = {"Нож", ":/img/Knife.png", []() { return new Knife; }};
    wepMap[5] = {"Катана", ":/img/Katana.jpg", []() { return new Katana; }};
    wepMap[6] = {"Меч", ":/img/Mech.png", []() { return new Sword; }};
    wepMap[7] = {"Кинжал", ":/img/Blade.jpg", []() { return new Blade; }};
    ui->comboBox_ChooseWeapon->setIconSize(QSize(iconSize, iconSize));
    ui->comboBox_WeaponList->setIconSize(QSize(iconSize, iconSize));
    for (int i = 0; i < WeaponTypesCount; i++) {
        ui->comboBox_ChooseWeapon->addItem(QIcon(wepMap[i].wepImgPath), wepMap[i].wepName);
    }
    fl = false;
    SetButtonsVisible();
    SetButtonsEnabled();
    SetTarget();
}

MainWindow::~MainWindow()
{
    u->listWidget_Info->clear();
    delete mediaPlayer;
    delete timerA;
    delete timerB;
    delete timerZ;
    delete ui;
}


void MainWindow::on_pushButton_Buy_clicked()
{
    auto iterator = wepMap.find(ui->comboBox_ChooseWeapon->currentIndex());
    if (iterator != wepMap.end()) {
        auto weapon = iterator->second.wepType();
        weapon_vect.push_back(weapon);
        ui->comboBox_WeaponList->addItem(QIcon(iterator->second.wepImgPath), iterator->second.wepName);
        ui->label_BuyNum->setText(QString::number(weapon->GetCount()));
    }
}


void MainWindow::on_pushButton_Throw_clicked()
{
    if (!weapon_vect.empty()) {
        int index = ui->comboBox_WeaponList->currentIndex();
        auto weapon = weapon_vect.at(index);
        int count = weapon->GetCount() - 1;
        ui->label_BuyNum->setText(QString::number(count));
        weapon_vect.erase(weapon_vect.begin() + index);
        ui->comboBox_WeaponList->removeItem(index);
        delete weapon;
    }
}

void MainWindow::on_comboBox_WeaponList_currentIndexChanged(int index)
{
    if (!weapon_vect.empty()) {
        auto weapon = weapon_vect.at(index);
        weapon->accept(&drawVisitor, "");
    }
    else {
        fl = false;
        SetButtonsVisible();
        SetButtonsEnabled();
        SetTarget();
    }
}

void MainWindow::doAction() {
    auto weapon = weapon_vect.at(ui->comboBox_WeaponList->currentIndex());
    weapon->accept(&drawVisitor, button->text());
}

void MainWindow::on_pushButton_Meth_1_clicked()
{
}

void MainWindow::on_pushButton_Meth_2_clicked()
{
}

void MainWindow::on_pushButton_Meth_3_clicked()
{
}

void MainWindow::on_pushButton_Aim_clicked()
{
    fl = true;
    SetTarget();
}

void toAim() {
    QPixmap pixmap(":/img/target.png");
    pixmap = pixmap.scaled(600, 600, Qt::KeepAspectRatio);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание для более качественного рисунка
    painter.setPen(Qt::red); // Устанавливаем цвет линии
    painter.drawLine(0, u->spinBox_Y->value(), pixmap.width(), u->spinBox_Y->value()); // Рисуем линию
    painter.drawLine(u->spinBox_X->value(), 0, u->spinBox_X->value(), pixmap.height()); // Рисуем линию
    painter.end();
    u->label_target->setPixmap(pixmap);
    X = u->spinBox_X->value();
    Y = u->spinBox_Y->value();
}

void MainWindow::on_spinBox_X_valueChanged(int arg1)
{
    toAim();
}

void MainWindow::on_spinBox_Y_valueChanged(int arg1)
{
    toAim();
}

void MainWindow::doAfterAction() {
    fl = false;
    QTimer *timer;
    if (isAttack) {
        SetTarget();
        timer = timerA;
    }
    else
        timer = timerB;
    SetButtonsEnabled();
    ui->pushButton_Aim->setEnabled(true);
    fl = true;
    timerZ->singleShot(timer->interval(), this, SetButtonsEnabled);
    timer->stop();
}

void MainWindow::on_pushButton_Meth_1_released()
{
    doAfterAction();
}

void MainWindow::on_pushButton_Meth_2_released()
{
    doAfterAction();
}

void MainWindow::on_pushButton_Meth_3_released()
{
    doAfterAction();
}

void MainWindow::on_pushButton_Meth_1_pressed()
{
    button = ui->pushButton_Meth_1;
    doAction();
}

void MainWindow::on_pushButton_Meth_2_pressed()
{
    button = ui->pushButton_Meth_2;
    doAction();
}


void MainWindow::on_pushButton_Meth_3_pressed()
{
    button = ui->pushButton_Meth_3;
    doAction();
}
