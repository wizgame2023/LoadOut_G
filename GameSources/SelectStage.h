/*!
@file TilteStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "BlackOut.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SpriteNum>m_sprite;

		shared_ptr<Sprite> m_StagePhoto;
		shared_ptr<Sprite> m_StageText;
		shared_ptr<NuberManager> m_NumberSprite;
		shared_ptr<BlackOut> m_blackOut;//暗転処理
		shared_ptr<Sprite>m_spriteMozi;
		shared_ptr<Sprite>m_spriteB;

		int m_SelectStage;//選択しているステージ

		const int m_allStage = 20;
		
		bool m_decisionFlag;//選択したかどうかのフラグ

		CONTROLER_STATE m_controler;//コントローラー

	public:
		//構築と破棄
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SelectionStage();//どのステージにするかの選択処理

		void OnDestroy()override;

	};


}
//end basecross

