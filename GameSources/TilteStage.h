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
		shared_ptr<Sprite> m_sprite;
		shared_ptr<Sprite> m_Credit;

		float m_transparency = 1;
		bool m_transparent = false;
		bool m_creditCount=true;
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

