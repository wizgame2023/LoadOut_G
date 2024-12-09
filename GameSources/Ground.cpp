/*!
@file Ground.cpp
@brief ブロックのオブジェクトの実装
担当：三瓶
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Ground::Ground(const shared_ptr<Stage>& StagePtr, Vec3 pos, Vec3 rot) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot)
	{
	}
	Ground::Ground(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_pos(Vec3(0.0f, 0.0f, 0.0f)),
		m_rot(Vec3(200.0f, 0.1f, 200.0f))
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::OnCreate()
	{
		//Transform作成
		auto ptr = GetComponent<Transform>();//Transform取得
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f,0.0f,0.0f);
		ptr->SetScale(m_rot);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Road");

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成 コリジョンいらなくなった
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(false);
		//ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる
		//ptrColl->SetDrawActive(true);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Ground");//地面用のタグ

	}

}