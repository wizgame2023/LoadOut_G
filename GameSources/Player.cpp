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
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(-90.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);


		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"Player_Mesh_Kari");
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//ptrDraw->SetTextureResource(L"");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//ptrColl->SetSleepActive(false);//ぶつからない限りスリープ状態になる
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする


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
		//コントローラーの取得
		m_controler = inputDevice.GetControlerVec()[0];
		auto pos = GetComponent<Transform>()->GetPosition();//ポジション取得


		PlayerMove();//プレイヤーの動き

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		Vec2 selPos = mapManager->ConvertSelMap(pos);//今いるセル座標を取得
		int selNow = mapManager->SelMapNow(pos);//現在いるセル座標に何があるかを取得

		ManholeSet(pos);//マンホールの上にわなを仕掛ける処理

		//デバック用でhpを減らす
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_Y)//Yボタンでhpを減らす
		{
			m_hp -= 1;
		}
		if (m_hp <= 0)//体力が0になったら
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//ゲームオーバシーンに移動する
		}

		auto rot = GetComponent<Transform>()->GetRotation();//回転度を取得

		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		wss << L"デバッグ用文字列 "
			<< L"\n傾き " << m_deg
			<< L"\nPos.x " << pos.x << "\nPos.z " << pos.z
			<<L"\nrot.x "<<rot.x << L"\nrot.y " << rot.y << "\nrot.z" << rot.z
			<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
			<< L"\nCount " << m_count
			<< L"\nSelNow " << selNow
			<< L"\ntest " <<  XMConvertToDegrees(XM_PI * 0.5f)
			<<L"\nFPS:"<< 1.0f/Delta
			<< endl;
		//XMConvertToRadians(-90.0f)e

		scene->SetDebugString(wss.str());

	}

	void Player::PlayerMove()//プレイヤーの向きや動きを管理する関数
	{
		auto pos = GetComponent<Transform>()->GetPosition();//ポジション取得
		auto Delta = App::GetApp()->GetElapsedTime();

		//左ステックの向きにプレイヤーが進む
		if (m_controler.bConnected)
		{

			pos.x += (m_controler.fThumbLX * 10 * Delta) * 2;
			pos.z += (m_controler.fThumbLY * 10 * Delta) * 2;

			m_Trans->SetPosition(pos);//ポジション更新
		}

		float deg = 0;
		//左ステックの向きにプレイヤーも向く
		if (m_controler.bConnected)
		{
			//スティックの傾きをラジアンにする
			float rad = -atan2(m_controler.fThumbLY, m_controler.fThumbLX);
			//ラジアンの傾きをディグリー角にする
			m_deg = rad * 180 / 3.14f;
			m_Rot.y = rad;
			//ゲームパットの傾きが無ければ回転度は更新しない
			if (m_controler.fThumbLY != 0.0f && m_controler.fThumbLX != 0.0f)
			{
				m_Trans->SetRotation(m_Rot);
			}

		}

	}

	//マンホールの上にわなを仕掛ける処理
	void Player::ManholeSet(Vec3 pos)
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得

		if (m_count >= 1)//カウントが１以上なら
		{
			auto device = App::GetApp()->GetInputDevice().GetControlerVec();
			if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)//Bボタンを押したとき
			{
				if (mapManager->SelMapNow(pos) == 1)//もし、現在いるセル座標がマンホールの上ならば
				{
					m_count--;
					mapManager->MapDataUpdate(pos, 2);//罠を設置する

				}
			}


		}
	}

	void Player::SetUp()
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		auto pos = GetComponent<Transform>()->GetPosition();

		//そのセル座標がマンホールの上なら罠を置く処理
		if (mapManager->SelMapNow(pos) == 1)
		{
			mapManager->MapDataUpdate(pos, 2);//現在のセル座標に罠を置く処理をする
		}
	}

	//m_countに数値がプラスされる
	void Player::AddCount(int add)
	{
		m_count += add;
	}

}
//end basecross

