/*!
@file Character.h
@brief ���[�r�[�֌W�̐e�N���X
*/

#pragma once
#include "stdafx.h"
#include "MyCamera.h"

namespace basecross {
	class Movie :public GameObject
	{
	private:
		weak_ptr<MyCamera> m_stageCamera;//�X�e�[�W�p�̃J����
		shared_ptr<Camera> m_movieCamera;//���[�r�[�p�̂��߂�
		Vec3 testPos;
	public:
		Movie(shared_ptr<Stage>& stagePtr);
		~Movie();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//���[�r�[�p�̃J�����ɕύX������
		virtual void CameraChange();

		//�J������ړI�n�Ɍ����Ĉړ�������
		virtual Vec3 CameraMove(float speed,Vec3 pos,Vec3 tagetPos);
	};

}
//end basecross
