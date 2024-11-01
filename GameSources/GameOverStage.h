/*!
@file GameOverStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

