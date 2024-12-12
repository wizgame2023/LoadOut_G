
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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTilteStage");

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
			ResetActiveStage<GameClearStage>();
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
		strTexture = texPath + L"Title.jpg";//タイトル用のテクスチャ
		app->RegisterTexture(L"Title", strTexture);
		strTexture = texPath + L"RordOutGameOver.png";//ゲームオーバー用のテクスチャ
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Manhole.png";//マンホール用の仮テクスチャ
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
		strTexture = texPath + L"Wall.png";//石壁のテクスチャ
		app->RegisterTexture(L"StoneWall", strTexture);
		strTexture = texPath + L"StartMozi.png";//石壁のテクスチャ
		app->RegisterTexture(L"StartMozi", strTexture);
		strTexture = texPath + L"Road5.jpg";//石壁のテクスチャ
		app->RegisterTexture(L"Road", strTexture);
		strTexture = texPath + L"Wow.png";//敵が見つけたときのテクスチャ
		app->RegisterTexture(L"Wow", strTexture);
		strTexture = texPath + L"QuestionMark.png";//敵が探しているときのテクスチャ
		app->RegisterTexture(L"search", strTexture);
		strTexture = texPath + L"ManholeRed.png";//敵が探しているときのテクスチャ
		app->RegisterTexture(L"RedManhole", strTexture);
		strTexture = texPath + L"Key.png";//鍵のテクスチャ
		app->RegisterTexture(L"Key", strTexture);
		strTexture = texPath + L"Clear.png";//透明のテクスチャ
		app->RegisterTexture(L"Clear", strTexture);


		//BGMSE
		wstring soundWav = SoundPath + L"StageBGM.wav";
		App::GetApp()->RegisterWav(L"StageBGM", soundWav);
		soundWav = SoundPath + L"StageBGMEscape.wav";//ステージBGM追いかけられているとき
		App::GetApp()->RegisterWav(L"StageBGMEscape", soundWav);
		soundWav = SoundPath + L"ItemGet.wav";
		App::GetApp()->RegisterWav(L"ItemGet", soundWav);
		soundWav = SoundPath + L"GameClrear.wav";
		App::GetApp()->RegisterWav(L"GameClrear", soundWav);
		soundWav = SoundPath + L"Scream.wav";//叫び声のSE
		App::GetApp()->RegisterWav(L"Scream", soundWav);
		soundWav = SoundPath + L"SetManhole.wav";//罠をセットするSE
		App::GetApp()->RegisterWav(L"SetManhole", soundWav);
	
		soundWav = SoundPath + L"Enemyded.wav";
		App::GetApp()->RegisterWav(L"EnemyDed", soundWav);
		soundWav = SoundPath + L"TIlteStage.wav";
		App::GetApp()->RegisterWav(L"TIlteStage", soundWav);
		soundWav = SoundPath + L"GameClear2.wav";//ゲームクリア
		App::GetApp()->RegisterWav(L"GameClear2", soundWav);
		soundWav = SoundPath + L"GameOver.wav";
		App::GetApp()->RegisterWav(L"GameOverBGM", soundWav);
		soundWav = SoundPath + L"Tracking.wav";//なぜかダメ
		App::GetApp()->RegisterWav(L"Tracking", soundWav);

		//モデルテクスチャ
		wstring modelTexture = modPath + L"Boss.png";//敵(仮)のテクスチャ
		app->RegisterTexture(L"Boss_Texture", strTexture);


		//ボーンモデル
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"police_ver1.1.bmf");//敵のメッシュ
		app->RegisterResource(L"Boss_Mesh_Kari", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"kid_ver1.1.bmf");//プレイヤーのメッシュ
		app->RegisterResource(L"kid_Mesh", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"battry_ver1.2.bmf");//電池用のメッシュ
		app->RegisterResource(L"Battry", boneModelMesh);

		//ボーンマルチメッシュ
		auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"Model_male.bmf");//プレイヤー(仮)メッシュ
		app->RegisterResource(L"Player_Mesh_Kari", boneMultiModelMesh);
		//boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"police_test.bmf");//敵(仮)メッシュ
		//app->RegisterResource(L"Boss_Mesh_Kari2", boneMultiModelMesh);

	}

	//１つのブロックの基準の大きさ これがセルでいうところの1に当たる大きさ
	int Scene::GetSelOneSize()
	{
		return m_OneBox;
	}

}
//end basecross
