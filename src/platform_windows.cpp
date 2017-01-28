#include <windows.h>
//#include <assert.h>
//#define Assert assert
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "glcorearb.h"
#include "wglext.h"

#include "util.h"
#include "game_math.cpp"
#include "renderer_opengl.cpp"
#include "game.h"

global_variable HWND GlobalDummyWindow;
global_variable HWND GlobalWindow;
global_variable HDC GlobalDeviceContext;
global_variable HGLRC GlobalRenderingContext;

global_variable uint64_t GlobalQueryPerformanceFrequency;
global_variable uint64_t GlobalStartCounter;

global_variable bool GlobalRunning = true;

inline uint64_t
GetCounter()
{
	LARGE_INTEGER LargeInteger;
	QueryPerformanceCounter(&LargeInteger);
	uint64_t Result = LargeInteger.QuadPart;

	return Result;
}

inline float
GetMillisecondsElapsed(uint64_t NewCounter, uint64_t OldCounter)
{
	float Result = ((float)(NewCounter - OldCounter) / (float)GlobalQueryPerformanceFrequency) * 1000.0f;

	return Result;
}

inline uint32_t
GetMillisecond()
{
	uint32_t Result = (uint32_t)GetMillisecondsElapsed(GetCounter(), GlobalStartCounter);

	return Result;
}

internal void
FreeFileMemory(void *Memory)
{
    if(Memory)
    {
        VirtualFree(Memory, 0, MEM_RELEASE);
    }
}

internal read_file_result
ReadEntireFile(char *FileName)
{
    read_file_result Result = {};

    HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
		LARGE_INTEGER FileSize;
		if(GetFileSizeEx(FileHandle, &FileSize) != 0)
		{
			Assert(FileSize.QuadPart <= UINT_MAX);
			uint32_t FileSize32 = (uint32_t)FileSize.QuadPart;
			Result.Contents = VirtualAlloc(0, FileSize32, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
			if(Result.Contents != NULL)
			{
				DWORD BytesRead;
				if((ReadFile(FileHandle, Result.Contents, FileSize32, &BytesRead, 0) != 0) &&
				   (FileSize32 == BytesRead))
				{
					Result.ContentsSize = FileSize32;
				}
				else
				{
					// TODO: Logging
					FreeFileMemory(Result.Contents);
					Result.Contents = 0;
				}
			}
			else
			{
				// TODO: Logging
			}
		}
		else
		{
			// TODO: Logging
		}

		CloseHandle(FileHandle);
	}
	else
	{
		// TODO: Logging
	}

    return Result;
}

