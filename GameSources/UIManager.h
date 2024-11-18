/*!
@file UIManager.h
@brief UIの管理をします
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIManager :public GameObject
	{
	private:

	public:
		UIManager(shared_ptr<Stage> &stagePtr);//コンストラクタ
		~UIManager();//デストラクタ

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void BatteryHow();//電池をどれくらい持っているかのUIを生成する
	};

}
//end basecross
