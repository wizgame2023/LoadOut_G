/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class BillBoard :public GameObject
	{


	protected:
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

		weak_ptr<GameObject> m_actor;

		shared_ptr<MeshResource> m_SquareMeshResource;

		vector<VertexPositionNormalTexture> m_vertices;

		size_t m_Number;

		wstring m_textureName;

		Vec3 m_scale;

		Col4 m_color;

		float m_pushY;

	public:
		//�\�z�Ɣj��
		BillBoard(const shared_ptr<Stage>& StagePtr,
			shared_ptr<GameObject>& actorPtr, size_t Number,float pushY = 18.0f, Vec3 scale = Vec3(3.0f, 3.0f, 3.0f));
		BillBoard(const shared_ptr<Stage>& StagePtr,
			shared_ptr<GameObject>& actorPtr, wstring spriteName, float pushY = 18.0f,Vec3 scale = Vec3(3.0f,3.0f,3.0f),Col4 color = Col4(1.0f,1.0f,1.0f,1.0f));
		virtual ~BillBoard();
		//������
		virtual void OnCreate() override;
		//�ω�
		virtual void OnUpdate() override;

		//�X�v���C�g�ύX
		virtual void ChangeTexture(wstring spriteName);

		//�T�C�Y�ύX
		virtual void SetScale(Vec3 scale);

		//�o�����鍂���ύX
		virtual void SetPushY(float pushY);

	};

}
//end basecross