#pragma once

#include "../engine/i_game.h"

class GCharacter;

class GGameServer : public IGame
{
public:
	~GGameServer();
	GGameServer();

	virtual void			OnLoaded();
	virtual void			Update( uint dt );
	virtual IGameObject*	GetPlayer( uint idx ) { return 0; }

private:
	GCharacter*				_player;
};

SERVER_API IGame*	G_CreateGame();

