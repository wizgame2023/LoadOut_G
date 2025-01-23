/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(shared_ptr<Stage>& StagePtr,Vec3 pos,Vec3 rot,bool gameFlag) :
		Actor(StagePtr),
		m_Pos(pos),
		m_Rot(rot),
		m_speed(10),
		m_pushSpeed(0),
		m_gameStageFlag(gameFlag)
		//m_move(true)
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
			Vec3(0.25f, 0.25f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(0.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//ドローメッシュの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"kid_Mesh");
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->AddAnimation(L"Walk", 4, 15, true, 30.0f);//歩き状態
		ptrDraw->AddAnimation(L"Stand", 5, 5, false, 1.0f);//待機状態
		ptrDraw->AddAnimation(L"Player_Down", 40, 60, false, 30.0f);//ゲームオーバー状態
		ptrDraw->AddAnimation(L"Happey", 20, 24, true, 30.0f);//ゲームクリア状態
		ptrDraw->ChangeCurrentAnimation(L"Walk");

		//ptrDraw->AddAnimation(L"Defalt2", 17, 25, true, 30.0f);
		//ptrDraw->Ani

		//ptrDraw->SetTextureResource(L"");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//ptrColl->SetSleepActive(false);//ぶつからない限りスリープ状態になる
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする

		//影を付ける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"kid_Mesh");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Player");//Player用のタグ

		//ゲームステージなら
		if (m_gameStageFlag)
		{
			//電池をどれくらい持っているかを表す
			GetStage()->AddGameObject<Sprite>(L"Cross", Vec2(30.0f, 30.0f), Vec3(-640.0f + 50.0f, 400 - 250.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));//クロス
			GetStage()->AddGameObject<Sprite>(L"Battery1", Vec2(30.0f, 50.0f), Vec3(-640.0f + 20.0f, 400 - 250.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));//電池のテクスチャ
			m_spriteNum = GetStage()->AddGameObject<NuberManager>(m_itemCount, Vec2(30.0f, 30.0f), Vec3(-640.0f + 100.0f, 400 - 250.0f, 0.0f), true);//個数
			MoveSwitch(true);

			//ビルボード生成
			m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(), L"Clear",2, 12.0f);
			//ステータス上方下方エフェクト
			m_pillar = GetStage()->AddGameObject<TrackingPillarEfect>(Vec3(0.0f, 0.0f, 0.0f), L"Clear", Vec2(0.0f, -1.0f));
			
		}
	}

	void Player::OnUpdate()
	{		

		//デルタタイム
		auto Delta = App::GetApp()->GetElapsedTime();


		if (!m_move||!m_gameStageFlag)//フラグがオンになったら動ける
		{
			return;
		}
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//キーボードデバック用

		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーの取得
		m_controler = inputDevice.GetControlerVec()[0];
		auto pos = GetComponent<Transform>()->GetPosition();//ポジション取得

		//y座標をずらさないようにする
		pos.y = 0.0f;
		GetComponent<Transform>()->SetPosition(pos);

		PlayerMove();//プレイヤーの動き

		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		Vec2 selPos = mapManager->ConvertSelMap(pos);//今いるセル座標を取得
		int selNow = mapManager->SelMapNow(pos);//現在いるセル座標に何があるかを取得

		ManholeSet(pos);//マンホールの上にわなを仕掛ける処理

		auto rot = GetComponent<Transform>()->GetRotation();//回転度を取得

		//もし鍵を持っているなら脱出できる
		if (m_key)
		{
			if (selNow == 4)//今いる床がハッチなら
			{
				if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B||keyState.m_bLastKeyTbl[VK_SPACE])//Bボタンを押したとき
				{
					mapManager->MapDataUpdate(pos, 5);//脱出状態にする

				}
			}
		}
		//バッテリーが1以上でマンホールの上にいるならBを押して設置するビルボードを出す
		if (selNow == 1)
		{
			if (m_itemCount > 0)
			{
				m_billBoard->SetScale(Vec3(8.0f, 3.0f, 3.0f));
				m_billBoard->ChangeTexture(L"Manhole_BillBoard_Push");
			}
			if (m_itemCount <= 0)
			{
				m_billBoard->SetScale(Vec3(3.0f, 3.0f, 3.0f));
				m_billBoard->ChangeTexture(L"Battery_HaveNo");
			}
		}

		//ハッチ上にいるときのビルボード処理
		if (selNow == 4)
		{
			if (!m_key)
			{
				m_billBoard->SetScale(Vec3(3.0f, 3.0f, 3.0f));
				m_billBoard->ChangeTexture(L"Key_HaveNo");
			}
			if (m_key)
			{
				m_billBoard->SetScale(Vec3(8.0f, 3.0f, 3.0f));
				m_billBoard->ChangeTexture(L"Manhole_BillBoard_Push");
			}
		}	
		
		if(selNow!=4 && selNow!=1)
		{
			if (m_key)
			{
				m_billBoard->SetScale(Vec3(3.0f, 3.0f, 3.0f));
				m_billBoard->ChangeTexture(L"Key");
			}
			if (!m_key)
			{
				m_billBoard->ChangeTexture(L"Clear");
			}
		}		


		//電池所持数は10個が限界
		if (m_itemCount > 10)
		{
			m_itemCount = 10;
		}
		m_spriteNum->SetNum(m_itemCount);//表示する数字を更新する

		//追加スピードが0ではない場合適応時間を計測して一定時間過ぎたら0にする
		if (m_pushSpeed != 0)
		{
			m_pushSpeedCountTime += Delta;
			//追加スピードが0より多いなら上昇エフェクトを出す
			if (m_pushSpeed > 0)
			{
				m_pillar->SetVelocity(Vec2(0.0f, 1.0f));
				m_pillar->SetTexture(L"StutasUp");
			}
			//追加スピードが0より小さいなら下方エフェクトを出す
			if (m_pushSpeed < 0)
			{
				m_pillar->SetVelocity(Vec2(0.0f, -1.0f));
				m_pillar->SetTexture(L"StutasDown");
			}
			if (m_pushSpeedCountTime >= 10.0f)
			{
				m_pillar->SetTexture(L"Clear");
				//追加スピードと計測時間リセット
				m_pushSpeed = 0;
				m_pushSpeedCountTime = 0.0f;
			}
		}

		//デバック用/////////////////////////////////////////////////////////////
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A)//Aボタンを押したとき
		{
			auto test = 0;
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)//L
		{
			auto test = 0;
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)//R
		{
			auto test = 0;
			//デバック用
			//auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");
			//mapManager->MapChange();
		}
		////////////////////////////////////////////////////////////////////////


		//////デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		////auto gameStage = scene->GetGameStage();
		//m_Pos = GetComponent<Transform>()->GetPosition();

		//wss /* << L"デバッグ用文字列 "*/
		//	<<L"\nSelx:"<<mapManager->ConvertSelMap(m_Pos).x
		//	<<L"\nSely:"<<mapManager->ConvertSelMap(m_Pos).y
		//	<< L"\n傾き " << m_deg
		//	<< L"\nPos.x " << pos.x << "\nPos.z " << pos.z
		//	<<L"\nrot.x "<<rot.x << L"\nrot.y " << rot.y << "\nrot.z" << rot.z
		//	<< L"\nSelPos.x " << selPos.x << "\nSelPos.y " << selPos.y
		//	<< L"\nm_count：  " << m_itemCount
		//	<< L"\nSelNow " << selNow
		//	<< L"\ntest " <<  XMConvertToDegrees(XM_PI * 0.5f)
		//	<<L"\nFPS:"<< 1.0f/Delta
		//	<<L"\nKey"<<m_key
		//	<<L"\nm_pushSpeedCountTime:"<< m_pushSpeedCountTime
		//	<< endl;

		//scene->SetDebugString(wss.str());

	}

	void Player::PlayerMove()//プレイヤーの向きや動きを管理する関数
	{
		auto pos = GetComponent<Transform>()->GetPosition();//ポジション取得
		auto Delta = App::GetApp()->GetElapsedTime();

		//左ステックの向きにプレイヤーが進む
		if (m_controler.bConnected)
		{
			pos.z += (m_controler.fThumbLY * (m_speed + m_pushSpeed) * Delta) * 2;
			pos.x += (m_controler.fThumbLX * (m_speed + m_pushSpeed) * Delta) * 2;

			m_Trans->SetPosition(pos);//ポジション更新
		}
		
		//ステックを傾けるとアニメーションが再生される
		if (!m_controler.fThumbLX == 0 || !m_controler.fThumbLY == 0)
		{
			auto Name = GetComponent<PNTBoneModelDraw>()->GetCurrentAnimation();
			if (Name != L"Walk")
			{
				//アニメーション変更
				GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");
			}

			//アニメーション再生
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(Delta);
		}
		else
		{
			auto Name = GetComponent<PNTBoneModelDraw>()->GetCurrentAnimation();
			if (Name != L"Stand")
			{
				//アニメーション変更
				GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Stand");
			}
			//アニメーション再生
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(0);

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

		//エラー音のSE			
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//キーボードデバック用

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bPushKeyTbl[VK_SPACE])//Bボタンを押したとき
		{
			if (mapManager->SelMapNow(pos) == 1)//もし、現在いるセル座標がマンホールなら
			{
				if (m_itemCount <= 0)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Error", 0, 0.9f);
				}
			}
			if (mapManager->SelMapNow(pos) == 4)//もし、現在いるセル座標がハッチなら
			{
				if (!m_key)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Error", 0, 0.9f);
				}
				if (m_key)
				{

				}
			}

		}

	}

	//マンホールの上にわなを仕掛ける処理
	void Player::ManholeSet(Vec3 pos)
	{
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//キーボードデバック用

		if (m_itemCount >= 1)//カウントが１以上なら
		{
			auto device = App::GetApp()->GetInputDevice().GetControlerVec();
			if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B||keyState.m_bPushKeyTbl[VK_SPACE])//Bボタンを押したとき
			{
				if (mapManager->SelMapNow(pos) == 1)//もし、現在いるセル座標がマンホールの上ならば
				{
					m_itemCount--;

					//SE生成マンホールにわなを仕掛ける音
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"SetManhole", 0, 0.9f);


					mapManager->MapDataUpdate(pos, 2);//罠を設置する

				}
			}


		}
	}

	void Player::AddBatteryUI()
	{
		auto stage = GetStage();

		stage->AddGameObject<SpriteNum>(L"Number", Vec2(30.0f, 30.0f), m_itemCount, Vec3(500.0f, 0.0f, 0.0f));//数字のスプライト生成
		stage->AddGameObject<Sprite>(L"Cross", Vec2(30.0f, 30.0f));


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
		m_itemCount += add;
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto enemy = dynamic_pointer_cast<Enemy>(other);//enemyクラスに変換
		if (enemy)
		{
			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//ゲームシーンに移動する
		}
	}

	//キーボード操作(デバック用)
	void Player::KeyBoardMove()
	{
		float speed = 30.0f;
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (keyState.m_bPushKeyTbl['W'])
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos.z += speed * delta;
			GetComponent<Transform>()->SetPosition(pos);
		}
		if (keyState.m_bPushKeyTbl['A'])
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos.x += -speed * delta;
			GetComponent<Transform>()->SetPosition(pos);
		}
		if (keyState.m_bPushKeyTbl['S'])
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos.z += -speed * delta;
			GetComponent<Transform>()->SetPosition(pos);
		}
		if (keyState.m_bPushKeyTbl['D'])
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos.x += speed * delta;
			GetComponent<Transform>()->SetPosition(pos);
		}
	}

	float Player::GetAngle()
	{
		auto pos = GetComponent<Transform>()->GetPosition();//ポジション取得
		auto Delta = App::GetApp()->GetElapsedTime();
		//スティックの傾きをラジアンにする
		float rad = -atan2(m_controler.fThumbLY, m_controler.fThumbLX);

		return rad;
	}

	int Player::GetBatteryCount()
	{
		return m_itemCount;
	}	

	//鍵を持っているかのゲッター
	bool Player::GetKey()
	{
		return m_key;
	}

	//鍵を持っているかのセッター
	void Player::SetKey(bool key)
	{
		m_key = key;
	}

	//追加スピードのセッター
	void Player::SetPushSpeed(float pushSpeed)
	{
		m_pushSpeed = pushSpeed;
		m_pushSpeedCountTime = 0.0f;
	}

}
//end basecross

