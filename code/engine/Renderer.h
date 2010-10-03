#pragma once

// foreground character colors.
#define COLOR_B		0x01
#define COLOR_G		0x02
#define COLOR_R		0x04
#define COLOR_I		0x08

// background character colors.
#define BK_COLOR_B	0x10
#define BK_COLOR_G	0x20
#define BK_COLOR_R	0x40
#define BK_COLOR_I	0x80

typedef struct RenderObj
{
	float xyz[ 3 ];					// floating point position.
	float zBias;					// non-projection altering z-bias.
	char value;						// character to use.
	unsigned char color;			// color of the object.
	unsigned short reserved;		// padding for alignment.
} RenderObj_t;

extern void GrInit( char* windowTitle, unsigned int width, unsigned int height );
extern void GrClear( char clearChar, unsigned char clearColor, float clearDepth );
extern void GrRender( const RenderObj_t* objects, unsigned int objCount,
					  const float* cameraPos );
extern void GrPresent();
extern void GrShutdown();
