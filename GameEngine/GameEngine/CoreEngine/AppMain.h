#ifndef APP_MAIN_H
#define APP_MAIN_H

// API Defines
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

// Library Links
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "Effects11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "pdh.lib")

// API Includes
#include <Windows.h>
#include <MMSystem.h>
#include <dinput.h>
#include <dxgi.h>
#include <D3Dcommon.h>
#include <D3DX11.h>
#include <d3dx11effect.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <D3Dcompiler.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
using namespace std;

// Engine Defines
#define SAFE_DELETE(X) if(X) { delete (X); (X) = NULL; }
#define SAFE_DELETE_ARRAY(X) if(X) { delete [] (X); (X) = NULL; }
#define DISPLAY_MESSAGE(TITLE, MESSAGE) MessageBox(NULL, MESSAGE, TITLE, MB_OK);

#define N_KEYS 256
#define IS_USEKEYBOARD 1
#define IS_USEMOUSE 2

enum WindowModeType
{
	WMT_FULLSCREEN = 0,
	WMT_WINDOWED = 1
};

enum VSyncState
{
	VSS_ENABLED = 0,
	VSS_DISABLED = 1
};

enum RenderModeType
{
	RMT_WIRE  = 0,
	RMT_SOLID = 1
};

enum CullModeType
{
	CMT_NONE = 0,
	CMT_FRONT = 1,
	CMT_BACK = 2
};

// Math Engine
#include "MathEngine/Mathf.h"
#include "MathEngine/Mathd.h"
#include "MathEngine/Vector2f.h"
#include "MathEngine/Vector2d.h"
#include "MathEngine/Vector3f.h"
#include "MathEngine/Vector3d.h"
#include "MathEngine/Vector4f.h"
#include "MathEngine/Vector4d.h"
#include "MathEngine/Matrix4x4f.h"
#include "MathEngine/Matrix4x4d.h"
#include "MathEngine/Quaternion.h"
#include "MathEngine/Plane.h"

// Audio Engine

// Input Engine

// Graphics Engine
#include "CoreEngine/GraphicsEngine.h"

#endif