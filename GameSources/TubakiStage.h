/*!
@file TubakiStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TubakiStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		TubakiStage() :Stage() {}
		virtual ~TubakiStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

