#pragma once
#include "SupervisionScene.h"
#include "GameObject.h"
enum SelectONPosition{
    SELECT_STATUS,
    SELECT_CANNON,
    SELECT_ENEMY,
    SELECT_OTHER,
    SELECT_NOTE2
};
enum NoteComment {
    NOTE_STATUS,
    NOTE_CANNON,
    NOTE_ENEMY,
    NOTE_OTHER,
    STATUS_POWER,
    STATUS_BULLET,
    STATUS_TENSION,
    STATUS_SCORE,
    CANNON_NORMAL,
    CANNON_CAKE,
    CANNON_DOLL,
    CANNON_ANGEL,
    ENEMY_SMALLSLIME,
    ENEMY_RARESLIME,
    ENEMY_BOSS,
    ENEMY_BIGSLIME,
    ENEMY_BOMB,
    OTHER_FEVER,
    OTHER_RANK,
    OTHER_BROTHER,
    OTHER_SISTER,
    OTHER_TRICK,
};
class Note :
    public SupervisionScene
{       
public:
        Note();
        void Initialize();
        void SceneUpdate();
        void NoteUpdate();
        void StatusIni();
        void StatusUpdate();
        void CannonIni();
        void CannonUpdate();
        void EnemyIni();
        void EnemyUpdate();
        void OtherIni();
        void OtherUpdate();
        void Draw();

        ~Note();
private:
        //ノート
        Image* mnBackground;  //背景
        Image* mnBackFlame;//選択肢可視化フレーム
        Image* mStatus;  //ステータス
        Image* mCannon;  //大砲
        Image* mEnemy;  //敵
        Image* mOther;  //その他

        //ステータス
        Image* msBackground;  //背景
        Image* msBackFlame;  //選択肢可視化フレーム
        Image* mPower;  //体力
        Image* mBullet;  //弾
        Image* mTension;  //テンション
        Image* mScore;  //スコア
          //説明
        Image* mPower_Comment;  //体力
        Image* mBullet_Comment;  //弾
        Image* mTension_Comment;  //テンション
        Image* mScore_Comment;  //スコア


        //大砲
        Image* mcBackground;  //背景
        Image* mcBackFlame;  //選択肢可視化フレーム
        Image* mNormal;  //通常弾
        Image* mCake;  //ケーキ弾
        Image* mDoll;  //人形弾
        Image* mAngel;  //天使弾
          //説明
        Image* mNormal_Comment;  //通常弾
        Image* mCake_Comment;  //ケーキ弾
        Image* mDoll_Comment;  //人形弾
        Image* mAngel_Comment;  //天使弾

        //敵
        Image* meBackground;  //背景
        Image* meBackFlame;  //選択肢可視化フレーム
        Image* mSmallslime;  //小さいスライム
        Image* mRareslime;  //レアスライム
        Image* mBoss;  //ボス
        Image* mBigslime;  //大きいスライム
        Image* mBomb;  //爆弾兵
          //説明
        Image* mSmallslime_Comment;  //小さいスライム
        Image* mRareslime_Comment;  //レアスライム
        Image* mBoss_Comment;  //ボス
        Image* mBigslime_Comment;  //大きいスライム
        Image* mBomb_Comment;  //爆弾兵

        //その他
        Image* moBackground;  //背景
        Image* moBackFlame;  //選択肢可視化フレーム
        Image* mFever;  //フィーバー
        Image* mRank;  //ランク
        Image* mBrother;  //兄
        Image* mSister;  //妹
        Image* mTricks;
          //説明
        Image* mFever_Comment;  //フィーバー
        Image* mRank_Comment;  //ランク
        Image* mBrother_Comment;  //兄
        Image* mSister_Comment;  //妹
        Image* mTricks_Comment;

        std::vector<GameObject*> mgNote;
        std::vector<GameObject*> mgStatus;
        std::vector<GameObject*> mgCannon;
        std::vector<GameObject*> mgEnemy;
        std::vector<GameObject*> mgOther;

        NoteComment Select_pos;  //選択肢
        SelectONPosition Select_Note;  //ノートの画面位置
};