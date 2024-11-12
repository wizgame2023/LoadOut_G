/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once

#include "Actor.h"//動くオブジェクトの親クラス

//ステート用
#include "State.h"//ステートの親クラス
#include "Tracking.h"
#include "State.h"
#include "Patrol.h"
#include "Attack.h"

//親クラス用
#include "Actor.h"

#include "ProjectShader.h"
#include "ProjectBehavior.h"
#include "Scene.h"
#include "GameStage.h"
#include "Character.h"
#include "Player.h"
#include "Block.h"
#include "TubakiStage.h"
#include "YuusinStage.h"
#include "YuutaStage.h"
#include "Ground.h"
#include "MapManager.h"
#include "Item.h"
#include "Enemy.h"
#include "Manhole.h"
#include "Wall.h"
#include "Sprite.h"//スプライト用
#include "TilteStage.h"//タイトルステージ
#include "GameOverStage.h"//ゲームオーバーステージ
#include "GameClearStage.h"//ゲームクリアステージ
#include "ClearObject.h"//透明な物理オブジェクト
#include "SpriteNum.h"//数字のスプライト
#include "WaterPillar.h"//水柱

//カメラ用
#include "MyCamera.h"//追尾カメラ用


//ツール用
#include "RaySphere.h";//レイの当たり判定
#include "Ray.h";//レイ



