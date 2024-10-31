/*!
@file YuusinStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class YushinStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		YushinStage() :Stage() {}
		virtual ~YushinStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

