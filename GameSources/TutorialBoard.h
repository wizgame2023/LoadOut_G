/*!
@file TutorialBoard.h
@brief �`���[�g���A�����Ǘ�����}�l�[�W���[
*/

#pragma once
#include "stdafx.h"
#include "Actor.h"

namespace basecross {
	class TutorialBoard :public Actor
	{
	private:
		//�̃e�N�X�`���̃A�j���[�V�����̗���
		enum TUTORIALBOARDFLOAW
		{
			TutorialBoard_Start,//�}���z�[���Ƀ����`���g�������Ă����e�N�X�`��
			TutorialBoard_EnemyUp1,//�}���z�[�����g���ēG��ł��グ�悤���ăe�N�X�`��
			TutorialBoard_EnemyUp2,//�}���z�[�����g���ēG��ł��グ�悤���ăe�N�X�`��
			TutorialBoard_EnemyUp3,//�}���z�[�����g���ēG��ł��グ�悤���ăe�N�X�`��
			TutorialBoard_Reset//�����ɗ�����TutorialBoard_Start�ɖ߂�
		};
		Vec3 m_pos;//���W

		weak_ptr<Player> m_player;//�v���C���[
		shared_ptr<PNTStaticDraw> m_ptrDraw;

		int m_flow;//�i�s�x�v��
		bool m_changeTexture;//�e�N�X�`�����ύX�������o����ϐ�
		float m_countTime;//���Ԍo�ߌv��
	public:
		TutorialBoard(shared_ptr<Stage>& stagPtr,Vec3 pos);
		~TutorialBoard();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross