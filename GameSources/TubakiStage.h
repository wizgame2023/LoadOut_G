/*!
@file TubakiStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TubakiStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		TubakiStage() :Stage() {}
		virtual ~TubakiStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

