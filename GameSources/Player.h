/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "SpriteNum.h"

namespace basecross{
	class Player :public Actor
	{
	private:
		Vec3 m_Pos;//�|�W�V����
		Vec3 m_Rot;//��]�x

		int m_count;//�A�C�e���̏������A���̐��̕������}���z�[�����グ���
		int m_hp = 3;//Player�̗̑�

		float m_deg;//�p�x

		shared_ptr<Transform> m_Trans;//�g�����X�t�H�[��

		shared_ptr<InputDevice> m_Device;//�R���g���[���[
		CONTROLER_STATE m_controler;//�R���g���[���[
		shared_ptr<SpriteNum> m_spriteNum;//�����̃X�v���C�g
		//float m_time;//�e�X�g�p�g��Ȃ��Ȃ���������Ă�������

	public:
		Player(shared_ptr<Stage>& StagePtr, Vec3 pos,Vec3 rot);//�R���X�g���N�^
		~Player();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�}���z�[���̏��㩂�ݒu����
		void SetUp();

		void AddCount(int add);
		void PlayerMove();
		void ManholeSet(Vec3 pos);//�}���z�[���̏�ɂ�Ȃ��d�|����

		void OnCollisionEnter(shared_ptr<GameObject>& other);//�����蔻��
		void KeyBoardMove();

		float GetAngle()override;//�p�x��n��
		void AddBatteryUI();//�d�r���ǂꂭ�炢�擾���Ă��邩��UI
	};

}
//end basecross

