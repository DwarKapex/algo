#include <iostream>
#include <cmath>

constexpr int N = 25;
void pic1() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x - y < 0 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic2() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x == y ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic3() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x + y == N -1 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic4() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x + y < N + 5 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic5() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x - y/2 == 0 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic6() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x < 11 || y < 11 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic7() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               (x >  N-9) && (y > N-9) ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic8() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x * y == 0 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic9() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               (x - y) / 11 != 0  ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic13() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               x + y > N-5 && x + y < N + 3 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}


void pic16() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
               std::abs(N/2-x) + std::abs(N/2-y) < N/2-2 ?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic19() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
              !(x % (N-1) && y % (N-1))?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic20() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
              (x+y+1)  % 2?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic22() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
              (x+y) % 3 == 0?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic24() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
              x==y || x == (N-y-1)?
               "#" : "."
            );
        std::cout << std::endl;
    }
}

void pic25() {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y)
            std::cout << (
              x % 6  == 0 || y % 6 == 0?
               "#" : "."
            );
        std::cout << std::endl;
    }
}


int main() {
    pic1(); pic2(); pic3(); pic4(); pic5();
    pic6(); pic7(); pic8(); pic9();
                    pic13();
    pic16();                pic19(); pic20();
            pic22();        pic24(); pic25();
    
    return 0;
}
