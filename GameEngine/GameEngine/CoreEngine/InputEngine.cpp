#include "CoreEngine/AppMain.h"

// Keyboard -------------------------------------
BYTE Keyboard::Keys[N_KEYS];

Keyboard::Keyboard(LPDIRECTINPUT8 directInput, HWND hWnd)
{
	if(FAILED(directInput->CreateDevice(GUID_SysKeyboard, &DirectInputDevice, NULL)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to create device for keyboard input");
		exit(EXIT_FAILURE);
	}

	if(FAILED(DirectInputDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to set data format for keyboard");
		exit(EXIT_FAILURE);
	}

//	cout<<"HWnd : "<<hWnd<<endl;

	if(FAILED(DirectInputDevice->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to set cooperative level");
		exit(EXIT_FAILURE);
	}

	if(FAILED(DirectInputDevice->Acquire()))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to Acquire Keyboard");
		exit(EXIT_FAILURE);
	}

	Clear();
}

Keyboard::~Keyboard()
{
	if(DirectInputDevice)
	{
		DirectInputDevice->Unacquire();
		DirectInputDevice->Release();
	}
}

bool Keyboard::KeyDown(BYTE key)
{
	return (Keys[key] & 0x80) ? true : false;
}

bool Keyboard::KeyUp(BYTE key)
{
	return (Keys[key] & 0x80) ? false : true;
}

bool Keyboard::Update()
{
	if(FAILED(DirectInputDevice->GetDeviceState(sizeof(Keys), (LPVOID)Keys)))
	{
		if(FAILED(DirectInputDevice->Acquire()))
		{
			return false;
		}

		if(FAILED(DirectInputDevice->GetDeviceState(sizeof(Keys), (LPVOID)Keys)))
		{
			return false;
		}
	}

	return true;
}

void Keyboard::Clear()
{
	ZeroMemory(Keys, 256 * sizeof(char));
}

bool Keyboard::Acquire()
{
	Clear();
	return (!FAILED(DirectInputDevice->Acquire()));
}

bool Keyboard::UnAcquire()
{
	Clear();
	return (!FAILED(DirectInputDevice->Unacquire()));
}

// Mouse -------------------------------------
Mouse::Mouse(LPDIRECTINPUT8 directInput, HWND hWnd, bool isExclusive)
{
	if(FAILED(directInput->CreateDevice(GUID_SysMouse, &DirectInputDevice, NULL)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to create device for mouse input");
		exit(EXIT_FAILURE);
	}

	if(FAILED(DirectInputDevice->SetDataFormat(&c_dfDIMouse)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to set data format for mouse");
		exit(EXIT_FAILURE);
	}

	DWORD dwFlags;

	if(isExclusive)
	{
		dwFlags = DISCL_BACKGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
	}
	else
	{
		dwFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
	}

	if(FAILED(DirectInputDevice->SetCooperativeLevel(hWnd, dwFlags)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to set cooperative level");
		exit(EXIT_FAILURE);
	}

	if(FAILED(DirectInputDevice->Acquire()))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to acquire mouse");
		exit(EXIT_FAILURE);
	}

	if(FAILED(DirectInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
	{
		DISPLAY_MESSAGE(L"Error!!!", L"Failed to get device state for mouse");
		exit(EXIT_FAILURE);
	}
}

Mouse::~Mouse()
{
	if(DirectInputDevice)
	{
		DirectInputDevice->Unacquire();
		DirectInputDevice->Release();
	}
}

bool Mouse::ButtonDown(int button)
{
	return (MouseState.rgbButtons[button] & 0x80) ? true : false;
}

bool Mouse::ButtonUp(int button)
{
	return (MouseState.rgbButtons[button] & 0x80) ? false : true;
}

int Mouse::GetWheelMovement()
{
	return MouseState.lZ;
}

void Mouse::GetMovement(int &dx, int &dy)
{
	dx += MouseState.lX;
	dy += MouseState.lY;

	if(dx < 0)
	{
		dx = 0;
	}

	if(dy < 0)
	{
		dy = 0;
	}

	if(dx > GlobalRefs::Window->ScreenWidth)
	{
		dx = GlobalRefs::Window->ScreenWidth;
	}

	if(dy > GlobalRefs::Window->ScreenHeight)
	{
		dy = GlobalRefs::Window->ScreenHeight;
	}

	return;
}

int Mouse::GetMovementX()
{
	return MouseState.lX;
}

int Mouse::GetMovementY()
{
	return MouseState.lY;
}

bool Mouse::Update()
{
	if(FAILED(DirectInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
	{
		if(FAILED(DirectInputDevice->Acquire()))
		{
			return false;
		}

		if(FAILED(DirectInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
		{
			return false;
		}
	}

	return true;
}

bool Mouse::Acquire()
{
	return (!FAILED(DirectInputDevice->Acquire()));
}

bool Mouse::UnAcquire()
{
	return (!FAILED(DirectInputDevice->Unacquire()));
}

// Input Engine -------------------------------------
InputEngine::InputEngine()
{
	KeyboardInput = NULL;
	MouseInput = NULL;
}

InputEngine::InputEngine(const InputEngine&)
{

}

InputEngine::~InputEngine()
{

}

bool InputEngine::Initialize(HWND hWnd,  HWND mouseHWND, bool isExclusive, DWORD dwFlags)
{
	if(FAILED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL)))
	{
		cout<<"Failed to create Direct Input"<<endl;
		return false;
	}

//	cout<<"Created DirectInput Successfully"<<endl;

	if(dwFlags && IS_USEKEYBOARD)
	{
		KeyboardInput = new Keyboard(DirectInput, hWnd);

		if(KeyboardInput == NULL)
		{
			return false;
		}
	}

//	cout<<"Created Keyboard Successfully"<<endl;

	if(dwFlags & IS_USEMOUSE)
	{
		MouseInput = new Mouse(DirectInput, mouseHWND, isExclusive);

		if(MouseInput == NULL)
		{
			return false;
		}
	}

//	cout<<"Created Mouse Successfully"<<endl;

	GlobalRefs::Debug->Log("Input Initialized...");

	return true;
}

bool InputEngine::Shutdown()
{
	this->UnAcquireAll();

	SAFE_DELETE(KeyboardInput);
	SAFE_DELETE(MouseInput);

	if(FAILED(DirectInput->Release()))
	{
		return false;
	}

	GlobalRefs::Debug->Log("Input Shutdown...");

	return true;
}

void InputEngine::AcquireAll()
{
	if(KeyboardInput)
	{
		KeyboardInput->Acquire();
	}

	if(MouseInput)
	{
		MouseInput->Acquire();
	}
}

void InputEngine::UnAcquireAll()
{
	if(KeyboardInput)
	{
		KeyboardInput->UnAcquire();
	}

	if(MouseInput)
	{
		MouseInput->UnAcquire();
	}
}

Keyboard* InputEngine::GetKeyboard()
{
	return KeyboardInput;
}

Mouse* InputEngine::GetMouse()
{
	return MouseInput;
}

bool InputEngine::Update()
{
	if(KeyboardInput)
	{
		KeyboardInput->Update();
	}

	if(MouseInput)
	{
		MouseInput->Update();
	}

	return true;
}

bool InputEngine::KeyDown(BYTE key)
{
	return (KeyboardInput && KeyboardInput->KeyDown(key));
}

bool InputEngine::KeyUp(BYTE key)
{
	return (KeyboardInput && KeyboardInput->KeyUp(key));
}

bool InputEngine::MouseButtonDown(int button)
{
	return (MouseInput && MouseInput->ButtonDown(button));
}

bool InputEngine::MouseButtonUp(int button)
{
	return (MouseInput && MouseInput->ButtonUp(button));
}

void InputEngine::GetMouseMovement(int &dx, int &dy)
{
	if(MouseInput)
	{
		MouseInput->GetMovement(dx, dy);
	}
}

float InputEngine::GetMouseMovementX()
{
	if(MouseInput)
	{
		return (float)MouseInput->GetMovementX();
	}

	return 0;
}

float InputEngine::GetMouseMovementY()
{
	if(MouseInput)
	{
		return (float)MouseInput->GetMovementY();
	}

	return 0;
}

int InputEngine::GetMouseWheelMovement()
{
	return (MouseInput) ? MouseInput->GetWheelMovement() : 0;
}