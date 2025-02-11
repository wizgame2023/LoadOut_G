/*!
@file GameExplanation.h
@brief ゲームの流れの説明
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameExplanation:public GameObject
	{	
	private:
		int m_countPage;//ページを数える変数
		shared_ptr<Sprite> m_spriteTitle;
		shared_ptr<Sprite> m_spriteInfo;
		shared_ptr<Stage> m_stage;//現在のステージを取得する変数
		shared_ptr<SelectStage> m_selectStage;//現在のステージがセレクトだったら使う変数

		vector<weak_ptr<Sprite>> m_spriteVec;//このクラスで生成したスプライトを保存する配列

		int m_SelectStage;//選択しているステージ
		bool m_decisionFlag;//選択したかどうかのフラグ
		bool m_stickCheck;//スティックの傾けた処理を受け取るかのフラグ

		float m_countTime = 0;


		CONTROLER_STATE m_controler;//コントローラー

	public:
		GameExplanation(shared_ptr<Stage>& ptrStage);
		~GameExplanation();

		//ページ遷移の処理
		void SelectionPage();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};


}
//end basecross
