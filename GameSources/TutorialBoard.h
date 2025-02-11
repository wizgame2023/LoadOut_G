/*!
@file TutorialBoard.h
@brief チュートリアルを管理するマネージャー
*/

#pragma once
#include "stdafx.h"
#include "Actor.h"

namespace basecross {
	class TutorialBoard :public Actor
	{
	private:
		//板のテクスチャのアニメーションの流れ
		enum TUTORIALBOARDFLOAW
		{
			TutorialBoard_Start,//マンホールにレンチを使おうっていうテクスチャ
			TutorialBoard_EnemyUp1,//マンホールを使って敵を打ち上げようってテクスチャ
			TutorialBoard_EnemyUp2,//マンホールを使って敵を打ち上げようってテクスチャ
			TutorialBoard_EnemyUp3,//マンホールを使って敵を打ち上げようってテクスチャ
			TutorialBoard_Reset//ここに来たらTutorialBoard_Startに戻る
		};
		Vec3 m_pos;//座標

		weak_ptr<Player> m_player;//プレイヤー
		shared_ptr<PNTStaticDraw> m_ptrDraw;

		int m_flow;//進行度計測
		bool m_changeTexture;//テクスチャが変更したか覚える変数
		float m_countTime;//時間経過計測
	public:
		TutorialBoard(shared_ptr<Stage>& stagPtr,Vec3 pos);
		~TutorialBoard();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross