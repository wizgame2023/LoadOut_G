
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
		if (event->m_MsgStr == L"ToGameStage02") {
			ResetActiveStage<GameStage02>();
		}
		if (event->m_MsgStr == L"ToGameStage03") {
			ResetActiveStage<GameStage03>();
		}
		if (event->m_MsgStr == L"ToGameStage04") {
			ResetActiveStage<GameStage04>();
		}
		if (event->m_MsgStr == L"ToGameStage05") {
			ResetActiveStage<GameStage05>();
		}
		if (event->m_MsgStr == L"ToGameStage06") {
			ResetActiveStage<GameStage06>();
		}
		if (event->m_MsgStr == L"ToGameStage07") {
			ResetActiveStage<GameStage07>();
		}
		if (event->m_MsgStr == L"ToGameStage08") {
			ResetActiveStage<GameStage08>();
		}
		if (event->m_MsgStr == L"ToGameStage09") {
			ResetActiveStage<GameStage09>();
		}
		if (event->m_MsgStr == L"ToGameStage10") {
			ResetActiveStage<GameStage10>();
		}
		if (event->m_MsgStr == L"ToTilteStage") {
			//タイトルのアクティブステージの設定
			ResetActiveStage<TilteStage>();
		}
		if (event->m_MsgStr == L"ToGameOverStage") {
			ResetActiveStage<GameOverStage>();
		}
		if (event->m_MsgStr == L"ToGameClearStage") {
			ResetActiveStage<GameClearStage>();
		}
		if (event->m_MsgStr == L"ToSelectStage") {
			ResetActiveStage<SelectStage>();
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
		strTexture = texPath + L"StartMozi.png";//Title画面に表示する文字
		app->RegisterTexture(L"StartMozi", strTexture);
		strTexture = texPath + L"StartMoziB.png";//Title画面に表示する文字
		app->RegisterTexture(L"StartMoziB", strTexture);
		strTexture = texPath + L"CreditMozi.png";//Title画面に表示する文字
		app->RegisterTexture(L"CreditMozi", strTexture);
		strTexture = texPath + L"water0.png";//Title画面に表示する水
		app->RegisterTexture(L"water0", strTexture);
		strTexture = texPath + L"water.png";//Title画面に表示する水
		app->RegisterTexture(L"water", strTexture);
		strTexture = texPath + L"water2.png";//Title画面に表示する水
		app->RegisterTexture(L"water2", strTexture);
		strTexture = texPath + L"water3.png";//Title画面に表示する水
		app->RegisterTexture(L"water3", strTexture);
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
		strTexture = texPath + L"Escape.png";//透明の柱のテクスチャ
		app->RegisterTexture(L"Escape", strTexture);
		strTexture = texPath + L"Hatch.png";//ハッチのテクスチャ
		app->RegisterTexture(L"Hatch", strTexture);
		strTexture = texPath + L"Credit.png";//ハッチのテクスチャ
		app->RegisterTexture(L"Credit", strTexture);
		strTexture = texPath + L"GameClear.png";//ゲームクリアのテクスチャ
		app->RegisterTexture(L"GameClearText", strTexture);
		strTexture = texPath + L"GameClearText2.png";//ゲームクリアのテクスチャ
		app->RegisterTexture(L"GameClearTextBButton", strTexture);
		strTexture = texPath + L"GameClearText3.png";//ゲームクリアのテクスチャ
		app->RegisterTexture(L"GameClearTextAButton", strTexture);
		strTexture = texPath + L"GameOver.png";//ゲームオーバーのテクスチャ
		app->RegisterTexture(L"GameOverText", strTexture);
		strTexture = texPath + L"Light.png";//ゲームオーバー用のライト
		app->RegisterTexture(L"GameOverLight", strTexture);
		strTexture = texPath + L"StageText.png";//ゲームオーバー用のライト
		app->RegisterTexture(L"StageText", strTexture);
		strTexture = texPath + L"BackGround.png";//背景用のスプライト
		app->RegisterTexture(L"BackGround", strTexture);
		strTexture = texPath + L"RightArrowVer1.1.png";//右矢印
		app->RegisterTexture(L"RightArrow", strTexture);
		strTexture = texPath + L"LeftArrowVer1.1.png";//左矢印
		app->RegisterTexture(L"LeftArrow", strTexture);
		//マンホールビルボードのテクスチャ////////////////////////////////////////////////////
		strTexture = texPath + L"Manhole_BillBoard_Push.png";
		app->RegisterTexture(L"Manhole_BillBoard_Push", strTexture);
		strTexture = texPath + L"Manhole_BillBoard_Hit.png";
		app->RegisterTexture(L"Manhole_BillBoard_Hit", strTexture);
		strTexture = texPath + L"Manhole_BillBoard_Up.png";
		app->RegisterTexture(L"Manhole_BillBoard_Up", strTexture);
		strTexture = texPath + L"battery_haveNo.png";
		app->RegisterTexture(L"Battery_HaveNo", strTexture);
		strTexture = texPath + L"Key_HaveNo.png";
		app->RegisterTexture(L"Key_HaveNo", strTexture);
		//////////////////////////////////////////////////////////////////////////////////////
		//ステージの上空写真//////////////////////////////////////////////////////////////////
		strTexture = texPath + L"Stage01.png";
		app->RegisterTexture(L"Stage01_HiShot", strTexture);
		strTexture = texPath + L"Stage02.png";
		app->RegisterTexture(L"Stage02_HiShot", strTexture);
		strTexture = texPath + L"Stage03.png";
		app->RegisterTexture(L"Stage03_HiShot", strTexture);
		strTexture = texPath + L"Stage04.png";
		app->RegisterTexture(L"Stage04_HiShot", strTexture);
		strTexture = texPath + L"Stage05.png";
		app->RegisterTexture(L"Stage05_HiShot", strTexture);
		strTexture = texPath + L"Stage06.png";
		app->RegisterTexture(L"Stage06_HiShot", strTexture);
		strTexture = texPath + L"Stage07.png";
		app->RegisterTexture(L"Stage07_HiShot", strTexture);
		strTexture = texPath + L"Stage08.png";
		app->RegisterTexture(L"Stage08_HiShot", strTexture);
		strTexture = texPath + L"Stage09.png";
		app->RegisterTexture(L"Stage09_HiShot", strTexture);
		strTexture = texPath + L"Stage10.png";
		app->RegisterTexture(L"Stage10_HiShot", strTexture);
		/////////////////////////////////////////////////////////////////////////////////////
		//ステータス状態を見せる
		strTexture = texPath + L"StutasDown.png";//ステータス上昇
		app->RegisterTexture(L"StutasDown", strTexture);
		strTexture = texPath + L"StutasUP.png";//ステータス下方
		app->RegisterTexture(L"StutasUp", strTexture);




		//BGMSE
		wstring soundWav = SoundPath + L"StageBGM.wav";
		App::GetApp()->RegisterWav(L"StageBGM", soundWav);
		soundWav = SoundPath + L"StageBGMEscape.wav";//ステージBGM追いかけられているとき
		App::GetApp()->RegisterWav(L"StageBGMEscape", soundWav);
		soundWav = SoundPath + L"SelectStageBGM.wav";//セレクトBGM
		App::GetApp()->RegisterWav(L"SelectStageBGM", soundWav);
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
		soundWav = SoundPath + L"Tracking.wav";
		App::GetApp()->RegisterWav(L"Tracking", soundWav);
		soundWav = SoundPath + L"Error.wav";//エラー音
		App::GetApp()->RegisterWav(L"Error", soundWav);
		soundWav = SoundPath + L"StatusUp.wav";//ステータスアップ
		App::GetApp()->RegisterWav(L"Status_Up", soundWav);
		soundWav = SoundPath + L"Status_DownVer1.2.wav";//ステータスダウン
		App::GetApp()->RegisterWav(L"Status_Down", soundWav);
		soundWav = SoundPath + L"Choice.wav";//選択移動
		App::GetApp()->RegisterWav(L"Choice", soundWav);
		soundWav = SoundPath + L"Decision.wav";//決定
		App::GetApp()->RegisterWav(L"Decision", soundWav);

		//モデルテクスチャ
		wstring modelTexture = modPath + L"Boss.png";//敵(仮)のテクスチャ
		app->RegisterTexture(L"Boss_Texture", strTexture);


		//ボーンモデル
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"police_ver1.1.bmf");//敵のメッシュ
		app->RegisterResource(L"Boss_Mesh_Kari", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"kid_ver1.3.bmf");//プレイヤーのメッシュ
		app->RegisterResource(L"kid_Mesh", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"battry_ver1.2.bmf");//電池用のメッシュ
		app->RegisterResource(L"Battry", boneModelMesh);

		//ボーンマルチメッシュ
		auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"Model_male.bmf");//プレイヤー(仮)メッシュ
		app->RegisterResource(L"Player_Mesh_Kari", boneMultiModelMesh);
		boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"misterybox.bmf");
		app->RegisterResource(L"MisteryBox", boneMultiModelMesh);
		//boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"police_test.bmf");//敵(仮)メッシュ
		//app->RegisterResource(L"Boss_Mesh_Kari2", boneMultiModelMesh);

	}

	void Scene::SetLastPlayStage(int playStage)
	{
		m_lastPlayStage = playStage;
	}

	//１つのブロックの基準の大きさ これがセルでいうところの1に当たる大きさ
	int Scene::GetSelOneSize()
	{
		return m_OneBox;
	}

	//最後にプレイしたステージを返す
	int Scene::GetLastPlayStage()
	{
		return m_lastPlayStage;
	}

}
//end basecross
