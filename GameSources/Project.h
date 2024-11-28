/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once

#include "Actor.h"//動くオブジェクトの親クラス

//ツール用
#include "RaySphere.h";//レイの当たり判定
#include "Ray.h";//レイ
#include "MathTools.h";//数学計算用ツール

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
#include "Sky_base.h"
#include "happysky.h"
#include "ClearObject.h"//透明な物理オブジェクト
#include "SpriteNum.h"//数字のスプライト
#include "WaterPillar.h"//水柱
#include "MiniMapActor.h"//ミニマップのPlayerやEnemy　オブジェクトで動くもの
#include "MiniMapItem.h"//ミニマップのItem
#include"NumberSquare.h"
#include"Hatch.h"//脱出用のハッチ
#include"Movie.h"//ムービー用の親クラス
#include"MovieGameStart.h"//ゲーム開始時のムービ

//マネージャー用
#include "MiniMapManager.h"//ミニマップ生成
#include "UIManager.h";//UIマネージャー
#include "StageManager.h"

//カメラ用
#include "MyCamera.h"//追尾カメラ用




