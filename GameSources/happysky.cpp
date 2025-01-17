/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include <string>

namespace basecross {
	const std::map<std::wstring, Vec3> happysky::pairs = {
		{ L"000_000_000", Vec3(0  ,0,  +0.5f) },
		{ L"000_090_000", Vec3(+0.5f, 0, 0  ) },
		{ L"000_180_000", Vec3(0  ,0,  -0.5f) },
		{ L"000_270_000", Vec3(-0.5f, 0, 0  ) },
		{ L"090_000_000", Vec3(0  ,-0.5f,0  ) },
		{ L"270_000_000", Vec3(0  ,+0.5f,0  ) }
	};
	
	void happysky::OnCreate()
	{
		for (const auto& pair : pairs)
		{
			auto sky_base = ObjectFactory::Create<Sky_base>(GetStage());

			auto planeDrawComp = sky_base->GetComponent<PTStaticDraw>();
			planeDrawComp->SetTextureResource(pair.first);
			planeDrawComp->SetDepthStencilState(DepthStencilState::None);
			planeDrawComp->SetSamplerState(SamplerState::LinearClamp);

			auto planeTransComp = sky_base->GetComponent<Transform>();
			float rotX = XMConvertToRadians(std::stof(pair.first.substr(0, 3)));
			float rotY = XMConvertToRadians(std::stof(pair.first.substr(4, 3)));
			float rotZ = XMConvertToRadians(std::stof(pair.first.substr(8, 3)));
			const float scale = 707.0f;
			planeTransComp->SetPosition(pair.second * scale);
			planeTransComp->SetRotation(rotX, rotY, rotZ);
			planeTransComp->SetScale(Vec3(scale));
			planeTransComp->SetParent(GetThis<GameObject>());

			m_skybase.push_back(sky_base);
		}
	}

	void happysky::OnUpdate()
	{

	}

	void happysky::OnDraw()
	{
		for (auto& sky_base : m_skybase)
		{
			sky_base->OnDraw();
		}
	}
}
//end basecross
