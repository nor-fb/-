//=============================================================================
//
// �T�E���h���� [XAudio2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>
#include"singleton.h"
#include<vector>
#include<unordered_map>
#include"SupervisionScene.h"
#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif


enum SOUND {
	//�^�C�g��
	SOUND_LABEL_TITLE_BGM ,				//�^�C�g��BGM
	SOUND_LABEL_TITLE_DECISION_SE,		//�^�C�g������SE
	SOUND_LABEL_TITLE_BACK_SE,			//�^�C�g���߂�SE
	SOUND_LABEL_TITLE_CURSOR_SE,		//�^�C�g���J�[�\��SE

	//�X�e�[�W�Z���N�g
	SOUND_LABEL_STAGE_MEADOW_BGM,		//�X�e�[�W�Z���N�gBGM(����)
	SOUND_LABEL_STAGE_ICE_BGM,			//�X�e�[�W�Z���N�gBGM(�X�R)
	SOUND_LABEL_STAGE_FORT_BGM,			//�X�e�[�W�Z���N�gBGM(��)
	SOUND_LABEL_STAGE_VOLCANO_BGM,		//�X�e�[�W�Z���N�gBGM(�ΎR)
	SOUND_LABEL_STAGE_CEMETERY_BGM,		//�X�e�[�W�Z���N�gBGM(��n)
	SOUND_LABEL_STAGE_DEMONCASTLE_BGM,	//�X�e�[�W�Z���N�gBGM(������)

	SOUND_LABEL_INGAMESTAGE1_SE,		//�Q�[���Z���N�gSE�Q�[������Ƃ�(�s����)
	SOUND_LABEL_INGAMESTAGE2_SE,		//�Q�[���Z���N�gSE�Q�[������Ƃ�(�����͂�������)
	SOUND_LABEL_INGAMESTAGE3_SE,		//�Q�[���Z���N�gSE�Q�[������Ƃ�(�p�p���ƍs�����Ⴈ��)
	SOUND_LABEL_INGAMESTAGE4_SE,		//�Q�[���Z���N�gSE�Q�[������Ƃ�(�����A�������Ă��Ȃ���)
	SOUND_LABEL_INGAMESTAGE5_SE,		//�Q�[���Z���N�gSE�Q�[������Ƃ�(��`���A��邼�`)
	SOUND_LABEL_STAGE_WALK_SE,			//�X�e�[�W�Z���N�g�����sSE
	SOUND_LABEL_STAGE_LILITHWALK_SE,	//�X�e�[�W�Z���N�g�������sSE
	SOUND_LABEL_LOAD_SE,				//�X�e�[�W�Z���N�g�����ł���SE
	SOUND_LABEL_STAGE_DECISION_SE,		//�X�e�[�W�Z���N�g����SE

	//�Q�[���V�[��
	SOUND_LABEL_STAGECLEAR,				//�X�e�[�W�N���ABGM
	SOUND_LABEL_FEVER,					//�t�B�[�o�[BGM
	SOUND_LABEL_STAGE_1_BGM,			//�Q�[��BGM(1)
	SOUND_LABEL_STAGE_2_BGM,			//�Q�[��BGM(2)
	SOUND_LABEL_STAGE_MINBOSS_BGM,		//�Q�[��BGM(2)
	SOUND_LABEL_STAGE_3_BGM,			//�Q�[��BGM(3)
	SOUND_LABEL_STAGE_4_BGM,			//�Q�[��BGM(4)
	SOUND_LABEL_STAGE_BOSS_BGM01,		//�Q�[��BGM(BOSS��F�O��)
	SOUND_LABEL_STAGE_BOSS_BGM02,		//�Q�[��BGM(BOSS��F�㔼)

