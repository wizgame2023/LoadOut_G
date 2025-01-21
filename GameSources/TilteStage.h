/*!
@file TilteStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "BlackOut.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TilteStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<Sprite>m_spriteMozi;
		shared_ptr<Sprite>m_spriteB;
		shared_ptr<Sprite> m_Credit;
		shared_ptr<Sprite> m_water;
		shared_ptr<BlackOut> m_black;

		float m_transparency = 1;
		float m_anCollar = 0;
		float m_waterH = 0.5f;
		float m_waterY = 0;
		float m_time = 0;

		int m_count=0;

		
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

