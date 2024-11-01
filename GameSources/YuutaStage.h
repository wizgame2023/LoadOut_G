/*!
@file YuutaStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class YuutaStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		YuutaStage() :Stage() {}
		virtual ~YuutaStage() {}
		//初期化
		virtual void OnCreate()override;
		void OutWallCreate(int selLength);//外壁を作る関数
	};


}
//end basecross

