#pragma once

#include "../game_shared/game_shared_common.h"

#ifdef GAME_SERVER_EXPORTS
#define SERVER_API		extern "C" __declspec( dllexport )
#else
#define SERVER_API		extern "C" __declspec( dllimport )
#endif
