#ifndef INPUTENGINE_H
#define INPUTENGINE_H

class Keyboard
{
	private:
			LPDIRECTINPUTDEVICE8 DirectInputDevice;
			static BYTE Keys[N_KEYS];
	public:
			Keyboard(LPDIRECTINPUT8 directInput, HWND hWnd);
			~Keyboard();

			bool KeyDown(BYTE key);
			bool KeyUp(BYTE key);
			bool Update();
			void Clear();
			bool Acquire();
			bool UnAcquire();
};

class Mouse
{
	private:
			LPDIRECTINPUTDEVICE8 DirectInputDevice;
			DIMOUSESTATE MouseState;
	public:
			Mouse(LPDIRECTINPUT8 directInput, HWND hWnd, bool isExclusive = true);
			~Mouse();

			bool ButtonDown(int button);
			bool ButtonUp(int button);

			int GetWheelMovement();
			void GetMovement(int &dx, int &dy);
			int GetMovementX();
			int GetMovementY();

			bool Update();
			bool Acquire();
			bool UnAcquire();
};

class InputEngine
{
	private:
			Keyboard *KeyboardInput;
			Mouse *MouseInput;
			LPDIRECTINPUT8 DirectInput;
	public:
			InputEngine();
			InputEngine(const InputEngine&);
			~InputEngine();

			bool Initialize(HWND hWnd, HWND mouseHWND, bool isExclusive = true, DWORD dwFlags = 0);
			bool Shutdown();

			void AcquireAll();
			void UnAcquireAll();
			Keyboard* GetKeyboard();
			Mouse* GetMouse();

			bool Update();
			bool KeyDown(BYTE key);
			bool KeyUp(BYTE key);
			bool MouseButtonDown(int button);
			bool MouseButtonUp(int button);
			void GetMouseMovement(int &dx, int &dy);
			float GetMouseMovementX();
			float GetMouseMovementY();
			int GetMouseWheelMovement();
};

#endif