/*!
@file YuutaStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class YuutaStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		YuutaStage() :Stage() {}
		virtual ~YuutaStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

