#pragma once
#include "stdafx.h"

namespace basecross {
	class Ground :public GameObject
	{
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転度
		int OneBlock;//このゲームの単位(この数値をセル座標では１とする)
	public:

		Ground(const shared_ptr<Stage>& StagePtr);//コンストラクタ
		~Ground();//デストラクタ

		virtual void OnCreate() override;//開始する際に呼び出す関数
		//virtual void OnUpdate() override;

	};
}
