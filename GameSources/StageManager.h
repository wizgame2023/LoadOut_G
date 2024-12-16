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
		bool m_BGMChase;//追いかけられているか保存する変数
		int m_BGMhow;//今なにのBGMを流れているか保存する変数

		bool m_ClearFlag;//クリアのフラグ判定
		bool m_GameOverFlag;//ゲームオーバー用のフラグ
		int m_PlayerKeyFlag;///Playerが鍵を持ったかのフラグ
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

		float m_repopItemCountTime;//リポップするタイム
		bool m_repopItemFlag;//アイテムのリポップフラグ

	public:
		StageManager(shared_ptr<Stage>& stagePtr);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;

		void BGMChange();//BGMの変更処理
		void OnDestroy()override;//削除されたときの処理

		void SetClearFlag(bool flag);//セッター
		void SetGameOverFlag(bool flag);//セッター
		void SetPlayerKeyFlag(int flag);//セッター
	};

}
//end basecross
