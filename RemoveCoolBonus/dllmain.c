#include "GameAPI/Game.h"
#include "Objects/Global/ActClear.h"
#include "Objects/Helpers/TimeAttackData.h"
#include "Objects/Global/Music.h"
#include "Objects/Global/Zone.h"
#include "Objects/Global/Player.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    MOD_REGISTER_OBJECT_HOOK(ActClear);
    MOD_REGISTER_OBJ_OVERLOAD(ActClear, NULL, NULL, NULL, ActClear_Draw, ActClear_Create, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJECT_HOOK(TimeAttackData);
    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJECT_HOOK(Music);

    TimeAttackData_GetPackedTime   = Mod.GetPublicFunction(NULL, "TimeAttackData_GetPackedTime");
    Mod.RegisterStateHook(TimeAttackData_GetPackedTime, TimeAttackData_GetPackedTime_Hook, false);
    TimeAttackData_GetUnpackedTime   = Mod.GetPublicFunction(NULL, "TimeAttackData_GetUnpackedTime");
    Mod.RegisterStateHook(TimeAttackData_GetUnpackedTime, TimeAttackData_GetUnpackedTime_Hook, false);
    TimeAttackData_TrackActClear = Mod.GetPublicFunction(NULL, "TimeAttackData_TrackActClear");
    Mod.RegisterStateHook(TimeAttackData_TrackActClear, TimeAttackData_TrackActClear_Hook, false);
    TimeAttackData_GetScore   = Mod.GetPublicFunction(NULL, "TimeAttackData_GetScore");
    Mod.RegisterStateHook(TimeAttackData_GetScore, TimeAttackData_GetScore_Hook, false);
    TimeAttackData_ConfigureTableView = Mod.GetPublicFunction(NULL, "TimeAttackData_ConfigureTableView");
    ActClear_State_EnterText          = Mod.GetPublicFunction(NULL, "ActClear_State_EnterText");
    Zone_GetZoneID                 = Mod.GetPublicFunction(NULL, "Zone_GetZoneID");
    Player_GiveScore               = Mod.GetPublicFunction(NULL, "Player_GiveScore");
    ActClear_DrawTime              = Mod.GetPublicFunction(NULL, "ActClear_DrawTime");
    ActClear_DrawNumbers           = Mod.GetPublicFunction(NULL, "ActClear_DrawNumbers");
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif