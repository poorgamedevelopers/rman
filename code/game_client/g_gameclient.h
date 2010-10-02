#pragma once

#include "../engine/i_game.h"

class GGameClient : public IGame
{
public:
	virtual void			Update( uint dt ) { }
	virtual IGameObject*	GetPlayer( uint idx ) { return 0; }
};

CLIENT_API IGame*	G_CreateGame();

