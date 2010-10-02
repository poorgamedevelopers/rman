#pragma once

#include "../engine/i_game.h"

class GGameClient : public IGame
{
public:
	virtual void			Update( uint dt ) { }
	virtual IGameObject*	GetPlayer( uint idx ) { return 0; }
};

extern IGame*	CL_CreateGame();

