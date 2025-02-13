
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
			//�^�C�g���̃A�N�e�B�u�X�e�[�W�̐ݒ�
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
		strTexture = texPath + L"water0.png";//Title��ʂɕ\�����鐅
		app->RegisterTexture(L"water0", strTexture);
		strTexture = texPath + L"water.png";//Title��ʂɕ\�����鐅
		app->RegisterTexture(L"water", strTexture);
		strTexture = texPath + L"water2.png";//Title��ʂɕ\�����鐅
		app->RegisterTexture(L"water2", strTexture);
		strTexture = texPath + L"water3.png";//Title��ʂɕ\�����鐅
		app->RegisterTexture(L"water3", strTexture);
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
		app->RegisterTexture(L"GameClearText0", strTexture);
		strTexture = texPath + L"GameClearText2.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearText1", strTexture);
		strTexture = texPath + L"GameClearText.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearText2", strTexture);
		strTexture = texPath + L"GameClearText3.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearText3", strTexture);
		strTexture = texPath + L"GameClearText4.png";//�Q�[���N���A�̃e�N�X�`��
		app->RegisterTexture(L"GameClearText4", strTexture);
		strTexture = texPath + L"GameOver.png";//�Q�[���I�[�o�[�̃e�N�X�`��
		app->RegisterTexture(L"GameOverText", strTexture);
		strTexture = texPath + L"Light.png";//�Q�[���I�[�o�[�p�̃��C�g
		app->RegisterTexture(L"GameOverLight", strTexture);
		strTexture = texPath + L"StageText.png";//�Q�[���I�[�o�[�p�̃��C�g
		app->RegisterTexture(L"StageText", strTexture);
		strTexture = texPath + L"BackGround.png";//�w�i�p�̃X�v���C�g
		app->RegisterTexture(L"BackGround", strTexture);
		strTexture = texPath + L"RightArrowVer1.1.png";//�E���
		app->RegisterTexture(L"RightArrow", strTexture);
		strTexture = texPath + L"LeftArrowVer1.1.png";//�����
		app->RegisterTexture(L"LeftArrow", strTexture);
		strTexture = texPath + L"GaugeCover.png";//�Q�[�W�̃J�o�[
		app->RegisterTexture(L"GaugeCover", strTexture);
		strTexture = texPath + L"Gauge.png";//�Q�[�W
		app->RegisterTexture(L"Gauge", strTexture);
		strTexture = texPath + L"KeyGetText.png";//�Q�[�W
		app->RegisterTexture(L"KeyGetText", strTexture);
		strTexture = texPath + L"PauseScene.png";//�|�[�Y���
		app->RegisterTexture(L"PauseScene", strTexture);
		strTexture = texPath + L"PauseText.png";//�|�[�Y��ʕ���1
		app->RegisterTexture(L"PauseText", strTexture);
		strTexture = texPath + L"PauseText2.png";//�|�[�Y��ʕ���2
		app->RegisterTexture(L"PauseText2", strTexture);
		strTexture = texPath + L"PauseText3.png";//�|�[�Y��ʕ���3
		app->RegisterTexture(L"PauseText3", strTexture);
		strTexture = texPath + L"PauseText4.png";//�|�[�Y��ʕ���4
		app->RegisterTexture(L"PauseText4", strTexture);
		strTexture = texPath + L"Operation.png";//����m�F�C���X�g
		app->RegisterTexture(L"Operation", strTexture);
		strTexture = texPath + L"DecisionMozi.png";//����m�F�C���X�g
		app->RegisterTexture(L"DecisionMozi", strTexture);
		strTexture = texPath + L"PauseButton.png";//����m�F�C���X�g
		app->RegisterTexture(L"PauseButton", strTexture);
		strTexture = texPath + L"AButton.png";//A�{�^���Ŗ߂邱�Ƃ�m�点��C���X�g
		app->RegisterTexture(L"AButton", strTexture);
		strTexture = texPath + L"EnemyUpText.png";//�e�L�X�g(�G��|������)
		app->RegisterTexture(L"EnemyUpText", strTexture);
		strTexture = texPath + L"EnemyUpText2.png";//�e�L�X�g(�G��ł��グ��I)
		app->RegisterTexture(L"EnemyUpText2", strTexture);
		strTexture = texPath + L"Slash.png";//�X���b�V��
		app->RegisterTexture(L"Slash", strTexture);
		strTexture = texPath + L"LStick.png";//L�X�e�B�b�N�i�j
		app->RegisterTexture(L"LStick", strTexture);
		strTexture = texPath + L"LStick2.png";//L�X�e�B�b�N�i�ԁj
		app->RegisterTexture(L"LStick2", strTexture);
		strTexture = texPath + L"LStickLeft.png";//L�X�e�B�b�N�i�E�ɓ|���j
		app->RegisterTexture(L"LStickLeft", strTexture);
		strTexture = texPath + L"LStickRight.png";//L�X�e�B�b�N�i���ɓ|���j
		app->RegisterTexture(L"LStickRight", strTexture);
		strTexture = texPath + L"BackMozi.png";//�Z���N�g�X�e�[�W�ɕ\�����镶��
		app->RegisterTexture(L"BackMozi", strTexture);
		strTexture = texPath + L"BackMozi2.png";//�Z���N�g�X�e�[�W�ɕ\�����镶��
		app->RegisterTexture(L"BackMozi2", strTexture);
		strTexture = texPath + L"BackMozi3.png";//�Z���N�g�X�e�[�W�ɕ\�����镶��
		app->RegisterTexture(L"BackMozi3", strTexture);
		strTexture = texPath + L"XButton.png";//�Z���N�g�X�e�[�W�ɕ\�����镶��
		app->RegisterTexture(L"XButton", strTexture);
		strTexture = texPath + L"ClearConditionsText1.png";//������肷������e�N�X�`��1
		app->RegisterTexture(L"ClearConditionsText1", strTexture);
		strTexture = texPath + L"ClearConditionsText2.png";//������肷������e�N�X�`��2
		app->RegisterTexture(L"ClearConditionsText2", strTexture);
		strTexture = texPath + L"Check.png";//�`�F�b�N�̃e�N�X�`��
		app->RegisterTexture(L"Check", strTexture);
		strTexture = texPath + L"Spanner.png";//�X�p�i�̃e�N�X�`��
		app->RegisterTexture(L"Spanner", strTexture);
		strTexture = texPath + L"Spanner_HaveNo.png";//�X�p�i�������ĂȂ��ƒm�点��e�N�X�`��
		app->RegisterTexture(L"Spanner_HaveNo", strTexture);
		strTexture = texPath + L"1Tex.png";//�J�E���g�_�E���̂P�̃e�N�X�`��
		app->RegisterTexture(L"1Tex", strTexture);
		strTexture = texPath + L"2Tex.png";//�J�E���g�_�E���̂Q�̃e�N�X�`��
		app->RegisterTexture(L"2Tex", strTexture);
		strTexture = texPath + L"3Tex.png";//�J�E���g�_�E���̂R�̃e�N�X�`��
		app->RegisterTexture(L"3Tex", strTexture);
		strTexture = texPath + L"StartTex.png";//�J�E���g�_�E���̂R�̃e�N�X�`��
		app->RegisterTexture(L"StartTex", strTexture);

		strTexture = texPath + L"Wow_AngerLow.png";//�������̓{��}�[�N�̃e�N�X�`��(��)
		app->RegisterTexture(L"Wow_AngerLow", strTexture);
		strTexture = texPath + L"Wow_AngerMiddle.png";//�������̓{��}�[�N�̃e�N�X�`��(��)
		app->RegisterTexture(L"Wow_AngerMiddle", strTexture);	
		strTexture = texPath + L"Wow_Anger.png";//�������̓{��}�[�N�̃e�N�X�`��(��)
		app->RegisterTexture(L"Wow_AngerHi", strTexture);

		strTexture = texPath + L"QuestionMark_AngerLow.png";//�p�g���[�����̓{��}�[�N�̃e�N�X�`��(��)
		app->RegisterTexture(L"search_AngerLow", strTexture);
		strTexture = texPath + L"QuestionMark_AngerMiddle.png";//�p�g���[�����̓{��}�[�N�̃e�N�X�`��(��)
		app->RegisterTexture(L"search_AngerMiddle", strTexture);	
		strTexture = texPath + L"QuestionMark_AngerHi.png";//�p�g���[�����̓{��}�[�N�̃e�N�X�`��(��)
		app->RegisterTexture(L"search_AngerHi", strTexture);

		strTexture = texPath + L"AngerEffectLow.png";//Enemy���{�������̃G�t�F�N�g�e�N�X�`��(��)
		app->RegisterTexture(L"AngerEffectLow", strTexture);
		strTexture = texPath + L"AngerEffectMiddle.png";//Enemy���{�������̃G�t�F�N�g�e�N�X�`��(��)
		app->RegisterTexture(L"AngerEffectMiddle", strTexture);
		strTexture = texPath + L"AngerEffectHi.png";//Enemy���{�������̃G�t�F�N�g�e�N�X�`��(��)
		app->RegisterTexture(L"AngerEffectHi", strTexture);

		strTexture = texPath + L"Tutorial_Manhole.png";//�`���[�g���A���p�̃e�N�X�`��(�}���z�[��)
		app->RegisterTexture(L"Tutorial_Manhole", strTexture);
		strTexture = texPath + L"Tutorial_Manhole2.png";//�`���[�g���A���p�̃e�N�X�`��(�}���z�[��)
		app->RegisterTexture(L"Tutorial_Manhole2", strTexture);
		strTexture = texPath + L"Tutorial_Manhole3.png";//�`���[�g���A���p�̃e�N�X�`��(�}���z�[��)
		app->RegisterTexture(L"Tutorial_Manhole3", strTexture);
		strTexture = texPath + L"Tutorial_Manhole4.png";//�`���[�g���A���p�̃e�N�X�`��(�}���z�[��)
		app->RegisterTexture(L"Tutorial_Manhole4", strTexture);

		strTexture = texPath + L"GameExplanationTex0.png";//�Q�[���̗����������邽�߂̃e�N�X�`��(�^�C�g��)
		app->RegisterTexture(L"GameExplanationTex0", strTexture);
		strTexture = texPath + L"GameExplanationTex1.png";//�Q�[���̗����������邽�߂̃e�N�X�`��
		app->RegisterTexture(L"GameExplanationTex1", strTexture);
		strTexture = texPath + L"GameExplanationTex2.png";//�Q�[���̗����������邽�߂̃e�N�X�`��
		app->RegisterTexture(L"GameExplanationTex2", strTexture);
		strTexture = texPath + L"GameExplanationTex3.png";//�Q�[���̗����������邽�߂̃e�N�X�`��
		app->RegisterTexture(L"GameExplanationTex3", strTexture);

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
		//�X�e�[�W�̏��ʐ^//////////////////////////////////////////////////////////////////
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
		//�X�e�[�^�X��Ԃ�������
		strTexture = texPath + L"StutasDown.png";//�X�e�[�^�X�㏸
		app->RegisterTexture(L"StutasDown", strTexture);
		strTexture = texPath + L"StutasUP.png";//�X�e�[�^�X����
		app->RegisterTexture(L"StutasUp", strTexture);




		//BGMSE
		wstring soundWav = SoundPath + L"StageBGM.wav";
		App::GetApp()->RegisterWav(L"StageBGM", soundWav);
		soundWav = SoundPath + L"StageBGMEscape.wav";//�X�e�[�WBGM�ǂ��������Ă���Ƃ�
		App::GetApp()->RegisterWav(L"StageBGMEscape", soundWav);
		soundWav = SoundPath + L"SelectStageBGM.wav";//�Z���N�gBGM
		App::GetApp()->RegisterWav(L"SelectStageBGM", soundWav);
		soundWav = SoundPath + L"ItemGet.wav";
		App::GetApp()->RegisterWav(L"ItemGet", soundWav);
		soundWav = SoundPath + L"GameClrear.wav";
		App::GetApp()->RegisterWav(L"GameClrear", soundWav);
		soundWav = SoundPath + L"Scream.wav";//���ѐ���SE
		App::GetApp()->RegisterWav(L"Scream", soundWav);
		soundWav = SoundPath + L"Scream2.wav";//���ѐ���SE
		App::GetApp()->RegisterWav(L"Scream2", soundWav);
		soundWav = SoundPath + L"SetManhole.wav";//㩂��Z�b�g����SE
		App::GetApp()->RegisterWav(L"SetManhole", soundWav);
		soundWav = SoundPath + L"KeySE.wav";//������ɓ��ꂽSE
		App::GetApp()->RegisterWav(L"KeySE", soundWav);

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
		soundWav = SoundPath + L"Choice.wav";//�I���ړ�
		App::GetApp()->RegisterWav(L"Choice", soundWav);
		soundWav = SoundPath + L"Decision.wav";//����
		App::GetApp()->RegisterWav(L"Decision", soundWav);
		soundWav = SoundPath + L"CountDown.wav";//�J�E���g�_�E��
		App::GetApp()->RegisterWav(L"CountDownSE", soundWav);

		//���f���e�N�X�`��
		wstring modelTexture = modPath + L"Boss.png";//�G(��)�̃e�N�X�`��
		app->RegisterTexture(L"Boss_Texture", strTexture);


		//�{�[�����f��
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"enemy_ver1.0.bmf");//�G�̃��b�V���x�_�����ĂȂ��o�[�W����
		app->RegisterResource(L"Boss_Mesh_Kari", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"spec_enemy_ver1.0.bmf");//�G�̃��b�V����������G
		app->RegisterResource(L"Boss_Mesh_Spec", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"kid_ver2.0.bmf");//�v���C���[�̃��b�V��
		app->RegisterResource(L"kid_Mesh", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Spana_v1.0.bmf");//�X�p�i�ɕύX
		app->RegisterResource(L"Battry", boneModelMesh);
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"waterpiller_ver1.3.bmf");//�����̃��b�V��
		app->RegisterResource(L"WaterPillerMesh", boneModelMesh);

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
