#ifndef Z4_FORMAT_H
#define Z4_FORMAT_H

#include <string>
#include <stdexcept>
#include <vector>

#define DEFAULT_PRECISION (-1)  //default value
#define WP_READ (-2)    // useful if we want to read a width or a precision value from the arguments list

namespace formatImpl {
    enum FormatSpec {
        def,
        automatic,

        d,
        u,
        o,
        x,
        X,
        f,
        F,
        e,
        E,
        g,
        G,
        a,
        A,
        c,
        s,
        p,
        n, //???

        hh,
        h,
        l,
        ll,
        j,
        z,
        t,
        L,
    };
/*
 * There are two types of tokens:
 *      1) string (str.size() > 0)
 *      2) format specifier (str.size() == 0)
 */
    struct Format {
        std::string str;
        union {
            int flags = 0;
            struct {
                bool zero:1;    //'0'
                bool plus:1;    //'+'
                bool minus:1;   //'-'
                bool sharp:1;   //'#'
                bool space:1;   //' '
            };
        };
        int width = 0;
        int precision = DEFAULT_PRECISION;
        FormatSpec length;
        FormatSpec type;
    };

/*
 * sprint() generates the string with the given format specifier and the given argument
 * If the argument does not match its specifier, it throws an exception
 */
    template<typename T>
    std::string sprint(Format const *fmt, T arg) {
        throw std::invalid_argument("Invalid argument, or this feature is not implemented.");
    }

/*
 * A simple checker for integer value
 * If the argument is not int, size_t or unsigned int this throws an exception below
 *
 * Otherwise returns the argument casted to int (template's specifications are in format.cpp)
 */
    template<typename T>
    int checkForInt(T arg) {
        throw std::invalid_argument("Invalid format: int, unsigned int or size_t were expected");
    }




//zero argument function
    void formatImplementation(Format *fmt, unsigned long size, std::string &str);

    template<typename T, typename... Args>
    void formatImplementation(Format *format, unsigned long tokensLeft, std::string &str, T curArgument, Args... args) {
        if (tokensLeft) {
            if (format->str.size()) {
                str += format->str;
                formatImplementation(format + 1, tokensLeft - 1, str, curArgument, args...);
            } else {
                if (format->width == WP_READ) {
                    format->width = checkForInt(curArgument);
                } else if (format->precision == WP_READ) {
                    format->precision = checkForInt(curArgument);
                } else {
                    str += sprint(format, curArgument);
                    format++;
                    tokensLeft--;
                }
                formatImplementation(format, tokensLeft, str, args...);
            }
        } else if (sizeof...(args)) {
            throw std::invalid_argument("Too many arguments are given");
        }
    };

    void parseFormatString(std::vector<Format> &fmt, const char *format);
}

    /**
     * Returns a formatted string using the specified format string and
     * arguments.
     *
     * @param  format
     *         A <a href="http://cplusplus.com/printf">format string</a>
     *
     * @param  args
     *         Arguments referenced by the format specifiers in the format
     *         string.  If there are more arguments than format specifiers, the
     *         extra arguments are ignored.  The number of arguments is
     *         variable and may be zero.  The maximum number of arguments is
     *         limited by the maximum dimension of a Java array as defined by
     *         <cite>The Java&trade; Virtual Machine Specification</cite>.
     *         The behaviour on a
     *         {@code null} argument depends on the <a
     *         href="../util/Formatter.html#syntax">conversion</a>.
     *
     * @throws  std::invalid_format
     *          If a format string contains an illegal syntax, a format
     *          specifier that is incompatible with the given arguments,
     *          insufficient arguments given the format string, or other
     *          illegal conditions.
     *
     * @throws  std::out_of_range
     *          If the arguments' list contains too few arguments
     *
     * @return  A formatted string
     */

template<typename... Args>
std::string format(std::string const &formatString, Args... args) {
    std::string str;
    std::vector<formatImpl::Format> fmt;

    formatImpl::parseFormatString(fmt, formatString.c_str()); //generates tokens from format string

    formatImpl::formatImplementation(fmt.data(), fmt.size(), str, args...);

    return str;
}
#endif 
