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
	class TilteStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<Sprite>m_spriteMozi;
		shared_ptr<Sprite>m_spriteB;
		shared_ptr<Sprite> m_Credit;
		shared_ptr<Sprite> m_break;
		shared_ptr<Sprite> m_water;

		float m_transparency = 1;
		float m_anCollar = 0;
		float m_waterH = 0.5f;
		float m_waterY = 0;
		float m_time = 0;

		int m_count=0;

		
		bool m_transparent = false;
		bool m_creditCount=true;
		bool m_onFaed = false;
	public:
		//構築と破棄
		TilteStage() :Stage() {}
		virtual ~TilteStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnDestroy()override;

	};


}
//end basecross

