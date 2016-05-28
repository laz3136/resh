#ifndef MY_FORMAT_FORMAT_H
#define MY_FORMAT_FORMAT_H


#include <string>
#include <stdexcept>
#include <iostream>



template<typename ...Args>
std::string format(const std::string &formatString, const Args &... args);

//enum contains allowed format specifiers
enum Format {
    def = '\0',

    d = 'd',
    i = 'i',
    u = 'u',
    o = 'o',
    x = 'x',
    X = 'X',
    f = 'f',
    F = 'F',
    e = 'e',
    E = 'E',
    g = 'g',
    G = 'G',
    a = 'a',
    A = 'A',
    c = 'c',
    s = 's',
    p = 'p',
    n = 'n',
};



std::string get_format(const std::string &fmt, size_t &index, bool &width_arg, bool &precision_arg,
                       Format &f);


// Replace '*' literal with needed wp value
std::string replace_format(const std::string &fmt, int &wp);


/*
 * Templates for type checking
 */

// String check, throws std::invalid_argument if string was not found
template<typename T>
bool check_type(Format format, T variable,
                typename std::enable_if<(std::is_convertible<T, std::string>::value), std::string>::type * = 0) {
    if (format == p || format == s) return true;
    else throw std::invalid_argument("String was not found");

}


//Checks ptr type
template<typename T>
bool check_type(Format format, T variable, typename std::enable_if<(!(std::is_convertible<T, std::string>::value) &&
                                         (std::is_pointer<T>::value)), std::string>::type * = 0) {
    return (format == p);
}

//Checks numerical types, throws std::invalid_argument
template<typename T>
bool check_type(Format format, T variable, typename std::enable_if<
        !(std::is_convertible<T, std::string>::value) && !(std::is_pointer<T>::value), std::string>::type * = 0) {
    if (!std::is_convertible<T, int>::value) throw std::invalid_argument("Invalid argument");

    if (format == d || format == i || format == u || format == o || format == x || format == X || format == f ||
        format == F || format == e || format == E || format == g || format == G || format == a || format == A ||
        format == c) {
        return true;
    }

    throw std::invalid_argument("Invalid argument");
}

// Formats arguments and returns it, throws std::invalid_argument
template<typename T>
std::string get_format_string(T &arg, Format &format, std::string &format_str,
                              typename std::enable_if<std::is_same<T, std::string>::value ||
                                                      std::is_same<T, const std::string>::value>::type * = 0) {
    char *arg_c = const_cast<char *>(arg.c_str());
    if (!check_type(format, arg_c)) {
        throw std::invalid_argument("Format : invalid type of  argument");
    }
    std::string result((size_t) snprintf(NULL, 0, const_cast<char *>(format_str.c_str()), arg_c), '\0');
    snprintf(const_cast<char *>(result.c_str()), result.length() + 1, const_cast<char *>(format_str.c_str()),
             arg_c);
    return result;
}

// Formats arguments and returns it, throws std::invalid_argument (for other types)
template<typename T>
std::string get_format_string(T &arg, Format &format, std::string &format_str, typename std::enable_if<
        !std::is_same<T, std::string>::value && !std::is_same<T, const std::string>::value>::type * = 0) {
    if (!check_type(format, arg)) {
        throw std::invalid_argument("Format : invalid type of  argument");
    }
    std::string result((size_t) snprintf(NULL, 0, const_cast<char *>(format_str.c_str()), arg), '\0');
    snprintf(const_cast<char *>(result.c_str()), result.length() + 1, const_cast<char *>(format_str.c_str()), arg);
    return result;
}


/*
 * Argument to int convertion functions
 */
template<typename T>
int read_int(T &arg, typename std::enable_if<std::is_integral<T>::value>::type * = 0) {
    return (int) arg;
}

template<typename T>
int read_int(T &arg, typename std::enable_if<!std::is_integral<T>::value>::type * = 0) {
    throw std::invalid_argument(std::string("Invalid argument, expected integral type"));
}

