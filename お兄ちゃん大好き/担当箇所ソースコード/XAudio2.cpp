//=============================================================================
//
// �T�E���h���� [XAudio2.cpp]
//
//=============================================================================

#include "XAudio2.h"


//=============================================================================
// ������(���[�v�FBGM=true,SE=false)
//=============================================================================
Sound::Sound(token)
{
	//�^�C�g��
	TitleSound = {
		{ "assets/BGM/Title.wav",true },//�^�C�g��BGM
		{ "assets/SE/19����/item-01.wav",false },//�^�C�g��SE����
		{ "assets/SE/20�߂�/item-02.wav",false },//�^�C�g��SE�߂�
		{ "assets/SE/21�J�[�\���ړ�/cursor-01.wav",false },//�^�C�g��SE�J�[�\���ړ�
	};
	//�X�e�[�W�Z���N�g
	StageSelectSound = {
		{ "assets/BGM/StageSelect01.wav",true },	//�X�e�[�W�Z���N�gBGM(����)
		{ "assets/BGM/StageSelect02.wav",true },	//�X�e�[�W�Z���N�gBGM(�X�R)
		{ "assets/BGM/StageSelectMinBoss.wav",true },//�X�e�[�W�Z���N�gBGM(��)
		{ "assets/BGM/StageSelect03.wav",true },	//�X�e�[�W�Z���N�gBGM(�ΎR)
		{ "assets/BGM/StageSelect04.wav",true },	//�X�e�[�W�Z���N�gBGM(��n)
		{ "assets/BGM/StageSelectBoss.wav",true },	//�X�e�[�W�Z���N�gBGM(������)

		{ "assets/SE/�X�e�[�W�J�n��/ikuyo_02.wav",false },//�X�e�[�W�Z���N�gSE����Ƃ�
		{ "assets/SE/�X�e�[�W�J�n��/junbiwaiikana_01.wav",false },//�X�e�[�W�Z���N�gSE����Ƃ�
		{ "assets/SE/�X�e�[�W�J�n��/papattoicchaou_01.wav",false },//�X�e�[�W�Z���N�gSE����Ƃ�
		{ "assets/SE/�X�e�[�W�J�n��/saakakattekinasai_01.wav",false },//�X�e�[�W�Z���N�gSE����Ƃ�
		{ "assets/SE/�X�e�[�W�J�n��/yoshiyaruzo_01.wav",false },//�X�e�[�W�Z���N�gSE����Ƃ�
		{ "assets/SE/18�X�e�Z�����s��/Accent41-1.wav",true },//�X�e�[�W�Z���N�gSE���s
		{ "assets/SE/����/�X�e�Z���ړ�.wav",false},//�X�e�[�W�Z���N�gSE�������s
		{ "assets/SE/���o��/2.wav",false},//���o��SE
		{ "assets/SE/19����/Accent24-2.wav",false },//�X�e�[�W�Z���N�gSE����

	};
	//�Q�[���V�[��
	GameSceneSound = {
		{"assets/BGM/GameCler.wav", true},			//�X�e�[�W�N���ABGM
		{ "assets/BGM/Fever.wav", true},			//�X�e�[�W�N���ABGM
		{ "assets/BGM/Stage01.wav",true },			//�Q�[��BGM(1)
		{ "assets/BGM/Stage02.wav",true },			//�Q�[��BGM(2)
		{ "assets/BGM/StageMinBoss.wav",true },		//�Q�[��BGM(2)
		{ "assets/BGM/Stage03.wav",true },			//�Q�[��BGM(3)
		{ "assets/BGM/Stage04.wav",true },			//�Q�[��BGM(4)
		{ "assets/BGM/StageBoss01.wav",true },		//�Q�[��BGM(BOSS��F�O��)
		{ "assets/BGM/StageBoss02.wav",true },		//�Q�[��BGM(BOSS��F�㔼)

		{ "assets/SE/�t�B�[�o�[��/Fever.wav",false },//�t�B�[�o�[��
		{"assets/SE/�e�������/�e�؂�.wav",false}, //�Q�[��SE�e�؂�
		{"assets/SE/�e�������/��C���Ă�.wav",false}, //�Q�[��SE�e�؂�(��C���Ă���)
		{ "assets/SE/00���C��/�P�[�L�A�l�`�e.wav", false},//�Q�[��SE�P�[�L�A�l�`�e���C
		{ "assets/SE/00���C��/�����e.wav",false },	//�Q�[��SE�����e���C
		{ "assets/SE/00���C��/�ʏ�e.wav",false },	//�Q�[��SE�ʏ�e���C
		{ "assets/SE/00���C��/�V�g�e.wav",false },	//�Q�[��SE�V�g�e
		{ "assets/SE/02���e��/�P�[�L�A�l�`�e���e.wav",false },//�Q�[��SE�P�[�L�l�`�e���e
		{ "assets/SE/02���e��/�����e���e.wav",false },//�Q�[��SE�����e���e
		{ "assets/SE/02���e��/�ʏ�e���e.wav",false },//�Q�[��SE�ʏ�e���e
		{ "assets/SE/02���e��/�V�g�e���e.wav",false },//�Q�[��SE�V�g�e���e
		{ "assets/SE/03�H�ׂ鉹/Sister_eat.wav",false },//�Q�[��SE���P�[�L�H�ׂ�
		{ "assets/SE/04�V�ԉ�/Sister_Doll.wav",false },//�Q�[��SE���l�`�V��
		{ "assets/SE/07.5�F������/�b��/Accent30-1.wav",false },//�Q�[��SE�X�e�[�W�ɐF����
		{ "assets/SE/07�G����/�b��/enemy-attack.wav",false },//�Q�[��SE�G����
		{ "assets/SE/09���΂̃J�E���g�A�b�v/���΃J�E���g.wav",false },//�Q�[��SE���΃J�E���g
		{ "assets/SE/13�J�b�g�C��/���ʉ����{/�b��/�X�e�[�^�X����2.wav",false },//�Q�[��SE�J�b�g�C��
		{ "assets/SE/14�������U��/������ ���ʉ� �G�t�F�N�g03.wav", false},//�Q�[��SE�������U��
		{ "assets/SE/14�������U��/se_chikara.wav",true},//�Q�[��SE�����͂𗭂߂�
		{ "assets/SE/16��C�j��i�P�R�Ɠ������j/se_explode08.wav",false},//�Q�[��SE��C�j��
		{"assets/SE/�e�������/sei_ge_syokki_wareru04.wav",false},//�Q�[��SE�e�������
		{"assets/SE/���@�w/ta_ta_syara02 .wav",false},//�Q�[��SE���@�w
		{"assets/SE/����/����.wav",false},//�Q�[��SE��������
		{"assets/SE/����/�C��.wav",false},//�Q�[��SE�����C��
		{"assets/SE/����/�Q�[���ړ�.wav",true},//�Q�[��SE�����Q�[���ړ�
		{ "assets/SE/17�����o���A����/���ʉ����{/���őł�����1.wav",false },//�Q�[��SE�����o���A
	};
	//���U���g
	ResultSound = {
		{ "assets/BGM/ResultWin.wav",true },		//���U���gBGM(����)
		{ "assets/BGM/ResultLose.wav",true },	//���U���gBGM(�s�k)
		{ "assets/SE/���U���g/Aranku.wav",false },//���U���gSEA�����N�Z���t
		{ "assets/SE/���U���g/Branku.wav",false },//���U���gSEB�����N�Z���t
		{ "assets/SE/���U���g/GameOver.wav",false },//���U���gSE�Q�[���I�[�o�[�Z���t
		{ "assets/SE/���U���g/Sranku.wav",false },//���U���gSES�����N�Z���t
		{ "assets/SE/���U���g/SSranku.wav",false },//���U���gSESS�����N�Z���t
		{ "assets/SE/23���̂͂܂鉹/yellowstar.wav",false },//���U���g���F�����͂܂�
		{ "assets/SE/23���̂͂܂鉹/pinkstar.wav",false },//���U���g�s���N�����͂܂�
	};
	//�X�g�[���[
	StorySound = {
		{"assets/BGM/Story.wav",false},//�X�g�[���[BGM
		{"assets/BGM/EndRoll.wav",true},//�G���h���[��BGM
		{"assets/SE/�G���h�X�g�[���[�Q�Z���t��/Endroll.wav", false},//�X�g�[���[SE�G���h�X�g�[���[�Q�Z���t
	};
	//�I�v�V����
	OptionSound = {
		{ "assets/SE/19����/item-01.wav",false },//�I�v�V����SE����
		{ "assets/SE/20�߂�/item-02.wav",false },//�I�v�V����SE�߂�
		{ "assets/SE/21�J�[�\���ړ�/cursor-01.wav",false },//�I�v�V����SE�J�[�\��
		{ "assets/SE/21�J�[�\���ړ�/cursor-01.wav",false },//�I�v�V����SE�J�[�\��
	};
	//PARAM g_param[SOUND_LABEL_MAX] =
	//{
	//	{"assets/BGM/TitleBGM.wav", true},			// �^�C�g��BGM
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//�I�v�V�����E�|�[�YBGM
	//	{"assets/BGM/ResultWinBGM.wav", true},		//���U���gBGM(����)
	//	{"assets/BGM/ResultLoseBGM.wav", true},		//���U���gBGM(�s�k)
	//	{"assets/BGM/StageClearBGM.wav", true},		//�X�e�[�W�N���ABGM
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//�m�[�gBGM
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//�X�e�[�W�Z���N�gBGM(����)
	//	{"assets/BGM/StageSelectBGM02.wav", true},	//�X�e�[�W�Z���N�gBGM(�X�R)
	//	{"assets/BGM/StageSelectBGM03.wav", true},	//�X�e�[�W�Z���N�gBGM(�ΎR)
	//	{"assets/BGM/StageSelectBGM04.wav", true},	//�X�e�[�W�Z���N�gBGM(��n)
	//	{"assets/BGM/StageSelectBGM05.wav", true},	//�X�e�[�W�Z���N�gBGM(������)
	//	{"assets/BGM/StageBGM01.wav", true},		//�Q�[��BGM(1)
	//	{"assets/BGM/StageBGM02.wav", true},		//�Q�[��BGM(2)
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//�Q�[��BGM(3)
	//	{"assets/BGM/StageBGM04.wav", true},		//�Q�[��BGM(4)
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//�Q�[��BGM(BOSS��F�O��)
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//�Q�[��BGM(BOSS��F�㔼)
	//	{"assets/SE/jump.wav", false},  		// �T���v��SE
	//	{"assets/SE/defend0.wav", false},		// �T���v��SE
	//	{"assets/SE/defend1.wav", false},		// �T���v��SE
	//	{"assets/SE/hit0.wav", false},			// �T���v��SE
	//	{"assets/SE/laser0.wav", false},		// �T���v��SE
	//	{"assets/SE/lockon0.wav", false},		// �T���v��SE
	//	{"assets/SE/shot0.wav", false},		// �T���v��SE
	//	{"assets/SE/shot1.wav", false},		// �T���v��SE
	//};
	HRESULT      hr;

	// �b�n�l�̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&g_pXAudio2, 0);		// �������ͤ����t���O �f�o�b�O���[�h�̎w��(���݂͖��g�p�Ȃ̂�0�ɂ���)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// ��O�����́Awindows�ł͖���
	if (FAILED(hr)) {
		//CoUninitialize();
	}

	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);			// ����͂o�b�̃f�t�H���g�ݒ�ɔC���Ă���
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// �{���U�̈����������Ă���
	if (FAILED(hr)) {
		if (g_pXAudio2)	g_pXAudio2->Release();
		//CoUninitialize();
	}

	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;


	for (int n= SOUND_LABEL_OPTION_DECISION_SE; n< SOUND_LABEL_NOTE_BGM+1; n++)
	{
		SOUND i = (SOUND)n;
		int a = n - SOUND_LABEL_OPTION_DECISION_SE;
		memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(OptionSound[a].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL);

		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &g_wfx[i], dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		g_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, g_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
		g_buffer[i].AudioBytes = dwChunkSize;
		g_buffer[i].pAudioData = g_DataBuffer[i];
		g_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		if (OptionSound[a].bLoop)
			g_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			g_buffer[i].LoopCount = 0;

		g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[i], &(g_wfx[i].Format));
	}
	{///**** Initalize Sound ****/
	//for (int i = 0; i < SOUND_LABEL_MAX; i++)
	//{
	//	memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
	//	memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

	//	hFile = CreateFileA(g_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
	//		OPEN_EXISTING, 0, NULL);

	//	//check the file type, should be fourccWAVE or 'XWMA'
	//	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	//	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

	//	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	//	ReadChunkData(hFile, &g_wfx[i], dwChunkSize, dwChunkPosition);

	//	//fill out the audio data buffer with the contents of the fourccDATA chunk
	//	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	//	g_DataBuffer[i] = new BYTE[dwChunkSize];
	//	ReadChunkData(hFile, g_DataBuffer[i], dwChunkSize, dwChunkPosition);

	//	CloseHandle(hFile);

	//	// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
	//	g_buffer[i].AudioBytes = dwChunkSize;
	//	g_buffer[i].pAudioData = g_DataBuffer[i];
	//	g_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
	//	if (g_param[i].bLoop)
	//		g_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
	//	else
	//		g_buffer[i].LoopCount = 0;

	//	g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[i], &(g_wfx[i].Format));
	//}
	}
}

