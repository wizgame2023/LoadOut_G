/*!
@file BlackOut.cpp
@brief 暗転
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BlackOut::BlackOut(shared_ptr<Stage>& stagePtr, bool blackorLight) :
		GameObject(stagePtr),
		m_switch(false),
		m_blackorLight(blackorLight),
		m_unBlackOutFlag(false),
		m_blackOutFlag(false)
	{

	}

	BlackOut::~BlackOut()
	{

	}

	void BlackOut::OnCreate()
	{
		//暗転する際の初期スプライト
		if (!m_blackorLight)
		{
			m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800), Vec3(0), Vec3(0), Col4(1.0f, 1.0f, 1.0f, 0.0f));
			m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));//色入れる
		}
		//明転する際の初期スプライト
		if (m_blackorLight)
		{
			m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800), Vec3(0), Vec3(0), Col4(1.0f, 1.0f, 1.0f, 1.0f));
			m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));//色入れる
		}

	}

	void BlackOut::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		Col4 spriteColor = m_sprite->GetColor();

		//暗転処理開始するなら通る
		if (m_switch)
		{
			//暗転処理
			if (!m_blackorLight)
			{
				spriteColor.w += delta;
				m_sprite->SetColor(spriteColor);//色入れる
			}
			//明転処理
			if (m_blackorLight)
			{
				spriteColor.w -= delta;
				m_sprite->SetColor(spriteColor);//色入れる
			}
		}

		//暗転する色で埋め尽くされたら暗転終了のフラグ
		if (spriteColor.w >= 1.0f)
		{
			m_blackOutFlag = true;
		}
		else
		{
			m_blackOutFlag = false;
		}

		//明転する色で埋め尽くされたら暗転終了のフラグ
		if (spriteColor.w <= 0.0f)
		{
			m_unBlackOutFlag = true;
		}
		else
		{
			m_unBlackOutFlag = false;
		}
	}

	//動くか動かないかのセッター
	void BlackOut::SetSwitch(bool OnOff)
	{
		m_switch = OnOff;
	}

	//暗転終わったかのゲッタ
	bool BlackOut::GetBlackOutFlag()
	{
		return m_blackOutFlag;
	}
	//明暗終わったかのゲッタ
	bool BlackOut::GetUnBlackOutFlag()
	{
		return m_unBlackOutFlag;
	}

	

}
//end basecross
