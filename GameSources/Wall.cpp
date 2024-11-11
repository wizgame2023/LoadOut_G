/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Wall::Wall(shared_ptr<Stage>& stagePtr, Vec3 pos, Vec3 rot,Vec3 scale) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rot(rot),
		m_scale(scale)
	{

	}
	Wall::~Wall()
	{
	}

	void Wall::OnCreate()
	{
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_pos);
		Trans->SetRotation(m_rot);
		Trans->SetScale(m_scale);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);


		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(false);//ぶつからない限りスリープ状態になる

		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Wall");//壁用のタグ

	}

}
//end basecross
