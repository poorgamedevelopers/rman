#pragma once

// forward declarations.
class IGame;

class EHostServer
{
public:
	~EHostServer();
	EHostServer();

	bool		Load();

	bool		Update( uint dt );

private:
	IGame*		_game;
};
