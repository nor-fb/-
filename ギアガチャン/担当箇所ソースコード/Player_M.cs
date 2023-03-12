using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;
using UnityEngine.UI;


/// <summary>
/// プレイヤーの管理・処理を行うスクリプトばぐあり
/// </summary>
public class Player_M : MonoBehaviour
{
    [Header("プレイヤーの中心を表すオブジェクト格納")]
    public GameObject Player_Center;
    [Header("収集物のエフェクト")]
    public GameObject[] Collection_EF = new GameObject[2];
    [Header("移動速度")]
    public float mo_Speed;
    [Header("回転速度")]
    public float ro_Speed;

    [Header("ギア移動速度")]
    public float G_mo_Speed;
    [Header("足場移動速度")]
    public float S_mo_Speed;
    [Header("ジャンプ力")]
    public float Jump_Power;
    [Header("ジャンプ移動力")]
    public float Jump_Move;
    [Header("ジャンプ回転力")]
    public float Jump_Rota;
    [Header("ジャンプ制限")]
    [Range(0.01f, 10)]
    public float Jump_Limit;
    private Vector2 Jump_Initial_Position;    //ジャンプ前の初期位置

    [Header("足場移動時のチャックマネージャー（チェックする距離の割合）")]
    [Range(0.0f, 2.0f)]
    public float raymaneger = 1.0f;
    [Header("空中移動時のチャックマネージャー（チェックする距離の割合）")]
    [Range(0.0f, 2.0f)]
    public float fallmaneger = 1.0f;
    [Header("ギア移動時のチャックマネージャー（チェックする距離の割合）")]
    [Range(0.0f, 2.0f)]
    public float gearmovemaneger = 1.0f;

    //フラグ
    private bool GearMoveflag;      //ギア移動フラグ・・・TRUE＝移動できる　FALSE＝移動できない
    private bool Jump_Descend_flag; //落下フラグ・・・TRUE=落下する、FLASE=落下しない
    private bool PRotate_flag;      //軸フラグ・・・TRUE=プレイヤー軸、FALSE=ギア軸
    private bool Roll_flag;         //回転落下フラグ・・・TRUE=転がり落ちる、FALSE=転がらない
    private bool AutoMoveG_flag;    //自動ギア移動フラグ・・・TRUE=移動可能、FALSE=移動不可能
    private bool Climb_flag;        //登るフラグ・・・TRUE=登れる、FALSE=登れない
    private bool Fixed_flag;        //固定フラグ・・・TRUE=固定化(入力あるまで)、FALSE=自由
    public bool Rotate_flag;       //回転フラグ・・・TRUE=回転してる、FAlSE=回転していない
    private bool TerrainHit_flag;   //地面接触フラグ・・・TRUE=地面と接触している、FALSE=地面と接触していない
    public bool Jump_flag;         //ジャンプフラグ・・・TRUE=ジャンプ許可あり、FALSE=ジャンプ許可なし
    private bool ClimbChanceflag;   //登るチャレンジフラグ・・・TRUE=チャンスがある、FALSE=チャンスがない
    private bool Death_flag;        //死亡フラグ・・・TRUE=死亡、FALSE=生存
    private bool Time_flag;         //時間停止フラグ・・・TRUE=時間停止中、FALSE=停止していない
    private bool Pause_flag;        //ポーズフラグ・・・TRUE=velocity更新必要、FALSE=velocity更新済み
    private bool CharFade_flag;     //フェードフラグ・・・
    private bool Engagement_flag;   //噛み合わせフラグ・・・TRUE=噛み合わせできる、FALSE=噛み合わせできない
    public bool MovePattern;       //移動方法フラグ・・・TRUE=ギア移動、FALSE=足場移動
    public bool DoubleCol_flag;    //複数接触フラグ・・・TRUE=二つ以上と接触している、FALSE=二つ以上と接触していない
    public bool Fall_flag;         //落下フラグ・・・TRUE=落下する、FALSE=落下しない
    public bool Move_flag;         //移動・回転フラグ・・・TRUE=行動可能、FALSE=行動不可能

    //当たったオブジェクト格納用
    [Header("格納用～デバックのため可視化中～")]
    public GameObject[] Col_Object = new GameObject[2];
    //収集物の格納用
    private GameObject[] Collection_Obj = new GameObject[3];   //収集物(本体)
    Rigidbody rb;         //プレイヤーの回転・当たり判定用Rigidbody2D
    Vector3 velocity = new Vector3(0, 0, 0);     //加えられた力の格納用

    [Header("落下し始めるギアとの距離")]
    [Range(-2, 2)]
    public float Fall_Distance;

    [Header("ギアの角度制限")]
    [Tooltip("指定した角度以上にギア上のプレイヤーが移動した場合、固定されず落ちていきます。(-値でも対応済み)")]
    [Range(10, 90)]
    public int GearAngle_Limit;
    [Header("足場の角度制限")]
    [Tooltip("指定した角度以上の足場に接触した場合、固定されず落ちていきます。(-値でも対応済み)")]
    [Range(10, 90)]
    public int ScaffoldAngle_Limit;
    [Header("歯付き足場の角度制限")]
    [Tooltip("指定した角度以上の歯付き足場に接触した場合、固定されず落ちていきます。(-値でも対応済み)")]
    [Range(10, 90)]
    public int JaggedScaffoldAngle_Limit;

    //登れる（登って落ちる）ギアの角度
    public float GearClimbAngleLimit = 180;
    //登れる（登って落ちる）足場の角度
    public float ScaffoldClimbAngleLimit = 0;
    //登れる（登っと落ちる）歯付き足場
    public float JaggedScaffoldClimbAngleLimit = 180;
    private float ClimbTime = 0;
    //落ちるまで時間
    public float GearClimbIntervalTime = 0.3f;
    public float ScaffoldClimbIntervalTime = 0.3f;
    public float JaggedScaffoldClimbIntervalTime = 0.3f;
    private float ClimbIntervalTime = 0;

    [HideInInspector]
    public int CollectionNum = 0;

    public const int jumpwaitframe = 8;
    private int jumpaitcount = 0;

    private bool Checkflg;
    private int GearTeeth = 12;

    private GameObject PauseObj;//追加

    //ギア移動時の回転速度に歯の枚数を使う(のちに使用する)
    //GearVariable gearvariable;
    //列挙系
    enum RotateDirect
    {
        NONE,
        LEFT,
        RIGHT
    }
    RotateDirect rotateDirect;//プレイヤーの回転状態

    enum Jump_State
    {
        NONE,       //なし
        RISE,       //上昇状態
        DESCEND,    //下降状態
    }
    Jump_State jump_State;//ジャンプ状態


    public GameObject EffectEngage01Obj;
    public GameObject EffectJumpObj;
    Volume postProcess;

    public Image blackcharabigImage;
    bool blackcharabigFadeInFlg = false;

    // Start is called before the first frame update
    void Start()
    {
        //フラグ初期化
        Jump_flag = false;
        GearMoveflag = true;
        Fall_flag = true;//初期状態が浮いているためTRUE
        DoubleCol_flag = false;
        TerrainHit_flag = false;
        PRotate_flag = false;
        ClimbChanceflag = false;
        Checkflg = true;
        //収集物オブジェクト取得
        Collection_Obj[0] = GameObject.Find("Collection_Object");
        Collection_Obj[1] = GameObject.Find("Collection_Object2");
        Collection_Obj[2] = GameObject.Find("Collection_Object3");


        GameObject[] collectionEffects = GameObject.FindGameObjectsWithTag("collectionEffect");
        for (int i = 0; i < collectionEffects.Length; i++)
        {
            collectionEffects[i].SetActive(false);
        }
        // Collection_UI[0] = GameObject.Find("SubMissionRawImage");
        // Collection_UI[1] = GameObject.Find("SubMissionRawImage (1)");
        // Collection_UI[2] = GameObject.Find("SubMissionRawImage (2)");
        //foreach (var obj in Collection_UI)
        //    //obj.SetActive(false);
        //    obj.GetComponent<MeshRenderer>().enabled = false;

        GameObject[] CollectionObjList = GameObject.FindGameObjectsWithTag("Collection");
        //Debug.Log(GameObject.FindGameObjectsWithTag("Collection"));
        Collection_Obj = CollectionObjList;
        //追加
        PauseObj = GameObject.Find("PauseGameScene");
        PauseObj.GetComponent<PauseGameSceneScript>().enabled = true;

        GearClimbAngleLimit = GearAngle_Limit > GearClimbAngleLimit ? GearAngle_Limit : GearClimbAngleLimit;
        ScaffoldClimbAngleLimit = ScaffoldAngle_Limit > ScaffoldClimbAngleLimit ? ScaffoldAngle_Limit : ScaffoldClimbAngleLimit;
        JaggedScaffoldClimbAngleLimit = JaggedScaffoldAngle_Limit > JaggedScaffoldClimbAngleLimit ? JaggedScaffoldAngle_Limit : JaggedScaffoldClimbAngleLimit;

        this.gameObject.transform.parent = Player_Center.transform;
        rb = GetComponent<Rigidbody>();                      //Player_BodyのRigidbody2Dを格納
        rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;//移動禁止

        var _o = GameObject.Find("Global Volume (GameOver)");
        if (_o != null)
        {
            postProcess = _o.GetComponent<Volume>();
            ChromaticAberration chromaticAberration;
            postProcess.profile.TryGet<ChromaticAberration>(out chromaticAberration);
            chromaticAberration.intensity.value = 0;
            LensDistortion lensDistortion;
            postProcess.profile.TryGet<LensDistortion>(out lensDistortion);
            lensDistortion.intensity.value = 0;
            //postProcess.gameObject.SetActive(false);
            postProcess.gameObject.GetComponent<Volume>().enabled = false;

            InputScript.Instance.SetGamePadVibrationStop();
        }

        blackcharabigImage = GameObject.Find("blackcharabig").GetComponent<Image>();
        //blackcharabigImage.gameObject.SetActive(false);
        blackcharabigImage.GetComponent<Image>().enabled = false;
        if (WorldDirectorScript.Instance.GetDeath() == true)
        {
            //blackcharabigImage.gameObject.SetActive(true);
            blackcharabigImage.GetComponent<Image>().enabled = true;
            blackcharabigImage.rectTransform.sizeDelta = new Vector2(2000, 2000);
            blackcharabigFadeInFlg = true;
            WorldDirectorScript.Instance.SetDeath(false);
        }
    }

