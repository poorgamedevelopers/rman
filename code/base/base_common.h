#pragma once

// standard headers.
#include <cstdlib>
#include <cassert>
#include <memory>
#include <iostream>

// project headers.
#include "b_config.h"
#include "b_types.h"
#include "b_stl.h"

// basic macros.
#define B_ASSERT( cond )					assert( cond )
#define B_VERIFY( cond, if_fail )			\
	if ( !( cond ) )						\
	{										\
		assert( !#cond );					\
		if_fail;							\
	}

// memory utils.
#define MemSet( p, val, size )				memset( p, val, size )
#define MemZero( p, size )					memset( p, 0, size )

// memory allocation / freeing.
#define B_NEW( ctx, type )					new type
#define B_DEL( ctx, obj )					delete obj
#define B_NEW_ARRAY( ctx, type, count )		new type[ count ]
#define B_DEL_ARRAY( ctx, obj )				delete [] obj
#define B_MEM_ALLOC( ctx, size )			malloc( size )
#define B_MEM_CALLOC( ctx, size )			calloc( 1, size )
#define B_MEM_FREE( ctx, p )				free( p )
