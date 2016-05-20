#include "format.h"

namespace My_format {
    std::string char_seq(char c, unsigned n) {
        std::string ret = "";
        for (unsigned i = 0; i < n; i++) {
            ret.push_back(c);
        }
        return ret;
    }

    using namespace std;

    string find_spec(const string &fmt, unsigned &pos, bool isArgs) {
        string ret = "";
        while (pos < fmt.length()) {
            for (; pos < fmt.length() && fmt[pos] != '%'; ret.push_back(fmt[pos++]));
            if (pos == fmt.length()) {
                if (isArgs) {
                    throw invalid_argument("Too many arguments for format");
                }
                return ret;
            }
            if (pos == fmt.length() - 1) {
                throw invalid_argument("Spurious trailing '%%' in format");
            }
            if (fmt[pos + 1] == '%') {
                ret.push_back('%');
                pos += 2;
            } else {
                pos++;
                if (!isArgs) {
                    throw out_of_range("Need more arguments");
                }
                break;
            }
        }
        return ret;
    }

    string format_impl(const string &fmt, unsigned pos, unsigned done) {
        return find_spec(fmt, pos, false);
    }

}
