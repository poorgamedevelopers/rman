#pragma once

#include "../engine/i_game.h"

// forward declarations.
class GCharacter;

class GGame : public IGame
{
public:
	void	Update( uint dt );

	void	OnLoaded();

	IGameObject*	GetPlayer( uint idx );

private:
	GCharacter*		_players[2];
};
