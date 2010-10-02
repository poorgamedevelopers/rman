#include "game_server_shared.h"
#include "g_gameserver.h"

#include "../game_shared/g_character.h"

//------------------------------------------------------------------
GGameServer::~GGameServer()
{
}

//------------------------------------------------------------------
GGameServer::GGameServer()
: _player( 0 )
{
}

//------------------------------------------------------------------
void GGameServer::OnLoaded()
{
	_player = B_NEW( "server", GCharacter );
	_player->Init();
}

//------------------------------------------------------------------
void GGameServer::Update( uint dt )
{
	if ( _player )
	{
		_player->Update( dt );
	}
}

//------------------------------------------------------------------
SERVER_API IGame*	G_CreateGame()
{
	return B_NEW( "gameserver", GGameServer );
}
