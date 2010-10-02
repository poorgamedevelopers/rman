#include "game_shared_common.h"
#include "g_game.h"

#include "g_character.h"

//------------------------------------------------------------------
IGame* G_CreateGame()
{
	GGame* result = B_NEW( "game", GGame );

	return result;
}

//------------------------------------------------------------------
void GGame::Update( uint dt )
{
	if ( _players[0] )
		_players[0]->Update( dt );
	if ( _players[1] )
		_players[1]->Update( dt );
}


//------------------------------------------------------------------
void GGame::OnLoaded()
{
	_players[0] = B_NEW( "game", GCharacter );
	_players[1] = B_NEW( "game", GCharacter );
}


//------------------------------------------------------------------
IGameObject* GGame::GetPlayer( uint idx )
{
	B_ASSERT( idx < 2 );
	return _players[ idx ];
}