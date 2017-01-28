#include "game_math.h"

inline void
Swap(float *X, float *Y)
{
	float Temp = *X;
	*X = *Y;
	*Y = Temp;
}

inline float
Square(float X)
{
	float Result = X*X;

	return Result;
}

inline float
Clamp(float X, float Min, float Max)
{
	float Result = X;
	if(Result < Min)
	{
		Result = Min;
	}
	else if(Result > Max)
	{
		Result = Max;
	}

	return Result;
}

inline float
Sin(float X)
{
	float Result = sinf(X);

	return Result;
}

inline float
Cos(float X)
{
	float Result = cosf(X);

	return Result;
}

inline float
Acos(float X)
{
	X = Clamp(X, -1.0f, 1.0f);
	float Result = acosf(X);

	return Result;
}

inline float
Sqrt(float X)
{
	Assert(X >= 0.0f);
	float Result = sqrtf(X);

	return Result;
}

inline v2
V2(float X, float Y)
{
	v2 Result = {X, Y};

	return Result;
}

inline v3
V3(float X, float Y, float Z)
{
	v3 Result = {X, Y, Z};

	return Result;
}

inline v4
V4(float X, float Y, float Z, float W)
{
	v4 Result = {X, Y, Z, W};

	return Result;
}

inline quaternion
Quaternion(float X, float Y, float Z, float W)
{
	quaternion Result = {X, Y, Z, W};

	return Result;
}

inline quaternion
Quaternion(v3 Axis, float Angle)
{
	float SineHalfTheta = sinf(Angle / 2.0f);
	quaternion Result = 
	{
		Axis.X * SineHalfTheta,
		Axis.Y * SineHalfTheta,
		Axis.Z * SineHalfTheta,
		cosf(Angle / 2.0f)
	};

	return Result;
}

inline quaternion
Quaternion(axis_angle A)
{
	quaternion Result = Quaternion(A.Axis, A.Angle);

	return Result;
}

inline quaternion
IdentityQuat()
{
	quaternion Result = {0.0f, 0.0f, 0.0f, 1.0f};

	return Result;
}

inline v2
operator+(v2 A, v2 B)
{
	v2 Result = 
	{
		A.X + B.X, 
		A.Y + B.Y
	};

	return Result;
}

inline v3
operator+(v3 A, v3 B)
{
	v3 Result = 
	{
		A.X + B.X, 
		A.Y + B.Y,
		A.Z + B.Z
	};

	return Result;
}

inline v4
operator+(v4 A, v4 B)
{
	v4 Result = 
	{
		A.X + B.X, 
		A.Y + B.Y,
		A.Z + B.Z,
		A.W + B.W
	};

	return Result;
}

inline quaternion
operator+(quaternion A, quaternion B)
{
	quaternion Result = 
	{
		A.X + B.X, 
		A.Y + B.Y,
		A.Z + B.Z,
		A.W + B.W
	};

	return Result;
}

inline v2 &
operator+=(v2 &A, v2 B)
{
	A.X += B.X;
	A.Y += B.Y;

	return A;
}

inline v2
operator-(v2 A, v2 B)
{
	v2 Result = 
	{
		A.X - B.X, 
		A.Y - B.Y
	};

	return Result;
}

inline v3
operator-(v3 A, v3 B)
{
	v3 Result = 
	{
		A.X - B.X, 
		A.Y - B.Y,
		A.Z - B.Z
	};

	return Result;
}

inline quaternion
operator-(quaternion A, quaternion B)
{
	quaternion Result = 
	{
		A.X - B.X, 
		A.Y - B.Y,
		A.Z - B.Z,
		A.W - B.W
	};

	return Result;
}

inline v3
operator-(v3 A)
{
	v3 Result = 
	{
		-A.X,
		-A.Y,
		-A.Z
	};

	return Result;
}

inline quaternion
operator-(quaternion A)
{
	quaternion Result = 
	{
		-A.X,
		-A.Y,
		-A.Z,
		-A.W
	};

	return Result;
}

inline v2
operator*(float B, v2 A)
{
	v2 Result = 
	{
		A.X * B, 
		A.Y * B 
	};

	return Result;
}