Sound::~Sound()
{
	for (int n = 0; n < g_pSourceVoice.size(); n++)
	{
		SOUND i = (SOUND)n;
		if (g_pSourceVoice[i]!=NULL)
		{
			g_pSourceVoice[i]->Stop(0);
			g_pSourceVoice[i]->FlushSourceBuffers();
			g_pSourceVoice[i]->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
			g_pSourceVoice.erase(i);
			delete[]  g_DataBuffer[i];
			g_DataBuffer.erase(i);
		}
	}

	if(g_pMasteringVoice!=nullptr)
	g_pMasteringVoice->DestroyVoice();

	if (g_pXAudio2) g_pXAudio2->Release();
}


//=============================================================================
// �J������
//=============================================================================
void Sound::Release(Scene_Transition scenename)
{
	int start = 0, end = 0;
	switch (scenename)
	{
	case SCENE_ROGO:
		start = 0;
		end = 0;
		break;
	case SCENE_TITLE:
		start = SOUND_LABEL_TITLE_BGM;
		end = SOUND_LABEL_TITLE_CURSOR_SE + 1;
		break;
	case SCENE_STAGESELECT:
		start = SOUND_LABEL_STAGE_MEADOW_BGM;
		end = SOUND_LABEL_STAGE_DECISION_SE + 1;
		break;
	case SCENE_GAMESCENE:
		start = SOUND_LABEL_STAGECLEAR;
		end = SOUND_LABEL_LILITHBARRIER_SE + 1;
		break;
	case SCENE_RESULT:
		start = SOUND_LABEL_RESULT_WIN_BGM;
		end = SOUND_LABEL_PINKSTAREFFECT_SE + 1;
		break;
	case SCENE_STORY:
		start = SOUND_LABEL_STORY_BGM;
		end = SOUND_LABEL_STORYEND_SE + 1;
		break;
	default:
		start = 0;
		end = 0;
		break;
	}

	for (int n = start; n < end; n++)
	{
		SOUND i = (SOUND)n;
		if (g_pSourceVoice[i])
		{
			g_pSourceVoice[i]->Stop(0);
			g_pSourceVoice[i]->FlushSourceBuffers();
			g_pSourceVoice[i]->DestroyVoice();			// �I�[�f�B�I�O���t����\�[�X�{�C�X���폜
			delete[]  g_DataBuffer[i];
			g_pSourceVoice.erase(i);
			g_DataBuffer.erase(i);
		}
	}
	if (end != 0 && start != 0) {
		g_pMasteringVoice->DestroyVoice();

		if (g_pXAudio2) g_pXAudio2->Release();
	}
	// �b�n�l�̔j��
	//CoUninitialize();
}

