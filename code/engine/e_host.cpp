#include "engine_common.h"
#include "e_host.h"

EHost*	gHost;

//------------------------------------------------------------------
EHost::~EHost()
{
	gHost = 0;
}

//------------------------------------------------------------------
EHost::EHost()
{
	B_ASSERT( !gHost );
	gHost = this;
}

//------------------------------------------------------------------
bool EHost::Update( uint dt )
{
	return true;
}
