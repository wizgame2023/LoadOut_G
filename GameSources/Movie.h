/*!
@file Character.h
@brief ムービー関係の親クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Movie :public GameObject
	{
	private:

	public:
		Movie(shared_ptr<Stage>& stagePtr);
		~Movie();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//ムービー用のカメラに変更させる
		virtual void CameraChange();
	};

}
//end basecross
