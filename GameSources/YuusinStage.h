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
	class YuusinStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		YuusinStage() :Stage() {}
		virtual ~YuusinStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

