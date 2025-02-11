/*!
@file GameExplanation.h
@brief �Q�[���̗���̐���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameExplanation:public GameObject
	{	
	private:
		int m_countPage;//�y�[�W�𐔂���ϐ�
		shared_ptr<Sprite> m_spriteTitle;
		shared_ptr<Sprite> m_spriteInfo;
		shared_ptr<Stage> m_stage;//���݂̃X�e�[�W���擾����ϐ�
		shared_ptr<SelectStage> m_selectStage;//���݂̃X�e�[�W���Z���N�g��������g���ϐ�

		vector<weak_ptr<Sprite>> m_spriteVec;//���̃N���X�Ő��������X�v���C�g��ۑ�����z��

		int m_SelectStage;//�I�����Ă���X�e�[�W
		bool m_decisionFlag;//�I���������ǂ����̃t���O
		bool m_stickCheck;//�X�e�B�b�N�̌X�����������󂯎�邩�̃t���O

		float m_countTime = 0;


		CONTROLER_STATE m_controler;//�R���g���[���[

	public:
		GameExplanation(shared_ptr<Stage>& ptrStage);
		~GameExplanation();

		//�y�[�W�J�ڂ̏���
		void SelectionPage();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;
	};


}
//end basecross