inline v3
operator*(float B, v3 A)
{
	v3 Result = 
	{
		A.X * B, 
		A.Y * B,
		A.Z * B
	};

	return Result;
}

inline quaternion
operator*(quaternion A, quaternion B)
{
	quaternion Result = 
	{
		(A.W * B.X) + (A.X * B.W) + (A.Y * B.Z) - (A.Z * B.Y),
		(A.W * B.Y) - (A.X * B.Z) + (A.Y * B.W) + (A.Z * B.X),
		(A.W * B.Z) + (A.X * B.Y) - (A.Y * B.X) + (A.Z * B.W),
		(A.W * B.W) - (A.X * B.X) - (A.Y * B.Y) - (A.Z * B.Z)
	};

	return Result;
}

inline quaternion
operator*(float B, quaternion A)
{
	quaternion Result = 
	{
		A.X * B, 
		A.Y * B,
		A.Z * B,
		A.W * B
	};

	return Result;
}

inline v2 &
operator*=(v2 &A, float B)
{
	A.X *= B;
	A.Y *= B;

	return A;
}

inline v3
Cross(v3 A, v3 B)
{
	v3 Result = 
	{
		A.Y*B.Z - A.Z*B.Y,
		A.Z*B.X - A.X*B.Z,
		A.X*B.Y - A.Y*B.X
	};

	return Result;
}

inline float
Dot(v2 A, v2 B)
{
	float Result = A.X*B.X + A.Y*B.Y;

	return Result;
}

inline float
Dot(v3 *A, v3 *B)
{
	float Result = A->X*B->X + A->Y*B->Y + A->Z*B->Z;

	return Result;
}

inline float
Dot(v3 A, v3 B)
{
	float Result = Dot(&A, &B);

	return Result;
}

inline float
Dot(quaternion *A, quaternion *B)
{
	float Result = A->X*B->X + A->Y*B->Y + A->Z*B->Z + A->W*B->W;

	return Result;
}

inline float
Dot(quaternion A, quaternion B)
{
	float Result = Dot(&A, &B);

	return Result;
}

inline float
Angle(v3 A, v3 B)
{
	float ADotB = Dot(A, B);
	float Result = Acos(ADotB);

	return Result;
}

inline float
LengthSq(v2 A)
{
	float Result = Dot(A, A);

	return Result;
}

inline float
LengthSq(v3 *A)
{
	float Result = Dot(A, A);

	return Result;
}

inline float
LengthSq(v3 A)
{
	float Result = LengthSq(&A);

	return Result;
}

inline float
Length(v2 A)
{
	float Result = sqrtf(LengthSq(A));

	return Result;
}

inline float
Length(v3 *A)
{
	float Result = sqrtf(LengthSq(A));

	return Result;
}

inline float
Length(v3 A)
{
	float Result = Length(&A);

	return Result;
}

inline float
Length(quaternion A)
{
	float Result = sqrtf((A.X * A.X) + 
						 (A.Y * A.Y) + 
						 (A.Z * A.Z) + 
						 (A.W * A.W));

	return Result;
}

inline void
SetLength(v3 *A, float NewLength)
{
	float OldLength = Length(A);
	Assert(OldLength != 0.0f);
	float Scale = NewLength / OldLength;

	A->X = Scale * A->X;
	A->Y = Scale * A->Y;
	A->Z = Scale * A->Z;
}

inline v3
SetLength(v3 A, float NewLength)
{
	SetLength(&A, NewLength);

	return A;
}

inline void
Normalize(v3 *A)
{
	SetLength(A, 1.0f);
}

inline v3
Normalize(v3 A)
{
	SetLength(&A, 1.0f);

	return A;
}

inline quaternion
Normalize(quaternion A)
{
	float Len = Length(A);
	Assert(Len != 0.0f);
	quaternion Result =
	{
		A.X / Len,
		A.Y / Len,
		A.Z / Len,
		A.W / Len
	};
	
	return Result;
}

inline quaternion 
Conjugate(quaternion A)
{
	quaternion Result = {-A.X, -A.Y, -A.Z, A.W};

	return Result;
}

