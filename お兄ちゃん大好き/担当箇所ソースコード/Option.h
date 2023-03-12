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
    void TitleInitialize();  //�^�C�g������̃I�v�V����
    void TitleUpdate();
    void StageSelectInitialize();  //�X�e�[�W�Z���N�g����̃I�v�V����
    void StageSelectUpdate();
    void GameInitialize();  //�Q�[����ʂ���̃I�v�V����
    void GameUpdate();
private:
    Image* mBackGround;         //�w�i
    //Image* mSister;           //�����G
    Image* mTitleBack;          //�^�C�g���ɖ߂�
    Image* mStageSelectBack;    //�X�e�[�W�Z���N�g�ɖ߂�
    Image* mGameBack;           //�Q�[���V�[���ɖ߂�
    Image* mNote;               //�m�[�g���J��
    Image* mDate;               //�f�[�^����
    Image* mOptionLogo;         //�I�v�V�������S
    Image* mPauseLogo;          //�|�[�Y���S
    Image* mBackFlame;          //�I���������t���[��
    std::vector<GameObject*>mOptionObject;
    SelectOPosition Select_pos;//�I����
    Scene_Transition BackScene;  //�O��Scene
    float SisiterCounter = 0.0f;
};