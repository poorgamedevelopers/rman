#include "game_client_shared.h"
#include "g_gameclient.h"

//------------------------------------------------------------------
CLIENT_API IGame*	G_CreateGame()
{
	return B_NEW( "gameclient", GGameClient );
}