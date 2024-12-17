/*!
@file ManholeSprite.cpp
@brief ミニマップ用のマンホールスプライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ManholeSprite::ManholeSprite(shared_ptr<Stage>& stagePtr,shared_ptr<Manhole> parent, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, int layer):
		Sprite(stagePtr,textureName,size,pos,rot,color,layer),
		m_parent(parent)
	{
	}

	ManholeSprite::~ManholeSprite()
	{
	}

	void ManholeSprite::OnUpdate()
	{
		auto lock = m_parent.lock();
		if (lock)
		{
			auto delta = App::GetApp()->GetElapsedTime();//デルタタイム
			auto DrawSprite = GetComponent<PCTSpriteDraw>();
			auto state = lock->GetState();//ステート取得
			//電池を設置されていれば
			if (state == lock->Manhole_Start)
			{
				DrawSprite->SetTextureResource(L"Red");
			}
			//もうすぐ上がるなら
			if (state == lock->Manhole_SoonUp)
			{
				m_countTime += delta;
				if (m_countTime < 0.1f)
				{
					DrawSprite->SetTextureResource(L"Red");
				}
				if (m_countTime >= 0.1f)
				{
					m_countTime = 0.0f;
					DrawSprite->SetTextureResource(L"Black");
				}
			}
			//通れなくなっているなら
			if (state == lock->Manhole_Used)
			{
				DrawSprite->SetTextureResource(L"Black");
			}
			//電池を設置されていなければ
			if (state == lock->Manhole_None)
			{
				DrawSprite->SetTextureResource(L"Bule");
			}

		}
		//追跡元がなければ自分自身を消去する
		if (!lock)
		{
			GetStage()->RemoveGameObject<ManholeSprite>(GetThis<ManholeSprite>());
		}
	}


}
//end basecross
