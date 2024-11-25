/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class NumberSquare :public GameObject
	{
		weak_ptr<Enemy> m_enemy;

		shared_ptr<MeshResource> m_SquareMeshResource;

		size_t m_Number;

		Quat Billboard(const Vec3& Line) 
		{
			Vec3 Temp = Line;
			Mat4x4 RotMatrix;
			Vec3 DefUp(0, 1.0f, 0);
			Vec2 TempVec2(Temp.x, Temp.z);
			if (TempVec2.length() < 0.1f)
			{
				DefUp = Vec3(0, 0, 1.0f);
			}
			Temp.normalize();
			RotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), Temp, DefUp);
			RotMatrix.inverse();
			Quat Qt;
			Qt = RotMatrix.quatInMatrix();
			Qt.normalize();
			return Qt;
		}
	public:
		//�\�z�Ɣj��
		NumberSquare(const shared_ptr<Stage>& StagePtr,
			shared_ptr<Enemy>& enemyPtr, size_t Number);
		virtual ~NumberSquare();
		//������
		virtual void OnCreate() override;
		//�ω�
		virtual void OnUpdate() override;

	};

}
//end basecross