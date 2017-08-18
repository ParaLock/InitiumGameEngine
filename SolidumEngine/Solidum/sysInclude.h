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
#include <random>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include <mutex>
#include <chrono>
#include <set>
#include <ctime>
#include <time.h> 
#include <functional>
#include <thread>
#include <locale>
#include <codecvt>

#include <typeinfo>
#include <typeindex>

#include "EngineUtils\include\EnumString.h"

#include "atlstr.h"

#include "EngineUtils\include\PerfProfiler.h"

#include <regex>

#include <stdlib.h>

#include "D3Dcompiler.h"

#include "../SolidumAPI/common.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment (lib, "dxguid.lib")

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


enum class TEX_FILTERS {
	TEX_FILTER_ANISOTROPHIC,
	TEX_FILTER_LINEAR,
	TEX_FILTER_POINT
};
enum class TEX_ADDR_MODES {
	TEX_ADDR_MODE_WRAP,
	TEX_ADDR_MODE_CLAMP
};

enum class TEX_FORMAT {
	INVALID,
	UNKNOWN,
	RGBA_32BIT_FLOAT,
	RGB_32BIT_FLOAT,
	D24_UNORM_S8_UINT_COUGH_FRAMEBUFFER,
	R24G8_TYPLESS
};

enum class BUFFER_CPU_ACCESS {
	CPU_ACCESS_WRITE,
	CPU_ACCESS_READ,
	CPU_ACCESS_READWRITE
};


enum class MATERIAL_TEX {
	ALBEDO_MAT_TEXTURE,
	SPECULAR_MAT_TEXTURE,
	NORMAL_MAT_TEXTURE,

	ROUGHNESS_PBR_TEXTURE,
	EMESSIVE_PBR_TEXTURE
};

enum class TASK_COMPLETION_STATUS {
	SUCCESS,
	FAILURE,
	RESTART
};


enum SHADER_TYPE {
	INVALID_ST,
	PIXEL_SHADER,
	VERTEX_SHADER,
	GEOMETRY_SHADER
};

Begin_Enum_String(SHADER_TYPE)
{
	Enum_String(PIXEL_SHADER);
	Enum_String(VERTEX_SHADER);
	Enum_String(GEOMETRY_SHADER);
}
End_Enum_String;

enum SHADER_RESOURCE_TYPE {
	INVALID_SR,
	TEXTURE_SAMPLER,
	RENDER_TARGET,
	DEPTH_STENCIL,
	CONSTANT_BUFFER,
	INPUT_LAYOUT,
	GPU_BUFFER,
	TEXTURE
};

Begin_Enum_String(SHADER_RESOURCE_TYPE)
{
	Enum_String(TEXTURE_SAMPLER);
	Enum_String(RENDER_TARGET);
	Enum_String(DEPTH_STENCIL);
	Enum_String(CONSTANT_BUFFER);
	Enum_String(INPUT_LAYOUT);
	Enum_String(GPU_BUFFER);
	Enum_String(TEXTURE);
}
End_Enum_String;


enum class DEFAULT_SHADER_TYPE {
	DEFAULT_MESH,
	DEFAULT_LIGHT
};

enum PIPELINE_OP_TYPE {
	CLEAR,
	SWAPFRAME
};

Begin_Enum_String(PIPELINE_OP_TYPE)
{
	Enum_String(CLEAR);
	Enum_String(SWAPFRAME);
}
End_Enum_String;

enum class PRIMITIVE_TOPOLOGY {
	INVALID,
	TRANGLE_LIST
};

enum class RENDER_TARGET_OP_TYPE {
	INVALID,
	CLEAR
};

#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define M_PI    3.14159265358979323846264338327950288

#define MAX_FORWARD_RENDERING_LIGHTS 10

class Event;

typedef std::shared_ptr<Event> EVENT_PTR;

class BoundingSphere;

struct RenderPassSpecificIOHookData {
	SHADER_TYPE _shaderType;
	SHADER_RESOURCE_TYPE _shaderResType;
};

#endif