inline float
GetAngle(quaternion A)
{
	float HalfAngle = Acos(A.W);
	float Result = 2.0f * HalfAngle;

	return Result;
}

//
// NOTE(nick): This doesn't return the EXACT axis and can cause subtle bugs.
//
inline v3
GetAxis_(quaternion A)
{
	v3 Result = {};

	float Divisor
#if 1
   	= Sqrt(1 - Square(A.W));
#else
	= Sin(GetAngle(A) / 2.0f);
#endif
	Result = 
	{
		A.X / Divisor,
		A.Y / Divisor,
		A.Z / Divisor
	};

	return Result;
}

inline quaternion
MulAngle(quaternion A, float B)
{
	Assert(false);
	quaternion Result = {};

	float Angle = GetAngle(A);
	if(Angle == 0.0f)
	{
		Result = A;
	}
	else
	{
		v3 Axis = Normalize(GetAxis_(A));
		Angle *= B;
		Result = Quaternion(Axis, Angle);
	}

	return Result;
}

inline v2
Lerp(v2 P0, v2 P1, float t)
{
	Assert(t <= 1.0f);
	v2 Result = P0 + t*(P1 - P0);

	return Result;
}

inline v3
Lerp(v3 P0, v3 P1, float t)
{
	Assert(t <= 1.0f);
	v3 Result = P0 + t*(P1 - P0);

	return Result;
}

inline quaternion
Lerp(quaternion P0, quaternion P1, float t)
{
	Assert(t <= 1.0f);
	quaternion Result = P0 + t*(P1 - P0);

	return Result;
}

//
// NOTE(nick): Copied and pasted from https://en.wikipedia.org/wiki/Slerp
//
inline quaternion 
Slerp(quaternion A, quaternion B, float t) {
	quaternion Result = {};

	float ADotB = Dot(A, B);
	float DotThreshold = 0.9995f;
	if (ADotB > DotThreshold) {
		// If the inputs are too close for comfort, linearly interpolate
		// and normalize the result.
		Result = Normalize(Lerp(A, B, t));
	}
	else
	{
		// If the dot product is negative, the quaternions
		// have opposite handed-ness and slerp won't take
		// the shorted path. Fix by reversing one quaternion.
		if (ADotB < 0.0f) {
			B = -B;
			ADotB = -ADotB;
		}

		ADotB = Clamp(ADotB, -1, 1); // Robustness: Stay within domain of acos()
		float ABAngle = Acos(ADotB); // ABAngle = angle between input vectors
		float ResultAngle = t * ABAngle; // ResultAngle = angle between v0 and result 

		quaternion BProjectedOnA = ADotB * A;
		quaternion C = Normalize(B - BProjectedOnA); // { A, C } is now an orthonormal basis

		Result = ((Cos(ResultAngle) * A) + (Sin(ResultAngle) * C));
	}

	return Result;
}

inline v3
Slerp(v3 P0, v3 P1, float t)
{
	// TODO: Fix this!
	Assert(false);

	Assert(t <= 1.0f);

	v3 Result;

	float Theta = Angle(P0, P1);
	if(Theta > 0.0f)
	{
		// NOTE: This will be very small if P0 and P1 are close to each other,
		// so maybe floating-point errors?
		float SineTheta = sinf(Theta);

		float CP0 = (sinf((1 - t) * Theta) / SineTheta);
		float CP1 = (sinf(t * Theta) / SineTheta);

		Result = (CP0 * P0) + (CP1 * P1);
	}
	else
	{
		Result = P0;
	}

	return Result;
}

inline v2
Rotate(v2 A, float Radians)
{
	float Cosine = cosf(Radians);
	float Sine = sinf(Radians);

	v2 Result = 
	{
		(A.X * Cosine - A.Y * Sine),
		(A.Y * Cosine + A.X * Sine)
	};

	return Result;
}

