/*!
@file StageManager.h
@brief �X�e�[�W�̐i�s���Ǘ�����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageManager :public GameObject
	{
	private:
		int m_BGMhow;//���Ȃɂ�BGM�𗬂�Ă��邩�ۑ�����ϐ�
		int m_PlayerKeyFlag;///Player���������������̃t���O
		int m_batteryCountMax;//�X�e�[�W�̃o�b�e���[�o�����

		int m_pausCount;
		int m_count;
		//int m_KeyTextFlag;//������ɓ���Ă��邩�̃t���O

		float m_repopItemCountTime;//�A�C�e�������|�b�v����^�C���𑪂�ϐ�
		float m_repopItemCountTimeMax;//�A�C�e�������|�b�v����܂ł̎���
		float m_repopEnemyCountTime;//�G�����|�b�v����^�C��
		float m_repopRamdomItemCountTime;//�����_���A�C�e�������|�b�v����^�C��

		bool m_ClearFlag;//�N���A�̃t���O����
		bool m_GameOverFlag;//�Q�[���I�[�o�[�p�̃t���O	
		bool m_repopItemFlag;//�A�C�e���̃��|�b�v�t���O
		bool m_BGMChase;//�ǂ��������Ă��邩�ۑ�����ϐ�
		bool m_updateFlag;//�A�b�v�f�[�g���������邩�̃t���O

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

		shared_ptr<BlackOut> m_blackOut;//�Ó]����

		vector<Vec3> m_repopEnemyPos;//���|�b�v����Enemy�̃|�W�V����
		vector<Vec3> m_repopRandomItemPos;//���|�b�v����RandomItem�̃|�W�V����

	public:
		StageManager(shared_ptr<Stage>& stagePtr, int batteryMax = 5, float repopItemCountTimeMax = 15.0f);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;

		void BGMChange();//BGM�̕ύX����
		void EnemyStateCheck();
		void OnDestroy()override;//�폜���ꂽ�Ƃ��̏���

		void RepopEnemy();//Enemy�̃��|�b�v����
		void RepopItem();//���d�r�̃��|�b�v����
		void RepopRandamItem();

		void PauseEvent();

		void KeyEvent();//���֌W�̃C�x���g

		void SetClearFlag(bool flag);//�Z�b�^�[
		void SetGameOverFlag(bool flag);//�Z�b�^�[
		void SetPlayerKeyFlag(int flag);//�Z�b�^�[
		void SetRepopEnemyPos(Vec3 pos);//�Z�b�^�[
		void SetRepopRandomItemPos(Vec3 pos);//�Z�b�^�[
		void SetUpdateFlag(bool flag);//�A�b�v�f�[�g���邩�̃Z�b�^�[
	};

}
//end basecross
