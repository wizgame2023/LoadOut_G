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
		vector<weak_ptr<Actor>> m_actorVec;
		vector<shared_ptr<Sprite>> m_spriteVec;
		shared_ptr<NuberManager> m_nuberManager;
		shared_ptr<Sprite> m_sprite;
	public:
		GameStart(shared_ptr<Stage>& StagePtr,int mode,int enemyUpClearNum);
		~GameStart();

		void OnCreate()override;//開始処理
		void OnUpdate()override;//更新処理
		void OnDestroy()override;//削除時処理
	};

}
//end basecross
