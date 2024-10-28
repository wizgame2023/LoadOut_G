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

		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得

		//コントローラーのアナログスティックの向き
		auto& gamePad = inputDevice.GetControlerVec()[0];


		//左ステックの向きにプレイヤーが進む
		if (gamePad.bConnected)
		{
			m_Pos.x += gamePad.fThumbLX*10*Delta;
			m_Pos.z += gamePad.fThumbLY*10*Delta;

			m_Trans->SetPosition(m_Pos);//ポジション更新
		}
		float deg = 0;
		//左ステックの向きにプレイヤーも向く
		if (gamePad.bConnected)
		{
			//スティックの傾きをラジアンにする
			float rad = -atan2(gamePad.fThumbLY, gamePad.fThumbLX);
			//ラジアンの傾きをディグリー角にする
			deg = rad * 180 / 3.14f;
			m_Rot.y = rad;

			m_Trans->SetRotation(m_Rot);

		}

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		Vec2 selPos = mapManager->ConvertSelMap(m_Pos);//今いるセル座標を取得
		int selNow = mapManager->SelMapNow(m_Pos);//現在いるセル座標に何があるかを取得

		//できました
		if (m_count >= 1)//カウントが１以上なら
		{
			auto device = App::GetApp()->GetInputDevice().GetControlerVec();
			if (gamePad.wPressedButtons & XINPUT_GAMEPAD_B)//Bボタンを押したとき
			{
				m_count--;
				if (mapManager->SelMapNow(m_Pos) == 1)//もし、現在いるセル座標がマンホールの上ならば
				{
					mapManager->MapDataUpdate(m_Pos, 2);//罠を設置する

				}
			}

			
		}

		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		wss << L"デバッグ用文字列 "
			<<L"\n傾き "<<deg
			<< L"\nPos.x " << m_Pos.x << "\nPos.z " << m_Pos.z
			<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
			<< L"\nCount " << m_count
			<< L"\nSelNow " << selNow
			<< endl;

		scene->SetDebugString(wss.str());

	}

	void Player::SetUp()
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得

		//そのセル座標がマンホールの上なら罠を置く処理
		if (mapManager->SelMapNow(m_Pos) == 1)
		{
			mapManager->MapDataUpdate(m_Pos, 2);//現在のセル座標に罠を置く処理をする
		}
	}

	//m_countに数値がプラスされる
	void Player::AddCount(int add)
	{
		m_count += add;
	}

}
//end basecross

