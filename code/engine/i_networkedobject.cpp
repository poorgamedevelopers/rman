#include "engine_common.h"
#include "i_gameobject.h"

//------------------------------------------------------------------
INetworkedObject::~INetworkedObject()
{

}

//------------------------------------------------------------------
INetworkedObject::INetworkedObject()
{
}

//------------------------------------------------------------------
void	INetworkedObject::Init()
{
	_fields.clear();
	RegisterFields();
}

//------------------------------------------------------------------
void	INetworkedObject::Update( uint dt )
{
	for ( size_t i = 0; i < _fields.size(); ++i )
	{
		SField& field( _fields[i] );
		if ( MemCmp( field.data, field.prevValue, field.size ) != 0 )
		{
			i = i;
		}
	}
}


//------------------------------------------------------------------
void	INetworkedObject::AddField( EFieldType type, uint bits, uint size, const void* data )
{
	_fields.resize( _fields.size() + 1 );

	SField& field( *_fields.rbegin() );
	field.type = type;
	field.bits = bits;
	field.data = data;
	field.size = size;
	MemZero( field.prevValue, size );
}