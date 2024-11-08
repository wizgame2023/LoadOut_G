/*!
@file RaySphere.h
@brief ���C�@���E
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RaySphere :public GameObject
	{
	private:
		vector<weak_ptr<GameObject>> m_discoveryObj;//�Ԃ������I�u�W�F�N�g�̃A�h���X����� �o����ΐÓI�ϐ��ɂ�����

		float m_range;//���E�̎˒�
		float m_move;//�������n�_����ǂꂭ�炢�ړ�����������ϐ�
		weak_ptr<GameObject> m_parentObj;//�e�I�u�W�F�N�g

		Vec3 m_pos;//�ʒu
		float m_rad;//�p�x

	public:
		RaySphere(shared_ptr<Stage>& stagePtr, Vec3 pos, float angle,weak_ptr<GameObject> parentObj);//�R���X�g���N�^
		~RaySphere();//�f�X�g���N�^

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		vector<weak_ptr<GameObject>> GetDisObj();//�擾�����I�u�W�F�N�g��n��

	};

}
//end basecross
