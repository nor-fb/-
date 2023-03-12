using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

/// <summary>
/// プレイヤー目の動き
/// </summary>
public class Player_Eye : MonoBehaviour
{
    [Header("目の移動最高速度")]
    [Tooltip("初期値：X=0.1、Y=0.2")]
    public Vector2 Max_move;
    [Header("瞬きクールタイム")]
    [Tooltip("初期値：2")]
    public float Blink_Cool_Time;
    [Header("瞬きの回数")]
    [Tooltip("初期値：3")]
    public int Blink_Count;
    [Header("瞬き時間")]
    [Tooltip("初期値：1")]
    public float BlinkTime;
    [Header("ZZZ移動速度")]
    [Tooltip("初期値：100")]
    public float Zzz_Move;
    [Header("ZZZ透明化速度")]
    [Tooltip("初期値：2")]
    public float Zzz_FadeSpeed;
    [Header("ZZZ移動量")]
    [Tooltip("初期値：X=1.7、Y=1.5")]
    public Vector2 ZzzMovePos;
    [Header("ZZZ拡大・縮小量")]
    [Tooltip("初期値：X=1、Y=1")]
    public Vector2 ZzzMoveSca;

    private GameObject EyeObject;             //目オブジェクト格納先
    private Image ZzzObject;                  //ZZZオブジェクト格納先
    private Image SurprisedObject;             //!オブジェクト格納先
    private Image Frame;                      //雲形フレーム格納先
    private GameObject Player;                //プレイヤー格納先
    private int Anima_Index;                  //アニメーション番号
    private Sprite[] Sprites = new Sprite[6]; //目玉の種類
    private float BlinkTimer;                 //瞬き時間計測用
    private int BlinkCounter;                 //瞬き回数計測用
    private Vector3 Zzz_Coordinate;           //ZZZオブジェクト初期位置格納先
    private Vector3 Zzz_Scale;                //ZZZオブジェクト初期サイズ格納先
    private Vector3 Surprised_Coordinate;      //!オブジェクト初期位置格納先
    private int Zzz_Count;                    //ZZZ移動回数計測用
    enum Status
    {
        NORMAL,       //通常
        BLINK,        //瞬き
        WAIT,         //停止
        FIT_ROTATE,   //噛み合い(回転:可)
        FIT_NOROTATE, //噛み合い(回転:不可)
        GOAL,         //ゴール
    }
    Status status;

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Start()
    {
        //格納
        EyeObject = GameObject.Find("eyeball");
        Player = gameObject.transform.parent.gameObject;
        ZzzObject = GameObject.Find("ZZZ").GetComponent<Image>();
        SurprisedObject = GameObject.Find("!").GetComponent<Image>();
        Frame = gameObject.transform.Find("Speech_Bubble").GetComponent<Image>();
        Sprites[0] = Resources.Load<Sprite>("Eye_Type/Eye_0");
        Sprites[1] = Resources.Load<Sprite>("Eye_Type/Eye_1");
        Sprites[2] = Resources.Load<Sprite>("Eye_Type/Eye_2");
        Sprites[3] = Resources.Load<Sprite>("Eye_Type/Eye_3");
        Sprites[4] = Resources.Load<Sprite>("Eye_Type/Eye_4");
        Sprites[5] = Resources.Load<Sprite>("Eye_Type/Eye_3");
        //計測用初期化
        Zzz_Count = 0;
        BlinkTimer = 0;
        BlinkCounter = 0;
        //初期座標格納
        Zzz_Coordinate = ZzzObject.transform.localPosition;
        Zzz_Scale = ZzzObject.transform.localScale;
        Surprised_Coordinate = SurprisedObject.transform.localPosition;
        //Frame・ZzzObject透明化
        Frame.color = new Color(0, 0, 0, 0);
        ZzzObject.color = new Color(0, 0, 0, 0);
        SurprisedObject.color = new Color(0, 0, 0, 0);
    }

    /// <summary>
    /// 更新処理(毎フレーム)
    /// </summary>
    void FixedUpdate()
    {
        this.transform.rotation = Quaternion.Euler(0, 0, 0);
        EyeObject.transform.rotation = Quaternion.Euler(0, 0, 0);
        EyeProcess();
    }

