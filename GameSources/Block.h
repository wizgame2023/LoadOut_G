#pragma once
#include "stdafx.h"

namespace basecross {
	class Block :public GameObject
	{
		Vec3 m_pos;
		Vec3 m_rot;
	public:

		Block(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot);
		~Block();

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;

	};
}
