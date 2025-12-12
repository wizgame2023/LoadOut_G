/*!
@file BlackOut.h
@brief 暗転,明転処理
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BlackOut :public GameObject
	{
	private:
		shared_ptr<Sprite> m_sprite; //スプライト(黒)

		bool m_blackOutFlag;   // 暗転フラグ
		bool m_unBlackOutFlag; // 明転フラグ
		bool m_blackorLight;   // 暗転はfalse明転はtrue
		bool m_switch;		   // 暗転、明転スタート

	public:
		BlackOut(shared_ptr<Stage>& stagePtr,bool blackorLight);
		~BlackOut();

		void OnCreate()override;
		void OnUpdate()override;

		void SetSwitch(bool OnOff); // 暗転するときのスイッチ
		bool GetSwitch();			// 暗転しているかのゲッタ

		bool GetBlackOutFlag();   // 暗転終了したかのフラグゲッタ
		bool GetUnBlackOutFlag(); // 明転終了したかのフラグゲッタ
	};

}
//end basecross
