/*!
@file GameOverStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
	private:
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;

	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnDestroy()override;

	};


}
//end basecross

