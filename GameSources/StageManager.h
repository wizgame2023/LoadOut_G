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
		int m_batteryCountMax;//ステージのバッテリー出現上限

		float m_repopItemCountTime;//アイテムがリポップするタイムを測る変数
		float m_repopItemCountTimeMax;//アイテムがリポップするまでの時間
		float m_repopEnemyCountTime;//敵がリポップするタイム
		float m_repopRamdomItemCountTime;//ランダムアイテムがリポップするタイム

		bool m_ClearFlag;//クリアのフラグ判定
		bool m_GameOverFlag;//ゲームオーバー用のフラグ	
		bool m_repopItemFlag;//アイテムのリポップフラグ
		bool m_BGMChase;//追いかけられているか保存する変数

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

		vector<Vec3> m_repopEnemyPos;//リポップするEnemyのポジション
		vector<Vec3> m_repopRandomItemPos;//リポップするRandomItemのポジション

	public:
		StageManager(shared_ptr<Stage>& stagePtr, int batteryMax = 5, float repopItemCountTimeMax = 15.0f);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;

		void BGMChange();//BGMの変更処理
		void EnemyStateCheck();
		void OnDestroy()override;//削除されたときの処理

		void RepopEnemy();//Enemyのリポップ処理
		void RepopItem();//乾電池のリポップ処理
		void RepopRandamItem();

		void KeyEvent();//鍵関係のイベント

		void SetClearFlag(bool flag);//セッター
		void SetGameOverFlag(bool flag);//セッター
		void SetPlayerKeyFlag(int flag);//セッター
		void SetRepopEnemyPos(Vec3 pos);//セッター
		void SetRepopRandomItemPos(Vec3 pos);//セッター
	};

}
//end basecross
