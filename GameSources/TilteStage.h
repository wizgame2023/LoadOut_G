/*!
@file TilteStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TilteStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		TilteStage() :Stage() {}
		virtual ~TilteStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

