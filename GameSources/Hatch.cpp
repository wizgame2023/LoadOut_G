/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Hatch::Hatch(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos)
	{

	}

	Hatch::~Hatch()
	{

	}

	void Hatch::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetScale(10.0f * 0.5f, 1.0f, 10.0f * 0.5f);

		//Transformに対しての等差数列
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(2.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//メッシュ生成
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"Hatch");
		ptrDraw->SetOwnShadowActive(true); // 影の映り込みを反映させる
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//コリジョン生成
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Hatch");//ハッチ用のタグ

	}

	void Hatch::OnUpdate()
	{
		//もしハッチが空いている状態ならステージマネージャーにゲームクリアだというフラグを渡す
		auto stage = GetStage();
		auto mapManager = stage->GetSharedGameObject<MapManager>(L"MapManager");
		auto pos = GetComponent<Transform>()->GetPosition();
		auto nowYuka = mapManager->SelMapNow(pos);//今のセル座標はどの状態かを見る
		if (nowYuka == 5)//ハッチが開かれている状態であれば
		{
			//色を変える
			auto ptrDraw = GetComponent<PNTStaticDraw>();
			ptrDraw->SetTextureResource(L"Black");

			if (m_count == 0)
			{
				m_count = 1;
				stage->AddGameObject<MovieGameClear>();//デバック用

			}


			

			//ステージマネージャーにゲームクリアのフラグを渡す
			//auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
			//stageManager->SetClearFlag(true);
		}
	}


}
//end basecross
