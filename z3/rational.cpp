#include "rational.h"

int rational::nod(int x, int y){
    /*  Метод реаилизующий поиск наибольшего общего делителя */
    while (x && y)
        if (x > y)
            x %= y;
        else
            y %= x;
    return x + y;
}

rational::rational(int num, int znam) {
    int x = nod(num, znam);
    this->n = num / x;
    this->d = znam / x;
}

rational::rational(int num) {
    this->n = num;
    this->d = 1;
}

int rational::getNum() const {
    return this->n;
}

int rational::getDenom() const {
    return this->d;
}

rational rational::operator +(rational const & x) const
{
    int xNum1 = getNum();
    int xDenom1 = getDenom();
    int xNum2 = x.getNum();
    int xDenom2 = x.getDenom();
    return rational(xNum1 * xDenom2 + xDenom1 * xNum2, xDenom1 * xDenom2);
}

rational rational::operator -(rational const & x) const
{
    int xNum1 = getNum();
    int xDenom1 = getDenom();
    int xNum2 = x.getNum();
    int xDenom2 = x.getDenom();
    return rational(xNum1 * xDenom2 - xDenom1 * xNum2, xDenom1 * xDenom2);
}

rational rational::operator *(rational const & x) const
{
    return rational(getNum() * x.getNum(), getDenom() * x.getDenom());
}

rational rational::operator /(rational const & x) const
{
    return rational(getNum() * x.getDenom(), getDenom() * x.getNum());
}
