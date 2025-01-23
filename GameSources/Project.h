/*!
@file Project.h
@brief �R���e���c�p�̃w�b�_���܂Ƃ߂�
*/

#pragma once

#include"Actor.h"//�����I�u�W�F�N�g�̐e�N���X

//�c�[���p
#include"RaySphere.h";//���C�̓����蔻��
#include"Ray.h";//���C
#include"MathTools.h";//���w�v�Z�p�c�[��
#include"AStar.h";//�o�H�T������

//�X�e�[�g�p
#include"State.h"//�X�e�[�g�̐e�N���X
#include"Tracking.h"
#include"State.h"
#include"Patrol.h"
#include"Attack.h"
#include"RepopEnemy.h"

//�e�N���X�p
#include"Actor.h"

#include"ProjectShader.h"
#include"ProjectBehavior.h"
#include"Scene.h"
#include"GameStage.h"
#include"Character.h"
#include"Player.h"
#include"Block.h"
#include"TubakiStage.h"
#include"YuusinStage.h"
#include"YuutaStage.h"
#include"Ground.h"
#include"MapManager.h"
#include"Battery.h"//�d�r
#include"Enemy.h"
#include"Manhole.h"
#include"Wall.h"
#include"Sprite.h"//�X�v���C�g�p
#include"TilteStage.h"//�^�C�g���X�e�[�W
#include"GameOverStage.h"//�Q�[���I�[�o�[�X�e�[�W
#include"GameClearStage.h"//�Q�[���N���A�X�e�[�W
#include"SelectStage.h"
#include"Sky_base.h"
#include"happysky.h"
#include"ClearObject.h"//�����ȕ����I�u�W�F�N�g
#include"SpriteNum.h"//�����̃X�v���C�g
#include"WaterPillar.h"//����
#include"MiniMapActor.h"//�~�j�}�b�v��Player��Enemy�@�I�u�W�F�N�g�œ�������
#include"MiniMapItem.h"//�~�j�}�b�v��Item
#include"BillBoard.h"
#include"Hatch.h"//�E�o�p�̃n�b�`
#include"Movie.h"//���[�r�[�p�̐e�N���X
#include"MovieGameStart.h"//�Q�[���J�n���̃��[�r
#include"MovieUpPlayer.h"//Player���ł������鎞�̃��[�r�[
#include"MovieGameClear.h"
#include"MovieGameOver.h"//�Q�[���I�[�o�[�J�ڎ��̂̃��[�r
#include"MovieUpEnemy.h"//Enemy���ł������鎞�̃��[�r�[
#include"MovieUpEandP.h"//Enemy��Player�������ɑł������鎞�̃��[�r�[
#include"PillarEfect.h"//����̃G�t�F�N�g
#include"ManholeSprite.h"//�~�j�}�b�v�p�̃}���z�[���X�v���C�g
#include"RandomItem.h"//�����_���ɃC�x���g����������A�C�e��
#include"GameStage02.h"
#include"GameStage03.h"
#include"GameStage04.h"
#include"GameStage05.h"
#include"GameStage06.h"
#include"GameStage07.h"
#include"GameStage08.h"
#include"GameStage09.h"
#include"GameStage10.h"
#include"GameStage11.h"
#include"GameStage12.h"
#include"GameStage13.h"
#include"GameStage14.h"
#include"GameStage15.h"
#include"GameStage16.h"
#include"GameStage17.h"
#include"GameStage18.h"
#include"GameStage19.h"
#include"GameStage20.h"
#include"BlackOut.h"
#include"TrackingPillarEfect.h"
#include"SpriteMove.h"

//�}�l�[�W���[�p
#include"MiniMapManager.h"//�~�j�}�b�v����
#include"UIManager.h";//UI�}�l�[�W���[
#include"StageManager.h"
#include"StageCollisionManager.h"//�R���W�����Ǘ�
#include"NumberManager.h";

//�J�����p
#include"MyCamera.h"//�ǔ��J�����p