/*
 * Following functions return formatted arguments according requested output format
 * Throw std::out_of_range exception if number of arguments is not equals to expected one
 */
template<typename T1, typename T2, typename T3, typename ...Args>
std::string format_3_args(std::string &formatSpec, Format &format, T1 &width, T2 &precision, T3 &arg,
                          Args &... rest) {
    int width_val = read_int(width);
    formatSpec = replace_format(formatSpec, width_val);
    int precision_val = read_int(precision);
    formatSpec = replace_format(formatSpec, precision_val);
    return get_format_string(arg, format, formatSpec);
};

template<typename ...Args>
std::string format_3_args(std::string &formatSpec, Format &f, Args &... rest) {
    throw std::out_of_range("Not enough arguments");
}

template<typename T1, typename T2, typename ...Args>
std::string format_2_args(std::string &formatSpec, Format &format, T1 &ws, T2 &arg, Args &... rest) {
    int val = read_int(ws);
    formatSpec = replace_format(formatSpec, val);
    return get_format_string(arg, format, formatSpec);
};

template<typename ...Args>
std::string format_2_args(std::string &formatSpec, Format &f, Args &... rest) {
    throw std::out_of_range("Not enough arguments");
}

template<typename T, typename ...Args>
std::string format_arg(std::string &formatSpec, Format &format, T &arg, Args &... rest) {
    return get_format_string(arg, format, formatSpec);
};

template<typename ...Args>
std::string format_arg(std::string &formatSpec, Format &f, Args &... rest) {
    throw std::out_of_range("Not enough arguments");
}


// Parses the rest of format string
template<typename ...Args>
std::string sprint(const std::string &fmt, int &count_of_args, size_t &index, Args &... rest) {
    if (index < fmt.length()) {
        std::string formatSpec, result = "";
        bool width_arg = false, precision_arg = false;
        Format format = def;
        do {
            formatSpec = get_format(fmt, index, width_arg, precision_arg, format);
            if (formatSpec[0] != '%') {
                result += formatSpec;
            } else if (formatSpec == "%") {
                result += formatSpec;
            } else {
                throw std::out_of_range("Format : not enough arguments");
            }
        } while (index < fmt.length());
        return result;
    }
    return "";
}
// Read format, read the required number of arguments and formatted it
template<typename T, typename ...Args>
std::string sprint(const std::string &fmt, int &count_of_extraArgs, size_t &index, T &head, Args &... rest) {
    if (count_of_extraArgs > 0) {
        return sprint(fmt, --count_of_extraArgs, index, rest...);
    }
    size_t len = fmt.length();
    std::string formatSpec;
    while (index < len) {
        bool width_arg = false, precision_arg = false;
        Format format = def;
        std::string temp;
        do {
            formatSpec = get_format(fmt, index, width_arg, precision_arg, format);
            temp += formatSpec;
        } while (formatSpec == "%" || formatSpec[0] != '%');

        formatSpec = temp;
        count_of_extraArgs = width_arg + precision_arg;
        std::string result;
        result = count_of_extraArgs == 0 ? format_arg(formatSpec, format, head, rest...) :
                 (count_of_extraArgs == 1 ? format_2_args(formatSpec, format, head, rest...) :
                  format_3_args(formatSpec, format, head, rest...));
        return result + sprint(fmt, count_of_extraArgs, index, rest...);
    }
    throw std::invalid_argument("Empty format or extra args");
}


/**
 * Returns string, formatted according to format specifiers
 * Throws std::out_of_range exception if number of argument is more or less than expected
 * Throws std::invalid_argument exception if format string has some illegal specifiers
 */
template<typename ...Args>
std::string format(const std::string &formatString, const Args &... args) {
    int count_of_args = 0;
    size_t index = 0;
    return sprint(formatString, count_of_args, index, args...);
}


#endif //MY_FORMAT_FORMAT_H
