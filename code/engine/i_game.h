#pragma once

// forward declarations.
class IGameObject;

class IGame
{
public:
	virtual ~IGame() { }

	virtual void	Update( uint dt )=0;

	// events.
	virtual void	OnLoaded() { }

	// accessors.
	virtual IGameObject*	GetPlayer( uint idx )=0;
};

typedef IGame*		(*G_CreateGameFn)();
