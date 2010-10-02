#include "engine_common.h"
#include "e_hostserver.h"

// project headers.
#include "i_game.h"

#include "e_system.h"

//------------------------------------------------------------------
EHostServer::~EHostServer()
{
	gSystem->UnloadLib( _dll );

	B_DEL( "hostserver", _game );
}

//------------------------------------------------------------------
EHostServer::EHostServer()
: _game( 0 )
, _dll( 0 )
{
}

//------------------------------------------------------------------
bool EHostServer::Load()
{
	B_VERIFY( !_game,
		return false );

	_dll = gSystem->LoadLib( "game_server.dll" );

	G_CreateGameFn fn = (G_CreateGameFn)gSystem->GetProcAddr( _dll, "G_CreateGame" );
	if ( !fn )
		return false;

	_game = fn();

	_game->OnLoaded();

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
