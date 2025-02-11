/*!
@file TutorialBoard.cpp
@brief チュートリアルのマネージャー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TutorialBoard::TutorialBoard(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		Actor(stagePtr),
		m_pos(pos),
		m_changeTexture(false),
		m_countTime(0.0f),
		m_flow(TutorialBoard_Start)
	{

	}


	TutorialBoard::~TutorialBoard()
	{

	}

	//作成
	void TutorialBoard::OnCreate()
	{
		//Transform作成
		auto ptr = GetComponent<Transform>();//Transform取得
		ptr->SetPosition(m_pos);
		ptr->SetRotation(Vec3(0.0f,0.0f,0.0f));
		ptr->SetScale(15.0f, 10.0f, 0.001f);

		//メッシュ生成
		m_ptrDraw = AddComponent<PNTStaticDraw>();
		m_ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		m_ptrDraw->SetTextureResource(L"Tutorial_Manhole");
		m_ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		SetAlphaActive(true);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//Player取得
		m_player = GetStage()->GetSharedGameObject<Player>(L"Player");

		//AddTag(L"Block");//ブロック用のタグこれが基礎のオブジェクト

	}

	//更新
	void TutorialBoard::OnUpdate()
	{
		//アップデートフラグがオンになったらアップデートする
		if (!m_move) return;

		auto player = m_player.lock();
		//参照元がいなくなったら自分も消える
		if (!player)
		{
			GetStage()->RemoveGameObject<TutorialBoard>(GetThis<TutorialBoard>());
			return;
		}
		auto delta = App::GetApp()->GetElapsedTime();

		m_countTime += delta;

		//進行度経過(敵を打ち上げろテクスチャが出ていない時)
		if (m_countTime > 2.0f && m_flow == TutorialBoard_Start)
		{
			m_flow++;
			m_countTime = 0.0f;
		}
		//進行度経過(敵を打ち上げろテクスチャが出ている時)
		if (m_countTime > 1.0f && m_flow != TutorialBoard_Start)
		{
			m_flow++;
			m_countTime = 0.0f;
			//進行度が一番最後になったら一番最初に戻る
			if (m_flow == TutorialBoard_Reset)
			{
				m_flow = TutorialBoard_Start;
			}
		}

		//進行度によってテクスチャが変わる
		switch (m_flow)
		{
		case TutorialBoard_Start:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole");
			break;
		case TutorialBoard_EnemyUp1:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole2");
			break;
		case TutorialBoard_EnemyUp2:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole3");
			break;
		case TutorialBoard_EnemyUp3:
			m_ptrDraw->SetTextureResource(L"Tutorial_Manhole4");
			break;
		default:
			break;
		}

		//Playerのpos取得
		Vec3 playerPos = player->GetComponent<Transform>()->GetPosition();
		//Playerのz座標が自分よりも高ければ半透明になる
		if (playerPos.z >= m_pos.z)
		{
			m_ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		}
		if (playerPos.z < m_pos.z)
		{
			m_ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

}
//end basecross