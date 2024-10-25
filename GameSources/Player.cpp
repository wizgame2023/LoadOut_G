/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const shared_ptr<Stage>& StagePtr,Vec3 pos,Vec3 rot) :
		GameObject(StagePtr),
		m_Pos(pos),
		m_Rot(rot)
	{
	}
	Player::~Player()
	{
	}

	void Player::OnCreate()
	{
		m_Trans = GetComponent<Transform>();
		m_Trans->SetPosition(m_Pos);
		m_Trans->SetRotation(m_Rot);
		m_Trans->SetScale(5.0f, 5.0f, 5.0f);

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


		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetFixed(true);
		ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる

		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Player");//タグ追加
	}

	void Player::OnUpdate()
	{
		//デルタタイム
		auto Delta = App::GetApp()->GetElapsedTime();

		//コントローラーのアナログスティックの向き
		auto contorollerVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//左ステックの向きにプレイヤーが進む
		if (contorollerVec[0].bConnected)
		{
			m_Pos.x += contorollerVec[0].fThumbLX*10*Delta;
			m_Pos.z += contorollerVec[0].fThumbLY*10*Delta;

			m_Trans->SetPosition(m_Pos);//ポジション更新
		}
		float deg;
		//左ステックの向きにプレイヤーも向く
		if (contorollerVec[0].bConnected)
		{
			//スティックの傾きをラジアンにする
			float rad = -atan2(contorollerVec[0].fThumbLY, contorollerVec[0].fThumbLX);
			//ラジアンの傾きをディグリー角にする
			deg = rad * 180 / 3.14f;
			m_Rot.y = rad;

			m_Trans->SetRotation(m_Rot);

		}

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		Vec2 selPos = mapManager->MyMapNow(m_Pos);

		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		wss << L"デバッグ用文字列 "
			<<L"\n傾き "<<deg
			<< L"\nPos.x " << m_Pos.x << "\nPos.z " << m_Pos.z
			<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
			<<L"\nCount "<<m_count
			<< endl;

		scene->SetDebugString(wss.str());

	}

	//m_countに数値がプラスされる
	void Player::AddCount(int add)
	{
		m_count += add;
	}

}
//end basecross

