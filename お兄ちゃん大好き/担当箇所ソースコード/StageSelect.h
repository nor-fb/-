#pragma once
#include "GameObject.h"
#include "SupervisionScene.h"
#include "XAudio2.h"
#include<vector>
enum SelectStage {
    STAGE_1_1,//����
    STAGE_1_2,
    STAGE_2_1,//�X
    STAGE_2_2,
    STAGE_MINIBOSS,
    STAGE_3_1,//�ΎR
    STAGE_3_2,
    STAGE_4_1,//��n
    STAGE_4_2,
    STAGE_BIGBOSS,//������
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
            delete mBackGround[i];          //�w�i
            delete mStageImage[i];          //�X�e�[�W�C���[�W
            delete mFrontImage[i];
            delete mStageRoute_main[i];     //�X�e�[�W�o�H(����������)
        }
        for (int i = 0; i < 10; i++)
            delete mStageNum[i];           //�X�e�[�W�ԍ�

        for (int i = 0; i < 5; i++) {
            delete mRank[i];                //�����N�\��
            delete mStanding_Position[i];   //�����ʒu(�ő�5��)
        }
        delete mOverall_Map;            //�S�̃}�b�v(�o�H)
        delete mOverall_Map_point;      //�S�̃}�b�v(�|�C���g)
        delete mSister;                 //��
        delete mBoss;                   //BOSS
        delete mFence;
    }
    void Initialize();
    void Update();
    void Draw();
    void Release();
    void EventUpdate();
    void Input_Update();
    SelectStage Get_SelectStage() { return this->now_stage; }//�I�������X�e�[�W�擾�pGet�֐�
    Event Get_NowEvent() { return now_event; }
    void Set_StageMovement_flag(bool flag) { StageMovement_flag = flag; }
    void Set_LoadText_flag(bool flag) { LoadText_flag = flag; }
    void Set_NowEvent(Event event) { now_event = event; }
    void Set_Eventflag(bool flag) { Event_flag = flag; }
private:
    void ObjectInitialize();
    void Texture();
    void StageRight_Normal();   //�E�ړ�(����)
    void StageRight_BOSS();     //���ړ�(����)
    void StageLeft_Normal();    //�E�ړ�(BOSS)
    void StageLeft_BOSS();      //���ړ�(BOSS)
    void StageMove();//�X�e�[�W�ړ�
    void PointMove();//�|�C���g�ړ�
    void ImageUpanddown();//�X�e�[�W�C���[�W�㉺�O��
    void StageChange();//�G���A�̍X�V
    void SisterAnim();//���A�j��
    void BossAnim();//�{�X�̃A�j���[�V����
    void StageSound();
    void StagePoint();
    void Standing_PosMove();    //�����ʒu�̈ړ�
    void Rord_PosMove();
    float SinF(float angle);
    float Cosf(float angle);
private:
    Image* mBackGround[6];          //�w�i
    Image* mStageImage[6];          //�X�e�[�W�C���[�W
    Image* mStageNum[10];           //�X�e�[�W�ԍ�
    Image* mRank[5];                //�����N�\��
    Image* mStageRoute_main[6];     //�X�e�[�W�o�H(����������)
    Image* mOverall_Map;            //�S�̃}�b�v(�o�H)
    Image* mOverall_Map_point;      //�S�̃}�b�v(�|�C���g)
    Image* mStanding_Position[5];   //�����ʒu(�ő�5��)
    Image* mSister;                 //��
    Image* mBoss;                   //BOSS
    Image* mFrontImage[6];
    Image* mFence;
    std::vector<GameObject*>mSelectObject;
private:
    SelectStage now_stage;//�I�𒆂̃X�e�[�W
    SelectStage max_stage;//�N���A�ς݃X�e�[�W
    StagePattern now_pattern;//���̃X�e�[�W
    SisterState now_state = STATE_WAITING;//�����
    SOUND now_sound;
    Event now_event = EVENT_NULL;
private:
    bool Operation_flag;//����t���O
    bool PointMovement_flag;//�X�e�[�W�n�_�ړ��t���O
    bool StageMovement_flag;//�X�e�[�W�ړ��t���O
    bool LoadText_flag;//�摜�ǂݍ��݃t���O
    bool UpDown_flag;//�㉺�t���O
    bool Event_flag;
    float Up_speed = 0.0f;
    float Down_speed = 0.0f;
    float SisiterCounter = 0.0f;
    float BossCounter = 0.0f;
    float Count;
    bool SisterAnim_flag;
    bool BossAnim_flag;
};