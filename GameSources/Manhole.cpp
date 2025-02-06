/*!
@file Manhole.cpp
@brief �}���z�[��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Manhole::Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos) :
		GameObject(stagePtr),
		m_pos(pos),
		m_charen(Manhole_None),
		m_UpdateFlag(true)
	{

	}
	Manhole::~Manhole()
	{
	}

	void Manhole::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(0.0f,0.0f,0.0f);
		ptr->SetScale(10.0f*0.5f, 1.0f, 10.0f*0.5f);

		//Transform�ɑ΂��Ă̓�������
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(2.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���b�V������
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CYLINDER");
		ptrDraw->SetTextureResource(L"Manhole");
		ptrDraw->SetOwnShadowActive(true); // �e�̉f�荞�݂𔽉f������
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);//�R���W������������悤�ɂ���

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�̃|�C���^�擾

		AddTag(L"Manhole");//�}���z�[���p�̃^�O

		//GetStage()->AddGameObject<BillBoard>();

		//�r���{�[�h�̐���
		m_billBoard = GetStage()->AddGameObject<BillBoard>(GetThis<GameObject>(), L"Clear",3, 13.0f, Vec3(0.0f, 0.0f, 0.0f));
		m_billBoardSecond = GetStage()->AddGameObject<BillBoardGauge>(GetThis<GameObject>(), L"Clear", 3, 13.0f, Vec3(0.0f, 0.0f, 0.0f));


	}

	void Manhole::OnUpdate()
	{
		//�I���Ȃ�A�b�v�f�[�g����
		if (!m_UpdateFlag) return;

		m_mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�̃|�C���^�擾
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto stage = GetStage();//�X�e�[�W�擾

		ManholeTransition();//�}���z�[���̑J��

		//�}���z�[���ɓd�r���ݒu���ꂽ�Ƃ��̃r���{�[�h����
		if (m_mapManager.lock()->SelMapNow(m_pos) >= 2)
		{			
			m_billBoardTime += delta;
			if (m_billBoardTime < 0.8f)
			{
				m_billBoard->SetPushY(13.0f);
				m_billBoard->SetScale(Vec3(5.0f, 5.0f, 5.0f));
				m_billBoard->ChangeTexture(L"Manhole_BillBoard_Hit");
			}
			if (m_billBoardTime >= 0.8f)
			{
				m_billBoard->SetPushY(13.0f);
				m_billBoard->SetScale(Vec3(5.0f, 5.0f, 5.0f));
				m_billBoard->ChangeTexture(L"Manhole_BillBoard_Up");
			}
			if (m_billBoardTime >= 1.6f)
			{
				m_billBoardTime = 0.0f;
			}
		}

		if (m_charen == Manhole_Used)
		{
			//�ǂ̂��炢�ɂȂ�����ʍs�֎~���猳�ɖ߂邩�̃Q�[�W
			//�Q�[�W�J�o�[
			m_billBoard->SetPushY(20.0f);
			m_billBoard->ChangeTexture(L"GaugeCover");
			m_billBoard->SetScale(Vec3(5.0f, 1.0f, 3.0f));
			//�Q�[�W�o�[
			m_billBoardSecond->SetPushY(20.0f);
			m_billBoardSecond->ChangeTexture(L"Gauge");
			m_billBoardSecond->SetScale(Vec3(5.0f, 1.0f, 3.0f));

		}

		//�e�N�X�`�����Z�b�g
		if (m_mapManager.lock()->SelMapNow(m_pos) < 2)
		{
			m_billBoard->SetScale(Vec3(0.0f, 0.0f, 0.0f));
			m_billBoard->ChangeTexture(L"Clear");
			m_billBoardSecond->SetScale(Vec3(0.0f, 0.0f, 0.0f));
			m_billBoardSecond->ChangeTexture(L"Clear");
		}

		//�v���C���[���ݒu�����}���z�[�����痣�ꂽ�ۂɏ����̊Ԃ������G�ɂ���
		if (m_playerStanbyFlag&& m_playerUpTime<0.5f)
		{
			m_playerUpTime += delta;
		}

	}

	//�}���z�[���̑J��
	void Manhole::ManholeTransition()
	{
		auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��
		auto stage = GetStage();//�X�e�[�W�擾
		auto a = m_mapManager.lock()->SelMapNow(m_pos);
		//�Z�����W�ɃA�C�e����ݒu������񂪂�������
		if (m_mapManager.lock()->SelMapNow(m_pos) == 2 && m_charen == Manhole_None)
		{
			m_charen = Manhole_Start;//�A�C�e�����u����Ă�����
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");//�������g�ɃA�C�e�����u����Ă���ƕ�����₷������
		}

		//�N�[���^�C���߂�����d�r�̍R�͂��؂�ă}���z�[�����オ��Ȃ��悤�ɂ���
		if (m_charen == Manhole_Start)//�d�r�����Ă�����
		{
			m_stanbyTime += delta;
			//3�b�o������_�ł���
			if (m_stanbyTime > 3.0f)
			{
				m_playerStanbyFlag = true;//�v���C���[���}���z�[���̏�ɂ���Ƒł�������悤�ɂ���
				m_charen = Manhole_SoonUp;//���������}���z�[�����オ����
			}
		}

		if (m_charen == Manhole_SoonUp)
		{
			m_stanbyTime += delta;
			m_blinkingTime += delta;

			if (m_blinkingTime < 0.1f)
			{
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");
			}
			if (m_blinkingTime > 0.2f)
			{
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"RedManhole");
			}
			if (m_blinkingTime > 0.3f)
			{
				m_blinkingTime = 0;
			}
			//�X�^���o�C��Ԃ��I����
			if (m_stanbyTime > 5.0f)
			{
				m_charen = Manhole_Up;//�d�r���オ������Ԃɂ���
				m_stanbyTime = 0;//�N�[���^�C�����Z�b�g
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//�������g�ɃA�C�e�����u����Ă��Ȃ���Ԃ��ƕ�����₷������
				m_mapManager.lock()->MapDataUpdate(m_pos, 3);//�グ��悤�ɂ���
			}

		}

		//�ʍs�֎~�ɂȂ鎞�̏���
		if (m_mapManager.lock()->SelMapNow(m_pos) == 3 && (m_charen == Manhole_Up||m_charen == Manhole_Start||m_charen == Manhole_None))
		{
			m_mapManager.lock()->SetUpdataUnityMapFlag(true);//UnityMap�f�[�^�X�V
			m_charen = Manhole_Used;//�ʍs�֎~�ɂȂ��Ă�����
			Vec3 clearPos = m_pos;
			clearPos.y += 0.0f;
			m_clearObject = GetStage()->AddGameObject<ClearObject>(clearPos, Vec3(0.0f, 0.0f, 0.0f));
			GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
			m_blinkingTime = 0;//�_�ł̃N�[���^�C�������Z�b�g����

			//��������������
			m_waterPillar = GetStage()->AddGameObject<WaterPillar>(clearPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(8.5f, 10.0f, 8.5f));
		}

		//�ʍs�֎~�̎��̍ۂ̏���
		if (m_charen == Manhole_Used)
		{

			//�N�[���^�C���߂�����ʂ��悤�ɂ���
			m_coolTime += delta;

			m_billBoardSecond->SetPercent(m_coolTime / 10.0f);//�N�[���^�C���̐i�s�x��n���Ă���
			
			if (m_coolTime > 10.0f)//���Ԃ��߂�����
			{
				m_mapManager.lock()->SetUpdataUnityMapFlag(true);//UnityMap�f�[�^�X�V
				m_coolTime = 0;//�N�[���^�C�����Z�b�g
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Manhole");//�������g�ɃA�C�e�����u����Ă���ƕ�����₷������
				m_mapManager.lock()->MapDataUpdate(m_pos, 1);//�}�b�v�}�l�[�W���[�ɒʂ���Ԃ��ƕԂ�
				stage->RemoveGameObject<ClearObject>(m_clearObject);//�O�������������ȃI�u�W�F�N�g������
				stage->RemoveGameObject<WaterPillar>(m_waterPillar);//�O������������������
				m_charen = Manhole_None;
				m_blinkingTime = 0;
				m_stanbyTime = 0;
				m_playerUpTime = 0;
				m_playerStanbyFlag = false;
			}

		}

	}

	//���葱���Ă���Ƃ�����
	void Manhole::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto mapManager = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);
		auto stage = GetStage();

		if (mapManager->SelMapNow(m_pos) == 2)
		{//�������������I�u�W�F�N�g���G�Ȃ�
			if (enemy)
			{
				mapManager->MapDataUpdate(m_pos, 3);//���݂͂��̓��͒ʂ�Ȃ��悤�ɂ���
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");//�}���z�[���̊W���o���e�N�X�`���ɂ���

				player = stage->GetSharedGameObject<Player>(L"Player");
				auto playerPos = stage->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
				auto playerSelPos = mapManager->ConvertSelMap(playerPos);
				auto selPos = mapManager->ConvertSelMap(m_pos);

				//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
				auto objVec = stage->GetGameObjectVec();
				//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
				for (auto obj : objVec)
				{
					auto castEnemy = dynamic_pointer_cast<Enemy>(obj);//Enemy�ɃL���X�g����

					//�L���X�g�ł����Ȃ�pos�����ă}���z�[���̃Z�����W�����Ȃ�ł��グ��z��ɓ����
					if (castEnemy) continue;

					auto castEnemyPos = castEnemy->GetComponent<Transform>()->GetPosition();
					auto castEnemySelPos = mapManager->ConvertSelMap(castEnemyPos);

					//Enemy�̃Z�����W�����ă}���z�[���̃Z�����W�����Ȃ�ł��グ��z��ɓ����
					if (castEnemySelPos == selPos)
					{
						m_upEnemyVec.push_back(castEnemy);//�z��ɓ����
					}
				}

				//�G���}���z�[���𓥂�ł���ۂɃv���C���[���}���z�[���𓥂�ł���ۂɂ̓v���C���[�ƓG���ł������郀�[�r�[���o��
				if (playerSelPos.x == selPos.x && playerSelPos.y == selPos.y)
				{
					stage->AddGameObject<MovieUpEandP>(enemy, player);
				}
				else if (m_upEnemyVec.size() >= 2)//�ł�������G���Q�̈ȏア����
				{
					stage->AddGameObject<MovieUpEnemyMulti>(m_upEnemyVec);//�����̓G���ł������鎞�̃��[�r�[
				}
				else//�G�����}���z�[���𓥂�ł���f��
				{
					stage->AddGameObject<MovieUpEnemy>(enemy);//�ł������鎞�̓G�̃��[�r�[
				}
			}
			else if (player)//�v���C���[�Ȃ�
			{
				if (m_playerUpTime >= 0.5f)
				{
					mapManager->MapDataUpdate(m_pos, 3);//���݂͂��̓��͒ʂ�Ȃ��悤�ɂ���
					m_charen = Manhole_Up;//�}���z�[�����オ���Ԃɂ���
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");//�}���z�[���̊W���o���e�N�X�`���ɂ���
					GetStage()->AddGameObject<MovieUpPlayer>();//Player���オ���Ă��܂����[�r���o��
				}
			}
		}

	}
	void Manhole::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		auto mapManager = m_mapManager.lock(); //->SelMapNow(m_pos) == 2
		auto enemy = dynamic_pointer_cast<Enemy>(other);
		auto player = dynamic_pointer_cast<Player>(other);
		auto stage = GetStage();

		if (mapManager->SelMapNow(m_pos) == 2)
		{//�������������I�u�W�F�N�g���G�Ȃ�
			if (enemy)
			{
				mapManager->MapDataUpdate(m_pos, 3);//���݂͂��̓��͒ʂ�Ȃ��悤�ɂ���
				GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");//�}���z�[���̊W���o���e�N�X�`���ɂ���

				player = stage->GetSharedGameObject<Player>(L"Player");
				auto playerPos = stage->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
				auto playerSelPos = mapManager->ConvertSelMap(playerPos);
				auto selPos = mapManager->ConvertSelMap(m_pos);

				//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
				auto objVec = stage->GetGameObjectVec();
				//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
				for (auto obj : objVec)
				{
					auto castEnemy = dynamic_pointer_cast<Enemy>(obj);//Enemy�ɃL���X�g����

					//�L���X�g�ł����Ȃ�pos�����ă}���z�[���̃Z�����W�����Ȃ�ł��グ��z��ɓ����
					if (castEnemy)
					{
						auto castEnemyPos = castEnemy->GetComponent<Transform>()->GetPosition();
						auto castEnemySelPos = mapManager->ConvertSelMap(castEnemyPos);

						//Enemy�̃Z�����W�����ă}���z�[���̃Z�����W�����Ȃ�ł��グ��z��ɓ����
						if (castEnemySelPos == selPos)
						{
							m_upEnemyVec.push_back(castEnemy);//�z��ɓ����
						}
					}
				}

				//�G���}���z�[���𓥂�ł���ۂɃv���C���[���}���z�[���𓥂�ł���ۂɂ̓v���C���[�ƓG���ł������郀�[�r�[���o��
				if (playerSelPos.x == selPos.x && playerSelPos.y == selPos.y)
				{
					stage->AddGameObject<MovieUpEandP>(enemy, player);
				}
				else if (m_upEnemyVec.size() >= 2)//�ł�������G���Q�̈ȏア����
				{
					stage->AddGameObject<MovieUpEnemyMulti>(m_upEnemyVec);//�����̓G���ł������鎞�̃��[�r�[
				}
				else//�G�����}���z�[���𓥂�ł���f��
				{
					stage->AddGameObject<MovieUpEnemy>(enemy);//�ł������鎞�̓G�̃��[�r�[
				}
				m_upEnemyVec.clear();//�g���I�����or�g��Ȃ��̂ō폜����

			}
			else if (player)//�v���C���[�Ȃ�
			{
				if (m_playerUpTime >= 0.5f)
				{
					mapManager->MapDataUpdate(m_pos, 3);//���݂͂��̓��͒ʂ�Ȃ��悤�ɂ���
					m_charen = Manhole_Up;//�}���z�[�����オ���Ԃɂ���
					GetComponent<PNTStaticDraw>()->SetTextureResource(L"Black");
					stage->AddGameObject<MovieUpPlayer>();//Player���オ���Ă��܂����[�r���o��
				}
			}
		}
	}

	void Manhole::OnCollisionExit(shared_ptr<GameObject>& other)
	{
		auto mapManager = m_mapManager.lock();
		auto player = dynamic_pointer_cast<Player>(other);

		if (mapManager->SelMapNow(m_pos)==2)
		{
			//Player�����ꂽ��܂��v���C�������邩�҂t���O�𗧂Ă�
			if (player)
			{
				m_playerStanbyFlag = true;
			}
		}

	}

	//�A�b�v�f�[�g���邩�̃Z�b�^�[
	void Manhole::SetUpdateSwitch(bool onOff)
	{
		m_UpdateFlag = onOff;
	}

	int Manhole::GetState()
	{
		return m_charen;
	}


}
//end basecross
