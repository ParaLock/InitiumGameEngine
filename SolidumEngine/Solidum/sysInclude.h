#pragma once

#ifndef _SYSINCLUDE_H
#define _SYSINCLUDE_H

#include <windows.h>
#include <Memory>
#include <Map>
#include <List>
#include <Vector>
#include <iostream>
#include <fstream> 

#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include <sstream>
#include <algorithm>
#include <iterator>

#include <functional>

#include <thread>

#include <locale>
#include <codecvt>

#include "EngineUtils\include\Vector4f.h"
#include "EngineUtils\include\Vector3f.h"
#include "EngineUtils\include\Vector2f.h"

#include "atlstr.h"

#include <regex>

#include <stdlib.h>

#include "DirectXMath.h"

#include "D3Dcompiler.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment (lib, "dxguid.lib")

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

enum TEX_FILTERS {
	TEX_FILTER_ANISOTROPHIC,
	TEX_FILTER_LINEAR,
	TEX_FILTER_POINT
};
enum TEX_ADDR_MODES {
	TEX_ADDR_MODE_WRAP,
	TEX_ADDR_MODE_CLAMP
};

enum TEX_FORMAT {
	RGBA_32BIT_FLOAT,
	RGB_32BIT_FLOAT,
	D24_UNORM_S8_UINT_COUGH_FRAMEBUFFER
};

enum ANISOTRPHIC_FILTER_LEVELS {
	HIGHEST_QUALITY = 16,
	HIGH_QUALITY = 8,
	MEDIUM_QUALITY = 4,
	NO_ANISOTROPHIC_FILTERING = 0
};

enum BUFFER_TYPE {
	VERTEX_BUFF,
	INDEX_BUFF,
	SHADER_BUFF,
};

enum BUFFER_CPU_ACCESS {
	CPU_ACCESS_WRITE,
	CPU_ACCESS_READ,
	CPU_ACCESS_READWRITE
};

enum KEY_MAP {
	Q, W, E, R, T, Y, U, I, O, P, A,
	S, D, F, G, H, J, K, L, z, X, V,
	B, N, M,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class IEvent;

typedef std::shared_ptr<IEvent> EVENT_PTR;

struct VERTEX { D3DXVECTOR3 Pos; D3DXVECTOR3 Normal; D3DXVECTOR2 TexCoords; };
struct LIGHT_VERTEX { D3DXVECTOR3 position; D3DXVECTOR2 texture; };

#endif