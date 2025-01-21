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

		int m_pausCount;
		int m_count;
		//int m_KeyTextFlag;//鍵を手に入れているかのフラグ

		float m_repopItemCountTime;//アイテムがリポップするタイムを測る変数
		float m_repopItemCountTimeMax;//アイテムがリポップするまでの時間
		float m_repopEnemyCountTime;//敵がリポップするタイム
		float m_repopRamdomItemCountTime;//ランダムアイテムがリポップするタイム

		bool m_ClearFlag;//クリアのフラグ判定
		bool m_GameOverFlag;//ゲームオーバー用のフラグ	
		bool m_repopItemFlag;//アイテムのリポップフラグ
		bool m_BGMChase;//追いかけられているか保存する変数
		bool m_updateFlag;//アップデート処理をするかのフラグ

		bool m_pause;
		bool m_pauseFlag;
		bool m_stickCheck;

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;
		shared_ptr<Sprite> m_KeyGetText;

		shared_ptr<Sprite> m_white;

		shared_ptr<Sprite> PauseScene;
		shared_ptr<Sprite> m_pauseText;
		shared_ptr<Sprite> m_pauseText2;
		shared_ptr<Sprite> m_pauseText3;

		shared_ptr<BlackOut> m_blackOut;//暗転処理

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

		void PauseEvent();

		void KeyEvent();//鍵関係のイベント

		void SetClearFlag(bool flag);//セッター
		void SetGameOverFlag(bool flag);//セッター
		void SetPlayerKeyFlag(int flag);//セッター
		void SetRepopEnemyPos(Vec3 pos);//セッター
		void SetRepopRandomItemPos(Vec3 pos);//セッター
		void SetUpdateFlag(bool flag);//アップデートするかのセッター
	};

}
//end basecross
