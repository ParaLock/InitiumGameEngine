#pragma once

#include "SolidumMath\Matrix3x3.h"
#include "SolidumMath\Matrix4x4.h"
#include "SolidumMath\Vector2.h"
#include "SolidumMath\Vector3.h"
#include "SolidumMath\Vector4.h"

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


#include "SolidumMath\Matrix3x3.h"
#include "SolidumMath\Matrix4x4.h"
#include "SolidumMath\Vector2.h"
#include "SolidumMath\Vector3.h"
#include "SolidumMath\Vector4.h"

#include <windows.h>
#include <Memory>
#include <Map>
#include <List>
#include <Vector>
#include <iostream>
#include <fstream> 
#include <random>

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

class IResource;


static int getRandomNumber() { return rand() % 100; }

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


enum class KEY_MAP {
	Q, W, E, R, T, Y, U, I, O, P, A,
	S, D, F, G, H, J, K, L, z, X, V,
	B, N, M,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define M_PI    3.14159265358979323846264338327950288

#define MAX_FORWARD_RENDERING_LIGHTS 10

class Event;

struct ParticleInstanceData {

	Vector2f _texOffset1;
	Vector2f _texOffset2;
	Vector2f _texCoordInfo;
	Matrix4f _mvMatrix;

};

class BoundingSphere;

enum class RENDER_DATA_TYPE {
	RENDER_CAMERA_DATA,
	RENDER_LIGHT_DATA,
	RENDER_MESH_DATA,
	RENDER_PARTICLE_EMITTER_DATA,
	SHADOW_MAP_RENDER_DATA,
	SKY_RENDER_DATA
};

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

struct VERTEX { Vector3f Pos; Vector3f Normal; Vector2f TexCoords; Vector3f biNormal; Vector3f Tangent; };
struct LIGHT_VERTEX { Vector3f position; Vector2f texture; };
