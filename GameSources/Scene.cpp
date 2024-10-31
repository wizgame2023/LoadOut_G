
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			auto& app = App::GetApp();

			auto path = app->GetDataDirWString();
			auto texPath = path + L"Textures/";


			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");

			GameResourses();


		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<YuutaStage>();
		}
	}

	void Scene::GameResourses()
	{
		auto& app = App::GetApp();

		auto path = app->GetDataDirWString();
		auto comPath = path + L"Comments/";
		auto texPath = path + L"Textures/";
		auto modPath = path + L"Models/";
		auto SoundPath = path + L"Sounds/";

		//テクスチャ
		wstring strTexture = texPath + L"Black.jpg";
		app->RegisterTexture(L"Black", strTexture);

		//モデルテクスチャ
		wstring modelTexture = modPath + L"Boss.png";//敵(仮)のテクスチャ
		app->RegisterTexture(L"Boss_Texture", strTexture);


		//ボーンモデル
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Boss.bmf");//敵(仮)のメッシュ
		app->RegisterResource(L"Boss_Mesh_Kari", boneModelMesh);

		//ボーンマルチメッシュ
		auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"Model_male.bmf");//プレイヤー(仮)メッシュ
		app->RegisterResource(L"Player_Mesh_Kari", boneMultiModelMesh);

	}

}
//end basecross
