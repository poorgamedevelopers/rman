#pragma once

#include "../game_shared/game_shared_common.h"

#ifdef GAME_CLIENT_EXPORTS
#define CLIENT_API		extern "C" __declspec( dllexport )
#else
#define CLIENT_API		extern "C" __declspec( dllimport )
#endif
