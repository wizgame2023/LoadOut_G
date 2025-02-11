/*!
@file GameExplanation.cpp
@brief 説明用のゲームオブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameExplanation::GameExplanation(shared_ptr<Stage>& ptrStage) :
		GameObject(ptrStage),
		m_countPage(1)
	{
	}

	GameExplanation::~GameExplanation()
	{
	}

	void GameExplanation::OnCreate()
	{
		m_stage = GetStage();
		m_selectStage = dynamic_pointer_cast<SelectStage>(m_stage);
		if (m_selectStage)
		{
			m_selectStage->SetUpdateFlag(false);//セレクトステージのアップデートしない
			
			//背景スプライト
			auto sprite = m_stage->AddGameObject<Sprite>(L"Black", Vec2(1280.0f, 800.0f), Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 0.8f), 2);
			m_spriteVec.push_back(sprite);//配列に入れる
		}

		//戻る用スプライト
		auto sprite = m_stage->AddGameObject<Sprite>(L"BackMozi", Vec2(900 * 0.2f, 150 * 0.4f), Vec3(600.0f, -380.0f, 0.0f), Vec3(0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f),4);
		m_spriteVec.push_back(sprite);//配列に入れる
		sprite = m_stage->AddGameObject<Sprite>(L"AButton", Vec2(900 * 0.2f, 150 * 0.4f), Vec3(600.0f, -382.0f, 0.0f), Vec3(0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 5);
		m_spriteVec.push_back(sprite);//配列に入れる

		//タイトル生成
		m_spriteTitle = m_stage->AddGameObject<Sprite>(L"GameExplanationTex0", Vec2(800.0f, 300.0f), Vec3(0.0f, 300.0f, 0.0f),
									Vec3(0.0f, 0.0f, 0.0f),Col4(1.0f,1.0f,1.0f,1.0f),3);
		m_spriteVec.push_back(m_spriteTitle);//配列に入れる

		//説明スプライト
		m_spriteInfo = m_stage->AddGameObject<Sprite>(L"GameExplanationTex1", Vec2(1200.0f, 600.0f), Vec3(0.0f, -80.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 3);
		m_spriteVec.push_back(m_spriteInfo);//配列に入れる

		//スティックテクスチャ(左)
		sprite = m_stage->AddGameObject<Sprite>(L"LeftArrow", Vec2(50.0f, 50.0f), Vec3(-600.0f, -100.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 4);
		m_spriteVec.push_back(sprite);//配列に入れる
		//スティックテクスチャ(右)
		sprite = m_stage->AddGameObject<Sprite>(L"RightArrow", Vec2(50.0f, 50.0f), Vec3(600.0f, -100.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 4);
		m_spriteVec.push_back(sprite);//配列に入れる
	}

	//更新
	void GameExplanation::OnUpdate()
	{
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーのアナログスティックの向き
		m_controler = inputDevice.GetControlerVec()[0];
		
		//ページ遷移の処理
		SelectionPage();

		//ページによってテクスチャが変わる
		switch (m_countPage)
		{
		case 1:
			m_spriteInfo->SetTexture(L"GameExplanationTex1");
			break;
		case 2:
			m_spriteInfo->SetTexture(L"GameExplanationTex2");
			break;
		case 3:
			m_spriteInfo->SetTexture(L"GameExplanationTex3");
			break;
		default:
			break;
		}

		//Bボタン押したら終了
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A)
		{
			//自分自身を削除
			m_stage->RemoveGameObject<GameExplanation>(GetThis<GameExplanation>());

			//自分で作ったスプライトをすべて削除する
			for (auto sprite : m_spriteVec)
			{
				auto sharedSprite = sprite.lock();
				if (sharedSprite)
				{
					m_stage->RemoveGameObject<Sprite>(sharedSprite);//スプライト削除
				}
			}
		}
	}

	//消去された際
	void GameExplanation::OnDestroy()
	{
		if (m_selectStage)
		{
			m_selectStage->SetUpdateFlag(true);//セレクトステージのアップデートを復活
		}

	}
	
	//ページ遷移の処理
	void GameExplanation::SelectionPage()
	{
		//スティックを離したらまた受け取れるようにする
		if (m_controler.fThumbLX == 0 && !m_stickCheck)
		{
			//初期化
			m_stickCheck = true;
		}
		else if (m_stickCheck)
		{
			if (m_controler.fThumbLX <= -0.9f && m_stickCheck)//左
			{
				if (m_countPage > 1)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage--;
				}
				else if (m_countPage == 1)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage = 3;
				}
				m_stickCheck = false;//スティックを受け取れないようにする
			}
			if (m_controler.fThumbLX >= 0.9f && m_stickCheck)//右
			{
				if (m_countPage < 3)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage++;
				}
				else if (m_countPage == 3)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage = 1;
				}
				m_stickCheck = false;//スティックを受け取れないようにする
			}
		}
	}
}
//end basecross
