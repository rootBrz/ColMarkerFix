#include "shared/SafeWrite/SafeWrite.hpp"
#include <nvse/PluginAPI.h>
#include <shared/Defines.hpp>
#include <shared/NVSEManager/NVSEGlobalManager.hpp>

#define VERSION 100

void MessageHandler(NVSEMessagingInterface::Message *msg)
{
        if (msg->type != NVSEMessagingInterface::kMessage_PostLoad)
                return;

        // NOP out the check that skips collision spheres, enabling culling for them
        SafeWrite16(0x0056B4C2, 0x9090);
}

EXTERN_DLL_EXPORT bool NVSEPlugin_Query(const NVSEInterface *nvse, PluginInfo *info)
{
        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = "ColMarkerFix";
        info->version = VERSION;
        return true;
}

EXTERN_DLL_EXPORT bool NVSEPlugin_Load(NVSEInterface *nvse)
{
        if (!nvse->isEditor)
        {
                NVSEGlobalManager &rNVSE = NVSEGlobalManager::GetSingleton();
                rNVSE.Initialize(nvse);
                rNVSE.RegisterPluginEventListener("NVSE", MessageHandler);
        }

        return true;
}

BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
        return TRUE;
}
