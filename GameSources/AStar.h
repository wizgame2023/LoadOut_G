/*!
@file AStar.h
@brief 経路探査処理
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class AStar :GameObject
	{
	private:

	public:
		AStar(shared_ptr<Stage>& stagePtr);//コンストラクタ
		~AStar();//デストラクタ

		void OnCreate() override;//作成
		void OnUpdate() override;//更新
	};

}
//end basecross
