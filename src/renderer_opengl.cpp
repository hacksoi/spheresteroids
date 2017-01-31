#ifndef RENDERER_OPENGL_CPP
#define RENDERER_OPENGL_CPP

global_variable PFNGLCLEARPROC glClear;
global_variable PFNGLENABLEPROC glEnable;
global_variable PFNGLENABLEPROC glDisable;
global_variable PFNGLVIEWPORTPROC glViewport;
global_variable PFNGLGETSTRINGPROC glGetString;
global_variable PFNGLUNIFORM3FPROC glUniform3f;
global_variable PFNGLUNIFORM1FPROC glUniform1f;
global_variable PFNGLBLENDFUNCPROC glBlendFunc;
global_variable PFNGLBINDBUFFERPROC glBindBuffer;
global_variable PFNGLBUFFERDATAPROC glBufferData;
global_variable PFNGLDRAWARRAYSPROC glDrawArrays;
global_variable PFNGLUSEPROGRAMPROC glUseProgram;
global_variable PFNGLCLEARCOLORPROC glClearColor;
global_variable PFNGLGENBUFFERSPROC glGenBuffers;
global_variable PFNGLGETSHADERIVPROC glGetShaderiv;
global_variable PFNGLLINKPROGRAMPROC glLinkProgram;
global_variable PFNGLATTACHSHADERPROC glAttachShader;
global_variable PFNGLGETPROGRAMIVPROC glGetProgramiv;
global_variable PFNGLCREATESHADERPROC glCreateShader;
global_variable PFNGLSHADERSOURCEPROC glShaderSource;
global_variable PFNGLDELETESHADERPROC glDeleteShader;
global_variable PFNGLCOMPILESHADERPROC glCompileShader;
global_variable PFNGLCREATEPROGRAMPROC glCreateProgram;
global_variable PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
global_variable PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
global_variable PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
global_variable PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
global_variable PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
global_variable PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
global_variable PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
global_variable PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

// unsorted
#if 0
global_variable PFN_PROC gl_;
#endif

global_variable PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
global_variable PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
global_variable PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

internal void
InitializeOpenGLFunctions()
{
	glClear = (PFNGLCLEARPROC)wglGetProcAddress("glClear");
	glEnable = (PFNGLENABLEPROC)wglGetProcAddress("glEnable");
	glDisable = (PFNGLENABLEPROC)wglGetProcAddress("glDisable");
	glViewport = (PFNGLVIEWPORTPROC)wglGetProcAddress("glViewport");
	glGetString = (PFNGLGETSTRINGPROC)wglGetProcAddress("glGetString");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	glBlendFunc = (PFNGLBLENDFUNCPROC)wglGetProcAddress("glBlendFunc");
	glClearColor = (PFNGLCLEARCOLORPROC)wglGetProcAddress("glClearColor");
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glDrawArrays = (PFNGLDRAWARRAYSPROC)wglGetProcAddress("glDrawArrays");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");

	// unsorted
#if 0
	gl_ = (PFN_PROC)wglGetProcAddress("gl_");
#endif

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
}

struct render_objects
{
	GLuint ShaderProgram;
	GLuint VertexBuffer;
	GLuint VertexArray;
};

internal GLuint
CreateShaderProgram(const char *VertexShaderSource, 
					const char *FragmentShaderSource)
{
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);

	glCompileShader(VertexShader);
	glCompileShader(FragmentShader);

	GLint VShaderCompileStatus;
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &VShaderCompileStatus);
	if(!VShaderCompileStatus)
	{
		GLchar InfoLog[512];
		glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
		DEBUGPrintf("\nERROR COMPILING VERTEX SHADER:\n%s", InfoLog);

		Assert(false);
	}

	GLint FShaderCompileStatus;
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &FShaderCompileStatus);
	if(!FShaderCompileStatus)
	{
		GLchar InfoLog[512];
		glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
		DEBUGPrintf("\nERROR COMPILING FRAGMENT SHADER:\n%s", InfoLog);

		Assert(false);
	}

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	GLint ShaderProgramLinkStatus;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ShaderProgramLinkStatus);
	if(!ShaderProgramLinkStatus)
	{
		GLchar InfoLog[512];
		glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
		DEBUGPrintf("\nRROR LINKING SHADER PROGRAM:\n%s", InfoLog);

		Assert(false);
	}
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return ShaderProgram;
}

internal void
DrawLine(render_objects *RenderObjects, v3 A, v3 B, v4 Color)
{
	GLfloat Vertices[] = 
	{
		A.X, A.Y, A.Z, Color.R, Color.G, Color.B, Color.A, 
		B.X, B.Y, B.Z, Color.R, Color.G, Color.B, Color.A
	};

	glBindBuffer(GL_ARRAY_BUFFER, RenderObjects->VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), (const GLvoid *)Vertices, GL_STREAM_DRAW);

	glUseProgram(RenderObjects->ShaderProgram);
	glBindVertexArray(RenderObjects->VertexArray);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

#endif