    /// <summary>
    /// 目処理(移動・アニメーション)
    /// </summary>
    private void EyeProcess()
    {
        //ゴールフラグ
        bool Goal_flag = Player.GetComponent<GoalPlayerScript>().goalflg || Player.GetComponent<GoalPlayerScript>().goalmoveflg || Player.GetComponent<GoalPlayerScript>().endflg;
        bool Time_flag = GameDirectorScript.Instance.time == 0;
        //ゲームパッド用
        bool LeftStick = InputScript.Instance.GetGamePadLeftStickX() != 0 || InputScript.Instance.GetGamePadLeftStickY() != 0;
        bool RightStick = InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetGamePadRightStickY() != 0;
        //キーボード用
        bool LeftInput = InputScript.Instance.GetKeyboardPress(KeyCode.W) || InputScript.Instance.GetKeyboardPress(KeyCode.A) || InputScript.Instance.GetKeyboardPress(KeyCode.S) || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool RightInput = InputScript.Instance.GetKeyboardPress(KeyCode.UpArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.DownArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow);
        //ジャンプ
        bool Jump = InputScript.Instance.GetGamePadButtonTrigger(GamePadKey.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.Space);

        bool movePattern = Player.GetComponent<Player_M>().MovePattern;
        bool double_flag = Player.GetComponent<Player_M>().DoubleCol_flag;
        bool Fall_flag = Player.GetComponent<Player_M>().Fall_flag;
        bool Rotate_flag = Player.GetComponent<Player_M>().Rotate_flag;
        bool Jump_flag = Player.GetComponent<Player_M>().Jump_flag;
        //ゴールフラグ確認
        if (Goal_flag)
        {
            status = Status.GOAL;
            AnimationSprite((int)status);
            EyeObject.transform.localPosition = new Vector3(0, 0, 0);//中央に移動
            ///////////追加///////////
            Frame.color = new Color(0, 0, 0, 0);    //吹き出し非表示
            ZzzObject.color = new Color(0, 0, 0, 0);
            ZzzObject.transform.localPosition = Zzz_Coordinate;
            ZzzObject.transform.localScale = Zzz_Scale;
            Zzz_Count = 0;
            SurprisedObject.color = new Color(0, 0, 0, 0);
            SurprisedObject.transform.localPosition = Surprised_Coordinate;
            //////////////////////////
            return;
        }
        //オプション確認
        if (Time_flag)
            return;
        //右スティック入力あり
        if (!Jump && RightStick || RightInput)//追加
        {
            if (status == Status.WAIT)
            {
                status = Status.NORMAL;
                AnimationSprite((int)Status.NORMAL);
                Frame.color = new Color(0, 0, 0, 0);    //吹き出し非表示
                //zzz初期化
                ZzzObject.color = new Color(0, 0, 0, 0);
                ZzzObject.transform.localPosition = Zzz_Coordinate;
                ZzzObject.transform.localScale = Zzz_Scale;
                Zzz_Count = 0;
                SurprisedObject.color = new Color(0, 0, 0, 0);
                SurprisedObject.transform.localPosition = Surprised_Coordinate;
            }
            if (!Fall_flag)//接触中
            {
                /////////追加・変更//////////
                if (!double_flag)
                {
                    //ギア
                    if (movePattern)
                    {
                        status = Status.FIT_ROTATE;
                        Frame.color = new Color(0, 0, 0, 0);
                        SurprisedObject.color = new Color(0, 0, 0, 0);
                        SurprisedObject.transform.localPosition = Surprised_Coordinate;
                        if (!Rotate_flag)
                            status = Status.FIT_NOROTATE;
                    }
                    //足場
                    else if (!movePattern)
                    {
                        status = Status.FIT_ROTATE;
                        Frame.color = new Color(0, 0, 0, 0);
                        SurprisedObject.color = new Color(0, 0, 0, 0);
                        SurprisedObject.transform.localPosition = Surprised_Coordinate;
                        if (!Rotate_flag)
                            status = Status.FIT_NOROTATE;
                    }
                }
                else
                {
                    status = Status.FIT_NOROTATE;
                }
                /////////////////////////////
                //眼の位置調整
                if (status == Status.FIT_ROTATE || status == Status.FIT_NOROTATE)
                    EyeObject.transform.localPosition = new Vector3(0, 0, 0);//中央に移動
            }
            else//非接触中
                status = Status.NORMAL;
            //表情変更
            AnimationSprite((int)status);
        }

        switch (status)
        {
            case Status.NORMAL:
                //スティック入力
                if (LeftStick)
                {
                    double Angle = Mathf.Atan2(InputScript.Instance.GetGamePadLeftStickY(), InputScript.Instance.GetGamePadLeftStickX());
                    float MoveX = Mathf.Cos((float)Angle) * Mathf.Abs(InputScript.Instance.GetGamePadLeftStickX()) * Max_move.x;
                    float MoveY = Mathf.Sin((float)Angle) * Mathf.Abs(InputScript.Instance.GetGamePadLeftStickY()) * Max_move.y;
                    EyeObject.transform.localPosition = new Vector3(MoveX, MoveY, EyeObject.transform.localPosition.z);
                }
                //キーボード入力
                else if (LeftInput)
                {
                    bool Right = InputScript.Instance.GetKeyboardPress(KeyCode.D);
                    bool Left = InputScript.Instance.GetKeyboardPress(KeyCode.A);
                    bool Up = InputScript.Instance.GetKeyboardPress(KeyCode.W);
                    bool Down = InputScript.Instance.GetKeyboardPress(KeyCode.S);

                    float MoveX = Convert.ToInt32(Right) + Convert.ToInt32(Left) * -1;
                    float MoveY = Convert.ToInt32(Up) + Convert.ToInt32(Down) * -1;
                    EyeObject.transform.localPosition = new Vector3(MoveX * Max_move.x, MoveY * Max_move.y, EyeObject.transform.localPosition.z);
                }
                //入力なし
                else if (!LeftStick && !LeftInput)
                {
                    EyeObject.transform.localPosition = new Vector3(0, 0, 0);//中央に移動
                }
                //NORMAL→BLINK
                if (BlinkTimer > Blink_Cool_Time && BlinkCounter < Blink_Count)
                {
                    status = Status.BLINK;
                    AnimationSprite((int)Status.BLINK);
                    BlinkTimer = 0.0f;
                    EyeObject.transform.localPosition = new Vector3(0.0f, 0.0f, EyeObject.transform.localPosition.z);
                }
                //NORMAL→WAIT
                else if (BlinkTimer > Blink_Cool_Time && BlinkCounter >= Blink_Count)
                {
                    BlinkCounter = 0;
                    BlinkTimer = 0.0f;
                    status = Status.WAIT;
                    AnimationSprite((int)Status.WAIT);
                    EyeObject.transform.localPosition = new Vector3(0.0f, 0.0f, EyeObject.transform.localPosition.z);
                    if (Player.transform.position.y < 0.25f)
                    {
                        Frame.color = new Color(255, 255, 255, 1.0f);
                        ZzzObject.color = new Color(255, 255, 255, 1.0f);
                        //吹き出し位置・向き調整処理
                        if (Player.transform.position.x >= 0)
                        {
                            Frame.transform.localPosition = new Vector3(-Mathf.Abs(Frame.transform.localPosition.x), Frame.transform.localPosition.y, Frame.transform.localPosition.z);
                            Frame.transform.localScale = new Vector3(-Mathf.Abs(Frame.transform.localScale.x), Frame.transform.localScale.y, Frame.transform.localScale.z);
                            ZzzObject.transform.localScale = new Vector3(-Mathf.Abs(ZzzObject.transform.localScale.x), ZzzObject.transform.localScale.y, ZzzObject.transform.localScale.z);
                        }
                        else
                        {
                            Frame.transform.localPosition = new Vector3(Mathf.Abs(Frame.transform.localPosition.x), Frame.transform.localPosition.y, Frame.transform.localPosition.z);
                            Frame.transform.localScale = new Vector3(Mathf.Abs(Frame.transform.localScale.x), Frame.transform.localScale.y, Frame.transform.localScale.z);
                            ZzzObject.transform.localScale = new Vector3(Mathf.Abs(ZzzObject.transform.localScale.x), ZzzObject.transform.localScale.y, ZzzObject.transform.localScale.z);
                        }
                    }
                }
                //時間加算
                if (!LeftStick && !RightStick && !LeftInput && !RightInput && !Jump)
                    BlinkTimer += Time.deltaTime;
                break;
            case Status.BLINK:
                //BLINK→NORMAL
                if (BlinkTimer > BlinkTime)
                {
                    status = Status.NORMAL;
                    AnimationSprite((int)Status.NORMAL);
                    BlinkCounter++;
                }
                //時間加算
                BlinkTimer += Time.deltaTime;
                break;
            case Status.WAIT:
                if (Player.transform.position.y < 2.0f)
                    ZzzProcess();
                break;
            case Status.FIT_ROTATE:
                if (!RightStick && !RightInput)
                {
                    status = Status.NORMAL;
                    AnimationSprite((int)Status.NORMAL);
                    Frame.color = new Color(0, 0, 0, 0);
                    SurprisedObject.color = new Color(0, 0, 0, 0);
                    SurprisedObject.transform.localPosition = Surprised_Coordinate;
                }
                break;
            case Status.FIT_NOROTATE:
                if (Player.transform.position.y < 2.0f && !Rotate_flag && !Jump_flag)
                    SurprisedProcess();

                if ((LeftStick || LeftInput) || (!RightStick && !RightInput))
                {
                    status = Status.NORMAL;
                    AnimationSprite((int)Status.NORMAL);
                    Frame.color = new Color(0, 0, 0, 0);
                    SurprisedObject.color = new Color(0, 0, 0, 0);
                    SurprisedObject.transform.localPosition = Surprised_Coordinate;
                }
                if (Rotate_flag && !double_flag && (RightStick || RightInput))
                {
                    status = Status.FIT_ROTATE;
                    AnimationSprite((int)Status.FIT_ROTATE);
                    Frame.color = new Color(0, 0, 0, 0);
                    SurprisedObject.color = new Color(0, 0, 0, 0);
                    SurprisedObject.transform.localPosition = Surprised_Coordinate;
                }
                break;
        }

        //入力されたら瞬き・待ち時間初期化 
        if (LeftStick || RightStick || LeftInput || RightInput || Jump)
        {
            if (status == Status.BLINK || status == Status.WAIT)
            {
                BlinkTimer = 0.0f;
                Zzz_Count = 0;
                status = Status.NORMAL;
                AnimationSprite((int)Status.NORMAL);
                Frame.color = new Color(0, 0, 0, 0);    //吹き出し非表示
                //zzz初期化
                ZzzObject.color = new Color(0, 0, 0, 0);
                ZzzObject.transform.localPosition = Zzz_Coordinate;
                ZzzObject.transform.localScale = Zzz_Scale;
                //下2行追加
                SurprisedObject.color = new Color(0, 0, 0, 0);
                SurprisedObject.transform.localPosition = Surprised_Coordinate;
                Zzz_Count = 0;
            }
        }
    }

