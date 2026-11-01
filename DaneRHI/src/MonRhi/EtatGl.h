#pragma once

#include "MonRhi/MonRhi.h"
#include "MonRhi/Gl.h"
#include "NKWindow/NKWindow.h"


namespace monrhi {

struct EtatGl {
    unsigned int programme = 0;
    unsigned int tableau = 0;
    unsigned int tampon = 0;
    int viewport[4]{};
    float couleurEffacement[4]{};

    static EtatGl Lire();
    nkentseu::NkString Decrire() const;
};

}