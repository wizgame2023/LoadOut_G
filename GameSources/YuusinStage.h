/*!
@file YuusinStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class YushinStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		YushinStage() :Stage() {}
		virtual ~YushinStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

