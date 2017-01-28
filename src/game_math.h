#ifndef GAME_MATH_HEADER
#define GAME_MATH_HEADER

#define Pi32 ((float)M_PI)
#define Half_Pi32 (Pi32/2.0f)
#define Two_Pi32 (2.0f*PI_32)

union v2
{
	struct
	{
		float X, Y;
	};

	struct
	{
		float Theta, Phi;
	};

	struct
	{
		float Width, Height;
	};
};

union v3
{
	struct
	{
		float X, Y, Z;
	};

	struct
	{
		v2 XY;
		float _Z;
	};

	struct
	{
		float R, G, B;
	};
};

union v4
{
	struct
	{
		float X, Y, Z, W;
	};

	struct
	{
		float R, G, B, A;
	};
};

struct axis_angle
{
	v3 Axis;
	float Angle;
};

struct quaternion
{
	float X, Y, Z, W;
};

#if 0
struct sphere_motion
{
	v3 Axis;
	float Rotation;
};
#endif

struct plane
{
	v3 BaseA, BaseB;
};

struct line3
{
	v3 A, B;
};

union mat4
{
	float Elements[16];
	struct
	{
		float m00, m01, m02, m03,
			  m10, m11, m12, m13,
			  m20, m21, m22, m23,
			  m30, m31, m32, m33;
	};
};

struct frustrum
{
	float Left, Right;
	float Bottom, Top;
	float Near, Far;

	float FieldOfView, AspectRatio;
};

struct rectangle
{
	v2 Min, Max;
};

struct rectangle_corners
{
	v2 Bl, Br, Tr, Tl;
};

struct circle
{
	v2 Pos;
	float Radius;
};

union triangle
{
	struct
	{
		v3 A, B, C;
	};
	struct
	{
		float X1, Y1, Z1,
			  X2, Y2, Z2,
			  X3, Y3, Z3;
	};

};

#endif
