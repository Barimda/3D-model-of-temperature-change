#include <math.h>
#include "progonka.h"
#include "stena.h"

using namespace std;


int main() {
    progonka prg;
    prg.showTemplate();

    stena stena1(100, 0.7, -30, 130);
    stena1.calculateDots();

    stena stena2(100, 0.7, 30, -30);
    stena2.calculateDots();

    stena stena3(100, 0.7, 303, -243);
    stena3.calculateDotsWithTime(60);

    return 0;
}


