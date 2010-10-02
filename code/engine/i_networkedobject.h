#pragma once

class INetworkedObject
{
public:
	virtual ~INetworkedObject();
	INetworkedObject();

	void			Init();

	virtual void	Update( uint dt );

protected:
	enum EFieldType
	{
		FIELD_EXACT
	};

	void			AddField( EFieldType type, uint bits, uint size, const void* data );

	virtual void	RegisterFields()=0;

private:
	struct SField
	{
		char			prevValue[ 16 ];
		const void*		data;
		uint			bits;
		uint			size;
		EFieldType		type;
	};

	vector< SField >	_fields;
};
