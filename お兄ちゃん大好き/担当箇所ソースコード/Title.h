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
private://�J�ڕʂ̍X�V����(�J�ڂ̐������X�V������I�I)
    void TitleInitialize();//�^�C�g����ʏ�����
    void MenuInitialize();//�^�C�g�����j���[������
    void TitleUpdate();//�^�C�g����ʏ���
    void MenuUpdate();//�^�C�g�����j���[����
    void ObjectInitialize();//�I�u�W�F�N�g�̏�����
    void FlameAnim();//�t���[���̓_�ŏ���
private:
    SceneTitle Current_Title;//�^�C�g���J��
    SelectPosition Select_pos;//�I����
private:
    Image* mBackGround;//�w�i
    Image* mTitle;//�^�C�g�����S
    Image* mPressUI;//�����Ƃ����ތnUI
    Image* mStartUI;//�͂��߂���
    Image* mNextUI; //�Â�����
    Image* mOptionUI;//�I�v�V����
    Image* mFinishUI;//�Q�[�����I���
    Image* mBackFlame;//�I���������t���[��
    std::vector<GameObject*>mTitleObject;
private:
    bool InitializePos_flag;
    bool FlameBlinking_Flag;
    int num = 0;
};
