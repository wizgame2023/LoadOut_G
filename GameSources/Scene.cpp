
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			auto& app = App::GetApp();

			auto path = app->GetDataDirWString();
			auto texPath = path + L"Textures/";


			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage02>();
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
			//�^�C�g���̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<TilteStage>();
		}
		if (event->m_MsgStr == L"ToGameOverStage") {
			ResetActiveStage<GameOverStage>();
		}
		if (event->m_MsgStr == L"ToGameClearStage") {
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

		//�e�N�X�`��
		wstring strTexture = texPath + L"Black.jpg";
		app->RegisterTexture(L"Black", strTexture);
		strTexture = texPath + L"Title.jpg";//�^�C�g���p�̃e�N�X�`��
		app->RegisterTexture(L"Title", strTexture);
		strTexture = texPath + L"RordOutGameOver.png";//�Q�[���I�[�o�[�p�̃e�N�X�`��
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Manhole.png";//�}���z�[���p�̉��e�N�X�`��
		app->RegisterTexture(L"Manhole", strTexture);
		strTexture = texPath + L"Red.png";//�}���z�[���p�̉��e�N�X�`���ݒu�����Ƃ�
		app->RegisterTexture(L"Red", strTexture);
		strTexture = texPath + L"Prohibited.png";//�}���z�[���p�̒ʂ�Ȃ����e�N�X�`���ݒu�����Ƃ�
		app->RegisterTexture(L"Prohibited", strTexture);
		strTexture = texPath + L"Bule.png";//�A�C�e���̉��̐F
		app->RegisterTexture(L"Bule", strTexture);
		strTexture = texPath + L"RordOutGameClear.png";//�A�C�e���̉��̐F
		app->RegisterTexture(L"GameClear", strTexture);
		strTexture = texPath + L"Number.png";//�����̃e�N�X�`��
		app->RegisterTexture(L"Number", strTexture);
		strTexture = texPath + L"Cross.png";//�����̃e�N�X�`��
		app->RegisterTexture(L"Cross", strTexture);
		strTexture = texPath + L"water_texture.jpg";//���̃e�N�X�`��
		app->RegisterTexture(L"Water", strTexture);
		strTexture = texPath + L"StoneRoad.jpg";//�n�ʂ̃e�N�X�`��
		app->RegisterTexture(L"StoneRoad", strTexture);
		strTexture = texPath + L"Gray.png";//�~�j�}�b�v�̔w�i�̃e�N�X�`��
		app->RegisterTexture(L"Gray", strTexture);
		strTexture = texPath + L"White.png";//�~�j�}�b�v�̔w�i�̃e�N�X�`��
		app->RegisterTexture(L"White", strTexture);
		strTexture = texPath + L"MiniMapPlayer.png";//�~�j�}�b�v��Player�̃e�N�X�`��
		app->RegisterTexture(L"MiniPlayer", strTexture);
		strTexture = texPath + L"MiniMapEnemy.png";//�~�j�}�b�v��Player�̃e�N�X�`��
		app->RegisterTexture(L"MiniEnemy", strTexture);
		strTexture = texPath + L"battery_tan1.png";//���d�r(�P��)�̃e�N�X�`��
		app->RegisterTexture(L"Battery1", strTexture);
		strTexture = texPath + L"Wall.png";//�Εǂ̃e�N�X�`��
		app->RegisterTexture(L"StoneWall", strTexture);
		strTexture = texPath + L"StartMozi.png";//Title��ʂɕ\�����镶��
		app->RegisterTexture(L"StartMozi", strTexture);
		strTexture = texPath + L"StartMoziB.png";//Title��ʂɕ\�����镶��
		app->RegisterTexture(L"StartMoziB", strTexture);
		strTexture = texPath + L"CreditMozi.png";//Title��ʂɕ\�����镶��
		app->RegisterTexture(L"CreditMozi", strTexture);
		strTexture = texPath + L"Road5.jpg";//�Εǂ̃e�N�X�`��
		app->RegisterTexture(L"Road", strTexture);
		strTexture = texPath + L"Wow.png";//�G���������Ƃ��̃e�N�X�`��
		app->RegisterTexture(L"Wow", strTexture);
		strTexture = texPath + L"QuestionMark.png";//�G���T���Ă���Ƃ��̃e�N�X�`��
		app->RegisterTexture(L"search", strTexture);
		strTexture = texPath + L"ManholeRed.png";//�G���T���Ă���Ƃ��̃e�N�X�`��
		app->RegisterTexture(L"RedManhole", strTexture);
		strTexture = texPath + L"Key.png";//���̃e�N�X�`��
		app->RegisterTexture(L"Key", strTexture);
		strTexture = texPath + L"Clear.png";//�����̃e�N�X�`��
		app->RegisterTexture(L"Clear", strTexture);
		strTexture = texPath + L"Escape.png";//�����̒��̃e�N�X�`��
		app->RegisterTexture(L"Escape", strTexture);
		strTexture = texPath + L"Hatch.png";//�n�b�`�̃e�N�X�`��
		app->RegisterTexture(L"Hatch", strTexture);
		strTexture = texPath + L"Credit.png";//�n�b�`�̃e�N�X�`��
		app->RegisterTexture(L"Credit", strTexture);
		strTexture = texPath + L"GameClear.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearText", strTexture);
		strTexture = texPath + L"GameClearText2.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearTextBButton", strTexture);
		strTexture = texPath + L"GameClearText3.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearTextAButton", strTexture);
		strTexture = texPath + L"GameOver.png";//�Q�[���I�[�o�[�̃e�N�X�`��
		app->RegisterTexture(L"GameOverText", strTexture);
		strTexture = texPath + L"Light.png";//�Q�[���I�[�o�[�p�̃��C�g
		app->RegisterTexture(L"GameOverLight", strTexture);
		//�}���z�[���r���{�[�h�̃e�N�X�`��////////////////////////////////////////////////////
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


		//BGMSE
		wstring soundWav = SoundPath + L"StageBGM.wav";
		App::GetApp()->RegisterWav(L"StageBGM", soundWav);
		soundWav = SoundPath + L"StageBGMEscape.wav";//�X�e�[�WBGM�ǂ��������Ă���Ƃ�
		App::GetApp()->RegisterWav(L"StageBGMEscape", soundWav);
		soundWav = SoundPath + L"ItemGet.wav";
		App::GetApp()->RegisterWav(L"ItemGet", soundWav);
		soundWav = SoundPath + L"GameClrear.wav";
		App::GetApp()->RegisterWav(L"GameClrear", soundWav);
		soundWav = SoundPath + L"Scream.wav";//���ѐ���SE
		App::GetApp()->RegisterWav(L"Scream", soundWav);
		soundWav = SoundPath + L"SetManhole.wav";//㩂��Z�b�g����SE
		App::GetApp()->RegisterWav(L"SetManhole", soundWav);
	
		soundWav = SoundPath + L"Enemyded.wav";
		App::GetApp()->RegisterWav(L"EnemyDed", soundWav);
		soundWav = SoundPath + L"TIlteStage.wav";
		App::GetApp()->RegisterWav(L"TIlteStage", soundWav);
		soundWav = SoundPath + L"GameClear2.wav";//�Q�[���N���A
		App::GetApp()->RegisterWav(L"GameClear2", soundWav);
		soundWav = SoundPath + L"GameOver.wav";
		App::GetApp()->RegisterWav(L"GameOverBGM", soundWav);
		soundWav = SoundPath + L"Tracking.wav";
		App::GetApp()->RegisterWav(L"Tracking", soundWav);
		soundWav = SoundPath + L"Error.wav";//�G���[��
		App::GetApp()->RegisterWav(L"Error", soundWav);
		soundWav = SoundPath + L"StatusUp.wav";//�X�e�[�^�X�A�b�v
		App::GetApp()->RegisterWav(L"Status_Up", soundWav);
		soundWav = SoundPath + L"Status_DownVer1.2.wav";//�X�e�[�^�X�_�E��
		App::GetApp()->RegisterWav(L"Status_Down", soundWav);

		//���f���e�N�X�`��
		wstring modelTexture = modPath + L"Boss.png";//�G(��)�̃e�N�X�`��
		app->RegisterTexture(L"Boss_Texture", strTexture);


		//�{�[�����f��
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"police_ver1.1.bmf");//�G�̃��b�V��
		app->RegisterResource(L"Boss_Mesh_Kari", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"kid_ver1.3.bmf");//�v���C���[�̃��b�V��
		app->RegisterResource(L"kid_Mesh", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"battry_ver1.2.bmf");//�d�r�p�̃��b�V��
		app->RegisterResource(L"Battry", boneModelMesh);

		//�{�[���}���`���b�V��
		auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"Model_male.bmf");//�v���C���[(��)���b�V��
		app->RegisterResource(L"Player_Mesh_Kari", boneMultiModelMesh);
		boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"misterybox.bmf");
		app->RegisterResource(L"MisteryBox", boneMultiModelMesh);
		//boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"police_test.bmf");//�G(��)���b�V��
		//app->RegisterResource(L"Boss_Mesh_Kari2", boneMultiModelMesh);

	}

	void Scene::SetLastPlayStage(int playStage)
	{
		m_lastPlayStage = playStage;
	}

	//�P�̃u���b�N�̊�̑傫�� ���ꂪ�Z���ł����Ƃ����1�ɓ�����傫��
	int Scene::GetSelOneSize()
	{
		return m_OneBox;
	}

	//�Ō�Ƀv���C�����X�e�[�W��Ԃ�
	int Scene::GetLastPlayStage()
	{
		return m_lastPlayStage;
	}

}
//end basecross
