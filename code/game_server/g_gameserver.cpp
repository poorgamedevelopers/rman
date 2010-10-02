#include "game_server_shared.h"
#include "g_gameserver.h"

//------------------------------------------------------------------
SERVER_API IGame*	SV_CreateGame()
{
	return B_NEW( "gameserver", GGameServer );
}
