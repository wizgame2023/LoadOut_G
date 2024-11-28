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
		bool m_BGMChase;//�ǂ��������Ă��邩�ۑ�����ϐ�
		int m_BGMhow;//���Ȃɂ�BGM�𗬂�Ă��邩�ۑ�����ϐ�

		bool m_ClearFlag;//�N���A�̃t���O����

		shared_ptr<SoundItem> m_BGM;
		shared_ptr<XAudio2Manager> m_bgmManager;

	public:
		StageManager(shared_ptr<Stage>& stagePtr);
		~StageManager();

		void OnCreate()override;
		void OnUpdate()override;

		void BGMChange();//BGM�̕ύX����
		void OnDestroy()override;//�폜���ꂽ�Ƃ��̏���

		void SetClearFlag(bool flag);//�Z�b�^�[
	};

}
//end basecross
