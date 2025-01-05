/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class BillBoard :public GameObject
	{
		weak_ptr<GameObject> m_actor;

		shared_ptr<MeshResource> m_SquareMeshResource;

		size_t m_Number;

		wstring m_textureName;

		Vec3 m_scale;

		float m_pushY;

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
		//構築と破棄
		BillBoard(const shared_ptr<Stage>& StagePtr,
			shared_ptr<GameObject>& actorPtr, size_t Number,float pushY = 18.0f, Vec3 scale = Vec3(3.0f, 3.0f, 3.0f));
		BillBoard(const shared_ptr<Stage>& StagePtr,
			shared_ptr<GameObject>& actorPtr, wstring spriteName, float pushY = 18.0f,Vec3 scale = Vec3(3.0f,3.0f,3.0f));
		virtual ~BillBoard();
		//初期化
		virtual void OnCreate() override;
		//変化
		virtual void OnUpdate() override;

		//スプライト変更
		void ChangeTexture(wstring spriteName);

		//サイズ変更
		void SetScale(Vec3 scale);

	};

}
//end basecross