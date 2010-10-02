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

#if E_SERVER
	_game = SV_CreateGame();
#elif E_CLIENT
	_game = CL_CreateGame();
#else
#error "bad definitions"
#endif

	return true;
}

//------------------------------------------------------------------
bool EHostServer::Update( uint dt )
{
	if ( !_game )
		return true;

	_game->Update( dt );

	return true;
}
