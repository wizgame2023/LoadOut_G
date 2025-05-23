/*!
@file BlackOut.h
@brief Γ]
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BlackOut :public GameObject
	{
	private:
		shared_ptr<Sprite> m_sprite;//XvCg()

		bool m_blackOutFlag;
		bool m_unBlackOutFlag;
		bool m_blackorLight;//Γ]ΝfalseΎ]Νtrue
		bool m_switch;//Γ]AΎ]X^[g

	public:
		BlackOut(shared_ptr<Stage>& stagePtr,bool blackorLight);
		~BlackOut();

		void OnCreate()override;
		void OnUpdate()override;

		void SetSwitch(bool OnOff);//Γ]·ιΖ«ΜXCb`
		bool GetSwitch();

		bool GetBlackOutFlag();
		bool GetUnBlackOutFlag();
	};

}
//end basecross
