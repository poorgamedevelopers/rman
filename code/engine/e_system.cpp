#include "engine_common.h"
#include "e_system.h"

#include <windows.h>

ESystem*		gSystem;

//------------------------------------------------------------------
ESystem::~ESystem()
{
	gSystem = 0;
}

//------------------------------------------------------------------
ESystem::ESystem()
{
	B_ASSERT( !gSystem );
	gSystem = this;
}

//------------------------------------------------------------------
void* ESystem::LoadLib( const char* path )
{
	return (void*)LoadLibraryA( path );
}

//------------------------------------------------------------------
void ESystem::UnloadLib( void* handle )
{
	if ( handle )
	{
		FreeLibrary( (HMODULE)handle );
	}
}

//------------------------------------------------------------------
void* ESystem::GetProcAddr( void* handle, const char* name )
{
	if ( !handle )
		return 0;

	return (void*)GetProcAddress( (HMODULE)handle, name );
}
