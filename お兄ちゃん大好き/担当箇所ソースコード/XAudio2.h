//=============================================================================
//
// サウンド処理 [XAudio2.h]
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
	//タイトル
	SOUND_LABEL_TITLE_BGM ,				//タイトルBGM
	SOUND_LABEL_TITLE_DECISION_SE,		//タイトル決定SE
	SOUND_LABEL_TITLE_BACK_SE,			//タイトル戻るSE
	SOUND_LABEL_TITLE_CURSOR_SE,		//タイトルカーソルSE

	//ステージセレクト
	SOUND_LABEL_STAGE_MEADOW_BGM,		//ステージセレクトBGM(草原)
	SOUND_LABEL_STAGE_ICE_BGM,			//ステージセレクトBGM(氷山)
	SOUND_LABEL_STAGE_FORT_BGM,			//ステージセレクトBGM(砦)
	SOUND_LABEL_STAGE_VOLCANO_BGM,		//ステージセレクトBGM(火山)
	SOUND_LABEL_STAGE_CEMETERY_BGM,		//ステージセレクトBGM(墓地)
	SOUND_LABEL_STAGE_DEMONCASTLE_BGM,	//ステージセレクトBGM(魔王城)

	SOUND_LABEL_INGAMESTAGE1_SE,		//ゲームセレクトSEゲーム入るとき(行くよ)
	SOUND_LABEL_INGAMESTAGE2_SE,		//ゲームセレクトSEゲーム入るとき(準備はいいかな)
	SOUND_LABEL_INGAMESTAGE3_SE,		//ゲームセレクトSEゲーム入るとき(パパっと行っちゃおう)
	SOUND_LABEL_INGAMESTAGE4_SE,		//ゲームセレクトSEゲーム入るとき(さぁ、かかってきなさい)
	SOUND_LABEL_INGAMESTAGE5_SE,		//ゲームセレクトSEゲーム入るとき(よ～し、やるぞ～)
	SOUND_LABEL_STAGE_WALK_SE,			//ステージセレクト妹歩行SE
	SOUND_LABEL_STAGE_LILITHWALK_SE,	//ステージセレクト魔王歩行SE
	SOUND_LABEL_LOAD_SE,				//ステージセレクト道ができるSE
	SOUND_LABEL_STAGE_DECISION_SE,		//ステージセレクト決定SE

	//ゲームシーン
	SOUND_LABEL_STAGECLEAR,				//ステージクリアBGM
	SOUND_LABEL_FEVER,					//フィーバーBGM
	SOUND_LABEL_STAGE_1_BGM,			//ゲームBGM(1)
	SOUND_LABEL_STAGE_2_BGM,			//ゲームBGM(2)
	SOUND_LABEL_STAGE_MINBOSS_BGM,		//ゲームBGM(2)
	SOUND_LABEL_STAGE_3_BGM,			//ゲームBGM(3)
	SOUND_LABEL_STAGE_4_BGM,			//ゲームBGM(4)
	SOUND_LABEL_STAGE_BOSS_BGM01,		//ゲームBGM(BOSS戦：前半)
	SOUND_LABEL_STAGE_BOSS_BGM02,		//ゲームBGM(BOSS戦：後半)

	SOUND_LABEL_FEVER_SE,				//ゲームSEフィーバー時	
	SOUND_LABEL_BULLETLOSE_SE,			//ゲームSE弾切れ	
	SOUND_LABEL_CANNONLOSE_SE,			//ゲームSE弾切れ	
	SOUND_LABEL_CAKEFIRE_SE,			//ゲームSEケーキ人形弾発砲
	SOUND_LABEL_STRONGFIRE_SE,			//ゲームSE強化弾発砲
	SOUND_LABEL_NORMALFIRE_SE,			//ゲームSE通常弾発砲
	SOUND_LABEL_FEVERFIRE_SE,			//ゲームSE天使弾発砲
	SOUND_LABEL_CAKELANDING_SE,			//ゲームSEケーキ、人形弾着弾
	SOUND_LABEL_STRONGLANDING_SE,		//ゲームSE強化弾着弾
	SOUND_LABEL_NORAMLLANDING_SE,		//ゲームSE通常弾着弾
	SOUND_LABEL_FEVERLANDING_SE,		//ゲームSE天使弾着弾
	SOUND_LABEL_SISTEREAT_SE,			//ゲームSE妹ケーキを食べる
	SOUND_LABEL_SISTERDOLL_SE,			//ゲームSE妹人形で遊ぶ
	SOUND_LABEL_CHANGECOLOUR_SE,		//ゲームSE色が変わる
	SOUND_LABEL_ENEMYDIE_SE,			//ゲームSE敵自爆
	SOUND_LABEL_MAGICSTONE_SE,			//ゲームSE魔石カウント
	SOUND_LABEL_CUTIN_SE,				//ゲームSEカットイン
	SOUND_LABEL_LILITHWAND_SE,			//ゲームSE魔王杖を振る
	SOUND_LABEL_LILITHWANDCHARGE_SE,	//ゲームSE魔王が力を溜める
	SOUND_LABEL_CANNONBREAK_SE,			//ゲームSE大砲を壊す
	SOUND_LABEL_BULLETBREAK_SE,			//ゲームSE弾が割れる
	SOUND_LABEL_MAGICCIRCLE_SE,			//ゲームSE魔法陣
	SOUND_LABEL_DEVILERASE_SE,			//ゲームSE魔王消滅
	SOUND_LABEL_DEVILSHELLING_SE,		//ゲームSE魔王砲撃
	SOUND_LABEL_DEVILMOVE_SE,			//ゲームSE魔王移動
	SOUND_LABEL_LILITHBARRIER_SE,		//ゲームSE魔王バリア

	//リザルト
	SOUND_LABEL_RESULT_WIN_BGM,			//リザルトBGM(勝利)
	SOUND_LABEL_RESULT_LOSE_BGM,		//リザルトBGM(敗北)
	SOUND_LABEL_ARANKU_SE,				//リザルトSEAランクセリフ
	SOUND_LABEL_BRANKU_SE,				//リザルトSEBランクセリフ
	SOUND_LABEL_GAMEOVER_SE,			//リザルトSEゲームオーバーセリフ
	SOUND_LABEL_SRANKU_SE,				//リザルトSESランクセリフ
	SOUND_LABEL_SSRANKU_SE,				//リザルトSESSランクセリフ
	SOUND_LABEL_YELLOWSTAREFFECT_SE,	//リザルトSE黄色星がはまる
	SOUND_LABEL_PINKSTAREFFECT_SE,		//リザルトSEピンク星がはまる

	//ストーリー
	SOUND_LABEL_STORY_BGM,				//ストーリーBGM
	SOUND_LABEL_ENDROLL_BGM,			//エンドロールBGM
	SOUND_LABEL_STORYEND_SE,			//ストーリーSEエンドストーリー２セリフ

	//オプション
	SOUND_LABEL_OPTION_DECISION_SE,		//オプションSE決定
	SOUND_LABEL_OPTION_BACK_SE,			//オプションSE戻る
	SOUND_LABEL_OPTION_CURSOR_SE,		//オプションSEカーソル
	SOUND_LABEL_NOTE_BGM,				//ノートBGM
};

// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
} PARAM;

class Sound:public singleton<Sound>
{
public:
	explicit Sound(token);
	~Sound();
	void Set_Scene(Scene_Transition scenename);
	void Play(SOUND label);	 //音声の開始(0から)
	void Stop(SOUND label);   //音声の停止
	void Pause(SOUND label);  //音声の一時停止
	void Restart(SOUND label);//音声の途中再生
	void Set_Volume(SOUND label,float volume);
	void Release(Scene_Transition scenename);//解放
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

	std::unordered_map<SOUND,WAVEFORMATEXTENSIBLE>g_wfx;			// WAVフォーマット
	std::unordered_map<SOUND,XAUDIO2_BUFFER>	g_buffer;
	std::unordered_map<SOUND, BYTE*> g_DataBuffer;
};

#endif
