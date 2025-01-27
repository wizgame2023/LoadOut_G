/*!
@file GameStart.h
@brief �X�e�[�W���J�n���邽�߂̏���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameStart :public GameObject
	{
	private:
		int m_stageMode;//�X�e�[�W�̃��[�h
		int m_EnemyUpClearNum;
		vector<weak_ptr<Actor>> m_actorVec;
		vector<shared_ptr<Sprite>> m_spriteVec;
		shared_ptr<NuberManager> m_nuberManager;
		shared_ptr<Sprite> m_sprite;
	public:
		GameStart(shared_ptr<Stage>& StagePtr,int mode,int enemyUpClearNum);
		~GameStart();

		void OnCreate()override;//�J�n����
		void OnUpdate()override;//�X�V����
		void OnDestroy()override;//�폜������
	};

}
//end basecross
