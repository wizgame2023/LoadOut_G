/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Wall::Wall(shared_ptr<Stage>& stagePtr, Vec3 pos, Vec3 rot,Vec3 miniMapStartPos,Vec3 scale) :
		GameObject(stagePtr),
		m_pos(pos),
		m_rot(rot),
		m_miniMapStartPos(miniMapStartPos),
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
		ptrDraw->SetTextureResource(L"StoneWall");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(false);//ぶつからない限りスリープ状態になる

		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Wall");//壁用のタグ


	}

	//ミニマップの自分自身を生成
	void Wall::MiniMapCreate(Vec3 miniMapStartPos)
	{
		//ミニマップに自分を映させる
		//auto Lenght = 200;
		//auto miniMapSize = 225;
		//auto mapSize = 400;
		//auto miniMapPos = m_pos;//ミニマップの座標を入れる
		//miniMapPos.y = miniMapPos.z;//座標を調整する
		//miniMapPos.z = 5;
		//auto mapMagnification = (miniMapSize / mapSize);
		//Vec3 stagePos = Vec3(-200.0f, 0.0f, 200.0f);

		//GetStage()->AddGameObject<Sprite>(L"White", Vec2(1.5f * mapMagnification, 4.5f * mapMagnification), (miniMapStartPos + (miniMapPos * mapMagnification), 0.0f));

	}

}
//end basecross
