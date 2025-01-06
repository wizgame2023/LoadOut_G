/*!
@file GameStage10.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "MiniMapManager.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage10 : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;
		shared_ptr<MiniMapManager> m_miniMapManager;

	public:
		//�\�z�Ɣj��
		GameStage10() :Stage() {}
		virtual ~GameStage10() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;
		void OutWallCreate(int selLength);//�O�ǂ����֐�
		int GameEnemyState();//�S�Ă̓G�̑J�ڏ�Ԃ��󂯎��
		int EnemyNow = 0;

		void CreatePlayer();//Player����
		void CreateBattery();//�A�C�e������
		void CreateEnemy();//Enemy����
		void CreateRamdomItem();//�����_���A�C�e������


		void SetEnemy(int num);

	};


}
//end basecross

