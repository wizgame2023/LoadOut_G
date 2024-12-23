/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "MiniMapManager.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;
		shared_ptr<MiniMapManager> m_miniMapManager;

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;
		void OutWallCreate(int selLength);//外壁を作る関数
		int GameEnemyState();//全ての敵の遷移状態を受け取る
		int EnemyNow = 0;

		void CreatePlayer();//Player生成
		void CreateItem();//アイテム生成
		void CreateEnemy();//Enemy生成

		void SetEnemy(int num);

	};


}
//end basecross

