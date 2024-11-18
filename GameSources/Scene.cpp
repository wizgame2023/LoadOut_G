
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
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToTilteStage") {
			//タイトルのアクティブステージの設定
			ResetActiveStage<TilteStage>();
		}
		if (event->m_MsgStr == L"ToGameOverStage") {
			//タイトルのアクティブステージの設定
			ResetActiveStage<GameOverStage>();
		}
		if (event->m_MsgStr == L"ToGameClearStage") {
			//タイトルのアクティブステージの設定
			ResetActiveStage<GameOverStage>();
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
		strTexture = texPath + L"RordOutTitle.png";//タイトル用のテクスチャ
		app->RegisterTexture(L"Title", strTexture);
		strTexture = texPath + L"RordOutGameOver.png";//ゲームオーバー用のテクスチャ
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Sand.jpg";//マンホール用の仮テクスチャ
		app->RegisterTexture(L"Manhole", strTexture);
		strTexture = texPath + L"Red.png";//マンホール用の仮テクスチャ設置したとき
		app->RegisterTexture(L"Red", strTexture);
		strTexture = texPath + L"Prohibited.png";//マンホール用の通れない仮テクスチャ設置したとき
		app->RegisterTexture(L"Prohibited", strTexture);
		strTexture = texPath + L"Bule.png";//アイテムの仮の色
		app->RegisterTexture(L"Bule", strTexture);
		strTexture = texPath + L"RordOutGameClear.png";//アイテムの仮の色
		app->RegisterTexture(L"GameClear", strTexture);
		strTexture = texPath + L"Number.png";//数字のテクスチャ
		app->RegisterTexture(L"Number", strTexture);
		strTexture = texPath + L"Cross.png";//数字のテクスチャ
		app->RegisterTexture(L"Cross", strTexture);
		strTexture = texPath + L"water_texture.jpg";//水のテクスチャ
		app->RegisterTexture(L"Water", strTexture);
		strTexture = texPath + L"StoneRoad.jpg";//地面のテクスチャ
		app->RegisterTexture(L"StoneRoad", strTexture);
		strTexture = texPath + L"Gray.png";//ミニマップの背景のテクスチャ
		app->RegisterTexture(L"Gray", strTexture);
		strTexture = texPath + L"White.png";//ミニマップの背景のテクスチャ
		app->RegisterTexture(L"White", strTexture);
		strTexture = texPath + L"MiniMapPlayer.png";//ミニマップのPlayerのテクスチャ
		app->RegisterTexture(L"MiniPlayer", strTexture);
		strTexture = texPath + L"MiniMapEnemy.png";//ミニマップのPlayerのテクスチャ
		app->RegisterTexture(L"MiniEnemy", strTexture);
		strTexture = texPath + L"battery_tan1.png";//乾電池(単一)のテクスチャ
		app->RegisterTexture(L"Battery1", strTexture);

		//BGMSE
		wstring soundWav = SoundPath + L"StageBGM.wav";
		App::GetApp()->RegisterWav(L"StageBGM", soundWav);
		soundWav = SoundPath + L"ItemGet.wav";
		App::GetApp()->RegisterWav(L"ItemGet", soundWav);


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

	//１つのブロックの基準の大きさ これがセルでいうところの1に当たる大きさ
	int Scene::GetSelOneSize()
	{
		return m_OneBox;
	}

}
//end basecross
