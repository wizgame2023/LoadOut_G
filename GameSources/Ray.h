/*!
@file Ray.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RaySphere;//�v���g�^�C�v�錾�݂����Ȃ��̉��}���u�݂����Ȃ��̂����炠�܂葽�p�������Ȃ�

	class Ray :public GameObject
	{
	private:
		vector<weak_ptr<GameObject>> m_discoveryObj;//�Ԃ������I�u�W�F�N�g�̃A�h���X�����

		float m_countTime;//���C�X�t�B�A�𐶐�����N�[���^�C���𑪂�ϐ�
		float m_range;//���C�̎˒�
		float m_angle;//�p�x

		weak_ptr<Actor> m_parentObj;//�e�I�u�W�F�N�g

		vector<weak_ptr<RaySphere>> m_raySphere;//�Ԃ������I�u�W�F�N�g�̃A�h���X�����

	public:
		Ray(shared_ptr<Stage>& stagePtr,shared_ptr<Actor> parentObj,float range);
		~Ray();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void ResetDisObj();//���C�X�t�B�A�̓��������I�u�W�F�N�g�̃|�C���^�z��̃��Z�b�g
		void ResetRaySphere();//�o�Ă��郌�C�X�t�B�A��S�č폜



		void SetAngle(float angle);//�p�x������Z�b�^�[
		float GetAngle();//�p�x��n���Q�b�^�[
		void SetDisObj(vector<weak_ptr<GameObject>> discoveryObj);//���C�X�t�B�A���擾�����I�u�W�F�N�g���󂯎��Z�b�^�[
		vector<weak_ptr<GameObject>> GetDisObj();//�擾�����I�u�W�F�N�g��n��

	};

}
//end basecross