internal v3
RotateEuler(v3 A, v3 Axis, float Radians)
{
	float Cosine = cosf(Radians);
	float Sine = sinf(Radians);
	float OneMinusCosine = 1.0f - Cosine;

	v3 Result = 
	{
		(A.X * (Cosine + Square(Axis.X) * OneMinusCosine)) + 
			(A.Y * (Axis.X * Axis.Y * OneMinusCosine - Axis.Z * Sine)) +
			(A.Z * (Axis.X * Axis.Z * OneMinusCosine + Axis.Y * Sine)),

		(A.X * (Axis.Y * Axis.X * OneMinusCosine + Axis.Z * Sine)) +
			(A.Y * (Cosine + Square(Axis.Y) * OneMinusCosine)) +
			(A.Z * (Axis.Y * Axis.Z * OneMinusCosine - Axis.X * Sine)),

		(A.X * (Axis.Z * Axis.X * OneMinusCosine - Axis.Y * Sine)) + 
			(A.Y * (Axis.Z * Axis.Y * OneMinusCosine + Axis.X * Sine)) +
			(A.Z * (Cosine + Square(Axis.Z) * OneMinusCosine))
	};

	return Result;
}

internal void
Rotate(v3 *A, quaternion Rotation)
{
	quaternion AQuat = {A->X, A->Y, A->Z, 0.0f};
	quaternion ResultQuat = Rotation * AQuat * Conjugate(Rotation);

	A->X = ResultQuat.X;
	A->Y = ResultQuat.Y;
	A->Z = ResultQuat.Z;
}

internal void
Rotate(v3 *A, v3 Axis, float Radians)
{
	quaternion Rotation = Quaternion(Axis, Radians);
	Rotate(A, Rotation);
}

internal void
RotateNormalize(v3 *A, quaternion Rotation)
{
	Rotate(A, Rotation);
	Normalize(A);
}

internal void
RotateNormalize(v3 *A, v3 Axis, float Radians)
{
	Rotate(A, Axis, Radians);
	Normalize(A);
}

internal v3
Rotate(v3 A, v3 Axis, float Radians)
{
	Rotate(&A, Axis, Radians);

	return A;
}

#if 0
inline sphere_motion
Add(sphere_motion A, sphere_motion B, v3 Point)
{
	sphere_motion Result = {};

	if((A.Rotation == 0.0f) && 
	   (B.Rotation == 0.0f))
	{
		Result = A;
	}
	else
	{
		v3 OldPoint = Point;
		v3 NewPoint = OldPoint;

		Rotate(&NewPoint, A.Axis, A.Rotation);
		Rotate(&NewPoint, B.Axis, B.Rotation);

		Result.Axis = Normalize(Cross(NewPoint, OldPoint));
		Result.Rotation = -Angle(OldPoint, NewPoint);
	}

	return Result;
}
#endif

inline plane
Plane(v3 BaseA, v3 BaseB)
{
	plane Result = {BaseA, BaseB};

	return Result;
}

internal v3
Project(v3 P, v3 PlaneNormal)
{
	float LengthOfPOnNormal = Dot(P, PlaneNormal);
	v3 PlaneNormalScaledToP = LengthOfPOnNormal * PlaneNormal;
	v3 Result = P - PlaneNormalScaledToP;

	return Result;
}

internal v3
Project(v3 P, plane Plane)
{
	v3 PlaneNormal = Normalize(Cross(Plane.BaseA, Plane.BaseB));
	v3 Result = Project(P, PlaneNormal);

	return Result;
}

inline v3
Cross(line3 Line)
{
	v3 Result = Cross(Line.A, Line.B);

	return Result;
}

inline float
Dot(line3 Line)
{
	float Result = Dot(Line.A, Line.B);

	return Result;
}

