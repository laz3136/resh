#ifndef LAZY_STRING_H
#define LAZY_STRING_H

#include <string>
#include <istream>
#include <ostream>

using namespace std;

class lazy_string {
private:
    size_t first, size_str;
    string str;

    lazy_string(const lazy_string &key, size_t start, size_t size);

public:
    
    operator string();
    /* Создание string объекта использьзуя алгоритм Copy-on-Write метод  */

    
    lazy_string();
    /* Конструктор для путой lazy_string */


    lazy_string(const string &str);
    /* Конструктор для путой lazy_stringс одним параметром  */

    
    size_t length() const;
    /* Возвращает длину объекта lazy_string */

    lazy_string substr(size_t pos = 0, size_t count = string::npos);
 
    const char &at(size_t pos) const;
    /* Возвращает указатель на символ заданной позиции текущего объекта */


   
    const char &operator[](size_t pos) const;
     /*  возвращает указатель на символ начиная с заданной позиции 
      *  используя квадратные скобочки */ 

    friend istream &operator>>(istream &in, lazy_string &lstr);
    /* Всавка последовательности символов запрошенных значений в stdin  */
  
    friend ostream &operator<<(ostream &out, lazy_string &lstr);
    /* Всавка последовательности символов запрошенных значений в stdout  */

};

#endif
