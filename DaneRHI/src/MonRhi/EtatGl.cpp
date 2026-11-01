#include "MonRhi/EtatGl.h"


monrhi::EtatGl monrhi::EtatGl::Lire() {
    EtatGl e{};
    int v = 0;

    glGetIntegerv(GL_CURRENT_PROGRAM, &v);
    e.programme = static_cast<unsigned int>(v);

    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &v);
    e.tableau = static_cast<unsigned int>(v);

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &v);
    e.tampon = static_cast<unsigned int>(v);

    glGetIntegerv(GL_VIEWPORT, e.viewport);
    glGetFloatv(GL_COLOR_CLEAR_VALUE, e.couleurEffacement);

    return e;
};

nkentseu::NkString monrhi::EtatGl::Decrire() const {
    return nkentseu::NkPrintf(
        "programme=%u, tableau=%u, tampon=%u, viewport=[%d, %d, %d, %d], effacement=[%.2f, %.2f, %.2f, %.2f]",
        programme, tableau, tampon,
        viewport[0], viewport[1], viewport[2], viewport[3],
        static_cast<double>(couleurEffacement[0]),
        static_cast<double>(couleurEffacement[1]),
        static_cast<double>(couleurEffacement[2]),
        static_cast<double>(couleurEffacement[3]));
}