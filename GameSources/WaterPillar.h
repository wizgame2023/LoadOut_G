#pragma once
#include "stdafx.h"

namespace basecross {
	class WaterPillar :public GameObject
	{
		Vec3 m_pos;//ポジション
		Vec3 m_originPos;//元々の指定されていた位置
		Vec3 m_rot;//回転度
		Vec3 m_scale;//サイズ
		const int m_oneBlock;//このゲームの単位(この数値をセル座標では１とする)
		wstring m_texName;//テクスチャの名前
		int shape;//形をどうするかの変数

		int m_count;//進行度
	public:

		WaterPillar(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot,Vec3 scale);//コンストラクタ
		~WaterPillar();//デストラクタ

		virtual void OnCreate() override;//開始する際に呼び出す関数
		virtual void OnUpdate() override;

	};
}
