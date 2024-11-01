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
	public:
		//構築と破棄
		TilteStage() :Stage() {}
		virtual ~TilteStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

