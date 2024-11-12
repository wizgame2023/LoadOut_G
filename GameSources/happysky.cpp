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
		{ L"270_000_000", Vec3(0  ,-0.5f,0  ) }
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
		}
	}
}
//end basecross
