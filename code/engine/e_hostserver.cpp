#include "engine_common.h"
#include "e_hostserver.h"

// project headers.
#include "i_game.h"

//------------------------------------------------------------------
EHostServer::~EHostServer()
{
	B_DEL( "hostserver", _game );
}

//------------------------------------------------------------------
EHostServer::EHostServer()
: _game( 0 )
{
}

//------------------------------------------------------------------
bool EHostServer::Load()
{
	B_VERIFY( !_game,
		return false );

	_game = G_CreateGame();

	return true;
}

//------------------------------------------------------------------
bool EHostServer::Update( uint dt )
{
	if ( !_game )
		return true;

	return true;
}
