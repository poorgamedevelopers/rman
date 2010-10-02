#include <iostream>

#include "../engine/Renderer.h"
#include "../engine/engine_common.h"
#include "../engine/e_host.h"
#include "../engine/e_system.h"

#define GAME_SCREEN_WIDTH		113
#define GAME_SCREEN_HEIGHT		50

//////////////////////////////////////////////////////////////////////////
// ZeroMQ Test

#define CL_TEST_SERVER
//#define CL_TEST_CLIENT

#include "../../lib/zeromq/include/zmq.h"

void	TestZeroMQ()
{
	void* context = zmq_init( 1 );

#ifdef CL_TEST_SERVER
	// create a socket to talk to clients.
	void* responder = zmq_socket( context, ZMQ_REP );
	zmq_bind( responder, "tcp://*:5555" );

	// initialize poll set.
	zmq_pollitem_t items[] = {
		{ responder, 0, ZMQ_POLLIN, 0 }
	};

	while ( 1 )
	{
		// wait for an event.
		zmq_poll( items, 1, 0 );

		if ( items[0].revents & ZMQ_POLLIN )
		{
			// read next request from client.
			zmq_msg_t request;
			zmq_msg_init( &request );
			zmq_recv( responder, &request, 0 );
			printf( "received request: [%s]\n",
				(char*)zmq_msg_data( &request ) );
			zmq_msg_close( &request );

			// do some work.
			//Sleep( 1 );

			// send reply back to client.
			zmq_msg_t reply;
			zmq_msg_init_size( &reply, 6 );
			memcpy( (void*)zmq_msg_data( &reply ), "World", 6 );
			zmq_send( responder, &reply, 0 );
			zmq_msg_close( &reply );
		}
	}
#else
	// create a socket to talk to the server.
	printf( "connecting to server...\n" );
	void* requester = zmq_socket( context, ZMQ_REQ );
	int result = zmq_connect( requester, "tcp://localhost:5555" );

	int request_nbr;
	for( request_nbr = 0; request_nbr != 10; request_nbr++ )
	{
        zmq_msg_t request;
        zmq_msg_init_data( &request, "Hello", 6, NULL, NULL );
        printf( "Sending request %d...\n", request_nbr );
        result = zmq_send( requester, &request, 0 );
        zmq_msg_close( &request );

        zmq_msg_t reply;
        zmq_msg_init( &reply );
        zmq_recv( requester, &reply, 0 );
        printf( "Received reply %d: [%s]\n", request_nbr,
            (char*)zmq_msg_data( &reply ) );
        zmq_msg_close( &reply );
    }
#endif

	zmq_term( context );
}

//////////////////////////////////////////////////////////////////////////


int main()
{
	// create the host subsystem.
	B_NEW( "client", EHost );

	B_VERIFY( gHost->Init(),
		return 0 );

	// initialize the renderer.
	GrInit( "ZOMG!", GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT );

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

	// shutdown the renderer.
	GrShutdown();

	// delete the host subsystem.
	B_DEL( "client", gHost );

	return 0;
}
