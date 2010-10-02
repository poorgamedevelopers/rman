#include "engine_common.h"

#include "gr_sceneobj.h"

#include "Renderer.h"


//=================================================================
// ctor & dtor
//=================================================================

//-----------------------------------------------------------------
GrSceneObj::GrSceneObj( const std::string& name )
: _name( name )
{

}

//-----------------------------------------------------------------
GrSceneObj::~GrSceneObj()
{

}


//=================================================================
// public methods
//=================================================================

//-----------------------------------------------------------------
GrSceneObj*	
GrSceneObj::Clone( const string& suffix )
{
	GrSceneObj* sceneObj = new GrSceneObj( _name + suffix );
	sceneObj->_renderObjs = _renderObjs;
	return sceneObj;
}

//-----------------------------------------------------------------
void
GrSceneObj::AddRenderObjs( RenderObj_t* objs, unsigned int count )
{
	_renderObjs.insert( _renderObjs.end(), objs, objs + count );
}

//-----------------------------------------------------------------
void
GrSceneObj::Render( const float* pos, const float* cameraPos )
{
	// render.
	GrRender( &_renderObjs.front(), ( unsigned int )_renderObjs.size(),
		cameraPos );
}


//=================================================================
// ctor & dtor
//=================================================================

//-----------------------------------------------------------------
GrSceneObjMgr::GrSceneObjMgr()
{

}

//-----------------------------------------------------------------
GrSceneObjMgr::~GrSceneObjMgr()
{

}


//=================================================================
// public methods
//=================================================================

//-----------------------------------------------------------------
GrSceneObj*
GrSceneObjMgr::CreateObj( const string& name )
{
	GrSceneObj* sceneObj = new GrSceneObj( name );
	_sceneObjs[ name ] = sceneObj;
	return sceneObj;
}

//-----------------------------------------------------------------
GrSceneObj*
GrSceneObjMgr::FindObj( const string& name )
{
	// find the first object with the name specified.
	SceneObjMap::iterator iter = _sceneObjs.find( name );
	if ( iter == _sceneObjs.end() )
		return 0;

	// we found the object requested, so return it.
	return iter->second;
}

#if 0
//-----------------------------------------------------------------
GrSceneObj*
GrSceneObjMgr::GetObj( const string& name )
{
	// find the object specified.
	return 0;
}
#endif

//-----------------------------------------------------------------
GrSceneObj*
GrSceneObjMgr::CloneObj( const string& name, const string& suffix )
{
	// if the clone already exists, simply return.
	GrSceneObj* clone = FindObj( name + suffix );
	if ( clone )
		return clone;

	// try to find the object that we want to clone.
	GrSceneObj* obj = FindObj( name );
	if ( !obj )
		return 0;

	// clone the object and add it to our database.
	clone = obj->Clone( suffix );
	_sceneObjs[ clone->GetName() ] = clone;

	// return the clone.
	return clone;
}

//-----------------------------------------------------------------
void
GrSceneObjMgr::DestroyObj( GrSceneObj* sceneObj )
{
	// find the object and free it.
	SceneObjMap::iterator iter = _sceneObjs.find( sceneObj->GetName() );
	if ( iter != _sceneObjs.end() )
	{
		_sceneObjs.erase( iter );
		delete sceneObj;
	}
	else
	{
		assert( false );
	}
}

//-----------------------------------------------------------------
void
GrSceneObjMgr::Clear()
{
	// delete all of the scene objects.
	SceneObjMap::iterator iter = _sceneObjs.begin();
	for ( ; iter != _sceneObjs.end(); ++iter )
		delete iter->second;

	// clear the database.
	_sceneObjs.clear();
}

