#include "format.h"


bool check_flags(char c) {
    return c == '-' || c == '+' || c == ' ' || c == '#' || c == '0';
}

bool check_fmt(Format format) {
    if (format == d || format == i || format == u || format == o || format == x || format == X || format == f ||
        format == F || format == e || format == E || format == g || format == G || format == a || format == A ||
        format == c) {
        return true;
    }

    return false;
}


// Checks if there extra format specifers (width and precision)
bool has_arg(const std::string &fmt, size_t &index) {
    if (fmt[index] == '*') {
        index++;
        return true;
    }
    while (isdigit(fmt[index])) {
        index++;
    }
    return false;
}

void check_specifier(const std::string &fmt, size_t &index) {
    std::string s;
    s.push_back(fmt[index]);
    if (index + 1 < fmt.length() && fmt[index + 1] == fmt[index]) {
        s.push_back(fmt[index + 1]);
    }
    if (s == "l" || s == "ll" || s == "h" || s == "hh"
        || s == "j" || s == "z" || s == "t" || s == "L") {
        index += s.length();
    }
}

Format get_format(const std::string &fmt, size_t &index) {
    char c = fmt[index++];
    Format f;
    if (c == 'a' || c == 'A' || c == 'c' || c == 'd' || c == 'i' || c == 'e' || c == 'E' || c == 'f' ||
        c == 'F' || c == 'g' || c == 'G' || c == 'o' || c == 's' || c == 'x' || c == 'X' || c == 'p' ||
        c == 'n' || c == 'u') {
        f = (Format) c;
        return f;
    }
    throw std::invalid_argument("Illegal format " + c);
}


std::string read_format_with_args(const std::string &fmt, size_t &index, bool &width_arg, bool &precision_arg,
                                  Format &format) {
    size_t start = index++, len = fmt.length();
    while (index < len && check_flags(fmt[index])) {
        index++;
    }
    if (fmt[index] == '*' || isdigit(fmt[index])) {
        width_arg = has_arg(fmt, index);
    }
    if (fmt[index] == '.') {
        precision_arg = has_arg(fmt, ++index);
    }
    check_specifier(fmt, index);
    format = get_format(fmt, index);
    return fmt.substr(start, index - start);
}


/*
 * Returns string's format specifier
 * Throws std::invalid_argument if correct specifier is not found
 */
std::string get_format(const std::string &fmt, size_t &index, bool &width_arg, bool &precision_arg,
                       Format &f) {
    size_t len = fmt.length(), start = index;
    char c;
    for (index; index < len; index++) {
        c = fmt[index];
        if (c != '%') {
            continue;
        } else if (index != start) {
            return fmt.substr(start, index - start);
        }
        if (index + 1 < len && fmt[index + 1] == '%') {
            index += 2;
            return "%";
        }
        return read_format_with_args(fmt, index, width_arg, precision_arg, f);
    }
    return fmt.substr(start, index - start);
}

std::string replace_format(const std::string &fmt, int &wp) {
    size_t first = fmt.find_first_of('*');
    std::string result = fmt.substr(0, first) + std::to_string(wp) + fmt.substr(first + 1, fmt.length());
    return result;
}