    /// <summary>
    /// ZZZ処理(吹き出し表示・ZZZアニメーション)
    /// </summary>
    private void ZzzProcess()
    {
        Vector3 NowPos = ZzzObject.transform.localPosition;
        Vector3 NowSca = ZzzObject.transform.localScale;
        //表示されている場合
        if (ZzzObject.color.a > 0)
        {
            //上限突破時非表示にし座標初期化
            if (Zzz_Count >= Zzz_Move)
            {
                if (Player.transform.position.x >= 0)
                    ZzzObject.transform.localPosition = Zzz_Coordinate * -1;
                else
                    ZzzObject.transform.localPosition = Zzz_Coordinate;
                ZzzObject.transform.localScale = Zzz_Scale;
                ZzzObject.color = new Color(255, 255, 255, 0.0f);
                Zzz_Count = 0;
            }
            //ZZZ移動アニメーション
            else
            {
                ZzzObject.transform.localPosition = new Vector3(NowPos.x + ZzzMovePos.x / Zzz_Move, NowPos.y + ZzzMovePos.y / Zzz_Move, NowPos.z);
                if (Player.transform.position.x >= 0)
                    ZzzObject.transform.localScale = new Vector3(NowSca.x - ZzzMoveSca.x / Zzz_Move, NowSca.y + ZzzMoveSca.y / Zzz_Move, NowSca.z);
                else
                    ZzzObject.transform.localScale = new Vector3(NowSca.x + ZzzMoveSca.x / Zzz_Move, NowSca.y + ZzzMoveSca.y / Zzz_Move, NowSca.z);
                Zzz_Count++;
            }
            //半分超えたら徐々にアルファ値を0に近づける
            if (Zzz_Count > Zzz_Move / 2)
                ZzzObject.color = new Color(255, 255, 255, ZzzObject.color.a - Zzz_FadeSpeed / Zzz_Move);
        }
        //非表示の場合
        else if (ZzzObject.color.a == 0)
        {
            if (Player.transform.position.x >= 0)
            {
                Frame.transform.localPosition = new Vector3(-Mathf.Abs(Frame.transform.localPosition.x), Frame.transform.localPosition.y, Frame.transform.localPosition.z);
                Frame.transform.localScale = new Vector3(-Mathf.Abs(Frame.transform.localScale.x), Frame.transform.localScale.y, Frame.transform.localScale.z);
                ZzzObject.transform.localScale = new Vector3(-Mathf.Abs(ZzzObject.transform.localScale.x), ZzzObject.transform.localScale.y, ZzzObject.transform.localScale.z);
            }
            else
            {
                Frame.transform.localPosition = new Vector3(Mathf.Abs(Frame.transform.localPosition.x), Frame.transform.localPosition.y, Frame.transform.localPosition.z);
                Frame.transform.localScale = new Vector3(Mathf.Abs(Frame.transform.localScale.x), Frame.transform.localScale.y, Frame.transform.localScale.z);
                ZzzObject.transform.localScale = new Vector3(Mathf.Abs(ZzzObject.transform.localScale.x), ZzzObject.transform.localScale.y, ZzzObject.transform.localScale.z);
            }
            ZzzObject.color = new Color(255, 255, 255, 1.0f);
            ZzzObject.transform.localPosition = Zzz_Coordinate;
            Zzz_Count = 0;
        }
    }

