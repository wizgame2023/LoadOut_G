/*!
@file Character.h
@brief ムービー関係の親クラス
*/

#pragma once
#include "stdafx.h"
#include "MyCamera.h"

namespace basecross {
	class Movie :public GameObject
	{
	private:
		weak_ptr<MyCamera> m_stageCamera;//ステージ用のカメラ
		shared_ptr<Camera> m_movieCamera;//ムービー用のかめら
		Vec3 testPos;
	public:
		Movie(shared_ptr<Stage>& stagePtr);
		~Movie();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//ムービー用のカメラに変更させる
		virtual void CameraChange();

		//カメラを目的地に向けて移動させる
		virtual Vec3 CameraMove(float speed,Vec3 pos,Vec3 tagetPos);
	};

}
//end basecross
