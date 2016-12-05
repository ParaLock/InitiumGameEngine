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

#include <stdlib.h>

#include "DirectXMath.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")


#define SHADER_RESOURCE_DXTEXSAMPLER 0x2
#define SHADER_RESOURCE_DXRENDERTARGET 0x3
#define SHADER_RESOURCE_DXTEXTURE 0x4

#define PARENT_SHADER_TYPE_VERTEX 0x1
#define PARENT_SHADER_TYPE_PIXEL 0x2
#define PARENT_SHADER_TYPE_AGNOSTIC 0x4

#define DXSHADER_TYPE_DEFERRED 0x0
#define DXSHADER_TYPE_DirectionalLight 0x1
#define DXSHADER_TYPE_SpotLight 0x2

#define DXTEXTURE 0x9

#define CBUFF_TYPE_MATRIX 0x2
#define CBUFF_TYPE_LIGHT 0x3
#define CBUFF_TYPE_LIGHT_MATRIX 0x4

#define GENERATE_MESH_PLANE L"solidum_gen_mesh_plane"

enum TEX_FILTERS {
	TEX_FILTER_ANISOTROPHIC = 9,
	TEX_FILTER_LINEAR = 8,
	TEX_FILTER_POINT = 7
};
enum TEX_ADDR_MODES {
	TEX_ADDR_MODE_WRAP = 1,
	TEX_ADDR_MODE_CLAMP = 2
};

enum ANISOTRPHIC_FILTER_LEVELS {
	HIGHEST_QUALITY = 16,
	HIGH_QUALITY = 8,
	MEDIUM_QUALITY = 4,
	NO_ANISOTROPHIC_FILTERING = 0
};

struct VERTEX { D3DXVECTOR3 Pos; D3DXVECTOR3 Normal; D3DXVECTOR2 TexCoords; };

struct LIGHT_VERTEX
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
};

struct CBUFFER_MATRIX {
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX OBJSpecificMatrix;
};

struct LIGHT_CBUFFER_MATRIX {
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
};

struct CBUFFER_LIGHT
{
	D3DXVECTOR3 LightDirection;
	float padding1;
	D3DXVECTOR3 LightPos;
	float padding2;
	D3DXVECTOR4 AmbientColor;
	D3DXVECTOR3 LightColor;
	float padding3;
	D3DXVECTOR3 eyeView;
	float padding4;
};

#endif