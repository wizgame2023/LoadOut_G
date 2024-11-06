/*!
@file Ray.h
@brief ���C
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Ray :public GameObject
	{
	private:
	public:
		Ray(shared_ptr<Stage>& stagePtr);//�R���X�g���N�^
		~Ray();//�f�X�g���N�^

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}
//end basecross
