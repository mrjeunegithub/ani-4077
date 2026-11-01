#include "NKWindow/Core/NkEvent.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKWindow/NkWindow.h"
#include "NKWindow/Core/NkMain.h"


int nkmain(const nkentseu::NkEntryState& state) {
    nkentseu::NkWindowConfig cfg;
    cfg.title       = "DaneVK";
    cfg.width       = 1280;
    cfg.height      = 720;
    cfg.centered    = true;
    cfg.resizable   = true;
    cfg.dropEnabled = true;

    nkentseu::NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[Sandbox] Window creation FAILED");
        return -2;
    }

    // Extraction correcte (par copie ou commente si inutile pour l'instant)
    auto surf = window.GetSurfaceDesc();
    
    auto& eventSystem = nkentseu::NkEvents();

    bool running = true;

    while (running)
    {
        while (nkentseu::NkEvent* event = eventSystem.PollEvent())
        {
            if (event->As<nkentseu::NkWindowCloseEvent>())
            {
                running = false;
                break;
            }
        }

        if (!running)
            break;
    }

    // -------------------------------------------------------------------------
    // Nettoyage
    // -------------------------------------------------------------------------

    logger.Infof("[DaneVK] VulkanContext destroyed");

    window.Close();
    return 0;
}