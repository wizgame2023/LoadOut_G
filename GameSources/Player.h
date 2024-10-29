/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player :public GameObject
	{
	private:
		Vec3 m_Pos;//�|�W�V����
		Vec3 m_Rot;//��]�x
		int m_count;//�A�C�e���̏������A���̐��̕������}���z�[�����グ���

		shared_ptr<Transform> m_Trans;//�g�����X�t�H�[��

	public:
		Player(const shared_ptr<Stage>& StagePtr, Vec3 pos,Vec3 rot);//�R���X�g���N�^
		~Player();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�}���z�[���̏��㩂�ݒu����
		void SetUp();

		void AddCount(int add);
	};

}
//end basecross

