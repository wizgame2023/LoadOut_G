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
	class SelectStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<Sprite>m_sprite;
		float m_transparency = 1;

		const int m_allStage = 10;
		bool m_transparent = false;

	public:
		//�\�z�Ɣj��
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnDestroy()override;

	};


}
//end basecross

