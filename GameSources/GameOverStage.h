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
		shared_ptr<Sprite> m_clearText1;
		shared_ptr<Sprite> m_clearText2;
		shared_ptr<Sprite> m_clearText3;

		int m_count = 0;
		bool m_stickCheck;
		bool m_buttonCheck;
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

