/*!
@file StageManager.h
@brief ステージの進行を管理する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageManager :public GameObject
	{
	private:
		int m_BGMhow;//今なにのBGMを流れているか保存する変数
		int m_PlayerKeyFlag;///Playerが鍵を持ったかのフラグ

		float m_repopItemCountTime;//アイテムがリポップするタイム
		float m_repopEnemyCountTime;//敵がリポップするタイム

		bool m_ClearFlag;//クリアのフラグ判定
		bool m_GameOverFlag;//ゲームオーバー用のフラグ	
		bool m_repopItemFlag;//アイテムのリポップフラグ
		bool m_BGMChase;//追いかけられているか保存する変数

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

		vector<Vec3> m_repopEnemyPos;//リポップするEnemyのポジション

	public:
		StageManager(shared_ptr<Stage>& stagePtr);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;

		void BGMChange();//BGMの変更処理
		void OnDestroy()override;//削除されたときの処理

		void RepopEnemy();//Enemyのリポップ処理
		void RepopItem();//乾電池のリポップ処理

		void SetClearFlag(bool flag);//セッター
		void SetGameOverFlag(bool flag);//セッター
		void SetPlayerKeyFlag(int flag);//セッター
		void SetRepopEnemyPos(Vec3 pos);//セッター
	};

}
//end basecross
