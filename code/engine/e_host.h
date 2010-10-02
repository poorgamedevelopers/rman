#pragma once

// forward declarations.
class EHostServer;
class EHostClient;

class EHost
{
public:
	~EHost();
	EHost();

	bool	Init();

	bool	Update( uint dt );

private:
	EHostServer*			_server;
	vector< EHostClient* >	_clients;

	bool					_running;
};
extern EHost*	gHost;
