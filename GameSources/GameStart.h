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
		int m_step;//GameStart�̗���
		float m_CountDownTimeCount;//�J�E���g�_�E���̎��Ԃ𑪂�ϐ�
		vector<weak_ptr<Actor>> m_actorVec;
		vector<shared_ptr<Sprite>> m_spriteVec;
		shared_ptr<NuberManager> m_nuberManager;
		shared_ptr<Sprite> m_sprite;
		shared_ptr<Sprite> m_spriteCountDown;//�J�E���g�_�E���p�̃X�v���C�g
	public:
		GameStart(shared_ptr<Stage>& StagePtr,int mode,int enemyUpClearNum);
		~GameStart();

		//GameStart�̗���
		enum GameStartCount
		{
			GAMESTART_Start,
			GAMESTART_CountDown_One,
			GAMESTART_CountDown_Two,
			GAMESTART_CountDown_Three,
			GAMESTART_CountDown_Start,
			GAMESTART_End
		};

		void OnCreate()override;//�J�n����
		void OnUpdate()override;//�X�V����
		void OnDestroy()override;//�폜������
	};

}
//end basecross
