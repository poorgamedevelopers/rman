#include "game_client_shared.h"
#include "g_gameclient.h"

//------------------------------------------------------------------
IGame*	CL_CreateGame()
{
	return B_NEW( "gameclient", GGameClient );
}