    /// <summary>
    /// ！処理
    /// </summary>
    private void SurprisedProcess()
    {
        //表示中
        if (SurprisedObject.color.a > 0)
        {
            SurprisedObject.color = new Color(255, 255, 255, 1.0f);
        }
        //非表示中
        else if (SurprisedObject.color.a == 0)
        {
            //座標に応じて位置を変更
            if (Player.transform.position.x >= 0)
            {
                Frame.transform.localPosition = new Vector3(-Mathf.Abs(Frame.transform.localPosition.x), Frame.transform.localPosition.y, Frame.transform.localPosition.z);
                Frame.transform.localScale = new Vector3(-Mathf.Abs(Frame.transform.localScale.x), Frame.transform.localScale.y, Frame.transform.localScale.z);
                SurprisedObject.transform.localScale = new Vector3(-Mathf.Abs(SurprisedObject.transform.localScale.x), SurprisedObject.transform.localScale.y, SurprisedObject.transform.localScale.z);
            }
            else
            {
                Frame.transform.localPosition = new Vector3(Mathf.Abs(Frame.transform.localPosition.x), Frame.transform.localPosition.y, Frame.transform.localPosition.z);
                Frame.transform.localScale = new Vector3(Mathf.Abs(Frame.transform.localScale.x), Frame.transform.localScale.y, Frame.transform.localScale.z);
                SurprisedObject.transform.localScale = new Vector3(Mathf.Abs(SurprisedObject.transform.localScale.x), SurprisedObject.transform.localScale.y, SurprisedObject.transform.localScale.z);
            }
            Frame.color = new Color(255, 255, 255, 1.0f);
            SurprisedObject.color = new Color(255, 255, 255, 1.0f);
            SurprisedObject.transform.localPosition = Surprised_Coordinate;
        }
    }

    /// <summary>
    /// 画像切り替え関数
    /// </summary>
    /// <param name="num">画像番号</param>
    private void AnimationSprite(int num)
    {
        Anima_Index = num;
        EyeObject.GetComponent<Image>().sprite = Sprites[Anima_Index];
        Anima_Index = (Anima_Index + 1) % (Sprites.Length);
    }
}