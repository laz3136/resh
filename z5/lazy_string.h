#ifndef LAZY_STRING_H
#define LAZY_STRING_H

#include <string>
#include <istream>
#include <ostream>

class lazy_string {
private:
    size_t first, size_str;
    std::string str;

    lazy_string(const lazy_string &key, size_t start, size_t size);

public:
    
    operator std::string();
    /* Создание string объекта использьзуя алгоритм Copy-on-Write метод  */

    
    lazy_string();
    /* Конструктор для путой lazy_string */


    lazy_string(const std::string &str);
    /* Конструктор для путой lazy_stringс одним параметром  */

    
    size_t length() const;
    /* Возвращает длину объекта lazy_string */

    /**
     * Returns a new constructed std::string object
     * with it's value initialized to a copy of a
     * substring of this object.
     *
     * @param pos Position of the first character to be copied as a substring.
     * @param count number of characters to include in the substring.
     * @return A lazy_string object with a substring of this object
     *     or empty string, if pos = size().
     */

    lazy_string substr(size_t pos = 0, size_t count = std::string::npos);
    /*  Врзвращает  */
    /**
     * Returns a reference to the character at pos position in the string.
     *
     * @param pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */

    const char &at(size_t pos) const;

    /**
     * Returns a reference to the character at position pos in the string.
     *
     * @param pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */

    const char &operator[](size_t pos) const;

    /**
     * Extracts a string from the input stream in, storing the sequence in lstr,
     * which is overwritten.
     *
     * @param in istream object from which characters are extracted.
     * @param lstr lazy_string object where the extracted content is stored.
     * @return The same as param in.
     */

    friend std::istream &operator>>(std::istream &in, lazy_string &lstr);

    /**
     * Inserts the sequence of characters that conforms value of lstr into out.
     *
     * @param out ostream object where characters are inserted.
     * @param lstr lazy_string object with the content to insert.
     * @return The same as parameter out.
     */

    friend std::ostream &operator<<(std::ostream &out, lazy_string &lstr);

};

#endif
