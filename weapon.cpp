#include "weapon.h"
#include <random>
int getRandomInt(int min_value, int max_value) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_value, max_value);
    return dis(gen);
}
QVector<QPoint> generatePointsAroundCenter(int n, double radius, double centerX, double centerY) {
    QVector<QPoint> points;
    double angleIncrement = 2 * M_PI / n;
    double angle = 0.0;

    for (int i = 0; i < n; ++i) {
        double randomAngle = ((double)rand() / RAND_MAX) * 0.7 - 0.2;
        double currentAngle = angle + randomAngle;

        QPoint p;
        p.setX(centerX + radius * cos(currentAngle));
        p.setY(centerY + radius * sin(currentAngle));
        points.push_back(p);
        angle += angleIncrement;
    }

    return points;
}
Weapon::Weapon()
{
    if (createNum == INT32_MAX)
        createNum = 0;
    else
        id = createNum++;
    if (count == INT32_MAX)
        count = 0;
    else
        count++;
}

Weapon::~Weapon()
{
    count--;
}

int Weapon::GetID()
{
    return id;
}

int Weapon::GetCount()
{
    return count;
}
int Weapon::count = 0;
int Weapon::createNum = 0;
