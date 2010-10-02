#include "game_shared_common.h"
#include "g_game.h"

//------------------------------------------------------------------
IGame* G_CreateGame()
{
	GGame* result = B_NEW( "game", GGame );

	return result;
}
