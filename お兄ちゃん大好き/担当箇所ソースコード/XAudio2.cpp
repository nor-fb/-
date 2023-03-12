//=============================================================================
//
// サウンド処理 [XAudio2.cpp]
//
//=============================================================================

#include "XAudio2.h"


//=============================================================================
// 初期化(ループ：BGM=true,SE=false)
//=============================================================================
Sound::Sound(token)
{
	//タイトル
	TitleSound = {
		{ "assets/BGM/Title.wav",true },//タイトルBGM
		{ "assets/SE/19決定/item-01.wav",false },//タイトルSE決定
		{ "assets/SE/20戻る/item-02.wav",false },//タイトルSE戻る
		{ "assets/SE/21カーソル移動/cursor-01.wav",false },//タイトルSEカーソル移動
	};
	//ステージセレクト
	StageSelectSound = {
		{ "assets/BGM/StageSelect01.wav",true },	//ステージセレクトBGM(草原)
		{ "assets/BGM/StageSelect02.wav",true },	//ステージセレクトBGM(氷山)
		{ "assets/BGM/StageSelectMinBoss.wav",true },//ステージセレクトBGM(砦)
		{ "assets/BGM/StageSelect03.wav",true },	//ステージセレクトBGM(火山)
		{ "assets/BGM/StageSelect04.wav",true },	//ステージセレクトBGM(墓地)
		{ "assets/BGM/StageSelectBoss.wav",true },	//ステージセレクトBGM(魔王城)

		{ "assets/SE/ステージ開始時/ikuyo_02.wav",false },//ステージセレクトSE入るとき
		{ "assets/SE/ステージ開始時/junbiwaiikana_01.wav",false },//ステージセレクトSE入るとき
		{ "assets/SE/ステージ開始時/papattoicchaou_01.wav",false },//ステージセレクトSE入るとき
		{ "assets/SE/ステージ開始時/saakakattekinasai_01.wav",false },//ステージセレクトSE入るとき
		{ "assets/SE/ステージ開始時/yoshiyaruzo_01.wav",false },//ステージセレクトSE入るとき
		{ "assets/SE/18ステセレ歩行音/Accent41-1.wav",true },//ステージセレクトSE歩行
		{ "assets/SE/魔王/ステセレ移動.wav",false},//ステージセレクトSE魔王歩行
		{ "assets/SE/道出現/2.wav",false},//道出現SE
		{ "assets/SE/19決定/Accent24-2.wav",false },//ステージセレクトSE決定

	};
	//ゲームシーン
	GameSceneSound = {
		{"assets/BGM/GameCler.wav", true},			//ステージクリアBGM
		{ "assets/BGM/Fever.wav", true},			//ステージクリアBGM
		{ "assets/BGM/Stage01.wav",true },			//ゲームBGM(1)
		{ "assets/BGM/Stage02.wav",true },			//ゲームBGM(2)
		{ "assets/BGM/StageMinBoss.wav",true },		//ゲームBGM(2)
		{ "assets/BGM/Stage03.wav",true },			//ゲームBGM(3)
		{ "assets/BGM/Stage04.wav",true },			//ゲームBGM(4)
		{ "assets/BGM/StageBoss01.wav",true },		//ゲームBGM(BOSS戦：前半)
		{ "assets/BGM/StageBoss02.wav",true },		//ゲームBGM(BOSS戦：後半)

		{ "assets/SE/フィーバー時/Fever.wav",false },//フィーバー時
		{"assets/SE/弾が割れる/弾切れ.wav",false}, //ゲームSE弾切れ
		{"assets/SE/弾が割れる/大砲壊れてる.wav",false}, //ゲームSE弾切れ(大砲壊れている)
		{ "assets/SE/00発砲音/ケーキ、人形弾.wav", false},//ゲームSEケーキ、人形弾発砲
		{ "assets/SE/00発砲音/強化弾.wav",false },	//ゲームSE強化弾発砲
		{ "assets/SE/00発砲音/通常弾.wav",false },	//ゲームSE通常弾発砲
		{ "assets/SE/00発砲音/天使弾.wav",false },	//ゲームSE天使弾
		{ "assets/SE/02着弾音/ケーキ、人形弾着弾.wav",false },//ゲームSEケーキ人形弾着弾
		{ "assets/SE/02着弾音/強化弾着弾.wav",false },//ゲームSE強化弾着弾
		{ "assets/SE/02着弾音/通常弾着弾.wav",false },//ゲームSE通常弾着弾
		{ "assets/SE/02着弾音/天使弾着弾.wav",false },//ゲームSE天使弾着弾
		{ "assets/SE/03食べる音/Sister_eat.wav",false },//ゲームSE妹ケーキ食べる
		{ "assets/SE/04遊ぶ音/Sister_Doll.wav",false },//ゲームSE妹人形遊ぶ
		{ "assets/SE/07.5色がつく音/暫定/Accent30-1.wav",false },//ゲームSEステージに色がつく
		{ "assets/SE/07敵自爆/暫定/enemy-attack.wav",false },//ゲームSE敵自爆
		{ "assets/SE/09魔石のカウントアップ/魔石カウント.wav",false },//ゲームSE魔石カウント
		{ "assets/SE/13カットイン/効果音ラボ/暫定/ステータス治療2.wav",false },//ゲームSEカットイン
		{ "assets/SE/14魔王杖を振る/魔王魂 効果音 エフェクト03.wav", false},//ゲームSE魔王杖を振る
		{ "assets/SE/14魔王杖を振る/se_chikara.wav",true},//ゲームSE魔王力を溜める
		{ "assets/SE/16大砲破壊（１３と同じ説）/se_explode08.wav",false},//ゲームSE大砲破壊
		{"assets/SE/弾が割れる/sei_ge_syokki_wareru04.wav",false},//ゲームSE弾が割れる
		{"assets/SE/魔法陣/ta_ta_syara02 .wav",false},//ゲームSE魔法陣
		{"assets/SE/魔王/消滅.wav",false},//ゲームSE魔王消滅
		{"assets/SE/魔王/砲撃.wav",false},//ゲームSE魔王砲撃
		{"assets/SE/魔王/ゲーム移動.wav",true},//ゲームSE魔王ゲーム移動
		{ "assets/SE/17魔王バリア発生/効果音ラボ/刀で打ち合う1.wav",false },//ゲームSE魔王バリア
	};
	//リザルト
	ResultSound = {
		{ "assets/BGM/ResultWin.wav",true },		//リザルトBGM(勝利)
		{ "assets/BGM/ResultLose.wav",true },	//リザルトBGM(敗北)
		{ "assets/SE/リザルト/Aranku.wav",false },//リザルトSEAランクセリフ
		{ "assets/SE/リザルト/Branku.wav",false },//リザルトSEBランクセリフ
		{ "assets/SE/リザルト/GameOver.wav",false },//リザルトSEゲームオーバーセリフ
		{ "assets/SE/リザルト/Sranku.wav",false },//リザルトSESランクセリフ
		{ "assets/SE/リザルト/SSranku.wav",false },//リザルトSESSランクセリフ
		{ "assets/SE/23星のはまる音/yellowstar.wav",false },//リザルト黄色星がはまる
		{ "assets/SE/23星のはまる音/pinkstar.wav",false },//リザルトピンク星がはまる
	};
	//ストーリー
	StorySound = {
		{"assets/BGM/Story.wav",false},//ストーリーBGM
		{"assets/BGM/EndRoll.wav",true},//エンドロールBGM
		{"assets/SE/エンドストーリー２セリフ目/Endroll.wav", false},//ストーリーSEエンドストーリー２セリフ
	};
	//オプション
	OptionSound = {
		{ "assets/SE/19決定/item-01.wav",false },//オプションSE決定
		{ "assets/SE/20戻る/item-02.wav",false },//オプションSE戻る
		{ "assets/SE/21カーソル移動/cursor-01.wav",false },//オプションSEカーソル
		{ "assets/SE/21カーソル移動/cursor-01.wav",false },//オプションSEカーソル
	};
	//PARAM g_param[SOUND_LABEL_MAX] =
	//{
	//	{"assets/BGM/TitleBGM.wav", true},			// タイトルBGM
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//オプション・ポーズBGM
	//	{"assets/BGM/ResultWinBGM.wav", true},		//リザルトBGM(勝利)
	//	{"assets/BGM/ResultLoseBGM.wav", true},		//リザルトBGM(敗北)
	//	{"assets/BGM/StageClearBGM.wav", true},		//ステージクリアBGM
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//ノートBGM
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//ステージセレクトBGM(草原)
	//	{"assets/BGM/StageSelectBGM02.wav", true},	//ステージセレクトBGM(氷山)
	//	{"assets/BGM/StageSelectBGM03.wav", true},	//ステージセレクトBGM(火山)
	//	{"assets/BGM/StageSelectBGM04.wav", true},	//ステージセレクトBGM(墓地)
	//	{"assets/BGM/StageSelectBGM05.wav", true},	//ステージセレクトBGM(魔王城)
	//	{"assets/BGM/StageBGM01.wav", true},		//ゲームBGM(1)
	//	{"assets/BGM/StageBGM02.wav", true},		//ゲームBGM(2)
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//ゲームBGM(3)
	//	{"assets/BGM/StageBGM04.wav", true},		//ゲームBGM(4)
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//ゲームBGM(BOSS戦：前半)
	//	{"assets/BGM/StageSelectBGM01.wav", true},	//ゲームBGM(BOSS戦：後半)
	//	{"assets/SE/jump.wav", false},  		// サンプルSE
	//	{"assets/SE/defend0.wav", false},		// サンプルSE
	//	{"assets/SE/defend1.wav", false},		// サンプルSE
	//	{"assets/SE/hit0.wav", false},			// サンプルSE
	//	{"assets/SE/laser0.wav", false},		// サンプルSE
	//	{"assets/SE/lockon0.wav", false},		// サンプルSE
	//	{"assets/SE/shot0.wav", false},		// サンプルSE
	//	{"assets/SE/shot1.wav", false},		// サンプルSE
	//};
	HRESULT      hr;

	// ＣＯＭの初期化
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&g_pXAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// 第三引数は、windowsでは無視
	if (FAILED(hr)) {
		//CoUninitialize();
	}

	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// 本当６個の引数を持っている
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

		// 	サブミットボイスで利用するサブミットバッファの設定
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

	//	// 	サブミットボイスで利用するサブミットバッファの設定
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
			g_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
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
// 開放処理
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
			g_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  g_DataBuffer[i];
			g_pSourceVoice.erase(i);
			g_DataBuffer.erase(i);
		}
	}
	if (end != 0 && start != 0) {
		g_pMasteringVoice->DestroyVoice();

		if (g_pXAudio2) g_pXAudio2->Release();
	}
	// ＣＯＭの破棄
	//CoUninitialize();
}

//=============================================================================
// 音量設定
//=============================================================================
void Sound::Set_Volume(SOUND label,float volume)
{
	//音量設定
	g_pSourceVoice[label]->SetVolume(volume);
}

//=============================================================================
// 再生
//=============================================================================
void Sound::Play(SOUND label)
{
	// ソースボイス作成
	g_pXAudio2->CreateSourceVoice(&(g_pSourceVoice[label]), &(g_wfx[label].Format));
	g_pSourceVoice[label]->SubmitSourceBuffer(&(g_buffer[label]));	// ボイスキューに新しいオーディオバッファーを追加

	// 再生
	g_pSourceVoice[label]->Start(0);

}

//=============================================================================
// 停止
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
// 一時停止
//=============================================================================
void Sound::Pause(SOUND label)
{
	g_pSourceVoice[label]->Stop(0);
}

//=============================================================================
// リスタート
//=============================================================================
void Sound::Restart(SOUND label)
{
	g_pSourceVoice[label]->Start(0);
}


void Sound::Set_Scene(Scene_Transition scenename)
{
	// ＣＯＭの初期化
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

		// 	サブミットボイスで利用するサブミットバッファの設定
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
// ユーティリティ関数群
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