	SOUND_LABEL_FEVER_SE,				//�Q�[��SE�t�B�[�o�[��	
	SOUND_LABEL_BULLETLOSE_SE,			//�Q�[��SE�e�؂�	
	SOUND_LABEL_CANNONLOSE_SE,			//�Q�[��SE�e�؂�	
	SOUND_LABEL_CAKEFIRE_SE,			//�Q�[��SE�P�[�L�l�`�e���C
	SOUND_LABEL_STRONGFIRE_SE,			//�Q�[��SE�����e���C
	SOUND_LABEL_NORMALFIRE_SE,			//�Q�[��SE�ʏ�e���C
	SOUND_LABEL_FEVERFIRE_SE,			//�Q�[��SE�V�g�e���C
	SOUND_LABEL_CAKELANDING_SE,			//�Q�[��SE�P�[�L�A�l�`�e���e
	SOUND_LABEL_STRONGLANDING_SE,		//�Q�[��SE�����e���e
	SOUND_LABEL_NORAMLLANDING_SE,		//�Q�[��SE�ʏ�e���e
	SOUND_LABEL_FEVERLANDING_SE,		//�Q�[��SE�V�g�e���e
	SOUND_LABEL_SISTEREAT_SE,			//�Q�[��SE���P�[�L��H�ׂ�
	SOUND_LABEL_SISTERDOLL_SE,			//�Q�[��SE���l�`�ŗV��
	SOUND_LABEL_CHANGECOLOUR_SE,		//�Q�[��SE�F���ς��
	SOUND_LABEL_ENEMYDIE_SE,			//�Q�[��SE�G����
	SOUND_LABEL_MAGICSTONE_SE,			//�Q�[��SE���΃J�E���g
	SOUND_LABEL_CUTIN_SE,				//�Q�[��SE�J�b�g�C��
	SOUND_LABEL_LILITHWAND_SE,			//�Q�[��SE�������U��
	SOUND_LABEL_LILITHWANDCHARGE_SE,	//�Q�[��SE�������͂𗭂߂�
	SOUND_LABEL_CANNONBREAK_SE,			//�Q�[��SE��C����
	SOUND_LABEL_BULLETBREAK_SE,			//�Q�[��SE�e�������
	SOUND_LABEL_MAGICCIRCLE_SE,			//�Q�[��SE���@�w
	SOUND_LABEL_DEVILERASE_SE,			//�Q�[��SE��������
	SOUND_LABEL_DEVILSHELLING_SE,		//�Q�[��SE�����C��
	SOUND_LABEL_DEVILMOVE_SE,			//�Q�[��SE�����ړ�
	SOUND_LABEL_LILITHBARRIER_SE,		//�Q�[��SE�����o���A

	//���U���g
	SOUND_LABEL_RESULT_WIN_BGM,			//���U���gBGM(����)
	SOUND_LABEL_RESULT_LOSE_BGM,		//���U���gBGM(�s�k)
	SOUND_LABEL_ARANKU_SE,				//���U���gSEA�����N�Z���t
	SOUND_LABEL_BRANKU_SE,				//���U���gSEB�����N�Z���t
	SOUND_LABEL_GAMEOVER_SE,			//���U���gSE�Q�[���I�[�o�[�Z���t
	SOUND_LABEL_SRANKU_SE,				//���U���gSES�����N�Z���t
	SOUND_LABEL_SSRANKU_SE,				//���U���gSESS�����N�Z���t
	SOUND_LABEL_YELLOWSTAREFFECT_SE,	//���U���gSE���F�����͂܂�
	SOUND_LABEL_PINKSTAREFFECT_SE,		//���U���gSE�s���N�����͂܂�

	//�X�g�[���[
	SOUND_LABEL_STORY_BGM,				//�X�g�[���[BGM
	SOUND_LABEL_ENDROLL_BGM,			//�G���h���[��BGM
	SOUND_LABEL_STORYEND_SE,			//�X�g�[���[SE�G���h�X�g�[���[�Q�Z���t

	//�I�v�V����
	SOUND_LABEL_OPTION_DECISION_SE,		//�I�v�V����SE����
	SOUND_LABEL_OPTION_BACK_SE,			//�I�v�V����SE�߂�
	SOUND_LABEL_OPTION_CURSOR_SE,		//�I�v�V����SE�J�[�\��
	SOUND_LABEL_NOTE_BGM,				//�m�[�gBGM
};

// �p�����[�^�\����
typedef struct
{
	LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
	bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
} PARAM;

class Sound:public singleton<Sound>
{
public:
	explicit Sound(token);
	~Sound();
	void Set_Scene(Scene_Transition scenename);
	void Play(SOUND label);	 //�����̊J�n(0����)
	void Stop(SOUND label);   //�����̒�~
	void Pause(SOUND label);  //�����̈ꎞ��~
	void Restart(SOUND label);//�����̓r���Đ�
	void Set_Volume(SOUND label,float volume);
	void Release(Scene_Transition scenename);//���
private:
	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	//PARAM g_param[SOUND_LABEL_MAX];

	IXAudio2* g_pXAudio2 = NULL;
	IXAudio2MasteringVoice* g_pMasteringVoice = NULL;
	std::unordered_map<SOUND,IXAudio2SourceVoice*> g_pSourceVoice;

	std::vector<PARAM> TitleSound;
	std::vector<PARAM> StageSelectSound;
	std::vector<PARAM> GameSceneSound;
	std::vector<PARAM> ResultSound;
	std::vector<PARAM> StorySound;
	std::vector<PARAM> OptionSound;

	std::unordered_map<SOUND,WAVEFORMATEXTENSIBLE>g_wfx;			// WAV�t�H�[�}�b�g
	std::unordered_map<SOUND,XAUDIO2_BUFFER>	g_buffer;
	std::unordered_map<SOUND, BYTE*> g_DataBuffer;
};

#endif
