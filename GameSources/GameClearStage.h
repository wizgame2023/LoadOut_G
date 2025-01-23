/*!
@file GameClearStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameClearStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<Sprite> m_clearText1;
		shared_ptr<Sprite> m_clearText2;
		shared_ptr<Sprite> m_clearText3;

		int m_count=0;
		bool m_stickCheck;
		bool m_buttonCheck;
	public:
		//構築と破棄
		GameClearStage() :Stage() {}
		virtual ~GameClearStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;

	};


}
//end basecross

