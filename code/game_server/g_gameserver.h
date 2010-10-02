#pragma once

#include "../engine/i_game.h"

class GGameServer : public IGame
{
public:
	virtual void			Update( uint dt ) { }
	virtual IGameObject*	GetPlayer( uint idx ) { return 0; }
};

SERVER_API IGame*	SV_CreateGame();

