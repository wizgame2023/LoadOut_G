/*!
@file BlackOut.h
@brief �Ó]
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BlackOut :public GameObject
	{
	private:
		shared_ptr<Sprite> m_sprite;//�X�v���C�g(��)

		bool m_blackOutFlag;
		bool m_unBlackOutFlag;
		bool m_blackorLight;//�Ó]��false���]��true
		bool m_switch;//�Ó]�A���]�X�^�[�g

	public:
		BlackOut(shared_ptr<Stage>& stagePtr,bool blackorLight);
		~BlackOut();

		void OnCreate()override;
		void OnUpdate()override;

		void SetSwitch(bool OnOff);//�Ó]����Ƃ��̃X�C�b�`
		bool GetSwitch();

		bool GetBlackOutFlag();
		bool GetUnBlackOutFlag();
	};

}
//end basecross
