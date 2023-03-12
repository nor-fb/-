#pragma once
#include "GameObject.h"
#include "SupervisionScene.h"

enum SelectOPosition {
    SELECT_BACK,
    SELECT_NOTE,
    SELECT_DELETE,
    SELECT_TITLE,
    SELECT_STAGE,
};

class Option :
    public SupervisionScene
{
public:
    Option();
    void Initialize();
    void Update();
    void Draw();
    void Release();
    ~Option();
    SelectOPosition Get_Select_pos() { return this->Select_pos; }
    void SetBackScene(Scene_Transition scene) { this->BackScene = scene; }
    Scene_Transition Get_BackScene() { return this->BackScene; }
private:
    void TitleInitialize();  //タイトルからのオプション
    void TitleUpdate();
    void StageSelectInitialize();  //ステージセレクトからのオプション
    void StageSelectUpdate();
    void GameInitialize();  //ゲーム画面からのオプション
    void GameUpdate();
private:
    Image* mBackGround;         //背景
    //Image* mSister;           //立ち絵
    Image* mTitleBack;          //タイトルに戻る
    Image* mStageSelectBack;    //ステージセレクトに戻る
    Image* mGameBack;           //ゲームシーンに戻る
    Image* mNote;               //ノートを開く
    Image* mDate;               //データ消去
    Image* mOptionLogo;         //オプションロゴ
    Image* mPauseLogo;          //ポーズロゴ
    Image* mBackFlame;          //選択肢可視化フレーム
    std::vector<GameObject*>mOptionObject;
    SelectOPosition Select_pos;//選択肢
    Scene_Transition BackScene;  //前のScene
    float SisiterCounter = 0.0f;
};