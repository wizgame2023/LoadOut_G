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
	class YuusinStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		YuusinStage() :Stage() {}
		virtual ~YuusinStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

