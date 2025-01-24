/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	//コンストラクタの宣言・デストラクタ
	Enemy::Enemy(shared_ptr<Stage>& StagePtr) :
		Actor(StagePtr),
		m_pos(-95.0f,2.5f,95.0f),
		m_startPos(-95.0f, 2.5f, 95.0f),
		m_scale(5.0f),
		m_playerPos(0,0,0),
		m_speed(10),
		m_angle(0),
		m_startPop(true)//初めてのスポーンかどうか
	{
	}
	Enemy::Enemy(shared_ptr<Stage>& StagePtr,Vec3 pos,bool startPop) :
		Actor(StagePtr),
		m_pos(pos),
		m_startPos(pos),
		m_scale(5.0f),
		m_playerPos(0, 0, 0),
		m_speed(10),
		m_angle(0),
		m_startPop(startPop)//初めてのスポーンかどうか
	{
	}
	Enemy::~Enemy()
	{

	}

	void Enemy::OnCreate()
	{
		GetComponent<Transform>()->SetScale(m_scale);
		GetComponent<Transform>()->SetPosition(m_pos);
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Boss_Mesh_Kari");
		ptrDraw->AddAnimation(L"Default", 6, 10, true, 20.0f);
		ptrDraw->AddAnimation(L"Ran", 6, 20, true, 20.0f);

		m_mapMgr = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");

		//初期配置ならパトロール状態再配置なら上から降ってくる演出付き
		if (m_startPop)
		{
			m_CurrentSt = make_shared<Patrol>(GetThis<Enemy>());
		}
		if (!m_startPop)
		{
			m_CurrentSt = make_shared<RepopEnemy>(GetThis<Enemy>(),0.0f);
		}

		Mat4x4 spanMat;
		spanMat.affineTransformation
		(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//影を付ける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"Boss_Mesh_Kari");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Enemy");

		m_CurrentSt->OnStart();

		//m_forwardRay = GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 15.0f);
		//m_playerRay= GetStage()->AddGameObject<Ray>(GetThis<Enemy>(), 60.0f);

		MoveSwitch(true);//動けるようにする

		//ビルボードの生成
		m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(),0);
	}

	void Enemy::OnUpdate()
	{
		if (!m_move)//フラグがオンになったら動ける
		{
			return;
		}

		auto trans = GetComponent<Transform>();
		auto app = App::GetApp;
		m_CurrentSt->OnUpdate();//現在のステート更新処理
		m_pos = trans->GetPosition();
		//次のステート用変数に何かしらのステートが代入されたら
		if(m_NextSt)
		{
			m_CurrentSt->OnExit();// 現在のステートが最後に行う処理
			
			m_CurrentSt.reset();// 現在のステート用の変数を空にする
		
			m_CurrentSt = m_NextSt;// 現在のステートに次のステートを代入
			
			m_NextSt.reset();// 次のステート用の変数を空にする
		
			m_CurrentSt->OnStart();// 切り替わった新しいステートの最初に行う処理
		}

		//auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得

		//if (mapManager->SelMapNow(trans->GetPosition())==2)
		//{
		//	GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
		//}
		auto rot = GetComponent<Transform>()->GetRotation();
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		float playerVec = atan2f((m_pos.x - m_playerPos.x), (m_pos.z - m_playerPos.z)) + XM_PI * 0.5;//所有者(Enemy)を中心にplayerの方向を計算


		auto state = GetNowState();
		//auto castEnemy = dynamic_pointer_cast<Enemy>(manhole);
		if (!dynamic_pointer_cast<Tracking>(state))
		{
			m_billBoard->ChangeTexture(L"search");
			m_speed = 10.0f;
		}
		if (dynamic_pointer_cast<Tracking>(state))
		{
			m_billBoard->ChangeTexture(L"Wow");
			m_speed = 20.0f;
		}

		//float angle = playerVec - m_angle;
		//視界の作成
		//if (angle > m_angle + XM_PI * 0.25 || angle < m_angle-XM_PI*0.25)
		//{
		//	angle = m_angle;
		//}
		//m_forwardRay->SetAngle(m_angle);
		//m_leftRay->SetAngle(m_angle - XM_PI * 0.5f);
		//m_playerRay->SetAngle(angle);
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"\n敵の回転.x : " << rot.x
		//	<< L"\n敵の回転.y : " << rot.y
		//	<< L"\n敵の回転.z : " << rot.z
		//	<< L"\nplayerPos.x : " << m_playerPos.x
		//	<< L"\nplayerPos.z : " << m_playerPos.z
		//	<< L"\nアングル : " << m_angle
		//	<< L"\nplayerRay : " << XMConvertToDegrees(playerVec)
		//	<< L"\nangle : " << XMConvertToDegrees(angle)
		//<< endl;

		//scene->SetDebugString(wss.str());

		//アニメーションの更新
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto delta = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(delta);

	}
	void Enemy::OnDestroy()
	{
		// オブジェクト自体が破棄される時に現在と次のステート用の変数を空にする
		m_CurrentSt.reset();
		m_NextSt.reset();
		////SE生成 敵の叫び声
		//auto SEManager = App::GetApp()->GetXAudio2Manager();
		//auto SE = SEManager->Start(L"Scream", 0, 0.9f);
		auto stage = GetStage();
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		//自分が鍵を持っているとき
		if (this->FindTag(L"Key"))
		{	
			//鍵をPlayerに渡す
			//GetStage()->GetSharedGameObject<Player>(L"Player")->SetKey(true);
			stageManager->SetPlayerKeyFlag(1);
		}
		stageManager->AddUpEnemyCount(1);//敵が１体打ちあがったことを知らせる

	}

	float Enemy::GetSpeed()
	{
		return m_speed;
	}

	float Enemy::GetAngle()
	{
		return  m_angle;
	}

	void Enemy::SetAngle(float angle)
	{
		m_angle = angle;
	}

	float Enemy::GetDistance(Vec3 a, Vec3 b)
	{ 
		float numX = a.x - b.x;
		float numY = a.y - b.y;
		float numZ = a.z - b.z;

		return  sqrtf(numX * numX + numY * numY + numZ * numZ);
	}

	Vec3 Enemy::GetPlayerPos()
	{
		return m_playerPos;
	}
	Vec3 Enemy::GetStartPos()
	{
		return m_startPos;
	}
	shared_ptr<Ray> Enemy::GetForwardRay()
	{
		return m_forwardRay;
	}

	shared_ptr<Ray> Enemy::GetPlayerRay()
	{
		return m_playerRay;
	}

	shared_ptr<StateBase> Enemy::GetNowState()
	{
		return m_CurrentSt;
	}

	shared_ptr<MapManager> Enemy::GetMapMgr()
	{
		return m_mapMgr;
	}

	void Enemy::GetGameOverScene()
	{
		GetStage()->AddGameObject<MovieGameOver>();
	}


}
//end basecross
