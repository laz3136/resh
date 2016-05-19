#include <iostream>
#include "format.h"

using namespace std;

int main() {
    printf("%+a, %a\n", 0., 2e-320);
    cout << format("%a\n", 2e-323);
    return 0;
}

