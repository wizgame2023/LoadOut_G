/*!
@file StageManager.h
@brief ステージの進行を管理する
*/

#pragma once
#include "stdafx.h"
#include"SpriteMove.h"

namespace basecross {
	class StageManager :public GameObject
	{
	private:
		int m_BGMhow;//今なにのBGMを流れているか保存する変数
		int m_PlayerKeyFlag;///Playerが鍵を持ったかのフラグ
		int m_batteryCountMax;//ステージのバッテリー出現上限
		int m_EnemyUpClearNum;//敵を倒す目標数

		int m_pausCount;
		int m_count;
		int m_upEnemyCount;//敵を打ち上げた数
		int m_clearManagerCount;//クリアマネージャーの処理のカウント
		int m_stageMode;//ステージのモードを決める変数

		float m_repopItemCountTime;//アイテムがリポップするタイムを測る変数
		float m_repopItemCountTimeMax;//アイテムがリポップする時間
		float m_repopEnemyCountTime;//敵がリポップするタイムを測る変数
		float m_repopEnemyCountTimeMax;//敵がリポップする時間
		float m_repopRamdomItemCountTime;//ランダムアイテムがリポップする時間を測る変数
		float m_repopRamdomItemCountTimeMax;//ランダムアイテムがリポップする時間
		
		bool m_startFlag;//ゲームスタート開始したかのフラグ
		bool m_ClearFlag;//クリアのフラグ判定
		bool m_GameOverFlag;//ゲームオーバー用のフラグ	
		bool m_repopItemFlag;//アイテムのリポップフラグ
		bool m_BGMChase;//追いかけられているか保存する変数
		bool m_updateFlag;//アップデート処理をするかのフラグ

		bool m_pause;
		bool m_pauseFlag;
		bool m_stickCheck;
		bool m_operationFlag;

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;
		shared_ptr<SpriteMove> m_KeyGetText;

		shared_ptr<Sprite> m_white;

		shared_ptr<Sprite> PauseScene;
		shared_ptr<Sprite> m_pauseText;
		shared_ptr<Sprite> m_pauseText2;
		shared_ptr<Sprite> m_pauseText3;
		shared_ptr<Sprite> m_pauseText4;

		shared_ptr<Sprite> m_decisionMozi;
		shared_ptr<Sprite> m_spriteB;
		shared_ptr<Sprite>m_pauseButton;

		shared_ptr<Sprite> m_operation;
		shared_ptr<BlackOut> m_blackOut;//暗転処理

		vector<Vec3> m_repopEnemyPos;//リポップするEnemyのポジション
		vector<Vec3> m_repopRandomItemPos;//リポップするRandomItemのポジション

	public:
		StageManager(shared_ptr<Stage>& stagePtr, int batteryMax = 5, float repopItemCountTimeMax = 15.0f,float repopEnemyCountTimeMax = 15.0f,
					 float repopRamdomItemCountTimeMax = 60.0f
					);
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

		void ClearMode(int mode,int modeTwoCount = 5);//ステージのクリア条件の管理

		void SetClearFlag(bool flag);//セッター
		void SetGameOverFlag(bool flag);//セッター
		void SetPlayerKeyFlag(int flag);//セッター
		void SetRepopEnemyPos(Vec3 pos);//セッター
		void SetRepopRandomItemPos(Vec3 pos);//セッター
		void SetUpdateFlag(bool flag);//アップデートするかのセッター
		void SetStartFlag(bool Step);//ゲームが開始したかのセッター

		bool GetStartFlag();//ゲームが開始したかのゲッター
		int GetStageMode();//ステージモードを取得
		int GetUpEnemyCount();//倒した敵の数を渡す
		int GetUpEnemyCountMax();//倒すべき敵の数を渡す
		void AddUpEnemyCount(int count);//倒した数を追加する
	};

}
//end basecross