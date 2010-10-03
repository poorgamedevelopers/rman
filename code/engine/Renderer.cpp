#include "engine_common.h"

// project includes.
#include "Renderer.h"

// windows includes.
#include <Windows.h>

// screen dimensions.
static unsigned int _screenWidth = 0;
static unsigned int _screenHeight = 0;

// character ratio and aspect ratio.
static float _aspectRatio = 1.0f;

// framebuffer and depth buffer.
static CHAR_INFO* _framebuffer = 0;
static float* _depthbuffer = 0;

// standard handle output.
static HANDLE _screen = INVALID_HANDLE_VALUE;

//-----------------------------------------------------------------
void GrInit( char* windowTitle, unsigned int width, unsigned int height )
{
	// grab the output window.
	_screen = GetStdHandle( STD_OUTPUT_HANDLE );

	// change the title of the window.
	SetConsoleTitle( windowTitle );

	// change the size of the console window's internal buffer.
	COORD size;
	size.X = width;
	size.Y = height;
	SetConsoleScreenBufferSize( _screen, size );
	
	// get the current console's font index.
	CONSOLE_FONT_INFO fontInfo;
	GetCurrentConsoleFont( _screen, FALSE, &fontInfo );

	// adjust the console window's size.
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;
	BOOL result = SetConsoleWindowInfo( _screen, TRUE, &rect );

	// initialize the framebuffer.
	unsigned int framebufferScreenSize = width * height * sizeof( CHAR_INFO );
	_framebuffer = ( CHAR_INFO* )malloc( framebufferScreenSize );
	memset( _framebuffer, 0, framebufferScreenSize );

	// initialize the depthbuffer.
	unsigned int depthbufferScreenSize = width * height * sizeof( float );
	_depthbuffer = ( float* )malloc( depthbufferScreenSize );
	memset( _depthbuffer, 0, depthbufferScreenSize );

	// store the screen's width and height.
	_screenWidth = width;
	_screenHeight = height;

	// calculate the aspect ratio, taking into account the character ratio.
	_aspectRatio = ( ( float )( int )fontInfo.dwFontSize.X / ( float )( int )fontInfo.dwFontSize.Y ) *
				   ( ( float )( int )width / ( float )( int )height );
}

//-----------------------------------------------------------------
void GrClear( char clearChar, unsigned char clearColor, float clearDepth )
{
	// initialize a single pixel value.
	CHAR_INFO charInfo;
	charInfo.Attributes = clearColor;
	charInfo.Char.AsciiChar = clearChar;

	unsigned int charCount = _screenWidth * _screenHeight;

	// determine how many chars we need to update.
	CHAR_INFO* curChar = _framebuffer;
	CHAR_INFO* endChar = curChar + charCount;
	for ( ; curChar != endChar; ++curChar )
		*curChar = charInfo;

	// clear the depth buffer.
	float* curDepth = _depthbuffer;
	float* endDepth = curDepth + charCount;
	for ( ; curDepth != endDepth; ++curDepth )
		*curDepth = clearDepth;
}

//-----------------------------------------------------------------
void GrRender( const RenderObj_t* objects, unsigned int objCount,
			   const float* cameraPos )
{
	// get the screen width and height as floating point values.
	float screenWidth = ( float )( int )_screenWidth;
	float screenHeight = ( float )( int )_screenHeight;

	// iterate through each object and render.
	const RenderObj_t* curObj = objects;
	const RenderObj_t* endObj = curObj + objCount;
	for ( ; curObj != endObj; ++curObj )
	{
		// calculate clip space coordinates.
		float cz = curObj->xyz[ 2 ] - cameraPos[ 2 ];
		if ( cz < 0.0f )
			continue;
		float cx = curObj->xyz[ 0 ] - cameraPos[ 0 ];
		float cy = curObj->xyz[ 1 ] - cameraPos[ 1 ];
		cy *= _aspectRatio;
		cz += curObj->zBias;
	
		// expand from clip space into screen space.
		float sx = screenWidth * ( 0.5f * cx + 0.5f );
		float sy = screenHeight * ( 0.5f * cy + 0.5f );
		if ( sx < 0.0f || sy < 0.0f )
			continue;
		if ( sx >= screenWidth || sy >= screenHeight )
			continue;

		// get integer coordinates.
		unsigned int isx = ( unsigned int )( int )sx;
		unsigned int isy = ( unsigned int )( int )sy;

		// calculate the pixel number.
		unsigned int offset = isy * _screenWidth + isx;

		// perform the z-test.
		float* curDepth = _depthbuffer + offset;
		if ( cz <= *curDepth )
			*curDepth = cz;
		else
			continue;

		// store the output color.
		CHAR_INFO* curValue = _framebuffer + offset;
		curValue->Char.AsciiChar = curObj->value;
		curValue->Attributes = curObj->color;
	}
}

//-----------------------------------------------------------------
void GrPresent()
{
	// buffer size.
	COORD bufSize;
	bufSize.X = _screenWidth;
	bufSize.Y = _screenHeight;

	// buffer origin.
	COORD bufOrig;
	bufOrig.X = 0;
	bufOrig.Y = 0;

	// buffer destination.
	SMALL_RECT destRect;
	destRect.Top = 0;
	destRect.Left = 0;
	destRect.Bottom = _screenHeight;
	destRect.Right = _screenWidth;

	// present the screen's contents.
	BOOL result = WriteConsoleOutput( _screen, _framebuffer, bufSize, bufOrig, &destRect );
}

//-----------------------------------------------------------------
void GrShutdown()
{
	// free up memory.
	free( _framebuffer );
	free( _depthbuffer );
	_framebuffer = 0;
	_depthbuffer = 0;
}
