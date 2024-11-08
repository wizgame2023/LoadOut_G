/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Sky_base::OnCreate()
	{
		std::vector<VertexPositionTexture> vertices = {
			{Vec3(-0.5f,+0.5f,0.0f),Vec2(0.0f,0.0f)},
			{Vec3(+0.5f,+0.5f,0.0f),Vec2(1.0f,0.0f)},
			{Vec3(-0.5f,-0.5f,0.0f),Vec2(0.0f,1.0f)},
			{Vec3(+0.5f,-0.5f,0.0f),Vec2(1.0f,1.0f)}
		};

		std::vector<uint16_t> indices = {
			0, 1, 2, 2, 1, 3
		};

		auto drawComp = AddComponent<PTStaticDraw>();
		drawComp->SetOriginalMeshUse(true);
		drawComp->CreateOriginalMesh(vertices, indices);
	}
}
//end basecross