LRESULT
MainWindowProcedure(HWND hWnd, 
					UINT uMsg, 
					WPARAM wParam, 
					LPARAM lParam)
{
	if(!GlobalDummyWindow)
	{
		GlobalDummyWindow = hWnd;
	}

	LRESULT Result = 1;

	if(hWnd != GlobalDummyWindow)
	{
		switch(uMsg)
		{
			case WM_SIZE:
			{
				RECT WindowRectangle;
				GetClientRect(hWnd, &WindowRectangle);
				glViewport(0, 0, WindowRectangle.right, WindowRectangle.bottom);
			} break;

			case WM_KEYDOWN:
			{
				switch(wParam)
				{
					case VK_LEFT:
					{
					} break;
				} break;
			} break;

			case WM_CLOSE:
			case WM_DESTROY:
			{
				GlobalRunning = false;
			} break;

			default:
			{
				Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
			} break;
		}
	}
	else
	{
		Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return Result;
}

internal void
Decompose(triangle Triangle,
		  float *VertexBuffer, uint32_t *VertexBufferIndex,
		  uint8_t MaxLayers, uint8_t CurrentLayer, v4 Color)
{
	if(CurrentLayer == MaxLayers)
	{
		v3 UnitA = SetLength(Triangle.A, 1.0f);
		v3 UnitB = SetLength(Triangle.B, 1.0f);
		v3 UnitC = SetLength(Triangle.C, 1.0f);

		v3 BA = UnitB - UnitA;
		v3 CA = UnitC - UnitA;
		v3 Center = UnitA + (0.5f * BA) + (0.5f * CA);
		v3 Normal = Normalize(Center);

		// position
		VertexBuffer[(*VertexBufferIndex)++] = UnitA.X;
		VertexBuffer[(*VertexBufferIndex)++] = UnitA.Y;
		VertexBuffer[(*VertexBufferIndex)++] = UnitA.Z;

		// normal
		VertexBuffer[(*VertexBufferIndex)++] = Normal.X;
		VertexBuffer[(*VertexBufferIndex)++] = Normal.Y;
		VertexBuffer[(*VertexBufferIndex)++] = Normal.Z;

		// color
		VertexBuffer[(*VertexBufferIndex)++] = Color.R;
		VertexBuffer[(*VertexBufferIndex)++] = Color.G;
		VertexBuffer[(*VertexBufferIndex)++] = Color.B;
		VertexBuffer[(*VertexBufferIndex)++] = Color.A;

		// position
		VertexBuffer[(*VertexBufferIndex)++] = UnitB.X;
		VertexBuffer[(*VertexBufferIndex)++] = UnitB.Y;
		VertexBuffer[(*VertexBufferIndex)++] = UnitB.Z;

		// normal
		VertexBuffer[(*VertexBufferIndex)++] = Normal.X;
		VertexBuffer[(*VertexBufferIndex)++] = Normal.Y;
		VertexBuffer[(*VertexBufferIndex)++] = Normal.Z;

		// color
		VertexBuffer[(*VertexBufferIndex)++] = Color.R;
		VertexBuffer[(*VertexBufferIndex)++] = Color.G;
		VertexBuffer[(*VertexBufferIndex)++] = Color.B;
		VertexBuffer[(*VertexBufferIndex)++] = Color.A;

		// position
		VertexBuffer[(*VertexBufferIndex)++] = UnitC.X;
		VertexBuffer[(*VertexBufferIndex)++] = UnitC.Y;
		VertexBuffer[(*VertexBufferIndex)++] = UnitC.Z;

		// normal
		VertexBuffer[(*VertexBufferIndex)++] = Normal.X;
		VertexBuffer[(*VertexBufferIndex)++] = Normal.Y;
		VertexBuffer[(*VertexBufferIndex)++] = Normal.Z;

		// color
		VertexBuffer[(*VertexBufferIndex)++] = Color.R;
		VertexBuffer[(*VertexBufferIndex)++] = Color.G;
		VertexBuffer[(*VertexBufferIndex)++] = Color.B;
		VertexBuffer[(*VertexBufferIndex)++] = Color.A;
	}
	else
	{
		v3 A = Triangle.A;
		v3 B = Triangle.B;
		v3 C = Triangle.C;

		v3 D = A + 0.5f * (B-A);
		v3 E = B + 0.5f * (C-B);
		v3 F = C + 0.5f * (A-C);

		triangle T1 = {A, D, F};
		triangle T2 = {D, B, E};
		triangle T3 = {F, E, C};
		triangle T4 = {F, D, E};

		Decompose(T1, VertexBuffer, VertexBufferIndex, MaxLayers, CurrentLayer+1, Color);
		Decompose(T2, VertexBuffer, VertexBufferIndex, MaxLayers, CurrentLayer+1, Color);
		Decompose(T3, VertexBuffer, VertexBufferIndex, MaxLayers, CurrentLayer+1, Color);
		Decompose(T4, VertexBuffer, VertexBufferIndex, MaxLayers, CurrentLayer+1, Color);
	}
}

internal entity *
AddEntity(game_state *GameState)
{
	entity *Result = &GameState->Entities[GameState->EntityCount++];

	return Result;
}

internal void
SetOldData(game_state *GameState)
{
	GameState->Camera.OldBases = GameState->Camera.Bases;
	GameState->Camera.OldPos = GameState->Camera.Pos;

	for(uint32_t EntityIndex = 0;
		EntityIndex < GameState->EntityCount;
		++EntityIndex)
	{
		entity *Entity = &GameState->Entities[EntityIndex];
		for(uint32_t EntityVertexIndex = 0;
			EntityVertexIndex < Entity->NumVertices;
			++EntityVertexIndex)
		{
			Entity->OldVertices[EntityVertexIndex] = Entity->Vertices[EntityVertexIndex];
		}
	}
}

internal void
SetCamera(camera *Camera, entity *Entity)
{
	Camera->Pos = Camera->Distance * Entity->Vertices[ENTITY_VERTEX_CENTER];

	v3 EntityCenterProjected = Normalize(Project(Entity->Vertices[ENTITY_VERTEX_CENTER], Camera->Bases.Up));
	float AngleToRotateAboutUp = Angle(-Camera->Bases.Forward, EntityCenterProjected);
	float EntityCenterProjectedDotCameraRight = Dot(EntityCenterProjected, Camera->Bases.Right);
	bool IsEntityCenterOnLeftSide = (EntityCenterProjectedDotCameraRight < 0);
	if(IsEntityCenterOnLeftSide)
	{
		AngleToRotateAboutUp = -AngleToRotateAboutUp;
	}
	RotateNormalize(&Camera->Bases.Forward, Camera->Bases.Up, AngleToRotateAboutUp);
	RotateNormalize(&Camera->Bases.Right, Camera->Bases.Up, AngleToRotateAboutUp);

	float AngleToRotateAboutRight = Angle(-Camera->Bases.Forward, Entity->Vertices[ENTITY_VERTEX_CENTER]);
	float EntityCenterDotCameraUp = Dot(Entity->Vertices[ENTITY_VERTEX_CENTER], Camera->Bases.Up);
	bool IsEntityCenterOnUpSide = (EntityCenterDotCameraUp > 0);
	if(IsEntityCenterOnUpSide)
	{
		AngleToRotateAboutRight = -AngleToRotateAboutRight;
	}
	RotateNormalize(&Camera->Bases.Forward, Camera->Bases.Right, AngleToRotateAboutRight);
	RotateNormalize(&Camera->Bases.Up, Camera->Bases.Right, AngleToRotateAboutRight);

	Assert(!isnan(Camera->Bases.Forward.X));
}

internal void
RotateEntity(entity *Entity, float RotateAngle, float dt)
{
	RotateNormalize(&Entity->RightAxis, Entity->Vertices[ENTITY_VERTEX_CENTER], RotateAngle * dt);
	for(uint32_t EntityVertexIndex = ENTITY_VERTEX_AFTER_CENTER;
		EntityVertexIndex < Entity->NumVertices;
		++EntityVertexIndex)
	{
		RotateNormalize(&Entity->Vertices[EntityVertexIndex], Entity->Vertices[ENTITY_VERTEX_CENTER], RotateAngle * dt);
	}
}

internal void
MoveEntity(entity *Entity, axis_angle Acceleration, float dt)
{
	// 0.5f*a*t^2 + v*t + p
	{
		quaternion AccelerationQuat = Normalize(Quaternion(Acceleration.Axis, Acceleration.Angle * dt / 20.0f));
		Entity->Velocity = Normalize(AccelerationQuat * Entity->Velocity);

		quaternion EntityDelta = Entity->Velocity;
		//quaternion EntityDelta = Normalize(Slerp(IdentityQuat(), Entity->Velocity, dt));

		RotateNormalize(&Entity->RightAxis, EntityDelta);
		for(uint32_t EntityVertexIndex = 0;
			EntityVertexIndex < Entity->NumVertices;
			++EntityVertexIndex)
		{
			RotateNormalize(&Entity->Vertices[EntityVertexIndex], EntityDelta);
		}

		Assert(!isnan(Entity->Vertices[ENTITY_VERTEX_CENTER].X));
	}
}

int
WinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		int nCmdShow)
{
	char AppName[] = "Asteroids";

	MMRESULT SetSleepGranularityResult = timeBeginPeriod(1);
	if(SetSleepGranularityResult == TIMERR_NOCANDO)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	LARGE_INTEGER LargeInteger;
	QueryPerformanceFrequency(&LargeInteger);
	GlobalQueryPerformanceFrequency = LargeInteger.QuadPart;

	GlobalStartCounter = GetCounter();

	WNDCLASS WindowClass = {};
	WindowClass.style = CS_OWNDC;
	WindowClass.lpfnWndProc = (WNDPROC)MainWindowProcedure;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszMenuName = AppName;
	WindowClass.lpszClassName = AppName;

	if(!RegisterClass(&WindowClass))
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	int WindowWidth = 1280;
	int WindowHeight = 720;
	float WindowAspectRatio = (float)WindowWidth / (float)WindowHeight;

	HWND DummyWindow = CreateWindow(AppName,
									"Asteroids",
									WS_OVERLAPPEDWINDOW,
									CW_USEDEFAULT,
									CW_USEDEFAULT,
									WindowWidth,
									WindowHeight,
									NULL,
									NULL,
									hInstance,
									NULL);

	// NOTE: Using the DummyWindow to my advantage here to get Monitor Resolution before creating the real window
	HMONITOR Monitor = MonitorFromWindow(DummyWindow, MONITOR_DEFAULTTONEAREST);
	MONITORINFO MonitorInfo;
	MonitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(Monitor, &MonitorInfo);
	int MonitorWidth = MonitorInfo.rcMonitor.right - MonitorInfo.rcMonitor.left;
	int MonitorHeight = MonitorInfo.rcMonitor.bottom - MonitorInfo.rcMonitor.top;

	if(!DummyWindow)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	HDC DummyDeviceContext = GetDC(DummyWindow);

	PIXELFORMATDESCRIPTOR DummyPixelFormatDescriptor;
	DummyPixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	DummyPixelFormatDescriptor.nVersion = 1;
	DummyPixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	DummyPixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	DummyPixelFormatDescriptor.cColorBits = 32;
	DummyPixelFormatDescriptor.cDepthBits = 24;
	DummyPixelFormatDescriptor.cStencilBits = 8;

	int DummyPixelFormat = ChoosePixelFormat(DummyDeviceContext, &DummyPixelFormatDescriptor);

	if(DummyPixelFormat == 0)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	if(SetPixelFormat(DummyDeviceContext, DummyPixelFormat, &DummyPixelFormatDescriptor) == FALSE)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	HGLRC DummyRenderingContext = wglCreateContext(DummyDeviceContext);
	if(DummyRenderingContext == 0)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	wglMakeCurrent(DummyDeviceContext, DummyRenderingContext);

	InitializeOpenGLFunctions();

	if(!DestroyWindow(DummyWindow))
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	ReleaseDC(DummyWindow, DummyDeviceContext);

	int WindowX = (MonitorWidth - WindowWidth) / 2;
	int WindowY = (MonitorHeight - WindowHeight) / 2;
	GlobalWindow = CreateWindow(AppName,
								"Asteroids",
								WS_OVERLAPPEDWINDOW,
								WindowX,
								WindowY,
								WindowWidth,
								WindowHeight,
								NULL,
								NULL,
								hInstance,
								NULL);

	GlobalDeviceContext = GetDC(GlobalWindow);
	if(!GlobalDeviceContext)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	const int PixelFormatAttributeList[] = 
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int PixelFormat;
	UINT NumFormats;
	wglChoosePixelFormatARB(GlobalDeviceContext, PixelFormatAttributeList, NULL, 1, &PixelFormat, &NumFormats);

	if(SetPixelFormat(GlobalDeviceContext, PixelFormat, NULL) == FALSE)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	const int ContextAttributeList[] = 
	{
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		0
	};

	GlobalRenderingContext = wglCreateContextAttribsARB(GlobalDeviceContext, NULL, ContextAttributeList);
	if(GlobalRenderingContext == 0)
	{
		// TODO: Logging
		Assert(false);
		return FALSE;
	}

	wglMakeCurrent(GlobalDeviceContext, GlobalRenderingContext);

	wglSwapIntervalEXT(1);

	ShowWindow(GlobalWindow, SW_SHOW);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const uint32_t BUTTON_ROTATE_LEFT = 0;
	const uint32_t BUTTON_ROTATE_RIGHT = 1;
	const uint32_t BUTTON_ACCELERATE = 2;
	const uint32_t BUTTON_SHOOT = 3;
	game_button Buttons[4];
	{
		for(uint8_t ButtonIndex = 0;
			ButtonIndex < ArrayCount(Buttons);
			++ButtonIndex)
		{
			Buttons[ButtonIndex].IsDown = false;
			Buttons[ButtonIndex].IsPressed = false;
		}
	}

	game_state GameState = {};
	AddEntity(&GameState); // NULL ENTITY

	entity *Player = AddEntity(&GameState);
	const float PLAYER_ROTATE_VELOCITY = DegreesToRadians(325.0f);
	const float PLAYER_MOVEMENT_ACCELERATION = DegreesToRadians(100.0f);
	const uint32_t PLAYER_TOP = 1;
	const uint32_t PLAYER_BOTTOM_LEFT = 2;
	const uint32_t PLAYER_BOTTOM_RIGHT = 3;
	const uint32_t PLAYER_UPPER_LEFT = 4;
	const uint32_t PLAYER_UPPER_RIGHT = 5;
	{
		Player->Type = ENTITY_TYPE_PLAYER;
		Player->RightAxis = V3(1.0f, 0.0f, 0.0f);
		Player->Velocity = Quaternion(Player->RightAxis, 0.0f);
		Player->NumVertices = 6;

		float HalfWidth = 1.5f;
		float HalfHeight = 3.0f;
		float UpperPercents = 0.8f;

		v2 SpherePlayerCenter = {0.0f, 90.0f};
		v2 SphereBl = {-HalfHeight, 90.0f - HalfWidth};
		v2 SphereBr = {-HalfHeight, 90.0f + HalfWidth};
		v2 SphereTo = {HalfHeight, 90.0f};

		Player->Vertices[ENTITY_VERTEX_CENTER] = SphereToCartesian(DegreesToRadians(SpherePlayerCenter));
		Player->Vertices[PLAYER_TOP] = SphereToCartesian(DegreesToRadians(SphereTo));
		Player->Vertices[PLAYER_BOTTOM_LEFT] = SphereToCartesian(DegreesToRadians(SphereBl));
		Player->Vertices[PLAYER_BOTTOM_RIGHT] = SphereToCartesian(DegreesToRadians(SphereBr));

		float PlayerAngle = Half_Pi32;
		Rotate(&Player->Vertices[PLAYER_TOP], Player->Vertices[ENTITY_VERTEX_CENTER], PlayerAngle);
		Rotate(&Player->Vertices[PLAYER_BOTTOM_LEFT], Player->Vertices[ENTITY_VERTEX_CENTER], PlayerAngle);
		Rotate(&Player->Vertices[PLAYER_BOTTOM_RIGHT], Player->Vertices[ENTITY_VERTEX_CENTER], PlayerAngle);

		Player->Vertices[PLAYER_UPPER_LEFT] = 
			Normalize(Lerp(Player->Vertices[PLAYER_TOP], Player->Vertices[PLAYER_BOTTOM_LEFT], UpperPercents));
		Player->Vertices[PLAYER_UPPER_RIGHT] = 
			Normalize(Lerp(Player->Vertices[PLAYER_TOP], Player->Vertices[PLAYER_BOTTOM_RIGHT], UpperPercents));
	}

	camera *Camera = &GameState.Camera;
	{
		Camera->Distance = 17.5f;
		Camera->Bases.Forward = V3(0, 0, -1);
		Camera->Bases.Right = V3(1, 0, 0);
		Camera->Bases.Up = V3(0, 1, 0);
		SetCamera(Camera, Player);
	}

	SetOldData(&GameState);

	mat4 Projection = {};
	{
		frustrum ProjectionFrustrum = {};
		ProjectionFrustrum = CreateFrustrum(45.0f, WindowAspectRatio, 0.1f, 100.0f);
		SetToPerspective(&Projection, ProjectionFrustrum);
		Transpose(&Projection);
	}

	render_objects Shape3RenderObjects = {};
	{
		read_file_result Shape3VertexShaderFile = ReadEntireFile("../src/shader_shape3_vertex.cpp");
		read_file_result Shape3FragmentShaderFile = ReadEntireFile("../src/shader_shape3_fragment.cpp");
		Shape3RenderObjects.ShaderProgram = CreateShaderProgram((GLchar *)Shape3VertexShaderFile.Contents, 
																(GLchar *)Shape3FragmentShaderFile.Contents);
		FreeFileMemory(Shape3VertexShaderFile.Contents);
		FreeFileMemory(Shape3FragmentShaderFile.Contents);

		GLint Shape3ProjectionLoc = glGetUniformLocation(Shape3RenderObjects.ShaderProgram, "Projection");
		glUseProgram(Shape3RenderObjects.ShaderProgram);
		glUniformMatrix4fv(Shape3ProjectionLoc, 1, GL_FALSE, Projection.Elements);

		glGenBuffers(1, &Shape3RenderObjects.VertexBuffer);
		glGenVertexArrays(1, &Shape3RenderObjects.VertexArray);
		glBindVertexArray(Shape3RenderObjects.VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, Shape3RenderObjects.VertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	float SphereRadius = 8.0f;
	GLint SphereNumVertices = 0;
	render_objects SphereRenderObjects = {};
	{
		read_file_result SphereVertexShaderFile = ReadEntireFile("../src/shader_sphere_vertex.cpp");
		read_file_result SphereFragmentShaderFile = ReadEntireFile("../src/shader_sphere_fragment.cpp");
		SphereRenderObjects.ShaderProgram = CreateShaderProgram((GLchar *)SphereVertexShaderFile.Contents, 
																(GLchar *)SphereFragmentShaderFile.Contents);
		FreeFileMemory(SphereVertexShaderFile.Contents);
		FreeFileMemory(SphereFragmentShaderFile.Contents);

		mat4 SphereModelScale = {};
		Scale(&SphereModelScale, SphereRadius);
		mat4 SphereModel = SphereModelScale;
		Transpose(&SphereModel);

		GLint SphereModelLoc = glGetUniformLocation(SphereRenderObjects.ShaderProgram, "Model");
		GLint ProjectionLoc = glGetUniformLocation(SphereRenderObjects.ShaderProgram, "Projection");
		glUseProgram(SphereRenderObjects.ShaderProgram);
		glUniformMatrix4fv(SphereModelLoc, 1, GL_FALSE, SphereModel.Elements);
		glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, Projection.Elements);

		glGenBuffers(1, &SphereRenderObjects.VertexBuffer);
		glGenVertexArrays(1, &SphereRenderObjects.VertexArray);
		glBindVertexArray(SphereRenderObjects.VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, SphereRenderObjects.VertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid *)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	// SPHERE
	{
		v4 Color = {0.2f, 0.2f, 0.2f, 1.0f};

		v3 Fr = {0.0f, 0.0f, 1.0f};
		v3 Ba = {0.0f, 0.0f, -1.0f};
		v3 Le = {-1.0f, 0.0f, 0.0f};
		v3 Ri = {1.0f, 0.0f, 0.0f};
		v3 Bo = {0.0f, -1.0f, 0.0f};
		v3 To = {0.0f, 1.0f, 0.0f};

		// top faces
		triangle Face1 = {Fr, Ri, To};
		triangle Face2 = {Ri, Ba, To};
		triangle Face3 = {Ba, Le, To};
		triangle Face4 = {Le, Fr, To};

		// bottom faces
		triangle Face5 = {Fr, Bo, Ri};
		triangle Face6 = {Ri, Bo, Ba};
		triangle Face7 = {Ba, Bo, Le};
		triangle Face8 = {Le, Bo, Fr};

		const uint8_t NumFaces = 8;
		const uint8_t NumLayers = 2;
		const uint8_t NumDataPerVertex = 10;
		const uint16_t NumTriangles = NumFaces * (4*4);//(uint16_t)(powf(4, (float)NumLayers));
		const uint16_t NumVertices = NumTriangles * 3;
		SphereNumVertices = NumVertices;
		const uint32_t SizeOfVertexBuffer = NumVertices * NumDataPerVertex;
		GLfloat VertexBuffer[SizeOfVertexBuffer];
		uint32_t VertexBufferIndex = 0;
		Decompose(Face1, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face2, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face3, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face4, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face5, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face6, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face7, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Decompose(Face8, VertexBuffer, &VertexBufferIndex, NumLayers, 0, Color);
		Assert(VertexBufferIndex == SizeOfVertexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, SphereRenderObjects.VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBuffer), VertexBuffer, GL_STATIC_DRAW);
	}

	uint32_t TicksPerSecond = 25;
	uint32_t SkipTicks = 1000 / TicksPerSecond;
	uint32_t MaxFrameSkip = 5;
	float dt = 1.0f / TicksPerSecond;

	uint32_t NextGameTick = GetMillisecond();

	while(GlobalRunning)
	{
		uint32_t Loops = 0;
		while(GetMillisecond() > NextGameTick && Loops < MaxFrameSkip)
		{
			if(Loops != 0)
			{
				OutputDebugString("Missed Frame!\n");
			}

			MSG Message;
			while(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE) == TRUE)
			{
				switch(Message.message)
				{
					case WM_KEYDOWN:
					{
						switch(Message.wParam)
						{
							case VK_LEFT:
							{
								Buttons[BUTTON_ROTATE_LEFT].IsDown = true;
							} break;

							case VK_RIGHT:
							{
								Buttons[BUTTON_ROTATE_RIGHT].IsDown = true;
							} break;

							case VK_UP:
							{
								Buttons[BUTTON_ACCELERATE].IsDown = true;
							} break;

							case VK_SPACE:
							{
								Buttons[BUTTON_SHOOT].IsDown = true;
							} break;

							default:
							{
							} break;
						}
					} break;

					case WM_KEYUP:
					{
						switch(Message.wParam)
						{
							case VK_LEFT:
							{
								Buttons[BUTTON_ROTATE_LEFT].IsDown = false;
							} break;

							case VK_RIGHT:
							{
								Buttons[BUTTON_ROTATE_RIGHT].IsDown = false;
							} break;

							case VK_UP:
							{
								Buttons[BUTTON_ACCELERATE].IsDown = false;
							} break;

							case VK_SPACE:
							{
								Buttons[BUTTON_SHOOT].IsDown = false;
							} break;

							default:
							{
							} break;
						}
					} break;

					default:
					{
						TranslateMessage(&Message);
						DispatchMessage(&Message);
					} break;
				}
			}

			SetOldData(&GameState);

			float PlayerRotateAngle = 0;
			float PlayerAccelerationAngle = 0;

			if(Buttons[BUTTON_ROTATE_LEFT].IsDown)
			{
				PlayerRotateAngle += PLAYER_ROTATE_VELOCITY;
			}

			if(Buttons[BUTTON_ROTATE_RIGHT].IsDown)
			{
				PlayerRotateAngle -= PLAYER_ROTATE_VELOCITY;
			}

			if(Buttons[BUTTON_ACCELERATE].IsDown)
			{
				PlayerAccelerationAngle -= PLAYER_MOVEMENT_ACCELERATION;
			}

			RotateEntity(Player, PlayerRotateAngle, dt);
			axis_angle PlayerAcceleration = {Player->RightAxis, PlayerAccelerationAngle};
			MoveEntity(Player, PlayerAcceleration, dt);
			SetCamera(Camera, Player);

			NextGameTick += SkipTicks;
			++Loops;
		}

		float Interpolation = (float)(GetMillisecond() + SkipTicks - NextGameTick) / (float)(SkipTicks);
		Assert(Interpolation >= 0.0f);
		if(Interpolation > 1.0f)
		{
			Interpolation = 1.0f;
		}

#define MAX_NUM_LINE_DATA 32
		line_data LineDatas[MAX_NUM_LINE_DATA];
		uint32_t LineDataCount = 0;

		glUseProgram(SphereRenderObjects.ShaderProgram);
		for(uint32_t EntityIndex = 1;
			EntityIndex < GameState.EntityCount;
			++EntityIndex)
		{
			entity *Entity = &GameState.Entities[EntityIndex];
			uint32_t LineDataAdded = 0;

			switch(Entity->Type)
			{
				case ENTITY_TYPE_PLAYER:
				{
					uint32_t LineDataIndex = LineDataCount;

					LineDatas[LineDataIndex].Line.A = Normalize(Lerp(Entity->OldVertices[PLAYER_TOP], 
																	 Entity->Vertices[PLAYER_TOP], Interpolation));
					LineDatas[LineDataIndex].Line.B = Normalize(Lerp(Entity->OldVertices[PLAYER_BOTTOM_LEFT], 
																	 Entity->Vertices[PLAYER_BOTTOM_LEFT], Interpolation));
					LineDatas[LineDataIndex].ACrossB = Normalize(Cross(LineDatas[LineDataIndex].Line));
					LineDatas[LineDataIndex].ADotB = Dot(LineDatas[LineDataIndex].Line);
					++LineDataIndex;

					LineDatas[LineDataIndex].Line.A = Normalize(Lerp(Entity->OldVertices[PLAYER_TOP], 
																	 Entity->Vertices[PLAYER_TOP], Interpolation));
					LineDatas[LineDataIndex].Line.B = Normalize(Lerp(Entity->OldVertices[PLAYER_BOTTOM_RIGHT], 
																	 Entity->Vertices[PLAYER_BOTTOM_RIGHT], Interpolation));
					LineDatas[LineDataIndex].ACrossB = Normalize(Cross(LineDatas[LineDataIndex].Line));
					LineDatas[LineDataIndex].ADotB = Dot(LineDatas[LineDataIndex].Line);
					++LineDataIndex;

					LineDatas[LineDataIndex].Line.A = Normalize(Lerp(Entity->OldVertices[PLAYER_UPPER_LEFT], 
																	 Entity->Vertices[PLAYER_UPPER_LEFT], Interpolation));
					LineDatas[LineDataIndex].Line.B = Normalize(Lerp(Entity->OldVertices[PLAYER_UPPER_RIGHT], 
																	 Entity->Vertices[PLAYER_UPPER_RIGHT], Interpolation));
					LineDatas[LineDataIndex].ACrossB = Normalize(Cross(LineDatas[LineDataIndex].Line));
					LineDatas[LineDataIndex].ADotB = Dot(LineDatas[LineDataIndex].Line);
					++LineDataIndex;

					LineDataAdded = LineDataIndex;
				} break;

				case ENTITY_TYPE_ASTEROID:
				{
					for(uint32_t EntityVertexIndex = 0;
						EntityVertexIndex < Entity->NumVertices;
						++EntityVertexIndex)
					{
						uint32_t EntityNextVertexIndex = (EntityVertexIndex != (Entity->NumVertices - 1)) ? EntityVertexIndex : 0;
						LineDatas[LineDataCount + LineDataAdded].Line.A = Normalize(Lerp(Entity->OldVertices[EntityVertexIndex], 
																						 Entity->Vertices[EntityVertexIndex], 
																						 Interpolation));
						LineDatas[LineDataCount + LineDataAdded].Line.B = Normalize(Lerp(Entity->OldVertices[EntityNextVertexIndex], 
																						 Entity->Vertices[EntityNextVertexIndex], 
																						 Interpolation));
						LineDatas[LineDataCount + LineDataAdded].ACrossB = Normalize(Cross(LineDatas[LineDataCount].Line));
						LineDatas[LineDataCount + LineDataAdded].ADotB = Dot(LineDatas[LineDataCount].Line);
						++LineDataAdded;
					}
				} break;
			}

			char Buffer[32];
			for(uint32_t LineDataIndex = LineDataCount;
				LineDataIndex < (LineDataCount + LineDataAdded);
				++LineDataIndex)
			{
				line_data LineData = LineDatas[LineDataIndex];

				sprintf_s(Buffer, "LineDatas[%d].A", LineDataIndex);
				GLint ALocation = glGetUniformLocation(SphereRenderObjects.ShaderProgram, (const GLchar *)Buffer);
				sprintf_s(Buffer, "LineDatas[%d].ACrossB", LineDataIndex);
				GLint ACrossBLocation = glGetUniformLocation(SphereRenderObjects.ShaderProgram, (const GLchar *)Buffer);
				sprintf_s(Buffer, "LineDatas[%d].ADotB", LineDataIndex);
				GLint ADotBLocation = glGetUniformLocation(SphereRenderObjects.ShaderProgram, (const GLchar *)Buffer);

				Assert(ALocation > 0);
				Assert(ACrossBLocation > 0);
				Assert(ADotBLocation > 0);

				glUniform3f(ALocation, LineData.Line.A.X, LineData.Line.A.Y, LineData.Line.A.Z);
				glUniform3f(ACrossBLocation, LineData.ACrossB.X, LineData.ACrossB.Y, LineData.ACrossB.Z);
				glUniform1f(ADotBLocation, LineData.ADotB);
			}

			LineDataCount += LineDataAdded;
		}

		// calculate and send View matrix
		{ 
			v3 CameraRenderPos = Lerp(Camera->OldPos, Camera->Pos, Interpolation);
			v3 CameraRenderForward = Lerp(Camera->OldBases.Forward, Camera->Bases.Forward, Interpolation);
			v3 CameraRenderRight = Lerp(Camera->OldBases.Right, Camera->Bases.Right, Interpolation);
			v3 CameraRenderUp = Lerp(Camera->OldBases.Up, Camera->Bases.Up, Interpolation);
			mat4 ViewMatrix;
			LookAt(&ViewMatrix, CameraRenderPos, CameraRenderForward, CameraRenderRight, CameraRenderUp);
			Transpose(&ViewMatrix);

			GLint SphereViewLoc = glGetUniformLocation(SphereRenderObjects.ShaderProgram, "View");
			GLint SphereViewPosLoc = glGetUniformLocation(SphereRenderObjects.ShaderProgram, "ViewPos");
			glUseProgram(SphereRenderObjects.ShaderProgram);
			glUniformMatrix4fv(SphereViewLoc, 1, GL_FALSE, ViewMatrix.Elements);
			glUniform3f(SphereViewPosLoc, CameraRenderPos.X, CameraRenderPos.Y, CameraRenderPos.Z);

			GLint Shape3ViewLoc = glGetUniformLocation(SphereRenderObjects.ShaderProgram, "View");
			glUseProgram(Shape3RenderObjects.ShaderProgram);
			glUniformMatrix4fv(Shape3ViewLoc, 1, GL_FALSE, ViewMatrix.Elements);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		{
			glUseProgram(SphereRenderObjects.ShaderProgram);
			glBindVertexArray(SphereRenderObjects.VertexArray);
			glDrawArrays(GL_TRIANGLES, 0, SphereNumVertices);
			glBindVertexArray(0);

#if 0
			glDisable(GL_DEPTH_TEST);
			DrawLine(&Shape3RenderObjects, V3(0, 0, 0), SphereRadius * -Player->RightAxis, V4(1.0f, 0.0f, 0.0f, 0.75f));
			v3 PlayerMovementAxis = GetAxis_(Player->Velocity);
			DrawLine(&Shape3RenderObjects, V3(0, 0, 0), SphereRadius * PlayerMovementAxis, V4(0.0f, 1.0f, 0.0f, 0.75f));
			glEnable(GL_DEPTH_TEST);
#endif
		}

		SwapBuffers(GlobalDeviceContext);
	}

	return 0;
}
