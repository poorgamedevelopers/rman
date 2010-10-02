#include <iostream>

#include "../engine/engine_common.h"
#include "../engine/e_host.h"

int main()
{
	// create the host subsystem.
	B_NEW( "client", EHost );

	// main loop.
	bool done = false;
	while ( !done )
	{
		// compute delta time.
		uint dt = 1000 / 60;

		// update the host subsystem.
		if ( !gHost->Update( dt ) )
			done = true;
	}

	// delete the host subsystem.
	B_DEL( "client", gHost );

	return 0;
}
