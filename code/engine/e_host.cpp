#include "engine_common.h"
#include "e_host.h"

// project headers.
#include "e_hostserver.h"

EHost*	gHost;

//------------------------------------------------------------------
EHost::~EHost()
{
	gHost = 0;
}

//------------------------------------------------------------------
EHost::EHost()
: _running( false )
, _server( 0 )
{
	B_ASSERT( !gHost );
	gHost = this;
}

//------------------------------------------------------------------
bool EHost::Init()
{
	B_VERIFY( !_running,
		return false );

#if E_SERVER
	_server = B_NEW( "host", EHostServer );

	// create a new game instance.
	B_VERIFY( _server->Load(),
	{
		B_DEL( "host", _server );
		_server = 0;
		return false;
	});
#else
	// connect to a server.
#endif

	_running = true;
	return true;
}

//------------------------------------------------------------------
bool EHost::Update( uint dt )
{
	// update the server.
	if ( _server )
	{
		if ( !_server->Update( dt ) )
			return false;
	}

	return true;
}
