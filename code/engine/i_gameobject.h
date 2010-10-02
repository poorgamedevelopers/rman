
class IGameObject
{
public:

protected:
	enum EFieldType
	{
		FIELD_EXACT
	};

	void		AddField( EFieldType type, uint bits, const void* data );

private:
	struct SField
	{
		char			prevValue[ 16 ];
		void*			data;
		uint			bits;
		EFieldType		type;
	};

	vector< SField >	_fields;
}: