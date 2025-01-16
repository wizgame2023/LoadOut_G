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

		float m_repopItemCountTime;//�A�C�e�������|�b�v����^�C���𑪂�ϐ�
		float m_repopItemCountTimeMax;//�A�C�e�������|�b�v����܂ł̎���
		float m_repopEnemyCountTime;//�G�����|�b�v����^�C��
		float m_repopRamdomItemCountTime;//�����_���A�C�e�������|�b�v����^�C��

		bool m_ClearFlag;//�N���A�̃t���O����
		bool m_GameOverFlag;//�Q�[���I�[�o�[�p�̃t���O	
		bool m_repopItemFlag;//�A�C�e���̃��|�b�v�t���O
		bool m_BGMChase;//�ǂ��������Ă��邩�ۑ�����ϐ�

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

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

		void KeyEvent();//���֌W�̃C�x���g

		void SetClearFlag(bool flag);//�Z�b�^�[
		void SetGameOverFlag(bool flag);//�Z�b�^�[
		void SetPlayerKeyFlag(int flag);//�Z�b�^�[
		void SetRepopEnemyPos(Vec3 pos);//�Z�b�^�[
		void SetRepopRandomItemPos(Vec3 pos);//�Z�b�^�[
	};

}
//end basecross
