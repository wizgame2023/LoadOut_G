#pragma once
#include "stdafx.h"

namespace basecross {
	class Block :public GameObject
	{
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転度
		const int m_oneBlock;//このゲームの単位(この数値をセル座標では１とする)
	public:

		Block(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot);//コンストラクタ
		~Block();//デストラクタ

		virtual void OnCreate() override;//開始する際に呼び出す関数
		//virtual void OnUpdate() override;

	};
}
