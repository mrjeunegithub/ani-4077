# Exercice 8 Lecture de NKRHI.jenga

## 1. Dépendances de base

Le projet `NKRHI` possède **10 dépendances de base**, déclarées avant les conditions :

- `NKMath`
- `NKTime`
- `NKLogger`
- `NKEvent`
- `NKWindow`
- `NKContainers`
- `NKMemory`
- `NKCore`
- `NKPlatform`
- `NKThreading`

Elles sont placées dans `_DEPS`, puis transmises à `dependson(_DEPS)`.

## 2. Dépendances conditionnelles

Il y a **3 conditions** portant sur des dépendances optionnelles :

- si `_USE_NKGLAD` est actif → ajout de `NKGlad` ;
- si `_USE_NKGLSLANG` est actif → ajout de `NKGLSlang` ;
- si `_USE_NKSPIRVCROSS` est actif → ajout de `NKSPIRVCross`.

Ces options sont déterminées à partir des variables d'environnement `NK_RENDERER_USE_NKGLAD`, `NK_ENABLE_GLSLANG` et `NK_ENABLE_SPIRVCROSS`. 

## 3. Defines

Le renderer pose d'abord **2 defines généraux** :

- `NKRENDERER_USE_NKGLAD`
- `NKENTSEU_ENABLE_VULKAN_BACKEND`

D'autres defines sont ajoutés conditionnellement :

- `NK_RHI_VK_ENABLED`
- `NK_RHI_GLSLANG_ENABLED`
- `ENABLE_HLSL`
- `ENABLE_OPT=0`
- `NK_RHI_SPIRVCROSS_ENABLED`

Le fichier pose également des defines dépendant de la plateforme et de la configuration : Windows active notamment `NK_RHI_DX11_ENABLED` et `NK_RHI_DX12_ENABLED`, Linux utilise des defines différents selon le backend (Xlib, XCB, Wayland ou headless), Android ajoute ses propres defines, et Debug/Release ajoutent respectivement `_DEBUG`, `DEBUG` ou `NDEBUG`.   

### Conclusion

`NKRHI` possède donc exactement **10 dépendances de base**, auxquelles peuvent s'ajouter **3 dépendances optionnelles**. Les defines montrent que la configuration du moteur varie selon les fonctionnalités activées, la plateforme utilisée et la configuration Debug/Release.
