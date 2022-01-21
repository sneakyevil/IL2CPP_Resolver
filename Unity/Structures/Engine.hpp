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

		void ToVectors(Vector3* m_pForward, Vector3* m_pRight, Vector3* m_pUp)
		{
			float m_fDeg2Rad = static_cast<float>(M_PI) / 180.f;

			float m_fSinX = sinf(x * m_fDeg2Rad);
			float m_fCosX = cosf(x * m_fDeg2Rad);

			float m_fSinY = sinf(y * m_fDeg2Rad);
			float m_fCosY = cosf(y * m_fDeg2Rad);

			float m_fSinZ = sinf(z * m_fDeg2Rad);
			float m_fCosZ = cosf(z * m_fDeg2Rad);

			if (m_pForward)
			{
				m_pForward->x = m_fCosX * m_fCosY;
				m_pForward->y = -m_fSinX;
				m_pForward->z = m_fCosX * m_fSinY;
			}

			if (m_pRight)
			{
				m_pRight->x = -1.f * m_fSinZ * m_fSinX * m_fCosY + -1.f * m_fCosZ * -m_fSinY;
				m_pRight->y = -1.f * m_fSinZ * m_fCosX;
				m_pRight->z = -1.f * m_fSinZ * m_fSinX * m_fSinY + -1.f * m_fCosZ * m_fCosY;
			}

			if (m_pUp)
			{
				m_pUp->x = m_fCosZ * m_fSinX * m_fCosY + -m_fSinZ * -m_fSinY;
				m_pUp->y = m_fCosZ * m_fCosX;
				m_pUp->z = m_fCosZ * m_fSinX * m_fSinY + -m_fSinZ * m_fCosY;
			}
		}
	};

	struct Vector4
	{
		float x, y, z, w;

		Vector4() { x = y = z = w = 0.f; }
		Vector4(float f1, float f2, float f3, float f4) { x = f1; y = f2; z = f3; w = f4; }
	};

	struct Quaternion
	{
		float x, y, z, w;

		Quaternion() { x = y = z = w = 0.f; }
		Quaternion(float f1, float f2, float f3, float f4) { x = f1; y = f2; z = f3; w = f4; }

		Quaternion Euler(float m_fX, float m_fY, float m_fZ)
		{
			float m_fDeg2Rad = static_cast<float>(M_PI) / 180.f;

			m_fX = m_fX * m_fDeg2Rad * 0.5f;
			m_fY = m_fY * m_fDeg2Rad * 0.5f;
			m_fZ = m_fZ * m_fDeg2Rad * 0.5f;

			float m_fSinX = sinf(m_fX);
			float m_fCosX = cosf(m_fX);

			float m_fSinY = sinf(m_fY);
			float m_fCosY = cosf(m_fY);

			float m_fSinZ = sinf(m_fZ);
			float m_fCosZ = cosf(m_fZ);

			x = m_fCosY * m_fSinX * m_fCosZ + m_fSinY * m_fCosX * m_fSinZ;
			y = m_fSinY * m_fCosX * m_fCosZ - m_fCosY * m_fSinX * m_fSinZ;
			z = m_fCosY * m_fCosX * m_fSinZ - m_fSinY * m_fSinX * m_fCosZ;
			w = m_fCosY * m_fCosX * m_fCosZ + m_fSinY * m_fSinX * m_fSinZ;

			return *this;
		}

		Quaternion Euler(Vector3 m_vRot)
		{
			return Euler(m_vRot.x, m_vRot.y, m_vRot.z);
		}

		Vector3 ToEuler()
		{
			Vector3 m_vEuler;

			float m_fDist = (x * x) + (y * y) + (z * z) + (w * w);

			float m_fTest = x * w - y * z;
			if (m_fTest > 0.4995f * m_fDist)
			{
				m_vEuler.x = static_cast<float>(M_PI) * 0.5f;
				m_vEuler.y = 2.f * atan2f(y, x);
				m_vEuler.z = 0.f;
			}
			else if (m_fTest < -0.4995f * m_fDist)
			{
				m_vEuler.x = static_cast<float>(M_PI) * -0.5f;
				m_vEuler.y = -2.f * atan2f(y, x);
				m_vEuler.z = 0.f;
			}
			else
			{
				m_vEuler.x = asinf(2.f * (w * x - y * z));
				m_vEuler.y = atan2f(2.f * w * y + 2.f * z * x, 1.f - 2.f * (x * x + y * y));
				m_vEuler.z = atan2f(2.f * w * z + 2.f * x * y, 1.f - 2.f * (z * z + x * x));
			}

			float m_fRad2Deg = 180.f / static_cast<float>(M_PI);
			m_vEuler.x *= m_fRad2Deg;
			m_vEuler.y *= m_fRad2Deg;
			m_vEuler.z *= m_fRad2Deg;

			return m_vEuler;
		}
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