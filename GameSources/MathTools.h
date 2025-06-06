/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	static class Math
	{
	public:
		float GetDistance(Vec3 a, Vec3 b)
		{
			float numX = a.x - b.x;
			float numY = a.y - b.y;
			float numZ = a.z - b.z;

			return  sqrt(numX * numX + numY * numY + numZ * numZ);
		}

		float GetCircleRange(float r, Vec3 a, Vec3 b)
		{
			float numX = a.x - b.x;
			float numY = a.y - b.y;
			float numZ = a.z - b.z;

			return numX * numX + numY * numY + numZ * numZ <= r * r;
		}

		float GetAngle(Vec3 a,Vec3 b)
		{
			float numX = a.x - b.x;
			float numZ = a.z - b.z;

			return atan2f(numX, numZ);
		}
	};
}
//end basecross
