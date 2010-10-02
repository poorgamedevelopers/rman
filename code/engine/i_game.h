#pragma once

class IGame
{
public:
	virtual ~IGame() { }

	virtual void	Update( uint dt )=0;

	// events.
	virtual void	OnLoaded() { }
};

extern IGame*		G_CreateGame();
