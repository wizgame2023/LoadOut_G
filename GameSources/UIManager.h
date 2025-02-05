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
		shared_ptr<StageManager> m_stageManager;//ステージマネージャー
		shared_ptr<NuberManager> m_spriteNum;//数字スプライト
		shared_ptr<NuberManager> m_spriteNumSecond;//数字スプライトの二つ目

		shared_ptr<Sprite> m_text;//テキストのスプライト
		shared_ptr<Sprite> m_sprite;

		bool m_keyGetFlag;//鍵を手に入れる条件を満たしているか確認するフラグ
	public:
		UIManager(shared_ptr<Stage> &stagePtr);//コンストラクタ
		~UIManager();//デストラクタ

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void BatteryHow();//電池をどれくらい持っているかのUIを生成する
	};

}
//end basecross
