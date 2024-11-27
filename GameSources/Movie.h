/*!
@file Character.h
@brief ���[�r�[�֌W�̐e�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Movie :public GameObject
	{
	private:

	public:
		Movie(shared_ptr<Stage>& stagePtr);
		~Movie();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//���[�r�[�p�̃J�����ɕύX������
		virtual void CameraChange();
	};

}
//end basecross