    void FixedUpdate()
    {
        if (blackcharabigFadeInFlg == true)
        {
            if (blackcharabigImage == null)
            {
                blackcharabigImage = GameObject.Find("blackcharabig").GetComponent<Image>();
                //blackcharabigImage.gameObject.SetActive(true);
                blackcharabigImage.GetComponent<Image>().enabled = true;
                blackcharabigImage.rectTransform.sizeDelta = new Vector2(2000, 2000);
            }
            blackcharabigImage.rectTransform.sizeDelta = new Vector2(blackcharabigImage.rectTransform.sizeDelta.x - (2500 / 1.0f) * Time.deltaTime, blackcharabigImage.rectTransform.sizeDelta.y - (2500 / 1.0f) * Time.deltaTime);
            if (blackcharabigImage.rectTransform.sizeDelta.x < 0)
            {
                blackcharabigFadeInFlg = false;
            }
        }

        Time_flag = GameDirectorScript.Instance.time == 0;
        if (Time_flag == true)
        {
            rb.velocity = Vector3.zero;
            InputScript.Instance.SetGamePadVibrationStop();
            rb.useGravity = false;
            Pause_flag = true;
            velocity = rb.velocity;
            Debug.Log("停止処理中");
            return;
        }
        //通常処理
        else
        {
            //ポーズ後の処理
            if (Pause_flag)
            {
                rb.useGravity = true;
                Pause_flag = false;
                rb.velocity = velocity;
            }
            //ゲームオーバー処理
            if (Death_flag)
            {
                //postProcess.gameObject.SetActive(true);
                postProcess.gameObject.GetComponent<Volume>().enabled = true;
                ChromaticAberration chromaticAberration;
                postProcess.profile.TryGet<ChromaticAberration>(out chromaticAberration);
                if (chromaticAberration.intensity.value < 1.0f)
                {
                    chromaticAberration.intensity.value = chromaticAberration.intensity.value + (1.0f / 0.25f) * Time.deltaTime;
                    LensDistortion lensDistortion;
                    postProcess.profile.TryGet<LensDistortion>(out lensDistortion);
                    lensDistortion.intensity.value = lensDistortion.intensity.value + (-0.25f / 0.25f) * Time.deltaTime;

                    blackcharabigImage.rectTransform.sizeDelta = new Vector2(blackcharabigImage.rectTransform.sizeDelta.x + (2500 / 0.25f) * Time.deltaTime, blackcharabigImage.rectTransform.sizeDelta.y + (2500 / 0.25f) * Time.deltaTime);
                }

            }
        }

        if (this.gameObject.transform.position.y < -18.0f)//追加(修正)
        {
            if (!Death_flag)
            {
                //InputScript.Instance.SetGamePadVibration(1.0f, 0.1f, 1);
                SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Death);
                VibrationDirectorScript.Instance.PlayVibration(1.0f, 0.1f, 1);

                //postProcess.gameObject.SetActive(true);
                postProcess.gameObject.GetComponent<Volume>().enabled = true;
                //blackcharabigImage.gameObject.SetActive(true);
                blackcharabigImage.GetComponent<Image>().enabled = true;
                blackcharabigImage.rectTransform.sizeDelta = new Vector2(100, 100);
                Death_flag = true;
                WorldDirectorScript.Instance.SetDeath(true);
            }
            Invoke("Death", 1.0f);
        }

        //if (this.gameObject.transform.position.y < -15.0f)
        //    SceneManager.LoadScene(SceneManager.GetActiveScene().name);

