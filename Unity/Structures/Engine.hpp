#pragma once

namespace Unity
{
	struct Vector2
	{
		float x, y;

		Vector2() { x = y = 0.f; }
		Vector2(float f1, float f2) { x = f1; y = f2; }
	};

	struct Vector3
	{
		float x, y, z;

		Vector3() { x = y = z = 0.f; }
		Vector3(float f1, float f2, float f3) { x = f1; y = f2; z = f3; }
	};

	struct Vector4
	{
		float x, y, z, w;

		Vector4() { x = y = z = w = 0.f; }
		Vector4(float f1, float f2, float f3, float f4) { x = f1; y = f2; z = f3; w = f4; }
	};

	struct Bounds
	{
		Vector3 m_vCenter;
		Vector3 m_vExtents;
	};

	struct Plane
	{
		Vector3 m_vNormal;
		float fDistance;
	};

	struct Ray
	{
		Vector3 m_vOrigin;
		Vector3 m_vDirection;
	};

	struct Rect
	{
		float fX, fY;
		float fWidth, fHeight;

		Rect() { fX = fY = fWidth = fHeight = 0.f; }
		Rect(float f1, float f2, float f3, float f4) { fX = f1; fY = f2; fWidth = f3; fHeight = f4; }
	};

	struct Color
	{
		float r, g, b, a;

		Color() { r = g = b = a = 0.f; }
		Color(float fRed = 0.f, float fGreen = 0.f, float fBlue = 0.f, float fAlpha = 1.f) { r = fRed; g = fGreen; b = fBlue; a = fAlpha; }
	};

	struct Matrix4x4
	{
		float m[4][4] = { 0 };

		Matrix4x4() { }

		float* operator[](int i) { return m[i]; }
	};
}