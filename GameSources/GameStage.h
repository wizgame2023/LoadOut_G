/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;
		void OutWallCreate(int selLength);//�O�ǂ����֐�
		void GameManager();//�X�e�[�W�̐i�s�x���Ǘ�����
		int GameEnemyState();//�S�Ă̓G�̑J�ڏ�Ԃ��󂯎��
		int EnemyNow = 0;

		void SetEnemy(int num);

	};


}
//end basecross

