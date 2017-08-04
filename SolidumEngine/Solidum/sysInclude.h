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

#include "EngineUtils\include\MiscMath.h"

#include "EngineUtils\include\Matrix3x3.h"
#include "EngineUtils\include\Matrix4x4.h"

#include "EngineUtils\include\Vector2.h"
#include "EngineUtils\include\Vector3.h"
#include "EngineUtils\include\Vector4.h"

#include "EngineUtils\include\VariantType.h"

#include "EngineUtils\include\EnumString.h"

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

enum class INPUT_LAYOUT_ELEMENT_CLASS {
	PER_VERTEX_DATA,
	PER_INSTANCE_DATA
};

enum class RASTER_STATE {
	NORMAL,
	DISABLE_TRIANGLE_CULL
};

enum class BLEND_STATE {
	INVALID,
	BLENDING_OFF,
	ADDITIVE_BLENDING,
	ALPHA_BLENDING,
	PARTICLE_BLENDING_TEST
};

enum class LIGHT_TYPE {
	DIRECTIONAL_LIGHT, 
	POINT_LIGHT
};

enum class DEPTH_TEST_STATE {
	INVALID,
	FULL_DISABLE,
	FULL_ENABLE,
	LESS_EQUAL
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
	D24_UNORM_S8_UINT_COUGH_FRAMEBUFFER,
	R24G8_TYPLESS
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
	INSTANCE_BUFF,
	INVALID
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

enum class RENDER_DATA_TYPE {
	RENDER_CAMERA_DATA,
	RENDER_LIGHT_DATA,
	RENDER_MESH_DATA,
	RENDER_PARTICLE_EMITTER_DATA,
	SHADOW_MAP_RENDER_DATA,
	SKY_RENDER_DATA
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

struct ParticleInstanceData {

	Vector2f _texOffset1;
	Vector2f _texOffset2;
	Vector2f _texCoordInfo;
	Matrix4f _mvMatrix;

};

class BoundingSphere;

struct RenderPassPacket_CameraData {

	Matrix4f _projectionMatrix;
	Matrix4f _orthoProjection;
	Matrix4f _viewMatrix;
	Matrix4f _worldMatrix;

	Matrix4f _startView;

	Vector3f _eyePosition;
};

struct RenderData_GlobalData {
	RenderPassPacket_CameraData global_cam;
	BoundingSphere* boundingSphere;
};


struct RenderPassSpecificIOHookData {
	SHADER_TYPE _shaderType;
	SHADER_RESOURCE_TYPE _shaderResType;
};

struct VERTEX { Vector3f Pos; Vector3f Normal; Vector2f TexCoords; Vector3f biNormal; Vector3f Tangent; };
struct LIGHT_VERTEX { Vector3f position; Vector2f texture; };

#endif