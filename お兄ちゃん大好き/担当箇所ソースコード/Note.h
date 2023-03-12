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
        //�m�[�g
        Image* mnBackground;  //�w�i
        Image* mnBackFlame;//�I���������t���[��
        Image* mStatus;  //�X�e�[�^�X
        Image* mCannon;  //��C
        Image* mEnemy;  //�G
        Image* mOther;  //���̑�

        //�X�e�[�^�X
        Image* msBackground;  //�w�i
        Image* msBackFlame;  //�I���������t���[��
        Image* mPower;  //�̗�
        Image* mBullet;  //�e
        Image* mTension;  //�e���V����
        Image* mScore;  //�X�R�A
          //����
        Image* mPower_Comment;  //�̗�
        Image* mBullet_Comment;  //�e
        Image* mTension_Comment;  //�e���V����
        Image* mScore_Comment;  //�X�R�A


        //��C
        Image* mcBackground;  //�w�i
        Image* mcBackFlame;  //�I���������t���[��
        Image* mNormal;  //�ʏ�e
        Image* mCake;  //�P�[�L�e
        Image* mDoll;  //�l�`�e
        Image* mAngel;  //�V�g�e
          //����
        Image* mNormal_Comment;  //�ʏ�e
        Image* mCake_Comment;  //�P�[�L�e
        Image* mDoll_Comment;  //�l�`�e
        Image* mAngel_Comment;  //�V�g�e

        //�G
        Image* meBackground;  //�w�i
        Image* meBackFlame;  //�I���������t���[��
        Image* mSmallslime;  //�������X���C��
        Image* mRareslime;  //���A�X���C��
        Image* mBoss;  //�{�X
        Image* mBigslime;  //�傫���X���C��
        Image* mBomb;  //���e��
          //����
        Image* mSmallslime_Comment;  //�������X���C��
        Image* mRareslime_Comment;  //���A�X���C��
        Image* mBoss_Comment;  //�{�X
        Image* mBigslime_Comment;  //�傫���X���C��
        Image* mBomb_Comment;  //���e��

        //���̑�
        Image* moBackground;  //�w�i
        Image* moBackFlame;  //�I���������t���[��
        Image* mFever;  //�t�B�[�o�[
        Image* mRank;  //�����N
        Image* mBrother;  //�Z
        Image* mSister;  //��
        Image* mTricks;
          //����
        Image* mFever_Comment;  //�t�B�[�o�[
        Image* mRank_Comment;  //�����N
        Image* mBrother_Comment;  //�Z
        Image* mSister_Comment;  //��
        Image* mTricks_Comment;

        std::vector<GameObject*> mgNote;
        std::vector<GameObject*> mgStatus;
        std::vector<GameObject*> mgCannon;
        std::vector<GameObject*> mgEnemy;
        std::vector<GameObject*> mgOther;

        NoteComment Select_pos;  //�I����
        SelectONPosition Select_Note;  //�m�[�g�̉�ʈʒu
};