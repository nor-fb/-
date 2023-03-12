#pragma once
#include "GameObject.h"
#include "SupervisionScene.h"
#include "XAudio2.h"
#include<vector>
enum SelectStage {
    STAGE_1_1,//草原
    STAGE_1_2,
    STAGE_2_1,//氷
    STAGE_2_2,
    STAGE_MINIBOSS,
    STAGE_3_1,//火山
    STAGE_3_2,
    STAGE_4_1,//墓地
    STAGE_4_2,
    STAGE_BIGBOSS,//魔王城
};

enum StagePattern {
    STAGE_MEADOW,
    STAGE_ICE,
    STAGE_CASTLE,
    STAGE_VOLCANO,
    STAGE_CEMETERY,
    STAGE_DEMONCASTLE,
};
enum SisterState {
    STATE_WAITING,
    STATE_MOVERIGHT,
    STATE_MOVELEFT
};
enum Event {
    EVENT_NULL,
    EVENT_LOAD_DISPLAY,
    EVENT_BOSS_MOVE,
};
class StageSelect :
    public SupervisionScene
{
public:
    StageSelect();
    ~StageSelect() {
        for (int i = 0; i < 6; i++) {
            delete mBackGround[i];          //背景
            delete mStageImage[i];          //ステージイメージ
            delete mFrontImage[i];
            delete mStageRoute_main[i];     //ステージ経路(妹が歩く道)
        }
        for (int i = 0; i < 10; i++)
            delete mStageNum[i];           //ステージ番号

        for (int i = 0; i < 5; i++) {
            delete mRank[i];                //ランク表示
            delete mStanding_Position[i];   //立ち位置(最大5個)
        }
        delete mOverall_Map;            //全体マップ(経路)
        delete mOverall_Map_point;      //全体マップ(ポイント)
        delete mSister;                 //妹
        delete mBoss;                   //BOSS
        delete mFence;
    }
    void Initialize();
    void Update();
    void Draw();
    void Release();
    void EventUpdate();
    void Input_Update();
    SelectStage Get_SelectStage() { return this->now_stage; }//選択したステージ取得用Get関数
    Event Get_NowEvent() { return now_event; }
    void Set_StageMovement_flag(bool flag) { StageMovement_flag = flag; }
    void Set_LoadText_flag(bool flag) { LoadText_flag = flag; }
    void Set_NowEvent(Event event) { now_event = event; }
    void Set_Eventflag(bool flag) { Event_flag = flag; }
private:
    void ObjectInitialize();
    void Texture();
    void StageRight_Normal();   //右移動(普通)
    void StageRight_BOSS();     //左移動(普通)
    void StageLeft_Normal();    //右移動(BOSS)
    void StageLeft_BOSS();      //左移動(BOSS)
    void StageMove();//ステージ移動
    void PointMove();//ポイント移動
    void ImageUpanddown();//ステージイメージ上下軌道
    void StageChange();//エリアの更新
    void SisterAnim();//妹アニメ
    void BossAnim();//ボスのアニメーション
    void StageSound();
    void StagePoint();
    void Standing_PosMove();    //立ち位置の移動
    void Rord_PosMove();
    float SinF(float angle);
    float Cosf(float angle);
private:
    Image* mBackGround[6];          //背景
    Image* mStageImage[6];          //ステージイメージ
    Image* mStageNum[10];           //ステージ番号
    Image* mRank[5];                //ランク表示
    Image* mStageRoute_main[6];     //ステージ経路(妹が歩く道)
    Image* mOverall_Map;            //全体マップ(経路)
    Image* mOverall_Map_point;      //全体マップ(ポイント)
    Image* mStanding_Position[5];   //立ち位置(最大5個)
    Image* mSister;                 //妹
    Image* mBoss;                   //BOSS
    Image* mFrontImage[6];
    Image* mFence;
    std::vector<GameObject*>mSelectObject;
private:
    SelectStage now_stage;//選択中のステージ
    SelectStage max_stage;//クリア済みステージ
    StagePattern now_pattern;//今のステージ
    SisterState now_state = STATE_WAITING;//妹状態
    SOUND now_sound;
    Event now_event = EVENT_NULL;
private:
    bool Operation_flag;//操作フラグ
    bool PointMovement_flag;//ステージ地点移動フラグ
    bool StageMovement_flag;//ステージ移動フラグ
    bool LoadText_flag;//画像読み込みフラグ
    bool UpDown_flag;//上下フラグ
    bool Event_flag;
    float Up_speed = 0.0f;
    float Down_speed = 0.0f;
    float SisiterCounter = 0.0f;
    float BossCounter = 0.0f;
    float Count;
    bool SisterAnim_flag;
    bool BossAnim_flag;
};