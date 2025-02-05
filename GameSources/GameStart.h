/*!
@file GameStart.h
@brief ステージを開始するための処理
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameStart :public GameObject
	{
	private:
		int m_stageMode;//ステージのモード
		int m_EnemyUpClearNum;
		int m_step;//GameStartの流れ
		float m_CountDownTimeCount;//カウントダウンの時間を測る変数
		vector<weak_ptr<Actor>> m_actorVec;
		vector<shared_ptr<Sprite>> m_spriteVec;
		shared_ptr<NuberManager> m_nuberManager;
		shared_ptr<Sprite> m_sprite;
		shared_ptr<Sprite> m_spriteCountDown;//カウントダウン用のスプライト
	public:
		GameStart(shared_ptr<Stage>& StagePtr,int mode,int enemyUpClearNum);
		~GameStart();

		//GameStartの流れ
		enum GameStartCount
		{
			GAMESTART_Start,
			GAMESTART_CountDown_One,
			GAMESTART_CountDown_Two,
			GAMESTART_CountDown_Three,
			GAMESTART_CountDown_Start,
			GAMESTART_End
		};

		void OnCreate()override;//開始処理
		void OnUpdate()override;//更新処理
		void OnDestroy()override;//削除時処理
	};

}
//end basecross
