/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;
		void OutWallCreate(int selLength);//外壁を作る関数
		void GameManager();//ステージの進行度を管理する
		int GameEnemyState();//全ての敵の遷移状態を受け取る
		int EnemyNow = 0;

		void SetEnemy(int num);

	};


}
//end basecross

