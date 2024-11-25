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