        //格納しているオブジェクトを整列させる
        if (Col_Object[0] == null && Col_Object[1] != null)
        {
            Col_Object[0] = Col_Object[1];
            Col_Object[1] = null;
        }
        //落下更新処理
        FallUpdate();
        //軸変更処理
        ShaftUpdate();
        //ジャンプ処理
        JumpUpdate();
        //自動処理
        //AutoMoveUpdate();
        //移動・回転処理
        MoveUpdate();
        //収集物更新処理
        //CollectionUpdate();
    }

    /// <summary>
    /// 落下処理
    /// </summary>
    void FallUpdate()
    {
        //何かに当たっているか調べる
        int count = 0;
        foreach (var obj in Col_Object)
        {
            if (obj != null)
                count++;
        }

        //何とも当たってない場合(通常)
        if (count == 0 && jump_State == Jump_State.NONE)
        {
            Roll_flag = false;
            Fall_flag = true;
            rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
            return;
        }

        //ジャンプ中の場合
        if (Jump_flag)
        {
            //上昇処理時
            if (jump_State == Jump_State.RISE)
            {
                //Rayで上にオブジェクトを確認した場合
                if (Ray_Confirmation_up() == true)
                {
                    if (Ray_Cofirmation_down())
                    {
                        //下地面又はギアにもあるとき
                        jump_State = Jump_State.NONE;
                        Fall_flag = false;
                        Jump_flag = false;
                    }
                    else
                    {
                        //下降状態に移行
                        jump_State = Jump_State.DESCEND;
                        rb.velocity = Vector3.zero;
                        Fall_flag = true;
                    }
                }
                if (this.gameObject.transform.position.y >= 12.0f)
                {
                    //下降状態に移行
                    jump_State = Jump_State.DESCEND;
                    rb.velocity = Vector3.zero;
                    Fall_flag = true;
                }
                //////追加06/37///////
                foreach (var obj in Col_Object)
                {
                    if (obj != null)
                    {
                        if (obj.tag == "Jagged_Scaffold" || obj.tag == "Scaffold")
                        {
                            if (obj.transform.up.y > 0.0f)
                            {
                                //転げ落ちない角度か調べる
                                float angle = Vector2.Angle(obj.transform.right, Vector2.right);
                                Fall_flag = false;
                                Roll_flag = false;
                                //rb.constraints = RigidbodyConstraints.FreezeAll;
                                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
                                float limit = obj.tag == "Scaffold" ? ScaffoldAngle_Limit : JaggedScaffoldAngle_Limit;
                                if (angle > limit && !DoubleCol_flag)
                                {
                                    //転げ落ちる
                                    rb.velocity = Vector3.zero;
                                    jump_State = Jump_State.NONE;
                                    Jump_Descend_flag = false;
                                    Roll_flag = true;
                                    Fall_flag = false;
                                    TerrainHit_flag = true;
                                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
                                }
                            }
                        }
                    }
                }
            }
        }
        //ジャンプ中ではない場合
        else
        {
            //強制落下状態にする
            Fall_flag = true;
            TerrainHit_flag = false;
            //落ちない条件を調べる
            foreach (var obj in Col_Object)
            {
                if (obj != null)
                {
                    //自動移動時
                    if (AutoMoveG_flag)
                    {
                        Fall_flag = false;
                        Roll_flag = false;
                        TerrainHit_flag = true;
                        return;
                    }
                    else if (obj.tag == "Gear")
                    {
                        //登れる角度を計算して求めることで出来る   
                        bool Position = this.gameObject.transform.position.x - obj.transform.position.x > 0;
                        bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
                        bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
                        bool move = (!Position && LeftInputR) || (Position && LeftInputL);

                        //一定の角度いないなら落ちない
                        var vec = this.gameObject.transform.position - obj.transform.position;
                        float angle = Vector2.Angle(Vector2.up, vec.normalized);
                        move = move && angle < 135 ? true : false;


                        if (DoubleCol_flag || move)
                        {
                            Roll_flag = false;
                            Fall_flag = false;
                            rb.constraints = RigidbodyConstraints.FreezeAll;
                            return;
                        }
                        //一定の角度以内なら落ちない
                        if (angle < 90)
                        {
                            bool flag = true;
                            if (DoubleCol_flag)
                            {//2つのオブジェクトと当たっている時その2つがギアかどうか判別する
                                foreach (var obja in Col_Object)
                                {
                                    if (obja.tag != "Gear" && obja.transform.up.y > 0.0f)
                                        flag = false;
                                }
                            }
                            if (flag)
                            {
                                Roll_flag = angle > GearAngle_Limit;
                                Fall_flag = false;
                                rb.constraints = RigidbodyConstraints.FreezeAll;
                            }
                        }
                    }
                    else if (obj.tag == "Jagged_Scaffold" || obj.tag == "Scaffold")
                    {
                        if (obj.transform.up.y > 0.0f)
                        {
                            //転げ落ちない角度か調べる
                            float angle = Vector2.Angle(obj.transform.right, Vector2.right);
                            Fall_flag = false;
                            Roll_flag = false;
                            rb.constraints = RigidbodyConstraints.FreezeAll;
                            float limit = obj.tag == "Scaffold" ? ScaffoldAngle_Limit : JaggedScaffoldAngle_Limit;
                            float climblimit = obj.tag == "Scaffold" ? ScaffoldClimbAngleLimit : JaggedScaffoldClimbAngleLimit;
                            if (angle < climblimit && angle > limit && ClimbChanceflag)
                            {
                                Climb_flag = true;
                                ClimbIntervalTime = obj.tag == "Scaffold" ? ScaffoldClimbIntervalTime : JaggedScaffoldClimbIntervalTime;
                                return;
                            }

                            if (angle > limit && !DoubleCol_flag)
                            {
                                //転げ落ちる
                                Roll_flag = true;
                                Fall_flag = false;
                                TerrainHit_flag = true;
                                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
                            }
                        }
                    }
                }
            }
        }
    }

    /// <summary>
    /// Ray：上部確認
    /// </summary>
    /// <returns>True=上にオブジェクト有,False=上にオブジェクト無</returns>
    private bool Ray_Confirmation_up()
    {
        bool hit_flag = false;   //Ray接触フラグ・・・TRUE=当たった、FALSE=当たってない
        foreach (var obj in Col_Object)
        {
            //格納されている場合
            if (obj != null)
            {
                float major = 1.7f;
                //上にRayを飛ばす
                Vector3 pos = this.transform.position;  //位置ベクトル
                Ray ray = new Ray(pos, Vector3.up);     //Ray生成
                //Ray可視化(デバック用)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Rayが当たったか確認
                foreach (var hitobj in Physics.RaycastAll(ray.origin, ray.direction, this.transform.lossyScale.y * major))
                {
                    if (hitobj.collider.gameObject != this.gameObject)
                    {
                        if (hitobj.collider.tag == "Gear" || hitobj.collider.tag == "Jagged_Scaffold" || hitobj.collider.tag == "Scaffold" || hitobj.collider.tag == "Wall")
                        {
                            hit_flag = true;
                        }
                    }
                }
                //上(右の方)にRayを飛ばす
                pos.x = this.transform.position.x + this.transform.lossyScale.y * 1.2f;
                ray = new Ray(pos, Vector3.up);
                //Ray可視化(デバック用)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Rayが当たったか確認
                foreach (var hitobj in Physics.RaycastAll(ray.origin, ray.direction, this.transform.lossyScale.y * major))
                {
                    if (hitobj.collider.gameObject != this.gameObject)
                    {
                        if (hitobj.collider.tag == "Gear" || hitobj.collider.tag == "Jagged_Scaffold" || hitobj.collider.tag == "Scaffold" || hitobj.collider.tag == "Wall")
                        {
                            hit_flag = true;
                        }
                    }
                }
                //上(左の方)にRayを飛ばす
                pos.x = this.transform.position.x - this.transform.lossyScale.x * 1.2f;
                ray = new Ray(pos, Vector3.up);
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                foreach (var hitobj in Physics.RaycastAll(ray.origin, ray.direction, this.transform.lossyScale.y * major))
                {
                    if (this.gameObject != hitobj.collider.gameObject)
                    {
                        if (hitobj.collider.tag == "Gear" || hitobj.collider.tag == "Jagged_Scaffold" || hitobj.collider.tag == "Scaffold" || hitobj.collider.tag == "Wall")
                        {
                            hit_flag = true;
                        }
                    }
                }
            }
        }
        return hit_flag;
    }

    /// <summary>
    /// Ray：下部確認
    /// </summary>
    /// <returns>True=下にオブジェクト有,False=下にオブジェクト無</returns>
    private bool Ray_Cofirmation_down()
    {
        bool hit_flag = false;   //Ray接触フラグ・・・TRUE=当たった、FALSE=当たってない
        foreach (var obj in Col_Object)
        {
            //格納されている場合
            if (obj != null)
            {
                float major = 1.7f;
                //下にRayを飛ばす
                Vector3 pos = this.transform.position;  //位置ベクトル
                Ray ray = new Ray(pos, Vector3.down);     //Ray生成
                //Ray可視化(デバック用)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Rayが当たったか確認
                foreach (var hitobj in Physics.RaycastAll(ray.origin, ray.direction, this.transform.lossyScale.y * major))
                {
                    if (hitobj.collider.gameObject != this.gameObject)
                    {
                        if (hitobj.collider.tag == "Gear" || hitobj.collider.tag == "Jagged_Scaffold" || hitobj.collider.tag == "Scaffold")
                        {
                            hit_flag = true;
                            break;
                        }
                    }
                }
                //下(右の方)にRayを飛ばす
                pos.x = this.transform.position.x + this.transform.lossyScale.y * 1.2f;
                ray = new Ray(pos, Vector3.down);
                //Ray可視化(デバック用)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Rayが当たったか確認
                foreach (var hitobj in Physics.RaycastAll(ray.origin, ray.direction, this.transform.lossyScale.y * major))
                {
                    if (hitobj.collider.gameObject != this.gameObject)
                    {
                        if (hitobj.collider.tag == "Gear" || hitobj.collider.tag == "Jagged_Scaffold" || hitobj.collider.tag == "Scaffold")
                        {
                            hit_flag = true;
                            break;
                        }
                    }
                }
                //下(左の方)にRayを飛ばす
                pos.x = this.transform.position.x - this.transform.lossyScale.x * 1.2f;
                ray = new Ray(pos, Vector3.down);
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                foreach (var hitobj in Physics.RaycastAll(ray.origin, ray.direction, this.transform.lossyScale.y * major))
                {
                    if (this.gameObject != hitobj.collider.gameObject)
                    {
                        if (hitobj.collider.tag == "Gear" || hitobj.collider.tag == "Jagged_Scaffold" || hitobj.collider.tag == "Scaffold")
                        {
                            hit_flag = true;
                            break;
                        }
                    }
                }
            }
        }
        return hit_flag;
    }

    /// <summary>
    /// ジャンプ処理
    /// </summary>
    void JumpUpdate()
    {
        if (Jump_flag)
        {
            if (jump_State == Jump_State.RISE)
            {
                Jump_Rise();
            }
            else if (jump_State == Jump_State.DESCEND)
            {
                Jump_Descend();
            }
        }
    }

    /// <summary>
    /// ジャンプ：上昇処理
    /// </summary>
    private void Jump_Rise()
    {
        if (!Jump_Descend_flag)
        {
            //限界点以下小ジャンプ限界点以上
            if (transform.position.y < Jump_Initial_Position.y + Jump_Limit && transform.position.y > (Jump_Initial_Position.y + Jump_Limit) / 2)
            {
                //入力無くなった場合
                if (!InputScript.Instance.GetGamePadButtonPress(GamePadKey.A) && !InputScript.Instance.GetKeyboardPress(KeyCode.Space))
                {
                    jump_State = Jump_State.DESCEND;
                    Fall_flag = true;
                }
            }
            //限界点超過
            else if (transform.position.y > Jump_Initial_Position.y + Jump_Limit)
            {
                //下降処理に移行する
                jump_State = Jump_State.DESCEND;
                Fall_flag = true;
            }
            //小ジャンプ限界点以下
            else if (transform.position.y < (Jump_Initial_Position.y + Jump_Limit) / 2)
            {
                //入力無くなった場合
                if (!InputScript.Instance.GetGamePadButtonPress(GamePadKey.A) && !InputScript.Instance.GetKeyboardPress(KeyCode.Space))
                {
                    jump_State = Jump_State.DESCEND;
                    Jump_Descend_flag = true;
                }
            }
            //上昇処理
            rb.velocity = new Vector3(0, Jump_Power * 2, 0);
        }
        else
        {
            //小ジャンプ限界点以上
            if (transform.position.y >= (Jump_Initial_Position.y + Jump_Limit) / 2)
            {
                jump_State = Jump_State.DESCEND;
                Fall_flag = true;
            }
        }
    }

    /// <summary>
    /// ジャンプ：下降処理
    /// </summary>
    private void Jump_Descend()
    {
        if (Ray_Confirmation_up())
            rb.velocity = Vector3.zero;
        Fall_flag = true;
        rb.mass = 20;
        rb.drag = 0.01f;
        if (rb.velocity.y > 0)
        {
            rb.velocity = new Vector3(0, rb.velocity.y * 0.9f, 0);
        }
        else if (rb.velocity.y <= 0)
        {
            //   rb.velocity = new Vector3(0, -Jump_Power * 0.9f, 0);
        }
    }

    /// <summary>
    /// 移動処理
    /// </summary>
    void MoveUpdate()
    {
        bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
        if (Fixed_flag && LeftInputR || LeftInputL)
            Fixed_flag = false;
        //オプション・リザルト画面ではない
        //if () {
        //落下・ジャンプしている時
        if (Fall_flag || Jump_flag)
        {
            //空中時移動
            Input_Air();
        }
        //落ちていない
        else
        {
            //ジャンプ可能
            if (!Jump_flag)
            {
                //ギア接触時
                if (MovePattern)
                {
                    if (Roll_flag)
                        Roll_Gear();
                    else if (!Roll_flag && !Fixed_flag)
                        Move_Gear();
                }
                //足場接触時
                else
                {
                    if (Roll_flag)
                        Roll_Scaffold();
                    else if (Climb_flag)
                        Climb_Scaffold();
                    else if (!Roll_flag && !Climb_flag && !Fixed_flag)
                        Move_Scaffold();
                }
                //ジャンプ
                bool JumpInput = InputScript.Instance.GetGamePadButtonTrigger(GamePadKey.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.Space);
                if (JumpInput && !Roll_flag && jump_State == Jump_State.NONE)
                {
                    Checkflg = false;
                    rb.useGravity = true;
                    rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;//回転のみ制限
                    Jump_flag = true;//ジャンプ中
                    TerrainHit_flag = false;
                    GearMoveflag = false;
                    jump_State = Jump_State.RISE;
                    Jump_Initial_Position = new Vector2(transform.position.x, transform.position.y);

                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Jump);
                    VibrationDirectorScript.Instance.PlayVibration(0.0f, 0.1f, 0.5f);
                    Instantiate(EffectJumpObj, this.transform.position, Quaternion.identity);
                }
            }
        }
    }

    /// <summary>
    /// 入力処理：ギア上移動・回転
    /// </summary>
    private void Move_Gear()
    {
        //DoubleCol_flagの場合、状況把握
        if (DoubleCol_flag)
        {
            Vector3 R_Object = this.transform.position.x > Col_Object[0].transform.position.x ? Col_Object[1].transform.position : Col_Object[0].transform.position;
            Vector3 L_Object = this.transform.position.x < Col_Object[0].transform.position.x ? Col_Object[1].transform.position : Col_Object[0].transform.position;
            //中心点がPlayerより右にある場合
            if (Player_Center.transform.position.x > this.gameObject.transform.position.x)
            {
                if (rotateDirect == RotateDirect.LEFT)
                {
                    Vector3 PlayerPos = this.transform.position;
                    Player_Center.transform.position = L_Object;
                    this.transform.position = PlayerPos;
                }
                else if (rotateDirect == RotateDirect.NONE)
                    rotateDirect = RotateDirect.LEFT;
            }
            //中心点がPlayerより左にある場合
            else if (Player_Center.transform.position.x < this.gameObject.transform.position.x)
            {
                if (rotateDirect == RotateDirect.RIGHT)
                {
                    Vector3 PlayerPos = this.transform.position;
                    Player_Center.transform.position = R_Object;
                    this.transform.position = PlayerPos;
                }
                else if (rotateDirect == RotateDirect.NONE)
                    rotateDirect = RotateDirect.RIGHT;
            }
        }

        bool RightInputR = InputScript.Instance.GetGamePadRightStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow);
        bool RightInputL = InputScript.Instance.GetGamePadRightStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow);
        bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
        //Player軸回転
        if (PRotate_flag && (InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow)))
        {
            //ギアを回せるか調べる
            bool Rota_flag = true;  //回る方向・・・True=右回転、False=左回転
            //右回転
            if (RightInputR && !AutoMoveG_flag)
                Rota_flag = true;
            //左回転
            else if (RightInputL && !AutoMoveG_flag)
                Rota_flag = false;
            //回せるか確認する
            foreach (var obj in Col_Object)
            {
                if (obj != null && obj.tag == "Gear")
                {
                    //obj.GetComponent<GearRote>().CheckMoveRote(Rota_flag, 6, G_mo_Speed * (GearTeeth / 6));
                    obj.GetComponent<GearRote>().CheckMoveRote(Rota_flag, 6, G_mo_Speed);
                    break;
                }
            }
            var test = GetComponent<GearVariable>();
            if (!test.MoveFlg)
            {
                float RotaSpeed = G_mo_Speed;
                //右回転
                if (RightInputR && !AutoMoveG_flag)
                {
                    Player_Center.transform.Rotate(0, 0, -RotaSpeed);
                    Rotate_flag = true;
                }
                //左回転
                else if (RightInputL && !AutoMoveG_flag)
                {
                    Player_Center.transform.Rotate(0, 0, RotaSpeed);
                    Rotate_flag = true;
                }
                //////////////追加////////////////////////
                //二つ以上のギアを回転中
                if (test.Search_GearNum() >= 2)
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage01);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                    Debug.Log("複数ギアのみ");
                }
                //大きなギアだけを回転中
                if (test.Search_BigGear())
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage03);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                    Debug.Log("全体ギアのみ");
                }
                //通常ギアだけを回転中
                else
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage02);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                    Debug.Log("通常ギアのみ");
                }
                rotateDirect = RotateDirect.NONE;
            }
            else
            {
                if (RightInputR)
                    rotateDirect = RotateDirect.RIGHT;
                else if (RightInputL)
                    rotateDirect = RotateDirect.LEFT;

                //二つ以上のギアを回転中
                if (test.Search_GearNum() >= 2)
                {

                }
                //大きなギアだけを回転中
                if (test.Search_BigGear())
                {

                }
                //通常ギアだけを回転中
                else
                {

                }

                Rotate_flag = false;
                rb.useGravity = true;
                rb.constraints = RigidbodyConstraints.FreezeAll;
            }
            //ギアの回転処理
            test.Rote();
        }
        //ギア軸移動
        else if (GearMoveflag)
        {
            float MoveSpeed = G_mo_Speed;
            float RotaSpeed = G_mo_Speed * (GearTeeth / 6);
            //移動
            if (LeftInputR && !AutoMoveG_flag)//右
            {
                if (CheckGearMove(-G_mo_Speed))
                {
                    this.transform.Rotate(0, 0, -RotaSpeed);
                    Player_Center.transform.Rotate(0, 0, -MoveSpeed);
                    rotateDirect = RotateDirect.RIGHT;

                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);

                }
            }
            else if (LeftInputL && !AutoMoveG_flag)//左
            {
                if (CheckGearMove(G_mo_Speed))
                {
                    this.transform.Rotate(0, 0, RotaSpeed);
                    Player_Center.transform.Rotate(0, 0, MoveSpeed);
                    rotateDirect = RotateDirect.LEFT;

                    //追加
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                }
            }
            //自動
            else if (AutoMoveG_flag && rotateDirect == RotateDirect.RIGHT)//右
            {
                this.transform.Rotate(0, 0, -RotaSpeed);
                Player_Center.transform.Rotate(0, 0, -MoveSpeed);
            }
            else if (AutoMoveG_flag && rotateDirect == RotateDirect.LEFT)//左
            {
                this.transform.Rotate(0, 0, RotaSpeed);
                Player_Center.transform.Rotate(0, 0, MoveSpeed);
            }
            //////////////////追加・変更//////////////////////////
            //入力なし・自動なし
            else if (!AutoMoveG_flag && !LeftInputR || !LeftInputL || !RightInputL || RightInputR)
            {
                rotateDirect = RotateDirect.NONE;
                rb.constraints = RigidbodyConstraints.FreezeAll;
                InputScript.Instance.SetGamePadVibrationStop();
                Debug.Log("振動停止");
            }
            ///////////////////////////////////////////////////////
        }
    }

    /// <summary>
    /// 入力処理：足場上移動
    /// </summary>
    private void Move_Scaffold()
    {
        if (DoubleCol_flag)
        {
            bool flg = true;
            flg = Col_Object[0] != null && Col_Object[0].transform.up.y < 0.0f ? flg : false;
            flg = Col_Object[1] != null && Col_Object[1].transform.up.y < 0.0f ? flg : false;
            if (flg)
                return;
        }

        ///地面移動
        if (!Fall_flag)//落下していない
        {
            bool RightInputR = InputScript.Instance.GetGamePadRightStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow);
            bool RightInputL = InputScript.Instance.GetGamePadRightStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow);
            bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
            bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
            ///足場：傾きorギザギザ足場：傾き
            float rad = 0;//角度→ラジアン
            float objangle = 0;
            Vector3 vec = Vector3.zero;//移動ベクトル　※歯付き足場(斜め時)に使用する
            bool oneobj = Col_Object[0] != null;
            //移動方向計算
            //2つのオブジェクトとぶつかっている時どちらで判定をとるか
            if (Col_Object[0] != null && Col_Object[1] != null)
            {//2つの足場とぶつかっている時
                if (LeftInputL)
                {
                    oneobj = Col_Object[0].transform.position.x < Col_Object[1].transform.position.x;
                }
                else
                    oneobj = Col_Object[0].transform.position.x > Col_Object[1].transform.position.x;
                Vector3 pos = this.transform.position;
                //当たった足場のどちらかが上にある場合
                Ray ray = new Ray(pos, Vector3.up);
                Debug.DrawRay(ray.origin, ray.direction * this.transform.localScale.y * 2, Color.red, 0.1f);
                foreach (var hit in Physics.RaycastAll(ray.origin, ray.direction, this.transform.localScale.y * 2))
                {
                    oneobj = hit.collider.gameObject == Col_Object[0] ? false : oneobj;
                    oneobj = hit.collider.gameObject == Col_Object[1] ? true : oneobj;
                }
                pos.x = this.transform.position.x + this.transform.localScale.x;
                ray = new Ray(pos, Vector3.up);
                Debug.DrawRay(ray.origin, ray.direction * this.transform.localScale.y * 2, Color.red, 0.1f);
                foreach (var hit in Physics.RaycastAll(ray.origin, ray.direction, this.transform.localScale.y * 2))
                {
                    oneobj = hit.collider.gameObject == Col_Object[0] ? false : oneobj;
                    oneobj = hit.collider.gameObject == Col_Object[1] ? true : oneobj;
                }
            }

            bool Scaffoldflag = false;
            if (oneobj)
            {//スタックの1つ目だけの時
             //1つ目で判定を取る
                objangle = Col_Object[0] != null ? Col_Object[0].transform.eulerAngles.z : 0;
                float angle = objangle > 90 && objangle <= 180 ? 180 - objangle : objangle;
                angle = angle > 180 && angle <= 270 ? 270 + (270 - angle) : angle;
                rad = angle * Mathf.Deg2Rad;
                Scaffoldflag = Col_Object[0] != null && Col_Object[0].tag == "Scaffold";
            }
            else
            {//スタックの2つ目だけの時
             //2つ目で判定を取る
                objangle = Col_Object[1] != null ? Col_Object[1].transform.eulerAngles.z : 0;
                float angle = objangle > 90 && objangle <= 180 ? 180 - objangle : objangle;
                angle = angle > 180 && angle <= 270 ? 270 + (270 - angle) : angle;
                rad = angle * Mathf.Deg2Rad;
                Scaffoldflag = Col_Object[1] != null && Col_Object[1].tag == "Scaffold";
            }
            Vector3 direction = new Vector3(Mathf.Cos(rad), Mathf.Sin(rad), 0);   //方向設定
            direction.y = objangle > 90 && objangle < 270 ? -direction.y : direction.y;
            vec = direction * mo_Speed;                          //移動ベクトル計算
            objangle = 180 < objangle ? objangle - 180 : objangle;
            float limit = Scaffoldflag ? ScaffoldAngle_Limit : JaggedScaffoldAngle_Limit;
            //見直し
            bool moveflg = true;// (objangle < limit || objangle > 180 - limit);
            //右移動
            if (LeftInputR && moveflg)
            {
                if (CheckMove(vec, raymaneger))
                {
                    rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;
                    vec = direction * mo_Speed * 2.5f;
                    rb.velocity = vec;
                    transform.Rotate(0, 0, -ro_Speed * 3.0f);

                    //追加
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                }
                rotateDirect = RotateDirect.RIGHT;
            }
            //左移動
            else if (LeftInputL && moveflg)
            {
                if (CheckMove(-vec, raymaneger))
                {
                    rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;
                    vec = direction * mo_Speed * 2.5f;
                    rb.velocity = vec * -1;
                    transform.Rotate(0, 0, ro_Speed * 3.0f);

                    //追加
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                }
                rotateDirect = RotateDirect.LEFT;
            }
            else if (!LeftInputR && !LeftInputL)
            //入力なし
            {
                if (!Jump_flag)
                {
                    //ギザギザ足場の場合、滑り落ちないようにする
                    rb.useGravity = true;
                    ////06/25追加・変更
                    if (Engagement_flag)
                    {//噛み合わせのため
                        rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
                        Engagement_flag = false;
                    }
                    else
                    {
                        rb.constraints = RigidbodyConstraints.FreezeAll;
                    }
                }
                //追加
                InputScript.Instance.SetGamePadVibrationStop();
            }
            if (RightInputR || RightInputL)
                rotateDirect = RotateDirect.NONE;
        }
    }

    /// <summary>
    /// 入力処理：空中移動
    /// </summary>
    private void Input_Air()
    {
        rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
        rb.mass = 20;
        rb.drag = 0.01f;
        if (rb.velocity.y > 0)
        {
            rb.velocity = new Vector3(rb.velocity.x, rb.velocity.y * 0.9f, 0);
        }
        else if (rb.velocity.y <= 0)
        {
            rb.velocity = new Vector3(rb.velocity.x, -Jump_Power * 1.5f, 0);
        }

        bool right_flag = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool left_flag = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
        float move_x = 0; //X方向移動力
                          //右移動
        if (right_flag)
        {
            if (CheckMove(Vector2.right, fallmaneger))
            {
                float Rotate = rotateDirect == RotateDirect.LEFT ? Jump_Rota * 0.5f : Jump_Rota;//追加修正
                transform.Rotate(0, 0, -Rotate);
                move_x = rotateDirect == RotateDirect.LEFT ? Jump_Move * 0.5f : Jump_Move;//追加修正
            }
        }
        //左移動
        else if (left_flag)
        {
            if (CheckMove(Vector2.left, fallmaneger))
            {
                float Rotate = rotateDirect == RotateDirect.RIGHT ? Jump_Rota * 0.5f : Jump_Rota;//追加修正
                transform.Rotate(0, 0, Rotate);
                move_x = rotateDirect == RotateDirect.RIGHT ? -Jump_Move * 0.5f : -Jump_Move;//追加修正
            }
        }
        //移動
        rb.velocity = new Vector2(move_x, rb.velocity.y);

    }

    /// <summary>
    /// 転がり処理：ギア
    /// </summary>
    private void Roll_Gear()
    {
        var vec = this.gameObject.transform.position - Col_Object[0].transform.position;
        float angle = Vector2.Angle(Vector2.up, vec.normalized);
        if (angle < 90)
        {
            Fall_flag = false;
            bool LeftStick_R = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
            bool LeftStick_L = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
            bool Roll_direction = false;    //転がる方向・・・TRUE=右転がり、FALSE=左転がり
            float MoveSpeed = G_mo_Speed * (12 / GearTeeth);
            float RotaSpeed = G_mo_Speed * (12 / GearTeeth);
            Roll_direction = Col_Object[0].transform.position.x < this.transform.position.x;

            //転がり落ちる処理
            if (Roll_direction)//みぎころ
            {
                if (!LeftStick_L && !LeftStick_R) //入力なし
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, -RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, -MoveSpeed);
                        rotateDirect = RotateDirect.RIGHT;
                    }
                }
                else if (LeftStick_R)//右入力
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, -RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, -MoveSpeed);
                        rotateDirect = RotateDirect.RIGHT;
                    }
                }
            }
            else//ひだりころ
            {
                if (!LeftStick_L && !LeftStick_R) //入力なし
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, MoveSpeed);
                        rotateDirect = RotateDirect.LEFT;
                    }
                }
                else if (LeftStick_L)//左入力
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, MoveSpeed);
                        rotateDirect = RotateDirect.LEFT;
                    }
                }
            }
        }
        else
        {
            rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY; rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            Roll_flag = false;
            Fall_flag = true;
        }
    }

    /// <summary>
    /// 転がり処理：足場
    /// </summary>
    private void Roll_Scaffold()
    {
        //足場に接している場合
        if (TerrainHit_flag)
        {
            //坂を転げ落ちる
            //移動方向計算
            float objangle = 0;
            float rad = 0;
            //2つのオブジェクトとぶつかっている時どちらで判定をとるか
            bool oneobj = Col_Object[0] != null && Tag_Confirmation(Col_Object[0], "Jagged_Scaffold", "Scaffold");
            bool Sca_Double = DoubleCol_flag && Tag_Confirmation(Col_Object[0], "Jagged_Scaffold", "Scaffold") && Tag_Confirmation(Col_Object[1], "Jagged_Scaffold", "Scaffold");
            if (Sca_Double)
            {//2つの足場とぶつかっている時
                oneobj = Col_Object[0].transform.position.x > Col_Object[1].transform.position.x;
            }

            if (oneobj && Col_Object[0] != null)
            {//スタックの1つ目だけの時
             //1つ目で判定を取る
                objangle = Col_Object[0].transform.eulerAngles.z;
            }
            else if (Col_Object[1] != null)
            {//スタックの2つ目だけの時
             //2つ目で判定を取る
                objangle = Col_Object[1].transform.eulerAngles.z;
            }

            rad = objangle * Mathf.Deg2Rad;
            Vector3 direction = new Vector3(Mathf.Cos(rad), Mathf.Sin(rad), 0);   //方向設定
            direction = objangle > 180 ? -direction : direction;
            Vector2 vec = direction * mo_Speed * 2.5f;                          //移動ベクトル計算
            rb.velocity = -vec;
            float move = -vec.x < 0 ? ro_Speed : -ro_Speed;
            transform.Rotate(0, 0, move * 2.5f);
        }
    }

    /// <summary>
    /// 登り更新処理：足場
    /// </summary>
    private void Climb_Scaffold()
    {
        //限界時間
        //if (ClimbTime > ClimbIntervalTime)
        bool LeftStickR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool LeftStickL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
        if (ClimbTime > 0.2f || (!LeftStickR && !LeftStickL))
        {
            Climb_flag = false;
            Roll_flag = true;
            ClimbTime = 0;
            ClimbChanceflag = false;
            return;
        }
        ClimbTime += Time.deltaTime;
        Move_Scaffold();
    }

    /// <summary>
    /// レイを飛ばして移動できるか調べる
    /// </summary>
    /// <param name="vec">レイを飛ばす方向</param>
    /// <returns>TRUE=移動できる　FALSE=移動できない</returns>
    private bool CheckMove(Vector2 vec, float maneger)
    {
        Vector3 vertical = new Vector3(vec.normalized.y, -vec.normalized.x, 0);

        //下からレイを飛ばす
        var pos = this.transform.position;
        pos = pos + vertical.normalized * -(this.transform.lossyScale.y / 1.5f);
        float aspeed = mo_Speed * maneger;
        Ray ray = new Ray(pos, vec.normalized);
        RaycastHit[] hitray = Physics.RaycastAll(ray.origin, ray.direction, aspeed);
        Debug.DrawRay(ray.origin, ray.direction * aspeed, Color.red, 1.1f);
        foreach (RaycastHit hit in hitray)
        {
            if (hit.collider.tag == "Scaffold" || hit.collider.tag == "Jagged_Scaffold")
            {
                if (hit.transform.up.y < 0.0f)
                {
                    //足場が下を向いていればfalseを返す
                    Move_flag = false;
                    return false;
                }
            }
            else if (hit.collider.tag == "Wall")
            {
                Move_flag = false;
                return false;
            }
        }
        //中心からレイを飛ばす
        pos = this.transform.position;
        ray = new Ray(pos, vec);
        hitray = Physics.RaycastAll(ray.origin, ray.direction, aspeed);
        Debug.DrawRay(ray.origin, ray.direction * aspeed, Color.red, 1.1f);
        foreach (RaycastHit hit in hitray)
        {
            if (hit.collider.tag == "Scaffold" || hit.collider.tag == "Jagged_Scaffold")
            {
                if (hit.transform.up.y < 0.0f)
                {
                    //足場が下を向いていればfalseを返す
                    Move_flag = false;
                    return false;
                }
            }
            else if (hit.collider.tag == "Wall")
            {
                Move_flag = false;
                return false;
            }
        }
        //上からレイを飛ばす
        pos = pos + vertical * (this.transform.lossyScale.y / 1.5f); //thispos + new Vector3(-vec1.y, vec1.x);
        ray = new Ray(pos, vec);
        hitray = Physics.RaycastAll(ray.origin, ray.direction, aspeed);
        Debug.DrawRay(ray.origin, ray.direction * aspeed, Color.red, 1.1f);
        foreach (RaycastHit hit in hitray)
        {
            if (hit.collider.tag == "Scaffold" || hit.collider.tag == "Jagged_Scaffold")
            {
                if (hit.transform.up.y < 0.0f)
                {
                    //足場が下を向いていればfalseを返す
                    Move_flag = false;
                    return false;
                }
            }
            else if (hit.collider.tag == "Wall")
            {
                Move_flag = false;
                return false;
            }
        }
        Move_flag = true;
        return true;
    }


    bool CheckGearMove(float speed)
    {
        //ギア軸移動時に移動方向に移動できるか調べる
        //ギア軸（Player_Center）とPlayerオブジェクトの垂直で調べる
        //どちら周り
        float right = speed > 0 ? 1 : -1;
        //ギア軸からのベクトルを求める
        Vector2 vec1 = Player_Center.transform.position - this.transform.position;
        //垂直ベクトル
        Vector2 vec2 = new Vector2(vec1.y * right, vec1.x * -right);
        float num = Mathf.Abs(speed) * gearmovemaneger;
        Ray ray = new Ray(this.transform.position, vec2);
        RaycastHit[] rayhit = Physics.RaycastAll(ray.origin, ray.direction, num);

        Debug.DrawRay(ray.origin, ray.direction * num, Color.red, 1.0f);
        foreach (RaycastHit hit in rayhit)
        {  //レイが当たった角度
            if (hit.collider.gameObject.tag == "Scaffold" || hit.collider.gameObject.tag == "Jagged_Scaffold")
            {//足場
                //0度ならTRUEをかえす
                if (hit.transform.up.y < 0.0f)
                {
                    Move_flag = false;
                    return false;
                }
            }
            else if (hit.collider.tag == "Wall")
            {
                Move_flag = false;
                return false;
            }
        }

        ray = new Ray(new Vector3(this.transform.position.x, this.transform.position.y + this.transform.localScale.y / 1.0f, this.transform.position.z), vec2);
        rayhit = Physics.RaycastAll(ray.origin, ray.direction, num);

        Debug.DrawRay(ray.origin, ray.direction * num, Color.green, 1.0f);
        foreach (RaycastHit hit in rayhit)
        {  //レイが当たった角度
            var hitrota = Quaternion.FromToRotation(Vector2.up, hit.normal);
            if (hit.collider.gameObject.tag == "Scaffold" || hit.collider.gameObject.tag == "Jagged_Scaffold")
            {//足場
                //0度ならTRUEをかえす
                if (hit.transform.up.y < 0.0f)
                {
                    Move_flag = false;
                    return false;
                }
            }
            else if (hit.collider.tag == "Wall")
            {
                Move_flag = false;
                return false;
            }
        }
        Move_flag = true;
        return true;
    }

    /// <summary>
    /// 収集物更新処理
    /// </summary>
    //void CollectionUpdate()
    //{
    //    int Collectio_num = 0;
    //    foreach (var obj in Collection_Obj)
    //    {
    //        //消滅していた場合
    //        if (obj == null)
    //        {
    //            Collectio_num++;
    //        }
    //    }
    //    //収集物を一つでも獲得している場合
    //    //if (Collectio_num > 0)
    //    //{
    //    //    for (int i = 0; i < Collectio_num; i++)
    //    //    {
    //    //        if (Collection_UI[i].activeSelf == false)
    //    //        {
    //    //            Collection_UI[i].SetActive(true);
    //    //        }
    //    //    }
    //    //}
    //}

    /// <summary>
    /// 当たり判定：当たった時
    /// </summary>
    /// <param name="collision">当たったオブジェクト</param>
    void OnCollisionEnter(Collision collision)
    {
        switch (collision.gameObject.tag)
        {
            case "Gear":
            case "Jagged_Scaffold":
            case "Scaffold":
                //ギア・足場SE
                SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Bump_gear);//追加
                CollisionHouse(true, collision.gameObject);//オブジェクトリスト格納関数
                break;
            case "Wall":
                //壁SE
                rb.velocity = Vector3.zero;
                jump_State = Jump_State.DESCEND;
                SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Bump_wall);//追加
                break;
        }
    }

    /// <summary>
    /// 当たり判定：当たった時(Trigger)
    /// </summary>
    /// <param name="collider"></param>
    private void OnTriggerEnter(Collider collider)
    {
        switch (collider.gameObject.tag)
        {
            case "Collection":
                //Instantiate(Collection_EF, new Vector3(collider.gameObject.transform.position.x, collider.gameObject.transform.position.y, collider.gameObject.transform.position.z), Quaternion.identity);
                CollectionNum++;
                foreach (var effect in Collection_EF)
                {
                    GameObject collectionEffectObj = Instantiate(effect, new Vector3(collider.gameObject.transform.position.x, collider.gameObject.transform.position.y, collider.gameObject.transform.position.z), Quaternion.identity);
                    var effscript = collectionEffectObj.GetComponent<moveCollectionParticle>();
                    if (effscript != null)
                        effscript.SetCollectionNum(CollectionNum);
                }

                SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Game_collect);
                Destroy(collider.gameObject);
                if (CollectionNum == 3)
                {
                    var goal = GameObject.Find("Goal");
                    if (goal != null)
                        goal.GetComponent<GoalGoalGearScript>().SetEffect();
                }
                break;
        }
    }

    /// <summary>
    /// 当たり判定：離れた時(Trigger)
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerExit(Collider other)
    {
        switch (other.gameObject.tag)
        {
            case "Jagged_Scaffold":
                if (!Jump_flag)
                {
                    rb.velocity = new Vector2(0, 0);
                }
                CollisionHouse(false, other.gameObject);//オブジェクトリスト削除関数
                //InputScript.Instance.SetGamePadVibrationStop();//追加
                break;
            case "Scaffold":
            case "Gear":
                CollisionHouse(false, other.gameObject);//オブジェクトリスト削除関数
                //InputScript.Instance.SetGamePadVibrationStop();//追加
                break;
        }
    }

    void Prevention_of_digging()
    {//ギアとプレイヤーのめり込み防止
        foreach (var gear in Col_Object)
        {
            if (gear != null && gear.tag == "Gear")
            {
                SphereCollider playercol = null, gearcol = null;
                //プレイヤーとの距離を測る
                foreach (var player in this.GetComponents<SphereCollider>())
                {
                    if (player.isTrigger == false)
                    {
                        playercol = player;
                        break;
                    }

                }
                foreach (var gearscript in gear.GetComponents<SphereCollider>())
                {
                    if (gearscript.isTrigger == false)
                    {
                        gearcol = gearscript;
                        break;
                    }
                }
                if (playercol != null && gearcol != null)
                {
                    var dist = playercol.radius + gearcol.radius;
                    dist = dist * 0.99f;
                    var gp_dist = Vector2.Distance(this.transform.position, gear.transform.position);
                    if (dist > gp_dist)
                    {//プレイヤーがギアに近いのでプレイヤーを当座ける
                        //方向
                        float posz = this.transform.position.z;
                        var dis = this.transform.position - gear.transform.position;
                        this.transform.position = gear.transform.position + dis.normalized * dist;
                        this.transform.position = new Vector3(this.transform.position.x, this.transform.position.y, posz);
                        jump_State = Jump_State.NONE;
                        Jump_flag = false;
                    }
                }
            }
        }
    }

    /// <summary>
    /// 当たる・離れるオブジェクトをリストに格納・削除する関数
    /// </summary>
    /// <param name="flag">格納=true、削除=false</param>
    /// <param name="obj">格納・削除したいオブジェクト</param>
    private void CollisionHouse(bool flag, GameObject obj)
    {
        //格納処理
        if (flag)
        {
            var s = obj.GetComponent<ConnectionObject>();
            if (s != null)
            {//親オブジェクト取得
                var part = s.GetListObject();
                if (part != null)
                {
                    //格納オブジェクトがあるかないか調べる
                    s = part.GetComponent<ConnectionObject>();
                    if (s != null)
                    {
                        foreach (var colobj in Col_Object)
                        {
                            if (s.SearchListObject(colobj))
                            {
                                //格納しない
                                return;
                            }

                        }
                    }

                }
            }


            int cout = 0;
            //オブジェクトが入っていないか調べて格納する
            for (int i = 0; i < Col_Object.Length; i++)
            {
                if (Col_Object[i] == obj)
                    break;
                if (Col_Object[i] == null)
                {
                    Col_Object[i] = obj;
                    break;
                }
            }
            //いくつオブジェクトが格納されているか調べる
            for (int i = 0; i < Col_Object.Length; i++)
                cout = Col_Object[i] != null ? cout + 1 : cout;

            DoubleCol_flag = cout >= Col_Object.Length;
            ClimbChanceflag = DoubleCol_flag ? true : ClimbChanceflag;
            //落ちてた場合
            if (Fall_flag && Ray_Cofirmation_down())
            {
                if (obj.tag == "Gear" || obj.tag == "Jagged_Scaffold")
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage01);
                }
                else if (obj.tag == "Scaffold")
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Landing);
                }

                //SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage01);
                GameObject effectEngage01 = Instantiate(EffectEngage01Obj);
                effectEngage01.transform.position = new Vector3(this.transform.position.x, this.transform.position.y - 1, this.transform.position.z);

                Fall_flag = false;
                Jump_flag = false;
                Jump_Descend_flag = false;
                TerrainHit_flag = true;
                rb.velocity = Vector3.zero;
                jump_State = Jump_State.NONE;
                Engagement_flag = true; //06/25：追加
                if (rb.mass > 1)
                    rb.mass = 1;
            }
            if (Roll_flag && Ray_Cofirmation_down())
            {
                Roll_flag = false;
                Jump_flag = false;
                Jump_Descend_flag = false;
                TerrainHit_flag = true;
                rb.velocity = Vector3.zero;
                jump_State = Jump_State.NONE;
                if (rb.mass > 1)
                    rb.mass = 1;
            }
        }
        //削除処理
        else
        {
            if (DoubleCol_flag && Roll_flag)
            {
                if (Col_Object[0].tag == "Gear" && Col_Object[1].tag == "Gear")
                {
                    Fixed_flag = true;
                    Roll_flag = false;
                }
            }
            for (int i = 0; i < Col_Object.Length; i++)
            {
                if (Col_Object[i] == obj)
                {
                    Col_Object[i] = null;
                    break;
                }
            }
            //当たっているオブジェクトがあるかどうか調べる
            int count = 0;
            for (int i = 0; i < Col_Object.Length; i++)
                count = Col_Object[i] != null ? count + 1 : count;
            //当たっているオブジェクトが1体以下の場合
            if (count < 2)
            {
                if (DoubleCol_flag)
                {
                    DoubleCol_flag = false;
                    AutoMoveG_flag = false;
                    rotateDirect = RotateDirect.NONE;
                }
                //何も当たっていない場合
                if (count == 0)
                {
                    ClimbChanceflag = false;
                    rb.useGravity = true;
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationX;
                    TerrainHit_flag = false;
                    Climb_flag = false;
                    Engagement_flag = false; //06/25：追加
                }
            }
        }
    }

    /// <summary>
    /// 軸更新
    /// </summary>
    private void ShaftUpdate()
    {
        //ギアとプレイヤーがめり込まないようにする
        if (!(InputScript.Instance.GetGamePadButtonTrigger(GamePadKey.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.Space)) && Checkflg)
        {
            Prevention_of_digging();
        }
        else
        {
            if (jumpaitcount >= jumpwaitframe)
            {
                jumpaitcount = 0;
                Checkflg = true;
            }
            else
                jumpaitcount++;
        }

        //軸更新処理
        if (!Fall_flag && !Jump_flag)
        {
            //単独接触時
            if (!DoubleCol_flag && Col_Object[0] != null)
            {
                //ギアの場合
                if (Col_Object[0].tag == "Gear")
                    Shaft_PG(Col_Object[0]);
                //足場、歯付き足場の場合
                else
                {
                    //足場、歯付き足場の場合
                    if (InputScript.Instance.GetGamePadLeftStickXTrigger(LeftStickXDirection.Left) || InputScript.Instance.GetGamePadLeftStickXTrigger(LeftStickXDirection.Right) ||
                        InputScript.Instance.GetKeyboardTrigger(KeyCode.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.D))
                    {
                        GetComponent<KamiwaseTestScript>().Engagenment(this.gameObject, Col_Object[0]);
                    }
                    Shaft_GP();
                }
            }
            //複数接触時
            else if (DoubleCol_flag)
            {
                if (Col_Object[0].tag == "Gear" && Col_Object[1].tag == "Gear")
                    Shaft_Double();
                else
                    Shaft_PGD();
            }
        }
        //ジャンプ中
        if (Jump_flag)
        {
            //プレイヤー軸に変更
            PRotate_flag = true;//プレイヤー軸変更
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
        }
    }

    /// <summary>
    /// 足場移動時の軸更新処理
    /// </summary>
    private void Shaft_GP()
    {
        //足場での移動時の軸
        MovePattern = false;
        if (InputScript.Instance.GetGamePadLeftStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A) || InputScript.Instance.GetKeyboardPress(KeyCode.D))
        {
            //プレイヤー軸に変更
            PRotate_flag = true;//プレイヤー軸変更
            GearMoveflag = false;
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
            rb.useGravity = false;
            rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;
        }
    }

    /// <summary>
    /// ギア移動時の軸更新処理
    /// </summary>
    private void Shaft_PG(GameObject obj)
    {
        //ギア時の軸
        MovePattern = true;
        var rote = obj.GetComponent<GearRote>();
        GearTeeth = rote == null ? 12 : rote.GearTeeth;
        if (InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) && !Roll_flag)
        {//右スティック入力があった場合
            //ギアの上に登れているかそれ以外だと回転できない
            //角度を調べる
            var vec = this.gameObject.transform.position - obj.transform.position;
            float angle = Vector2.Angle(Vector2.up, vec.normalized);
            //二つのオブジェクトに当たっている時その片方が足場なら回らないようにする
            bool flg = angle > GearAngle_Limit;
            //if (DoubleCol_flag&&!flg)
            //{
            //    foreach (var objs in Col_Object)
            //    {
            //        flg = objs.tag == "Gear" ? flg : true;
            //    }
            //}
            if (flg)
            {
                PRotate_flag = false;
                GearMoveflag = false;
                return;
            }
            //プレイヤー軸に変更
            if (!PRotate_flag)
            {
                GetComponent<KamiwaseTestScript>().Engagenment(this.gameObject, obj);
            }
            GearMoveflag = false;
            PRotate_flag = true;//プレイヤー軸変更
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
        }
        else
        {
            //移動できるか調べる
            var vec = this.gameObject.transform.position - obj.transform.position;
            float angle = Vector2.Angle(Vector2.up, vec.normalized);
            GearMoveflag = true;
            //軸をギアに変更する
            PRotate_flag = false;//ギア軸変更
            Vector3 PlayerPos = this.transform.position;
            Player_Center.transform.position = obj.transform.position;
            this.transform.position = PlayerPos;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
        }
    }

    /// <summary>
    /// 複数接触時の処理(自動移動発生)
    /// </summary>
    private void Shaft_Double()
    {
        int EndObj = Col_Object.Length - 1;
        //当たったオブジェクトが何か確認
        if (Col_Object[EndObj].tag == "Gear" && Col_Object[EndObj - 1].tag == "Gear")
        {
            //ギア移動に変更する
            MovePattern = true;
            PRotate_flag = false;
            GearMoveflag = true;
            Vector3 PlayerPos = this.transform.position;
            Player_Center.transform.position = Col_Object[EndObj].transform.position;
            this.transform.position = PlayerPos;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
            //自動移動させる
            AutoMoveG_flag = true;
        }
    }

    /// <summary>
    /// 複数の時ギア移動か足場移動か決めて更新する
    /// </summary>
    private void Shaft_PGD()
    {
        //右スティック入力
        if (InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow))
        {
            //ギアと当たっている場合
            for (int i = 0; i < Col_Object.Length; i++)
            {
                if (Col_Object[i].tag == "Gear")
                {//ギア軸にする
                    Shaft_PG(Col_Object[i]);
                    return;
                }
            }
        }

        //当たっているオブジェクトどちらで判定を取るか決める
        GameObject kari = null;
        bool leftstickright = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool leftstickleft = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);

        //左スティック入力
        if (leftstickright)
        {//右移動
            //プレイヤーより右にあるオブジェクトがいくつあるか
            int count = 0;
            for (int i = 0; i < Col_Object.Length; i++)
            {
                count = this.transform.position.x < Col_Object[i].transform.position.x ? count + 1 : count;
            }

            if (count == 0)
            {//どちらも左にある場合
                //当たっているオブジェクトで比べて上にあるオブジェクトで軸を決める
                kari = Col_Object[0].transform.position.y < Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
            else if (count == 1)
            {//1つだけの場合
                for (int i = 0; i < Col_Object.Length; i++)
                {
                    kari = this.transform.position.x < Col_Object[i].transform.position.x ? Col_Object[i] : kari;
                }
            }
            else
            {//2つとも右にある場合
             //当たっているオブジェクトで比べて左側にあるオブジェクトで軸を決める
                kari = Col_Object[0].transform.position.y > Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
        }
        else if (leftstickleft)
        {//左移動
         //プレイヤーより左にあるオブジェクトがいくつあるか
            int count = 0;
            for (int i = 0; i < Col_Object.Length; i++)
            {
                count = this.transform.position.x > Col_Object[i].transform.position.x ? count + 1 : count;
            }

            if (count == 0)
            {//どちらも右にある場合
             //当たっているオブジェクトで比べて左側にあるオブジェクトで軸を決める
                kari = Col_Object[0].transform.position.y < Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
            else if (count == 1)
            {//1つだけの場合
                for (int i = 0; i < Col_Object.Length; i++)
                {
                    kari = this.transform.position.x > Col_Object[i].transform.position.x ? Col_Object[i] : kari;
                }
            }
            else
            {//2つとも左にある場合
             //当たっているオブジェクトで比べて右側にあるオブジェクトで軸を決める
                kari = Col_Object[0].transform.position.y > Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
        }
        else
        {//何もない時
         //プレイヤー軸に変更
            GearMoveflag = false;
            PRotate_flag = true;//プレイヤー軸変更
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
        }

        if (kari != null)
        {
            if (kari.tag == "Gear")
            {//ギアの場合
                Shaft_PG(kari);
            }
            else
            {//足場、歯付き足場の場合
                if (InputScript.Instance.GetGamePadLeftStickXTrigger(LeftStickXDirection.Left) || InputScript.Instance.GetGamePadLeftStickXTrigger(LeftStickXDirection.Right) ||
                   InputScript.Instance.GetKeyboardTrigger(KeyCode.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.D))
                {
                    GetComponent<KamiwaseTestScript>().Engagenment(this.gameObject, kari);
                }
                Shaft_GP();
            }
        }
    }

    /// <summary>
    /// オブジェクトタグ名確認関数
    /// </summary>
    /// <param name="obj">確認したいオブジェクト</param>
    /// <param name="tag">確認したいタグ名</param>
    /// <param name="tag2">確認したいタグ名(必須ではない)</param>
    /// <param name="tag3">確認したいタグ名(必須ではない)</param>
    /// <returns>True=確認したいタグ名と一致した、False=確認したいタグ名と一致しなかった</returns>
    private bool Tag_Confirmation(GameObject obj, string tag, string tag2 = "NONE", string tag3 = "NONE")
    {
        if (obj.tag == tag || obj.tag == tag2 || obj.tag == tag3)
            return true;
        return false;
    }

    void Death()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    /// <summary>
    /// Rigidbody制限関数
    /// </summary>
    /// <param name="move">制限したいもの(Position,Rotation,All,Free)</param>
    /// <param name="axis"><para>All以外：制限したい軸(X,Y,Z,XYZ,XY,YZ,All,Free)</para>All時：制限したい移動軸(X,Y,Z,XYZ,XY,YZ,All,Free)</param>
    /// <param name="axis2"><para>All以外：機能しない(NONEを代入)</para>All時：制限したい回転軸(X,Y,Z,XYZ,XY,YZ,All,Free)</param>
    private void Rigidbody_Constraints(string move, string axis, string axis2 = "NONE")
    {
        //移動・回転ALL制限
        if (move == "All" && axis == "All")
        {
            rb.constraints = RigidbodyConstraints.FreezeAll;
            return;
        }
        //移動・回転ALL無制限
        else if (move == "Free" || axis == "Free")
        {
            rb.constraints = RigidbodyConstraints.None;
            return;
        }

        //移動・回転制限
        if (move == "All" && axis2 != "NONE" || axis2 != "Free")
        {
            if (axis == ("XYZ") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XYZ") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XYZ") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XYZ") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("XYZ") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XYZ") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XY") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XY") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XY") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XY") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("XY") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XY") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XY") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotation;
            if (axis == ("XZ") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XZ") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XZ") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XZ") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("XZ") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XZ") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XZ") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
            if (axis == ("YZ") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("YZ") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("YZ") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("YZ") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("YZ") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("YZ") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("YZ") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
            if (axis == ("X") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("X") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("X") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("X") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("X") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("X") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("X") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezeRotation;
            if (axis == ("Y") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("Y") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("Y") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("Y") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("Y") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("Y") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("Y") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezeRotation;
            if (axis == ("Z") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("Z") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("Z") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("Z") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("Z") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("Z") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("Z") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("XY"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("X"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationX;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("Y"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationY;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("Z"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotationZ;
            if (axis == ("XYZ") || axis == ("All") && axis2 == ("XYZ") || axis2 == ("All"))
                rb.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotation;
            return;
        }
        //移動制限
        else if (move == "Position" || move == "All" && axis2 == "NONE" || axis2 == "Free")
        {
            if (axis.Contains("XYZ") || axis.Contains("All"))
                rb.constraints = RigidbodyConstraints.FreezePosition;
            else if (axis.Contains("XY"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionY;
            else if (axis.Contains("XZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ;
            else if (axis.Contains("YZ"))
                rb.constraints = RigidbodyConstraints.FreezePositionY | RigidbodyConstraints.FreezePositionZ;
            else if (axis.Contains("X"))
                rb.constraints = RigidbodyConstraints.FreezePositionX;
            else if (axis.Contains("Y"))
                rb.constraints = RigidbodyConstraints.FreezePositionY;
            else if (axis.Contains("Z"))
                rb.constraints = RigidbodyConstraints.FreezePositionZ;
            else
                Debug.LogError("制限したい移動軸が指定されていません");
            return;
        }
        //回転制限
        else if (move == "Rotation")
        {
            if (axis.Contains("XYZ") || axis.Contains("All"))
                rb.constraints = RigidbodyConstraints.FreezeRotation;
            else if (axis.Contains("XY"))
                rb.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
            else if (axis.Contains("XZ"))
                rb.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationZ;
            else if (axis.Contains("YZ"))
                rb.constraints = RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            else if (axis.Contains("X"))
                rb.constraints = RigidbodyConstraints.FreezeRotationX;
            else if (axis.Contains("Y"))
                rb.constraints = RigidbodyConstraints.FreezeRotationY;
            else if (axis.Contains("Z"))
                rb.constraints = RigidbodyConstraints.FreezeRotationZ;
            else
                Debug.LogError("制限したい回転軸が指定されていません");

        }
        //名称が不適切
        else
        {
            Debug.LogError("制限したいものの名称が指定されていません");
        }
    }
}