internal void
SetToOrtho(mat4 *Matrix, 
		   float Width, float Height)
{
	// Formula and notation from http://www.songho.ca/opengl/gl_projectionmatrix.html
	float l = 0;
	float r = Width;

	float t = Height;
	float b = 0;

	float n = -1;
	float f = 1;

	Matrix->m00 = (2 / (r - l));
	Matrix->m01 = 0;
	Matrix->m02 = 0;
	Matrix->m03 = -((r + l) / (r - l));

	Matrix->m10 = 0;
	Matrix->m11 = (2 / (t - b));
	Matrix->m12 = 0;
	Matrix->m13 = -((t + b) / (t - b));

	Matrix->m20 = 0;
	Matrix->m21 = 0;
	Matrix->m22 = (-2 / (f - n));
	Matrix->m23 = -((f + n) / (f - n));

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal frustrum
CreateFrustrum(float FieldOfView, float AspectRatio, float Near, float Far)
{
	frustrum Result;

	Result.FieldOfView = FieldOfView;
	Result.AspectRatio = AspectRatio;

	float HalfHeight = Near * tanf(FieldOfView/2.0f);
	float HalfWidth = HalfHeight * AspectRatio;

	Result.Left = -HalfWidth;
	Result.Right = HalfWidth;

	Result.Bottom = -HalfHeight;
	Result.Top = HalfHeight;

	Result.Near = Near;
	Result.Far = Far;

	return Result;
}

internal void
SetToPerspective(mat4 *Matrix, frustrum Frustrum)
{
	// Formula and notation from http://www.songho.ca/opengl/gl_projectionmatrix.html
	// NOTE: only supports r = -l and b = -t

	Matrix->m00 = (Frustrum.Near / Frustrum.Right);
	Matrix->m01 = 0;
	Matrix->m02 = 0;
	Matrix->m03 = 0;

	Matrix->m10 = 0;
	Matrix->m11 = (Frustrum.Near / Frustrum.Top);
	Matrix->m12 = 0;
	Matrix->m13 = 0;

	Matrix->m20 = 0;
	Matrix->m21 = 0;
	Matrix->m22 = (-(Frustrum.Far + Frustrum.Near) / (Frustrum.Far - Frustrum.Near));
	Matrix->m23 = (-(2 * Frustrum.Far * Frustrum.Near) / (Frustrum.Far - Frustrum.Near));

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = -1;
	Matrix->m33 = 0;
}

inline v3
operator*(mat4 A, v3 B)
{
	v3 Result = 
	{
		A.m00*B.X + A.m01*B.Y + A.m02*B.Z,
		A.m10*B.X + A.m11*B.Y + A.m12*B.Z,
		A.m20*B.X + A.m21*B.Y + A.m22*B.Z
	};

	return Result;
}

inline mat4
operator*(mat4 A, mat4 B)
{
	mat4 Result;

	Result.m00 = A.m00*B.m00 + A.m01*B.m10 + A.m02*B.m20 + A.m03*B.m30;
	Result.m01 = A.m00*B.m01 + A.m01*B.m11 + A.m02*B.m21 + A.m03*B.m31;
	Result.m02 = A.m00*B.m02 + A.m01*B.m12 + A.m02*B.m22 + A.m03*B.m32;
	Result.m03 = A.m00*B.m03 + A.m01*B.m13 + A.m02*B.m23 + A.m03*B.m33;

	Result.m10 = A.m10*B.m00 + A.m11*B.m10 + A.m12*B.m20 + A.m13*B.m30;
	Result.m11 = A.m10*B.m01 + A.m11*B.m11 + A.m12*B.m21 + A.m13*B.m31;
	Result.m12 = A.m10*B.m02 + A.m11*B.m12 + A.m12*B.m22 + A.m13*B.m32;
	Result.m13 = A.m10*B.m03 + A.m11*B.m13 + A.m12*B.m23 + A.m13*B.m33;

	Result.m20 = A.m20*B.m00 + A.m21*B.m10 + A.m22*B.m20 + A.m23*B.m30;
	Result.m21 = A.m20*B.m01 + A.m21*B.m11 + A.m22*B.m21 + A.m23*B.m31;
	Result.m22 = A.m20*B.m02 + A.m21*B.m12 + A.m22*B.m22 + A.m23*B.m32;
	Result.m23 = A.m20*B.m03 + A.m21*B.m13 + A.m22*B.m23 + A.m23*B.m33;

	Result.m30 = A.m30*B.m00 + A.m31*B.m10 + A.m32*B.m20 + A.m33*B.m30;
	Result.m31 = A.m30*B.m01 + A.m31*B.m11 + A.m32*B.m21 + A.m33*B.m31;
	Result.m32 = A.m30*B.m02 + A.m31*B.m12 + A.m32*B.m22 + A.m33*B.m32;
	Result.m33 = A.m30*B.m03 + A.m31*B.m13 + A.m32*B.m23 + A.m33*B.m33;

	return Result;
}

internal void
RotateXEuler(mat4 *Matrix, float Radians)
{
	float Cosine = cosf(Radians);
	float Sine = sinf(Radians);

	Matrix->m00 = 1;
	Matrix->m01 = 0;
	Matrix->m02 = 0;
	Matrix->m03 = 0;

	Matrix->m10 = 0;
	Matrix->m11 = Cosine;
	Matrix->m12 = -Sine;
	Matrix->m13 = 0;

	Matrix->m20 = 0;
	Matrix->m21 = Sine;
	Matrix->m22 = Cosine;
	Matrix->m23 = 0;

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
RotateYEuler(mat4 *Matrix, float Radians)
{
	float Cosine = cosf(Radians);
	float Sine = sinf(Radians);

	Matrix->m00 = Cosine;
	Matrix->m01 = 0;
	Matrix->m02 = Sine;
	Matrix->m03 = 0;

	Matrix->m10 = 0;
	Matrix->m11 = 1;
	Matrix->m12 = 0;
	Matrix->m13 = 0;

	Matrix->m20 = -Sine;
	Matrix->m21 = 0;
	Matrix->m22 = Cosine;
	Matrix->m23 = 0;

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
Rotate(mat4 *Matrix, v3 Axis, float Radians)
{
	quaternion Q = Quaternion(Axis, Radians);

	Matrix->m00 = 1 - 2 * ((Q.Y * Q.Y) + (Q.Z * Q.Z));
	Matrix->m01 = 2 * ((Q.X * Q.Y) - (Q.W * Q.Z));
	Matrix->m02 = 2 * ((Q.X * Q.Z) + (Q.W * Q.Y));
	Matrix->m03 = 0;

	Matrix->m10 = 2 * ((Q.X * Q.Y) + (Q.W * Q.Z));
	Matrix->m11 = 1 - 2 * ((Q.X * Q.X) + (Q.Z * Q.Z));
	Matrix->m12 = 2 * ((Q.Y * Q.Z) - (Q.W * Q.X));
	Matrix->m13 = 0;

	Matrix->m20 = 2 * ((Q.X * Q.Z) - (Q.W * Q.Y));
	Matrix->m21 = 2 * ((Q.Y * Q.Z) + (Q.W * Q.X));
	Matrix->m22 = 1 - 2 * ((Q.X * Q.X) + (Q.Y * Q.Y));
	Matrix->m23 = 0;

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
Scale(mat4 *Matrix, float Scale)
{
	Matrix->m00 = Scale;
	Matrix->m01 = 0;
	Matrix->m02 = 0;
	Matrix->m03 = 0;

	Matrix->m10 = 0;
	Matrix->m11 = Scale;
	Matrix->m12 = 0;
	Matrix->m13 = 0;

	Matrix->m20 = 0;
	Matrix->m21 = 0;
	Matrix->m22 = Scale;
	Matrix->m23 = 0;

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
Translate(mat4 *Matrix, v3 Translation)
{
	Matrix->m00 = 1;
	Matrix->m01 = 0;
	Matrix->m02 = 0;
	Matrix->m03 = Translation.X;

	Matrix->m10 = 0;
	Matrix->m11 = 1;
	Matrix->m12 = 0;
	Matrix->m13 = Translation.Y;

	Matrix->m20 = 0;
	Matrix->m21 = 0;
	Matrix->m22 = 1;
	Matrix->m23 = Translation.Z;

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
LookAt(mat4 *Matrix, v3 EyePos, v3 Forward, v3 Right, v3 Up)
{
	Forward = -Forward;
	EyePos = -EyePos;

	Matrix->m00 = Right.X;
	Matrix->m01 = Right.Y;
	Matrix->m02 = Right.Z;
	Matrix->m03 = (EyePos.X * Right.X) + (EyePos.Y * Right.Y) + (EyePos.Z * Right.Z);

	Matrix->m10 = Up.X;
	Matrix->m11 = Up.Y;
	Matrix->m12 = Up.Z;
	Matrix->m13 = (EyePos.X * Up.X) + (EyePos.Y * Up.Y) + (EyePos.Z * Up.Z);

	Matrix->m20 = Forward.X;
	Matrix->m21 = Forward.Y;
	Matrix->m22 = Forward.Z;
	Matrix->m23 = (EyePos.X * Forward.X) + (EyePos.Y * Forward.Y) + (EyePos.Z * Forward.Z);

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
LookAt(mat4 *Matrix, v3 EyePos, v3 CenterPos, v3 WorldUp)
{
	v3 Forward = Normalize(CenterPos - EyePos);
	v3 Right = Normalize(Cross(Forward, WorldUp));
	v3 Up = Normalize(Cross(Right, Forward));

	LookAt(Matrix, EyePos, Forward, Right, Up);
}

internal void
SetIdentity(mat4 *Matrix)
{
	Matrix->m00 = 1;
	Matrix->m01 = 0;
	Matrix->m02 = 0;
	Matrix->m03 = 0;

	Matrix->m10 = 0;
	Matrix->m11 = 1;
	Matrix->m12 = 0;
	Matrix->m13 = 0;

	Matrix->m20 = 0;
	Matrix->m21 = 0;
	Matrix->m22 = 1;
	Matrix->m23 = 0;

	Matrix->m30 = 0;
	Matrix->m31 = 0;
	Matrix->m32 = 0;
	Matrix->m33 = 1;
}

internal void
Transpose(mat4 *Matrix)
{
	Swap(&Matrix->m01, &Matrix->m10);
	Swap(&Matrix->m02, &Matrix->m20);
	Swap(&Matrix->m03, &Matrix->m30);
	Swap(&Matrix->m12, &Matrix->m21);
	Swap(&Matrix->m13, &Matrix->m31);
	Swap(&Matrix->m23, &Matrix->m32);
}

inline rectangle
Rectangle(float MinX, float MinY,
		  float MaxX, float MaxY)
{
	rectangle Result = 
	{
		V2(MinX, MinY), 
		V2(MaxX, MaxY)
	};

	return Result;
}

inline rectangle
RectangleFromPosDim(float X, float Y, 
					float Width, float Height)
{
	rectangle Result = 
	{
		V2(X, Y),
		V2(X + Width, Y + Height)
	};

	return Result;
}

inline rectangle
RectangleFromPosDim(v2 Pos, v2 Dim)
{
	rectangle Result = RectangleFromPosDim(Pos.X, Pos.Y, Dim.Width, Dim.Height);

	return Result;
}

inline rectangle_corners
GetCorners(rectangle Rectangle)
{
	rectangle_corners Result = 
	{
		V2(Rectangle.Min.X, Rectangle.Min.Y),
		V2(Rectangle.Max.X, Rectangle.Min.Y),
		V2(Rectangle.Max.X, Rectangle.Max.Y),
		V2(Rectangle.Min.X, Rectangle.Max.Y)
	};

	return Result;
}

inline bool
IsInCircle(circle Circle, v2 Point)
{
	v2 FromCenterToPoint = (Point - Circle.Pos);

	float FromCenterToPointLengthSq = LengthSq(FromCenterToPoint);
	float CircleRadiusSq = Square(Circle.Radius);

	bool Result = (FromCenterToPointLengthSq < CircleRadiusSq);

	return Result;
}

inline float
RadiansToDegrees(float Radians)
{
	float Result = 180.0f * Radians / Pi32;

	return Result;
}

inline float
DegreesToRadians(float Degrees)
{
	float Result = Degrees / 180.0f * Pi32;

	return Result;
}

inline v2
DegreesToRadians(v2 Degrees)
{
	v2 Result = 
	{
		DegreesToRadians(Degrees.X),
		DegreesToRadians(Degrees.Y)
	};

	return Result;
}

inline v3
SphereToCartesian(v2 SphereCoords)
{
	float CosineTheta = cosf(SphereCoords.Theta);
	float SineTheta = sinf(SphereCoords.Theta);
	float CosinePhi = cosf(SphereCoords.Phi);
	float SinePhi = sinf(SphereCoords.Phi);

	v3 Result = 
	{
		SineTheta * SinePhi,
		CosinePhi,
		CosineTheta * SinePhi
	};

	return Result;
}
