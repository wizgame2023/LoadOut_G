
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
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToTilteStage") {
			//�^�C�g���̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<TilteStage>();
		}
		if (event->m_MsgStr == L"ToGameOverStage") {
			//�^�C�g���̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameOverStage>();
		}
		if (event->m_MsgStr == L"ToGameClearStage") {
			//�^�C�g���̃A�N�e�B�u�X�e�[�W�̐ݒ�
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

		//�e�N�X�`��
		wstring strTexture = texPath + L"Black.jpg";
		app->RegisterTexture(L"Black", strTexture);
		strTexture = texPath + L"RordOutTitle.png";//�^�C�g���p�̃e�N�X�`��
		app->RegisterTexture(L"Title", strTexture);
		strTexture = texPath + L"RordOutGameOver.png";//�Q�[���I�[�o�[�p�̃e�N�X�`��
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Sand.jpg";//�}���z�[���p�̉��e�N�X�`��
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

		//BGMSE
		wstring soundWav = SoundPath + L"StageBGM.wav";
		App::GetApp()->RegisterWav(L"StageBGM", soundWav);
		soundWav = SoundPath + L"ItemGet.wav";
		App::GetApp()->RegisterWav(L"ItemGet", soundWav);


		//���f���e�N�X�`��
		wstring modelTexture = modPath + L"Boss.png";//�G(��)�̃e�N�X�`��
		app->RegisterTexture(L"Boss_Texture", strTexture);


		//�{�[�����f��
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Boss.bmf");//�G(��)�̃��b�V��
		app->RegisterResource(L"Boss_Mesh_Kari", boneModelMesh);

		//�{�[���}���`���b�V��
		auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"Model_male.bmf");//�v���C���[(��)���b�V��
		app->RegisterResource(L"Player_Mesh_Kari", boneMultiModelMesh);

	}

	//�P�̃u���b�N�̊�̑傫�� ���ꂪ�Z���ł����Ƃ����1�ɓ�����傫��
	int Scene::GetSelOneSize()
	{
		return m_OneBox;
	}

}
//end basecross
