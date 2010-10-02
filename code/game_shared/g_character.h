#pragma once

#include "../engine/i_gameobject.h"

class GCharacter : public IGameObject
{
public:
	virtual void	Update( uint dt );

protected:
	virtual void	RegisterFields();

private:
	uint			_test;
};
