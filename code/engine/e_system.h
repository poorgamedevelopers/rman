#pragma once

class ESystem
{
public:
	~ESystem();
	ESystem();

	void*		LoadLib( const char* path );
	void		UnloadLib( void* handle );
	void*		GetProcAddr( void* handle, const char* name );
};
extern ESystem*		gSystem;
