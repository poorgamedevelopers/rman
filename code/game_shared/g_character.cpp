#include "game_shared_common.h"
#include "g_character.h"

//------------------------------------------------------------------
void GCharacter::Update( uint dt )
{
	_test = rand();

	IGameObject::Update( dt );
}


//------------------------------------------------------------------
void GCharacter::RegisterFields()
{
	AddField( FIELD_EXACT, 32, sizeof( uint ), (const void*)&_test );
}
