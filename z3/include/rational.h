#ifndef Z3_RATIONAL_H
#define Z3_RATIONAL_H

class rational {
    /* Класс рационального числа */
private:
    int n;
    int d;
    int nod(int, int);
public:
    rational(int num, int denom);
    rational(int num);
    int getNum() const;
    int getDenom() const;
    rational operator +(rational const &x) const;
    rational operator -(rational const &x) const;
    rational operator *(rational const &x) const;
    rational operator /(rational const &x) const;

};

#endif

