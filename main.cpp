#include <iostream>
#include "App.h"


int main() {
    std::srand(time(0));        // Generating a seed for srand, so that we can use truly random numbers
    App app;
    app.run();
    return 0;
}