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

		float m_repopItemCountTime;//�A�C�e�������|�b�v����^�C��
		float m_repopEnemyCountTime;//�G�����|�b�v����^�C��

		bool m_ClearFlag;//�N���A�̃t���O����
		bool m_GameOverFlag;//�Q�[���I�[�o�[�p�̃t���O	
		bool m_repopItemFlag;//�A�C�e���̃��|�b�v�t���O
		bool m_BGMChase;//�ǂ��������Ă��邩�ۑ�����ϐ�

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

		vector<Vec3> m_repopEnemyPos;//���|�b�v����Enemy�̃|�W�V����

	public:
		StageManager(shared_ptr<Stage>& stagePtr);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;

		void BGMChange();//BGM�̕ύX����
		void OnDestroy()override;//�폜���ꂽ�Ƃ��̏���

		void RepopEnemy();//Enemy�̃��|�b�v����
		void RepopItem();//���d�r�̃��|�b�v����

		void SetClearFlag(bool flag);//�Z�b�^�[
		void SetGameOverFlag(bool flag);//�Z�b�^�[
		void SetPlayerKeyFlag(int flag);//�Z�b�^�[
		void SetRepopEnemyPos(Vec3 pos);//�Z�b�^�[
	};

}
//end basecross
