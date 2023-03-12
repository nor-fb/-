#pragma once
#include "GameObject.h"
#include "SupervisionScene.h"
#include<vector>

enum SceneTitle {
    TITLE_SCENE,
    TITLE_MENU,
};
enum SelectPosition {
    SELECT_START,
    SELECT_OPTION,
    SELECT_END,
};

class Title :public SupervisionScene
{
public:
    Title();
    void Initialize();
    void Update();
    void Draw();
    void Release();
    void Input_Update();
private://遷移別の更新処理(遷移の数だけ更新がある！！)
    void TitleInitialize();//タイトル画面初期化
    void MenuInitialize();//タイトルメニュー初期化
    void TitleUpdate();//タイトル画面処理
    void MenuUpdate();//タイトルメニュー処理
    void ObjectInitialize();//オブジェクトの初期化
    void FlameAnim();//フレームの点滅処理
private:
    SceneTitle Current_Title;//タイトル遷移
    SelectPosition Select_pos;//選択肢
private:
    Image* mBackGround;//背景
    Image* mTitle;//タイトルロゴ
    Image* mPressUI;//押すとすすむ系UI
    Image* mStartUI;//はじめから
    Image* mNextUI; //つづきから
    Image* mOptionUI;//オプション
    Image* mFinishUI;//ゲームを終わる
    Image* mBackFlame;//選択肢可視化フレーム
    std::vector<GameObject*>mTitleObject;
private:
    bool InitializePos_flag;
    bool FlameBlinking_Flag;
    int num = 0;
};
