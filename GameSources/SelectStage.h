/*!
@file TilteStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SpriteNum>m_sprite;

		const int m_allStage = 20;
		

	public:
		//構築と破棄
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnDestroy()override;

	};


}
//end basecross

