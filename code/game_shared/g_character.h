#pragma once

#include "../engine/i_gameobject.h"

class GCharacter : public IGameObject
{
public:

protected:
	virtual void	RegisterFields();

private:
	uint			_test;
};
