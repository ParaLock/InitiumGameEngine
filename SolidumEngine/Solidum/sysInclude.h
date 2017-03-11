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

#include <functional>

#include <thread>

#include <locale>
#include <codecvt>

#include "../Solidum/EngineUtils/include/MiscMath.h"

#include "../Solidum/EngineUtils/include/Matrix3x3.h"
#include "../Solidum/EngineUtils/include/Matrix4x4.h"

#include "../Solidum/EngineUtils/include/Vector2.h"
#include "../Solidum/EngineUtils/include/Vector3.h"
#include "../Solidum/EngineUtils/include/Vector4.h"

#include "atlstr.h"

#include <regex>

#include <stdlib.h>

#include "D3Dcompiler.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment (lib, "dxguid.lib")

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

enum class RASTER_STATE {
	NORMAL,
	DISABLE_TRIANGLE_CULL
};

enum class BLEND_STATE {
	BLENDING_OFF,
	LIGHT_BLENDING,
	PASS_BLENDING
};

enum class DEPTH_TEST_STATE {
	FULL_DISABLE,
	FULL_ENABLE
};

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
	D24_UNORM_S8_UINT_COUGH_FRAMEBUFFER
};

enum class ANISOTRPHIC_FILTER_LEVELS {
	HIGHEST_QUALITY = 16,
	HIGH_QUALITY = 8,
	MEDIUM_QUALITY = 4,
	NO_ANISOTROPHIC_FILTERING = 0
};

enum class BUFFER_TYPE {
	VERTEX_BUFF,
	INDEX_BUFF,
	SHADER_BUFF,
};

enum class BUFFER_CPU_ACCESS {
	CPU_ACCESS_WRITE,
	CPU_ACCESS_READ,
	CPU_ACCESS_READWRITE
};

enum class KEY_MAP {
	Q, W, E, R, T, Y, U, I, O, P, A,
	S, D, F, G, H, J, K, L, z, X, V,
	B, N, M,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

enum class LIGHT_TYPE {
	DIRECTIONAL_LIGHT,
	POINT_LIGHT
};

enum class MATERIAL_TEX {
	ALBEDO_MAT_TEXTURE,
	SPECULAR_MAT_TEXTURE,
	NORMAL_MAT_TEXTURE,

	ROUGHNESS_PBR_TEXTURE,
	EMESSIVE_PBR_TEXTURE
};

enum class RENDER_NODE_TYPE {
	LIGHT_RENDER_NODE,
	MESH_RENDER_NODE,
	POST_FX_RENDER_NODE
};

enum class SHADER_RENDER_TYPE {
	INVALID,
	DEFERRED_RENDERING,
	DEFERRED_RENDERING_LIGHT,
	FORWARD_RENDERING,
	MULTI_PASS_RENDERING
};

enum class SHADER_TYPE {
	INVALID,
	PIXEL_SHADER,
	VERTEX_SHADER,
	GEOMETRY_SHADER
};

enum class SHADER_RESOURCE_TYPE {
	INVALID,
	SHADER_TEX_SAMPLER,
	SHADER_RENDER_TARGET,
	SHADER_ZBUFFER,
	SHADER_CONSTANT_BUFFER,
	SHADER_INPUT_LAYOUT,
	SHADER_BUFFER_HOOK,
	SHADER_TEXTURE_HOOK
};

enum class COMPONENT_TYPE {
	MOVE_COMPONENT,
	LIGHT_COMPONENT,
	MESH_COMPONENT,
	CAMERA_COMPONENT
};

enum class GPUPIPELINE_OP_TYPE {
	CLEAR,
	SWAPFRAME
};

enum class PRIMITIVE_TOPOLOGY {
	TRANGLE_LIST
};

enum class RENDER_TARGET_OP_TYPE {
	CLEAR,
	BIND_AS_INPUT,
	BIND_AS_OUTPUT
};

#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define M_PI    3.14159265358979323846264338327950288

#define MAX_FORWARD_RENDERING_LIGHTS 10

class IEvent;

typedef std::shared_ptr<IEvent> EVENT_PTR;

struct VERTEX { Vector3f Pos; Vector3f Normal; Vector2f TexCoords; Vector3f biNormal; Vector3f Tangent; };
struct LIGHT_VERTEX { Vector3f position; Vector2f texture; };

#endif