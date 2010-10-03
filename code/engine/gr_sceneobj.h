
// forward declarations.
struct RenderObj;
typedef struct RenderObj RenderObj_t;

// scene object.
class GrSceneObj
{
public:
	GrSceneObj( const std::string& name );
	~GrSceneObj();

	const std::string&	GetName()		{	return _name;			}

	// clone the object.
	GrSceneObj*			Clone( const std::string& suffix );

	// adds render objects to the object.
	void				AddRenderObjs( RenderObj_t* objs, unsigned int count );

	// render the object at the specified position.
	void				Render( const float* pos, const float* cameraPos );

private:
	typedef std::vector< RenderObj_t > RenderObjVec;
	
	RenderObjVec		_renderObjs;
	string				_name;
};

class GrSceneObjMgr
{
public:
	GrSceneObjMgr();
	~GrSceneObjMgr();

	// create/find a scene object.
	GrSceneObj*			CreateObj( const string& name );
	GrSceneObj*			FindObj( const string& name );
	GrSceneObj*			CloneObj( const string& name, const string& suffix );
	
#if 0
	GrSceneObj*			GetObj( const string& name );
#endif

	// destroy a specific scene object.
	void				DestroyObj( GrSceneObj* sceneObj );

	// clear all loaded scene objects.
	void				Clear();

private:
	typedef std::map< std::string, GrSceneObj* > SceneObjMap;

	SceneObjMap			_sceneObjs;
};
extern GrSceneObjMgr* g_GrSceneObjMgr;