//=============================================================================
// ���ʐݒ�
//=============================================================================
void Sound::Set_Volume(SOUND label,float volume)
{
	//���ʐݒ�
	g_pSourceVoice[label]->SetVolume(volume);
}

//=============================================================================
// �Đ�
//=============================================================================
void Sound::Play(SOUND label)
{
	// �\�[�X�{�C�X�쐬
	g_pXAudio2->CreateSourceVoice(&(g_pSourceVoice[label]), &(g_wfx[label].Format));
	g_pSourceVoice[label]->SubmitSourceBuffer(&(g_buffer[label]));	// �{�C�X�L���[�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�

	// �Đ�
	g_pSourceVoice[label]->Start(0);

}

//=============================================================================
// ��~
//=============================================================================
void Sound::Stop(SOUND label)
{
	if (g_pSourceVoice[label] == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	g_pSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		g_pSourceVoice[label]->Stop(0);
	}
}

//=============================================================================
// �ꎞ��~
//=============================================================================
void Sound::Pause(SOUND label)
{
	g_pSourceVoice[label]->Stop(0);
}

//=============================================================================
// ���X�^�[�g
//=============================================================================
void Sound::Restart(SOUND label)
{
	g_pSourceVoice[label]->Start(0);
}


void Sound::Set_Scene(Scene_Transition scenename)
{
	// �b�n�l�̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	XAudio2Create(&g_pXAudio2, 0);
	g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	int start = 0, end = 0;
	std::vector<PARAM> sound;
	switch (scenename)
	{
	case SCENE_ROGO:
		start = 0;
		end = 0;
		break;
	case SCENE_TITLE:
		sound = TitleSound;
		start = SOUND_LABEL_TITLE_BGM;
		end = SOUND_LABEL_TITLE_CURSOR_SE+1;
		break;
	case SCENE_STAGESELECT:
		sound = StageSelectSound;
		start = SOUND_LABEL_STAGE_MEADOW_BGM;
		end = SOUND_LABEL_STAGE_DECISION_SE + 1;
		break;
	case SCENE_GAMESCENE:
		sound = GameSceneSound;
		start = SOUND_LABEL_STAGECLEAR;
		end = SOUND_LABEL_LILITHBARRIER_SE + 1;
		break;
	case SCENE_RESULT:
		sound = ResultSound;
		start = SOUND_LABEL_RESULT_WIN_BGM;
		end = SOUND_LABEL_PINKSTAREFFECT_SE + 1;
		break; 
	case SCENE_STORY:
		sound = StorySound;
		start = SOUND_LABEL_STORY_BGM;
		end = SOUND_LABEL_STORYEND_SE + 1;
		break;
	default:
		break;
	}


	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;
	for (int n = start; n < end; n++)
	{
		SOUND i = (SOUND)n;
		int a = n - start;
		memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(sound[a].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL);

		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &g_wfx[i], dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		g_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, g_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 	�T�u�~�b�g�{�C�X�ŗ��p����T�u�~�b�g�o�b�t�@�̐ݒ�
		g_buffer[i].AudioBytes = dwChunkSize;
		g_buffer[i].pAudioData = g_DataBuffer[i];
		g_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		if (sound[a].bLoop)
			g_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			g_buffer[i].LoopCount = 0;

		g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[i], &(g_wfx[i].Format));
	}

}


//=============================================================================
// ���[�e�B���e�B�֐��Q
//=============================================================================
HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT Sound::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}