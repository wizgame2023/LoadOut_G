/*!
@file BlackOut.h
@brief 暗転
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BlackOut :public GameObject
	{
	private:
		shared_ptr<Sprite> m_sprite;//スプライト(黒)

		bool m_blackOutFlag;
		bool m_unBlackOutFlag;
		bool m_blackorLight;//暗転はfalse明転はtrue
		bool m_switch;//暗転、明転スタート

	public:
		BlackOut(shared_ptr<Stage>& stagePtr,bool blackorLight);
		~BlackOut();

		void OnCreate()override;
		void OnUpdate()override;

		void SetSwitch(bool OnOff);//暗転するときのスイッチ
		bool GetSwitch();

		bool GetBlackOutFlag();
		bool GetUnBlackOutFlag();
	};

}
//end basecross
