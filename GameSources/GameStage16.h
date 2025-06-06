/*!
@file GameStage16.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "MiniMapManager.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage16 : public Stage {
		//ビューの作成
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;
		shared_ptr<MiniMapManager> m_miniMapManager;

	public:
		//構築と破棄
		GameStage16() :Stage() {}
		virtual ~GameStage16() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;
		void OutWallCreate(int selLength);//外壁を作る関数
		int GameEnemyState();//全ての敵の遷移状態を受け取る
		int EnemyNow = 0;

		void CreatePlayer();//Player生成
		void CreateBattery();//アイテム生成
		void CreateEnemy();//Enemy生成

		void SetEnemy(int num);

	};


}
//end basecross

