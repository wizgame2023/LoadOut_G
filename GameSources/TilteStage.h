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
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<Sprite> m_sprite;
		shared_ptr<Sprite> m_Credit;

		float m_transparency = 1;
		bool m_transparent = false;
		bool m_creditCount=true;
	public:
		//�\�z�Ɣj��
		TilteStage() :Stage() {}
		virtual ~TilteStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnDestroy()override;

	};


}
//end basecross

