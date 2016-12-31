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

#include "atlstr.h"

#include <regex>

#include <stdlib.h>

#include "DirectXMath.h"

#include "D3Dcompiler.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")

enum SUPPORTED_GRAPHICS_API {
	DIRECTX11 = 0x1,
	UNKNOWN = 0xff
};

enum TEX_FILTERS {
	TEX_FILTER_ANISOTROPHIC = 9,
	TEX_FILTER_LINEAR = 8,
	TEX_FILTER_POINT = 7
};
enum TEX_ADDR_MODES {
	TEX_ADDR_MODE_WRAP = 1,
	TEX_ADDR_MODE_CLAMP = 2
};

enum TEX_FORMAT {
	RGBA_32BIT_FLOAT = 0x0,
	RGB_32BIT_FLOAT = 0x1
};

enum ANISOTRPHIC_FILTER_LEVELS {
	HIGHEST_QUALITY = 16,
	HIGH_QUALITY = 8,
	MEDIUM_QUALITY = 4,
	NO_ANISOTROPHIC_FILTERING = 0
};

enum BUFFER_TYPE {
	VERTEX_BUFF = 0x1,
	INDEX_BUFF = 0x2,
	SHADER_BUFF = 0x3,
};

enum BUFFER_CPU_ACCESS {
	CPU_ACCESS_WRITE = 0x0,
	CPU_ACCESS_READ = 0x1,
	CPU_ACCESS_READWRITE = 0x2
};

struct VERTEX { D3DXVECTOR3 Pos; D3DXVECTOR3 Normal; D3DXVECTOR2 TexCoords; };

struct LIGHT_VERTEX
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
};

#endif