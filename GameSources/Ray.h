/*!
@file Ray.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Ray :public GameObject
	{
	private:
		vector<weak_ptr<GameObject>> m_discoveryObj;//�Ԃ������I�u�W�F�N�g�̃A�h���X�����

		float m_countTime;//���C�X�t�B�A�𐶐�����N�[���^�C���𑪂�ϐ�
		float m_range;//���C�̎˒�

		//weak_ptr<Enemy> m_parentObj;//�e�I�u�W�F�N�g
		weak_ptr<Enemy> m_parentObj;

	public:
		Ray(shared_ptr<Stage>& stagePtr,shared_ptr<Enemy> parentObj,float range);
		~Ray();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void SetDisObj(vector<weak_ptr<GameObject>> discoveryObj);//���C�X�t�B�A���擾�����I�u�W�F�N�g���󂯎��Z�b�^�[
		vector<weak_ptr<GameObject>> GetDisObj();//�擾�����I�u�W�F�N�g��n��

	};

}
//end basecross
