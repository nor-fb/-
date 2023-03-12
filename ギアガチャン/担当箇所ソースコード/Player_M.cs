using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;
using UnityEngine.UI;


/// <summary>
/// �v���C���[�̊Ǘ��E�������s���X�N���v�g�΂�����
/// </summary>
public class Player_M : MonoBehaviour
{
    [Header("�v���C���[�̒��S��\���I�u�W�F�N�g�i�[")]
    public GameObject Player_Center;
    [Header("���W���̃G�t�F�N�g")]
    public GameObject[] Collection_EF = new GameObject[2];
    [Header("�ړ����x")]
    public float mo_Speed;
    [Header("��]���x")]
    public float ro_Speed;

    [Header("�M�A�ړ����x")]
    public float G_mo_Speed;
    [Header("����ړ����x")]
    public float S_mo_Speed;
    [Header("�W�����v��")]
    public float Jump_Power;
    [Header("�W�����v�ړ���")]
    public float Jump_Move;
    [Header("�W�����v��]��")]
    public float Jump_Rota;
    [Header("�W�����v����")]
    [Range(0.01f, 10)]
    public float Jump_Limit;
    private Vector2 Jump_Initial_Position;    //�W�����v�O�̏����ʒu

    [Header("����ړ����̃`���b�N�}�l�[�W���[�i�`�F�b�N���鋗���̊����j")]
    [Range(0.0f, 2.0f)]
    public float raymaneger = 1.0f;
    [Header("�󒆈ړ����̃`���b�N�}�l�[�W���[�i�`�F�b�N���鋗���̊����j")]
    [Range(0.0f, 2.0f)]
    public float fallmaneger = 1.0f;
    [Header("�M�A�ړ����̃`���b�N�}�l�[�W���[�i�`�F�b�N���鋗���̊����j")]
    [Range(0.0f, 2.0f)]
    public float gearmovemaneger = 1.0f;

    //�t���O
    private bool GearMoveflag;      //�M�A�ړ��t���O�E�E�ETRUE���ړ��ł���@FALSE���ړ��ł��Ȃ�
    private bool Jump_Descend_flag; //�����t���O�E�E�ETRUE=��������AFLASE=�������Ȃ�
    private bool PRotate_flag;      //���t���O�E�E�ETRUE=�v���C���[���AFALSE=�M�A��
    private bool Roll_flag;         //��]�����t���O�E�E�ETRUE=�]���藎����AFALSE=�]����Ȃ�
    private bool AutoMoveG_flag;    //�����M�A�ړ��t���O�E�E�ETRUE=�ړ��\�AFALSE=�ړ��s�\
    private bool Climb_flag;        //�o��t���O�E�E�ETRUE=�o���AFALSE=�o��Ȃ�
    private bool Fixed_flag;        //�Œ�t���O�E�E�ETRUE=�Œ艻(���͂���܂�)�AFALSE=���R
    public bool Rotate_flag;       //��]�t���O�E�E�ETRUE=��]���Ă�AFAlSE=��]���Ă��Ȃ�
    private bool TerrainHit_flag;   //�n�ʐڐG�t���O�E�E�ETRUE=�n�ʂƐڐG���Ă���AFALSE=�n�ʂƐڐG���Ă��Ȃ�
    public bool Jump_flag;         //�W�����v�t���O�E�E�ETRUE=�W�����v������AFALSE=�W�����v���Ȃ�
    private bool ClimbChanceflag;   //�o��`�������W�t���O�E�E�ETRUE=�`�����X������AFALSE=�`�����X���Ȃ�
    private bool Death_flag;        //���S�t���O�E�E�ETRUE=���S�AFALSE=����
    private bool Time_flag;         //���Ԓ�~�t���O�E�E�ETRUE=���Ԓ�~���AFALSE=��~���Ă��Ȃ�
    private bool Pause_flag;        //�|�[�Y�t���O�E�E�ETRUE=velocity�X�V�K�v�AFALSE=velocity�X�V�ς�
    private bool CharFade_flag;     //�t�F�[�h�t���O�E�E�E
    private bool Engagement_flag;   //���ݍ��킹�t���O�E�E�ETRUE=���ݍ��킹�ł���AFALSE=���ݍ��킹�ł��Ȃ�
    public bool MovePattern;       //�ړ����@�t���O�E�E�ETRUE=�M�A�ړ��AFALSE=����ړ�
    public bool DoubleCol_flag;    //�����ڐG�t���O�E�E�ETRUE=��ȏ�ƐڐG���Ă���AFALSE=��ȏ�ƐڐG���Ă��Ȃ�
    public bool Fall_flag;         //�����t���O�E�E�ETRUE=��������AFALSE=�������Ȃ�
    public bool Move_flag;         //�ړ��E��]�t���O�E�E�ETRUE=�s���\�AFALSE=�s���s�\

    //���������I�u�W�F�N�g�i�[�p
    [Header("�i�[�p�`�f�o�b�N�̂��߉������`")]
    public GameObject[] Col_Object = new GameObject[2];
    //���W���̊i�[�p
    private GameObject[] Collection_Obj = new GameObject[3];   //���W��(�{��)
    Rigidbody rb;         //�v���C���[�̉�]�E�����蔻��pRigidbody2D
    Vector3 velocity = new Vector3(0, 0, 0);     //������ꂽ�͂̊i�[�p

    [Header("�������n�߂�M�A�Ƃ̋���")]
    [Range(-2, 2)]
    public float Fall_Distance;

    [Header("�M�A�̊p�x����")]
    [Tooltip("�w�肵���p�x�ȏ�ɃM�A��̃v���C���[���ړ������ꍇ�A�Œ肳�ꂸ�����Ă����܂��B(-�l�ł��Ή��ς�)")]
    [Range(10, 90)]
    public int GearAngle_Limit;
    [Header("����̊p�x����")]
    [Tooltip("�w�肵���p�x�ȏ�̑���ɐڐG�����ꍇ�A�Œ肳�ꂸ�����Ă����܂��B(-�l�ł��Ή��ς�)")]
    [Range(10, 90)]
    public int ScaffoldAngle_Limit;
    [Header("���t������̊p�x����")]
    [Tooltip("�w�肵���p�x�ȏ�̎��t������ɐڐG�����ꍇ�A�Œ肳�ꂸ�����Ă����܂��B(-�l�ł��Ή��ς�)")]
    [Range(10, 90)]
    public int JaggedScaffoldAngle_Limit;

    //�o���i�o���ė�����j�M�A�̊p�x
    public float GearClimbAngleLimit = 180;
    //�o���i�o���ė�����j����̊p�x
    public float ScaffoldClimbAngleLimit = 0;
    //�o���i�o���Ɨ�����j���t������
    public float JaggedScaffoldClimbAngleLimit = 180;
    private float ClimbTime = 0;
    //������܂Ŏ���
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

    private GameObject PauseObj;//�ǉ�

    //�M�A�ړ����̉�]���x�Ɏ��̖������g��(�̂��Ɏg�p����)
    //GearVariable gearvariable;
    //�񋓌n
    enum RotateDirect
    {
        NONE,
        LEFT,
        RIGHT
    }
    RotateDirect rotateDirect;//�v���C���[�̉�]���

    enum Jump_State
    {
        NONE,       //�Ȃ�
        RISE,       //�㏸���
        DESCEND,    //���~���
    }
    Jump_State jump_State;//�W�����v���


    public GameObject EffectEngage01Obj;
    public GameObject EffectJumpObj;
    Volume postProcess;

    public Image blackcharabigImage;
    bool blackcharabigFadeInFlg = false;

    // Start is called before the first frame update
    void Start()
    {
        //�t���O������
        Jump_flag = false;
        GearMoveflag = true;
        Fall_flag = true;//������Ԃ������Ă��邽��TRUE
        DoubleCol_flag = false;
        TerrainHit_flag = false;
        PRotate_flag = false;
        ClimbChanceflag = false;
        Checkflg = true;
        //���W���I�u�W�F�N�g�擾
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
        //�ǉ�
        PauseObj = GameObject.Find("PauseGameScene");
        PauseObj.GetComponent<PauseGameSceneScript>().enabled = true;

        GearClimbAngleLimit = GearAngle_Limit > GearClimbAngleLimit ? GearAngle_Limit : GearClimbAngleLimit;
        ScaffoldClimbAngleLimit = ScaffoldAngle_Limit > ScaffoldClimbAngleLimit ? ScaffoldAngle_Limit : ScaffoldClimbAngleLimit;
        JaggedScaffoldClimbAngleLimit = JaggedScaffoldAngle_Limit > JaggedScaffoldClimbAngleLimit ? JaggedScaffoldAngle_Limit : JaggedScaffoldClimbAngleLimit;

        this.gameObject.transform.parent = Player_Center.transform;
        rb = GetComponent<Rigidbody>();                      //Player_Body��Rigidbody2D���i�[
        rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;//�ړ��֎~

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
            Debug.Log("��~������");
            return;
        }
        //�ʏ폈��
        else
        {
            //�|�[�Y��̏���
            if (Pause_flag)
            {
                rb.useGravity = true;
                Pause_flag = false;
                rb.velocity = velocity;
            }
            //�Q�[���I�[�o�[����
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

        if (this.gameObject.transform.position.y < -18.0f)//�ǉ�(�C��)
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

        //�i�[���Ă���I�u�W�F�N�g�𐮗񂳂���
        if (Col_Object[0] == null && Col_Object[1] != null)
        {
            Col_Object[0] = Col_Object[1];
            Col_Object[1] = null;
        }
        //�����X�V����
        FallUpdate();
        //���ύX����
        ShaftUpdate();
        //�W�����v����
        JumpUpdate();
        //��������
        //AutoMoveUpdate();
        //�ړ��E��]����
        MoveUpdate();
        //���W���X�V����
        //CollectionUpdate();
    }

    /// <summary>
    /// ��������
    /// </summary>
    void FallUpdate()
    {
        //�����ɓ������Ă��邩���ׂ�
        int count = 0;
        foreach (var obj in Col_Object)
        {
            if (obj != null)
                count++;
        }

        //���Ƃ��������ĂȂ��ꍇ(�ʏ�)
        if (count == 0 && jump_State == Jump_State.NONE)
        {
            Roll_flag = false;
            Fall_flag = true;
            rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
            return;
        }

        //�W�����v���̏ꍇ
        if (Jump_flag)
        {
            //�㏸������
            if (jump_State == Jump_State.RISE)
            {
                //Ray�ŏ�ɃI�u�W�F�N�g���m�F�����ꍇ
                if (Ray_Confirmation_up() == true)
                {
                    if (Ray_Cofirmation_down())
                    {
                        //���n�ʖ��̓M�A�ɂ�����Ƃ�
                        jump_State = Jump_State.NONE;
                        Fall_flag = false;
                        Jump_flag = false;
                    }
                    else
                    {
                        //���~��ԂɈڍs
                        jump_State = Jump_State.DESCEND;
                        rb.velocity = Vector3.zero;
                        Fall_flag = true;
                    }
                }
                if (this.gameObject.transform.position.y >= 12.0f)
                {
                    //���~��ԂɈڍs
                    jump_State = Jump_State.DESCEND;
                    rb.velocity = Vector3.zero;
                    Fall_flag = true;
                }
                //////�ǉ�06/37///////
                foreach (var obj in Col_Object)
                {
                    if (obj != null)
                    {
                        if (obj.tag == "Jagged_Scaffold" || obj.tag == "Scaffold")
                        {
                            if (obj.transform.up.y > 0.0f)
                            {
                                //�]�������Ȃ��p�x�����ׂ�
                                float angle = Vector2.Angle(obj.transform.right, Vector2.right);
                                Fall_flag = false;
                                Roll_flag = false;
                                //rb.constraints = RigidbodyConstraints.FreezeAll;
                                rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
                                float limit = obj.tag == "Scaffold" ? ScaffoldAngle_Limit : JaggedScaffoldAngle_Limit;
                                if (angle > limit && !DoubleCol_flag)
                                {
                                    //�]��������
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
        //�W�����v���ł͂Ȃ��ꍇ
        else
        {
            //����������Ԃɂ���
            Fall_flag = true;
            TerrainHit_flag = false;
            //�����Ȃ������𒲂ׂ�
            foreach (var obj in Col_Object)
            {
                if (obj != null)
                {
                    //�����ړ���
                    if (AutoMoveG_flag)
                    {
                        Fall_flag = false;
                        Roll_flag = false;
                        TerrainHit_flag = true;
                        return;
                    }
                    else if (obj.tag == "Gear")
                    {
                        //�o���p�x���v�Z���ċ��߂邱�Ƃŏo����   
                        bool Position = this.gameObject.transform.position.x - obj.transform.position.x > 0;
                        bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
                        bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
                        bool move = (!Position && LeftInputR) || (Position && LeftInputL);

                        //���̊p�x���Ȃ��Ȃ痎���Ȃ�
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
                        //���̊p�x�ȓ��Ȃ痎���Ȃ�
                        if (angle < 90)
                        {
                            bool flag = true;
                            if (DoubleCol_flag)
                            {//2�̃I�u�W�F�N�g�Ɠ������Ă��鎞����2���M�A���ǂ������ʂ���
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
                            //�]�������Ȃ��p�x�����ׂ�
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
                                //�]��������
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
    /// Ray�F�㕔�m�F
    /// </summary>
    /// <returns>True=��ɃI�u�W�F�N�g�L,False=��ɃI�u�W�F�N�g��</returns>
    private bool Ray_Confirmation_up()
    {
        bool hit_flag = false;   //Ray�ڐG�t���O�E�E�ETRUE=���������AFALSE=�������ĂȂ�
        foreach (var obj in Col_Object)
        {
            //�i�[����Ă���ꍇ
            if (obj != null)
            {
                float major = 1.7f;
                //���Ray���΂�
                Vector3 pos = this.transform.position;  //�ʒu�x�N�g��
                Ray ray = new Ray(pos, Vector3.up);     //Ray����
                //Ray����(�f�o�b�N�p)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Ray�������������m�F
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
                //��(�E�̕�)��Ray���΂�
                pos.x = this.transform.position.x + this.transform.lossyScale.y * 1.2f;
                ray = new Ray(pos, Vector3.up);
                //Ray����(�f�o�b�N�p)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Ray�������������m�F
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
                //��(���̕�)��Ray���΂�
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
    /// Ray�F�����m�F
    /// </summary>
    /// <returns>True=���ɃI�u�W�F�N�g�L,False=���ɃI�u�W�F�N�g��</returns>
    private bool Ray_Cofirmation_down()
    {
        bool hit_flag = false;   //Ray�ڐG�t���O�E�E�ETRUE=���������AFALSE=�������ĂȂ�
        foreach (var obj in Col_Object)
        {
            //�i�[����Ă���ꍇ
            if (obj != null)
            {
                float major = 1.7f;
                //����Ray���΂�
                Vector3 pos = this.transform.position;  //�ʒu�x�N�g��
                Ray ray = new Ray(pos, Vector3.down);     //Ray����
                //Ray����(�f�o�b�N�p)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Ray�������������m�F
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
                //��(�E�̕�)��Ray���΂�
                pos.x = this.transform.position.x + this.transform.lossyScale.y * 1.2f;
                ray = new Ray(pos, Vector3.down);
                //Ray����(�f�o�b�N�p)
                Debug.DrawRay(ray.origin, ray.direction * this.transform.lossyScale.y * major, Color.black, 0.1f);
                //Ray�������������m�F
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
                //��(���̕�)��Ray���΂�
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
    /// �W�����v����
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
    /// �W�����v�F�㏸����
    /// </summary>
    private void Jump_Rise()
    {
        if (!Jump_Descend_flag)
        {
            //���E�_�ȉ����W�����v���E�_�ȏ�
            if (transform.position.y < Jump_Initial_Position.y + Jump_Limit && transform.position.y > (Jump_Initial_Position.y + Jump_Limit) / 2)
            {
                //���͖����Ȃ����ꍇ
                if (!InputScript.Instance.GetGamePadButtonPress(GamePadKey.A) && !InputScript.Instance.GetKeyboardPress(KeyCode.Space))
                {
                    jump_State = Jump_State.DESCEND;
                    Fall_flag = true;
                }
            }
            //���E�_����
            else if (transform.position.y > Jump_Initial_Position.y + Jump_Limit)
            {
                //���~�����Ɉڍs����
                jump_State = Jump_State.DESCEND;
                Fall_flag = true;
            }
            //���W�����v���E�_�ȉ�
            else if (transform.position.y < (Jump_Initial_Position.y + Jump_Limit) / 2)
            {
                //���͖����Ȃ����ꍇ
                if (!InputScript.Instance.GetGamePadButtonPress(GamePadKey.A) && !InputScript.Instance.GetKeyboardPress(KeyCode.Space))
                {
                    jump_State = Jump_State.DESCEND;
                    Jump_Descend_flag = true;
                }
            }
            //�㏸����
            rb.velocity = new Vector3(0, Jump_Power * 2, 0);
        }
        else
        {
            //���W�����v���E�_�ȏ�
            if (transform.position.y >= (Jump_Initial_Position.y + Jump_Limit) / 2)
            {
                jump_State = Jump_State.DESCEND;
                Fall_flag = true;
            }
        }
    }

    /// <summary>
    /// �W�����v�F���~����
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
    /// �ړ�����
    /// </summary>
    void MoveUpdate()
    {
        bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
        if (Fixed_flag && LeftInputR || LeftInputL)
            Fixed_flag = false;
        //�I�v�V�����E���U���g��ʂł͂Ȃ�
        //if () {
        //�����E�W�����v���Ă��鎞
        if (Fall_flag || Jump_flag)
        {
            //�󒆎��ړ�
            Input_Air();
        }
        //�����Ă��Ȃ�
        else
        {
            //�W�����v�\
            if (!Jump_flag)
            {
                //�M�A�ڐG��
                if (MovePattern)
                {
                    if (Roll_flag)
                        Roll_Gear();
                    else if (!Roll_flag && !Fixed_flag)
                        Move_Gear();
                }
                //����ڐG��
                else
                {
                    if (Roll_flag)
                        Roll_Scaffold();
                    else if (Climb_flag)
                        Climb_Scaffold();
                    else if (!Roll_flag && !Climb_flag && !Fixed_flag)
                        Move_Scaffold();
                }
                //�W�����v
                bool JumpInput = InputScript.Instance.GetGamePadButtonTrigger(GamePadKey.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.Space);
                if (JumpInput && !Roll_flag && jump_State == Jump_State.NONE)
                {
                    Checkflg = false;
                    rb.useGravity = true;
                    rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;//��]�̂ݐ���
                    Jump_flag = true;//�W�����v��
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
    /// ���͏����F�M�A��ړ��E��]
    /// </summary>
    private void Move_Gear()
    {
        //DoubleCol_flag�̏ꍇ�A�󋵔c��
        if (DoubleCol_flag)
        {
            Vector3 R_Object = this.transform.position.x > Col_Object[0].transform.position.x ? Col_Object[1].transform.position : Col_Object[0].transform.position;
            Vector3 L_Object = this.transform.position.x < Col_Object[0].transform.position.x ? Col_Object[1].transform.position : Col_Object[0].transform.position;
            //���S�_��Player���E�ɂ���ꍇ
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
            //���S�_��Player��荶�ɂ���ꍇ
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
        //Player����]
        if (PRotate_flag && (InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow)))
        {
            //�M�A���񂹂邩���ׂ�
            bool Rota_flag = true;  //�������E�E�ETrue=�E��]�AFalse=����]
            //�E��]
            if (RightInputR && !AutoMoveG_flag)
                Rota_flag = true;
            //����]
            else if (RightInputL && !AutoMoveG_flag)
                Rota_flag = false;
            //�񂹂邩�m�F����
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
                //�E��]
                if (RightInputR && !AutoMoveG_flag)
                {
                    Player_Center.transform.Rotate(0, 0, -RotaSpeed);
                    Rotate_flag = true;
                }
                //����]
                else if (RightInputL && !AutoMoveG_flag)
                {
                    Player_Center.transform.Rotate(0, 0, RotaSpeed);
                    Rotate_flag = true;
                }
                //////////////�ǉ�////////////////////////
                //��ȏ�̃M�A����]��
                if (test.Search_GearNum() >= 2)
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage01);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                    Debug.Log("�����M�A�̂�");
                }
                //�傫�ȃM�A��������]��
                if (test.Search_BigGear())
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage03);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                    Debug.Log("�S�̃M�A�̂�");
                }
                //�ʏ�M�A��������]��
                else
                {
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage02);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                    Debug.Log("�ʏ�M�A�̂�");
                }
                rotateDirect = RotateDirect.NONE;
            }
            else
            {
                if (RightInputR)
                    rotateDirect = RotateDirect.RIGHT;
                else if (RightInputL)
                    rotateDirect = RotateDirect.LEFT;

                //��ȏ�̃M�A����]��
                if (test.Search_GearNum() >= 2)
                {

                }
                //�傫�ȃM�A��������]��
                if (test.Search_BigGear())
                {

                }
                //�ʏ�M�A��������]��
                else
                {

                }

                Rotate_flag = false;
                rb.useGravity = true;
                rb.constraints = RigidbodyConstraints.FreezeAll;
            }
            //�M�A�̉�]����
            test.Rote();
        }
        //�M�A���ړ�
        else if (GearMoveflag)
        {
            float MoveSpeed = G_mo_Speed;
            float RotaSpeed = G_mo_Speed * (GearTeeth / 6);
            //�ړ�
            if (LeftInputR && !AutoMoveG_flag)//�E
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
            else if (LeftInputL && !AutoMoveG_flag)//��
            {
                if (CheckGearMove(G_mo_Speed))
                {
                    this.transform.Rotate(0, 0, RotaSpeed);
                    Player_Center.transform.Rotate(0, 0, MoveSpeed);
                    rotateDirect = RotateDirect.LEFT;

                    //�ǉ�
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                }
            }
            //����
            else if (AutoMoveG_flag && rotateDirect == RotateDirect.RIGHT)//�E
            {
                this.transform.Rotate(0, 0, -RotaSpeed);
                Player_Center.transform.Rotate(0, 0, -MoveSpeed);
            }
            else if (AutoMoveG_flag && rotateDirect == RotateDirect.LEFT)//��
            {
                this.transform.Rotate(0, 0, RotaSpeed);
                Player_Center.transform.Rotate(0, 0, MoveSpeed);
            }
            //////////////////�ǉ��E�ύX//////////////////////////
            //���͂Ȃ��E�����Ȃ�
            else if (!AutoMoveG_flag && !LeftInputR || !LeftInputL || !RightInputL || RightInputR)
            {
                rotateDirect = RotateDirect.NONE;
                rb.constraints = RigidbodyConstraints.FreezeAll;
                InputScript.Instance.SetGamePadVibrationStop();
                Debug.Log("�U����~");
            }
            ///////////////////////////////////////////////////////
        }
    }

    /// <summary>
    /// ���͏����F�����ړ�
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

        ///�n�ʈړ�
        if (!Fall_flag)//�������Ă��Ȃ�
        {
            bool RightInputR = InputScript.Instance.GetGamePadRightStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow);
            bool RightInputL = InputScript.Instance.GetGamePadRightStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow);
            bool LeftInputR = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
            bool LeftInputL = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);
            ///����F�X��or�M�U�M�U����F�X��
            float rad = 0;//�p�x�����W�A��
            float objangle = 0;
            Vector3 vec = Vector3.zero;//�ړ��x�N�g���@�����t������(�΂ߎ�)�Ɏg�p����
            bool oneobj = Col_Object[0] != null;
            //�ړ������v�Z
            //2�̃I�u�W�F�N�g�ƂԂ����Ă��鎞�ǂ���Ŕ�����Ƃ邩
            if (Col_Object[0] != null && Col_Object[1] != null)
            {//2�̑���ƂԂ����Ă��鎞
                if (LeftInputL)
                {
                    oneobj = Col_Object[0].transform.position.x < Col_Object[1].transform.position.x;
                }
                else
                    oneobj = Col_Object[0].transform.position.x > Col_Object[1].transform.position.x;
                Vector3 pos = this.transform.position;
                //������������̂ǂ��炩����ɂ���ꍇ
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
            {//�X�^�b�N��1�ڂ����̎�
             //1�ڂŔ�������
                objangle = Col_Object[0] != null ? Col_Object[0].transform.eulerAngles.z : 0;
                float angle = objangle > 90 && objangle <= 180 ? 180 - objangle : objangle;
                angle = angle > 180 && angle <= 270 ? 270 + (270 - angle) : angle;
                rad = angle * Mathf.Deg2Rad;
                Scaffoldflag = Col_Object[0] != null && Col_Object[0].tag == "Scaffold";
            }
            else
            {//�X�^�b�N��2�ڂ����̎�
             //2�ڂŔ�������
                objangle = Col_Object[1] != null ? Col_Object[1].transform.eulerAngles.z : 0;
                float angle = objangle > 90 && objangle <= 180 ? 180 - objangle : objangle;
                angle = angle > 180 && angle <= 270 ? 270 + (270 - angle) : angle;
                rad = angle * Mathf.Deg2Rad;
                Scaffoldflag = Col_Object[1] != null && Col_Object[1].tag == "Scaffold";
            }
            Vector3 direction = new Vector3(Mathf.Cos(rad), Mathf.Sin(rad), 0);   //�����ݒ�
            direction.y = objangle > 90 && objangle < 270 ? -direction.y : direction.y;
            vec = direction * mo_Speed;                          //�ړ��x�N�g���v�Z
            objangle = 180 < objangle ? objangle - 180 : objangle;
            float limit = Scaffoldflag ? ScaffoldAngle_Limit : JaggedScaffoldAngle_Limit;
            //������
            bool moveflg = true;// (objangle < limit || objangle > 180 - limit);
            //�E�ړ�
            if (LeftInputR && moveflg)
            {
                if (CheckMove(vec, raymaneger))
                {
                    rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;
                    vec = direction * mo_Speed * 2.5f;
                    rb.velocity = vec;
                    transform.Rotate(0, 0, -ro_Speed * 3.0f);

                    //�ǉ�
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                }
                rotateDirect = RotateDirect.RIGHT;
            }
            //���ړ�
            else if (LeftInputL && moveflg)
            {
                if (CheckMove(-vec, raymaneger))
                {
                    rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;
                    vec = direction * mo_Speed * 2.5f;
                    rb.velocity = vec * -1;
                    transform.Rotate(0, 0, ro_Speed * 3.0f);

                    //�ǉ�
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Move);
                    VibrationDirectorScript.Instance.PlayVibration(VibrationDirectorScript.VibrationType.Walk);
                }
                rotateDirect = RotateDirect.LEFT;
            }
            else if (!LeftInputR && !LeftInputL)
            //���͂Ȃ�
            {
                if (!Jump_flag)
                {
                    //�M�U�M�U����̏ꍇ�A���藎���Ȃ��悤�ɂ���
                    rb.useGravity = true;
                    ////06/25�ǉ��E�ύX
                    if (Engagement_flag)
                    {//���ݍ��킹�̂���
                        rb.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
                        Engagement_flag = false;
                    }
                    else
                    {
                        rb.constraints = RigidbodyConstraints.FreezeAll;
                    }
                }
                //�ǉ�
                InputScript.Instance.SetGamePadVibrationStop();
            }
            if (RightInputR || RightInputL)
                rotateDirect = RotateDirect.NONE;
        }
    }

    /// <summary>
    /// ���͏����F�󒆈ړ�
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
        float move_x = 0; //X�����ړ���
                          //�E�ړ�
        if (right_flag)
        {
            if (CheckMove(Vector2.right, fallmaneger))
            {
                float Rotate = rotateDirect == RotateDirect.LEFT ? Jump_Rota * 0.5f : Jump_Rota;//�ǉ��C��
                transform.Rotate(0, 0, -Rotate);
                move_x = rotateDirect == RotateDirect.LEFT ? Jump_Move * 0.5f : Jump_Move;//�ǉ��C��
            }
        }
        //���ړ�
        else if (left_flag)
        {
            if (CheckMove(Vector2.left, fallmaneger))
            {
                float Rotate = rotateDirect == RotateDirect.RIGHT ? Jump_Rota * 0.5f : Jump_Rota;//�ǉ��C��
                transform.Rotate(0, 0, Rotate);
                move_x = rotateDirect == RotateDirect.RIGHT ? -Jump_Move * 0.5f : -Jump_Move;//�ǉ��C��
            }
        }
        //�ړ�
        rb.velocity = new Vector2(move_x, rb.velocity.y);

    }

    /// <summary>
    /// �]���菈���F�M�A
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
            bool Roll_direction = false;    //�]��������E�E�ETRUE=�E�]����AFALSE=���]����
            float MoveSpeed = G_mo_Speed * (12 / GearTeeth);
            float RotaSpeed = G_mo_Speed * (12 / GearTeeth);
            Roll_direction = Col_Object[0].transform.position.x < this.transform.position.x;

            //�]���藎���鏈��
            if (Roll_direction)//�݂�����
            {
                if (!LeftStick_L && !LeftStick_R) //���͂Ȃ�
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, -RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, -MoveSpeed);
                        rotateDirect = RotateDirect.RIGHT;
                    }
                }
                else if (LeftStick_R)//�E����
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, -RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, -MoveSpeed);
                        rotateDirect = RotateDirect.RIGHT;
                    }
                }
            }
            else//�Ђ��肱��
            {
                if (!LeftStick_L && !LeftStick_R) //���͂Ȃ�
                {
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY;
                    {
                        this.transform.Rotate(0, 0, RotaSpeed);
                        Player_Center.transform.Rotate(0, 0, MoveSpeed);
                        rotateDirect = RotateDirect.LEFT;
                    }
                }
                else if (LeftStick_L)//������
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
    /// �]���菈���F����
    /// </summary>
    private void Roll_Scaffold()
    {
        //����ɐڂ��Ă���ꍇ
        if (TerrainHit_flag)
        {
            //���]��������
            //�ړ������v�Z
            float objangle = 0;
            float rad = 0;
            //2�̃I�u�W�F�N�g�ƂԂ����Ă��鎞�ǂ���Ŕ�����Ƃ邩
            bool oneobj = Col_Object[0] != null && Tag_Confirmation(Col_Object[0], "Jagged_Scaffold", "Scaffold");
            bool Sca_Double = DoubleCol_flag && Tag_Confirmation(Col_Object[0], "Jagged_Scaffold", "Scaffold") && Tag_Confirmation(Col_Object[1], "Jagged_Scaffold", "Scaffold");
            if (Sca_Double)
            {//2�̑���ƂԂ����Ă��鎞
                oneobj = Col_Object[0].transform.position.x > Col_Object[1].transform.position.x;
            }

            if (oneobj && Col_Object[0] != null)
            {//�X�^�b�N��1�ڂ����̎�
             //1�ڂŔ�������
                objangle = Col_Object[0].transform.eulerAngles.z;
            }
            else if (Col_Object[1] != null)
            {//�X�^�b�N��2�ڂ����̎�
             //2�ڂŔ�������
                objangle = Col_Object[1].transform.eulerAngles.z;
            }

            rad = objangle * Mathf.Deg2Rad;
            Vector3 direction = new Vector3(Mathf.Cos(rad), Mathf.Sin(rad), 0);   //�����ݒ�
            direction = objangle > 180 ? -direction : direction;
            Vector2 vec = direction * mo_Speed * 2.5f;                          //�ړ��x�N�g���v�Z
            rb.velocity = -vec;
            float move = -vec.x < 0 ? ro_Speed : -ro_Speed;
            transform.Rotate(0, 0, move * 2.5f);
        }
    }

    /// <summary>
    /// �o��X�V�����F����
    /// </summary>
    private void Climb_Scaffold()
    {
        //���E����
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
    /// ���C���΂��Ĉړ��ł��邩���ׂ�
    /// </summary>
    /// <param name="vec">���C���΂�����</param>
    /// <returns>TRUE=�ړ��ł���@FALSE=�ړ��ł��Ȃ�</returns>
    private bool CheckMove(Vector2 vec, float maneger)
    {
        Vector3 vertical = new Vector3(vec.normalized.y, -vec.normalized.x, 0);

        //�����烌�C���΂�
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
                    //���ꂪ���������Ă����false��Ԃ�
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
        //���S���烌�C���΂�
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
                    //���ꂪ���������Ă����false��Ԃ�
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
        //�ォ�烌�C���΂�
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
                    //���ꂪ���������Ă����false��Ԃ�
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
        //�M�A���ړ����Ɉړ������Ɉړ��ł��邩���ׂ�
        //�M�A���iPlayer_Center�j��Player�I�u�W�F�N�g�̐����Œ��ׂ�
        //�ǂ������
        float right = speed > 0 ? 1 : -1;
        //�M�A������̃x�N�g�������߂�
        Vector2 vec1 = Player_Center.transform.position - this.transform.position;
        //�����x�N�g��
        Vector2 vec2 = new Vector2(vec1.y * right, vec1.x * -right);
        float num = Mathf.Abs(speed) * gearmovemaneger;
        Ray ray = new Ray(this.transform.position, vec2);
        RaycastHit[] rayhit = Physics.RaycastAll(ray.origin, ray.direction, num);

        Debug.DrawRay(ray.origin, ray.direction * num, Color.red, 1.0f);
        foreach (RaycastHit hit in rayhit)
        {  //���C�����������p�x
            if (hit.collider.gameObject.tag == "Scaffold" || hit.collider.gameObject.tag == "Jagged_Scaffold")
            {//����
                //0�x�Ȃ�TRUE��������
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
        {  //���C�����������p�x
            var hitrota = Quaternion.FromToRotation(Vector2.up, hit.normal);
            if (hit.collider.gameObject.tag == "Scaffold" || hit.collider.gameObject.tag == "Jagged_Scaffold")
            {//����
                //0�x�Ȃ�TRUE��������
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
    /// ���W���X�V����
    /// </summary>
    //void CollectionUpdate()
    //{
    //    int Collectio_num = 0;
    //    foreach (var obj in Collection_Obj)
    //    {
    //        //���ł��Ă����ꍇ
    //        if (obj == null)
    //        {
    //            Collectio_num++;
    //        }
    //    }
    //    //���W������ł��l�����Ă���ꍇ
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
    /// �����蔻��F����������
    /// </summary>
    /// <param name="collision">���������I�u�W�F�N�g</param>
    void OnCollisionEnter(Collision collision)
    {
        switch (collision.gameObject.tag)
        {
            case "Gear":
            case "Jagged_Scaffold":
            case "Scaffold":
                //�M�A�E����SE
                SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Bump_gear);//�ǉ�
                CollisionHouse(true, collision.gameObject);//�I�u�W�F�N�g���X�g�i�[�֐�
                break;
            case "Wall":
                //��SE
                rb.velocity = Vector3.zero;
                jump_State = Jump_State.DESCEND;
                SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Bump_wall);//�ǉ�
                break;
        }
    }

    /// <summary>
    /// �����蔻��F����������(Trigger)
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
    /// �����蔻��F���ꂽ��(Trigger)
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
                CollisionHouse(false, other.gameObject);//�I�u�W�F�N�g���X�g�폜�֐�
                //InputScript.Instance.SetGamePadVibrationStop();//�ǉ�
                break;
            case "Scaffold":
            case "Gear":
                CollisionHouse(false, other.gameObject);//�I�u�W�F�N�g���X�g�폜�֐�
                //InputScript.Instance.SetGamePadVibrationStop();//�ǉ�
                break;
        }
    }

    void Prevention_of_digging()
    {//�M�A�ƃv���C���[�̂߂荞�ݖh�~
        foreach (var gear in Col_Object)
        {
            if (gear != null && gear.tag == "Gear")
            {
                SphereCollider playercol = null, gearcol = null;
                //�v���C���[�Ƃ̋����𑪂�
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
                    {//�v���C���[���M�A�ɋ߂��̂Ńv���C���[�𓖍�����
                        //����
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
    /// ������E�����I�u�W�F�N�g�����X�g�Ɋi�[�E�폜����֐�
    /// </summary>
    /// <param name="flag">�i�[=true�A�폜=false</param>
    /// <param name="obj">�i�[�E�폜�������I�u�W�F�N�g</param>
    private void CollisionHouse(bool flag, GameObject obj)
    {
        //�i�[����
        if (flag)
        {
            var s = obj.GetComponent<ConnectionObject>();
            if (s != null)
            {//�e�I�u�W�F�N�g�擾
                var part = s.GetListObject();
                if (part != null)
                {
                    //�i�[�I�u�W�F�N�g�����邩�Ȃ������ׂ�
                    s = part.GetComponent<ConnectionObject>();
                    if (s != null)
                    {
                        foreach (var colobj in Col_Object)
                        {
                            if (s.SearchListObject(colobj))
                            {
                                //�i�[���Ȃ�
                                return;
                            }

                        }
                    }

                }
            }


            int cout = 0;
            //�I�u�W�F�N�g�������Ă��Ȃ������ׂĊi�[����
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
            //�����I�u�W�F�N�g���i�[����Ă��邩���ׂ�
            for (int i = 0; i < Col_Object.Length; i++)
                cout = Col_Object[i] != null ? cout + 1 : cout;

            DoubleCol_flag = cout >= Col_Object.Length;
            ClimbChanceflag = DoubleCol_flag ? true : ClimbChanceflag;
            //�����Ă��ꍇ
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
                Engagement_flag = true; //06/25�F�ǉ�
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
        //�폜����
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
            //�������Ă���I�u�W�F�N�g�����邩�ǂ������ׂ�
            int count = 0;
            for (int i = 0; i < Col_Object.Length; i++)
                count = Col_Object[i] != null ? count + 1 : count;
            //�������Ă���I�u�W�F�N�g��1�̈ȉ��̏ꍇ
            if (count < 2)
            {
                if (DoubleCol_flag)
                {
                    DoubleCol_flag = false;
                    AutoMoveG_flag = false;
                    rotateDirect = RotateDirect.NONE;
                }
                //�����������Ă��Ȃ��ꍇ
                if (count == 0)
                {
                    ClimbChanceflag = false;
                    rb.useGravity = true;
                    rb.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationX;
                    TerrainHit_flag = false;
                    Climb_flag = false;
                    Engagement_flag = false; //06/25�F�ǉ�
                }
            }
        }
    }

    /// <summary>
    /// ���X�V
    /// </summary>
    private void ShaftUpdate()
    {
        //�M�A�ƃv���C���[���߂荞�܂Ȃ��悤�ɂ���
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

        //���X�V����
        if (!Fall_flag && !Jump_flag)
        {
            //�P�ƐڐG��
            if (!DoubleCol_flag && Col_Object[0] != null)
            {
                //�M�A�̏ꍇ
                if (Col_Object[0].tag == "Gear")
                    Shaft_PG(Col_Object[0]);
                //����A���t������̏ꍇ
                else
                {
                    //����A���t������̏ꍇ
                    if (InputScript.Instance.GetGamePadLeftStickXTrigger(LeftStickXDirection.Left) || InputScript.Instance.GetGamePadLeftStickXTrigger(LeftStickXDirection.Right) ||
                        InputScript.Instance.GetKeyboardTrigger(KeyCode.A) || InputScript.Instance.GetKeyboardTrigger(KeyCode.D))
                    {
                        GetComponent<KamiwaseTestScript>().Engagenment(this.gameObject, Col_Object[0]);
                    }
                    Shaft_GP();
                }
            }
            //�����ڐG��
            else if (DoubleCol_flag)
            {
                if (Col_Object[0].tag == "Gear" && Col_Object[1].tag == "Gear")
                    Shaft_Double();
                else
                    Shaft_PGD();
            }
        }
        //�W�����v��
        if (Jump_flag)
        {
            //�v���C���[���ɕύX
            PRotate_flag = true;//�v���C���[���ύX
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
        }
    }

    /// <summary>
    /// ����ړ����̎��X�V����
    /// </summary>
    private void Shaft_GP()
    {
        //����ł̈ړ����̎�
        MovePattern = false;
        if (InputScript.Instance.GetGamePadLeftStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A) || InputScript.Instance.GetKeyboardPress(KeyCode.D))
        {
            //�v���C���[���ɕύX
            PRotate_flag = true;//�v���C���[���ύX
            GearMoveflag = false;
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
            rb.useGravity = false;
            rb.constraints = RigidbodyConstraints.FreezeRotation | RigidbodyConstraints.FreezePositionZ;
        }
    }

    /// <summary>
    /// �M�A�ړ����̎��X�V����
    /// </summary>
    private void Shaft_PG(GameObject obj)
    {
        //�M�A���̎�
        MovePattern = true;
        var rote = obj.GetComponent<GearRote>();
        GearTeeth = rote == null ? 12 : rote.GearTeeth;
        if (InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) && !Roll_flag)
        {//�E�X�e�B�b�N���͂��������ꍇ
            //�M�A�̏�ɓo��Ă��邩����ȊO���Ɖ�]�ł��Ȃ�
            //�p�x�𒲂ׂ�
            var vec = this.gameObject.transform.position - obj.transform.position;
            float angle = Vector2.Angle(Vector2.up, vec.normalized);
            //��̃I�u�W�F�N�g�ɓ������Ă��鎞���̕Е�������Ȃ���Ȃ��悤�ɂ���
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
            //�v���C���[���ɕύX
            if (!PRotate_flag)
            {
                GetComponent<KamiwaseTestScript>().Engagenment(this.gameObject, obj);
            }
            GearMoveflag = false;
            PRotate_flag = true;//�v���C���[���ύX
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
        }
        else
        {
            //�ړ��ł��邩���ׂ�
            var vec = this.gameObject.transform.position - obj.transform.position;
            float angle = Vector2.Angle(Vector2.up, vec.normalized);
            GearMoveflag = true;
            //�����M�A�ɕύX����
            PRotate_flag = false;//�M�A���ύX
            Vector3 PlayerPos = this.transform.position;
            Player_Center.transform.position = obj.transform.position;
            this.transform.position = PlayerPos;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
        }
    }

    /// <summary>
    /// �����ڐG���̏���(�����ړ�����)
    /// </summary>
    private void Shaft_Double()
    {
        int EndObj = Col_Object.Length - 1;
        //���������I�u�W�F�N�g�������m�F
        if (Col_Object[EndObj].tag == "Gear" && Col_Object[EndObj - 1].tag == "Gear")
        {
            //�M�A�ړ��ɕύX����
            MovePattern = true;
            PRotate_flag = false;
            GearMoveflag = true;
            Vector3 PlayerPos = this.transform.position;
            Player_Center.transform.position = Col_Object[EndObj].transform.position;
            this.transform.position = PlayerPos;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
            //�����ړ�������
            AutoMoveG_flag = true;
        }
    }

    /// <summary>
    /// �����̎��M�A�ړ�������ړ������߂čX�V����
    /// </summary>
    private void Shaft_PGD()
    {
        //�E�X�e�B�b�N����
        if (InputScript.Instance.GetGamePadRightStickX() != 0 || InputScript.Instance.GetKeyboardPress(KeyCode.RightArrow) || InputScript.Instance.GetKeyboardPress(KeyCode.LeftArrow))
        {
            //�M�A�Ɠ������Ă���ꍇ
            for (int i = 0; i < Col_Object.Length; i++)
            {
                if (Col_Object[i].tag == "Gear")
                {//�M�A���ɂ���
                    Shaft_PG(Col_Object[i]);
                    return;
                }
            }
        }

        //�������Ă���I�u�W�F�N�g�ǂ���Ŕ������邩���߂�
        GameObject kari = null;
        bool leftstickright = InputScript.Instance.GetGamePadLeftStickX() > 0 || InputScript.Instance.GetKeyboardPress(KeyCode.D);
        bool leftstickleft = InputScript.Instance.GetGamePadLeftStickX() < 0 || InputScript.Instance.GetKeyboardPress(KeyCode.A);

        //���X�e�B�b�N����
        if (leftstickright)
        {//�E�ړ�
            //�v���C���[���E�ɂ���I�u�W�F�N�g���������邩
            int count = 0;
            for (int i = 0; i < Col_Object.Length; i++)
            {
                count = this.transform.position.x < Col_Object[i].transform.position.x ? count + 1 : count;
            }

            if (count == 0)
            {//�ǂ�������ɂ���ꍇ
                //�������Ă���I�u�W�F�N�g�Ŕ�ׂď�ɂ���I�u�W�F�N�g�Ŏ������߂�
                kari = Col_Object[0].transform.position.y < Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
            else if (count == 1)
            {//1�����̏ꍇ
                for (int i = 0; i < Col_Object.Length; i++)
                {
                    kari = this.transform.position.x < Col_Object[i].transform.position.x ? Col_Object[i] : kari;
                }
            }
            else
            {//2�Ƃ��E�ɂ���ꍇ
             //�������Ă���I�u�W�F�N�g�Ŕ�ׂč����ɂ���I�u�W�F�N�g�Ŏ������߂�
                kari = Col_Object[0].transform.position.y > Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
        }
        else if (leftstickleft)
        {//���ړ�
         //�v���C���[��荶�ɂ���I�u�W�F�N�g���������邩
            int count = 0;
            for (int i = 0; i < Col_Object.Length; i++)
            {
                count = this.transform.position.x > Col_Object[i].transform.position.x ? count + 1 : count;
            }

            if (count == 0)
            {//�ǂ�����E�ɂ���ꍇ
             //�������Ă���I�u�W�F�N�g�Ŕ�ׂč����ɂ���I�u�W�F�N�g�Ŏ������߂�
                kari = Col_Object[0].transform.position.y < Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
            else if (count == 1)
            {//1�����̏ꍇ
                for (int i = 0; i < Col_Object.Length; i++)
                {
                    kari = this.transform.position.x > Col_Object[i].transform.position.x ? Col_Object[i] : kari;
                }
            }
            else
            {//2�Ƃ����ɂ���ꍇ
             //�������Ă���I�u�W�F�N�g�Ŕ�ׂĉE���ɂ���I�u�W�F�N�g�Ŏ������߂�
                kari = Col_Object[0].transform.position.y > Col_Object[1].transform.position.y ? Col_Object[0] : Col_Object[1];
            }
        }
        else
        {//�����Ȃ���
         //�v���C���[���ɕύX
            GearMoveflag = false;
            PRotate_flag = true;//�v���C���[���ύX
            Player_Center.transform.position = this.transform.position;
            this.transform.position = Player_Center.transform.position;
            rb.useGravity = true;
            rb.constraints = RigidbodyConstraints.FreezeAll;
        }

        if (kari != null)
        {
            if (kari.tag == "Gear")
            {//�M�A�̏ꍇ
                Shaft_PG(kari);
            }
            else
            {//����A���t������̏ꍇ
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
    /// �I�u�W�F�N�g�^�O���m�F�֐�
    /// </summary>
    /// <param name="obj">�m�F�������I�u�W�F�N�g</param>
    /// <param name="tag">�m�F�������^�O��</param>
    /// <param name="tag2">�m�F�������^�O��(�K�{�ł͂Ȃ�)</param>
    /// <param name="tag3">�m�F�������^�O��(�K�{�ł͂Ȃ�)</param>
    /// <returns>True=�m�F�������^�O���ƈ�v�����AFalse=�m�F�������^�O���ƈ�v���Ȃ�����</returns>
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
    /// Rigidbody�����֐�
    /// </summary>
    /// <param name="move">��������������(Position,Rotation,All,Free)</param>
    /// <param name="axis"><para>All�ȊO�F������������(X,Y,Z,XYZ,XY,YZ,All,Free)</para>All���F�����������ړ���(X,Y,Z,XYZ,XY,YZ,All,Free)</param>
    /// <param name="axis2"><para>All�ȊO�F�@�\���Ȃ�(NONE����)</para>All���F������������]��(X,Y,Z,XYZ,XY,YZ,All,Free)</param>
    private void Rigidbody_Constraints(string move, string axis, string axis2 = "NONE")
    {
        //�ړ��E��]ALL����
        if (move == "All" && axis == "All")
        {
            rb.constraints = RigidbodyConstraints.FreezeAll;
            return;
        }
        //�ړ��E��]ALL������
        else if (move == "Free" || axis == "Free")
        {
            rb.constraints = RigidbodyConstraints.None;
            return;
        }

        //�ړ��E��]����
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
        //�ړ�����
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
                Debug.LogError("�����������ړ������w�肳��Ă��܂���");
            return;
        }
        //��]����
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
                Debug.LogError("������������]�����w�肳��Ă��܂���");

        }
        //���̂��s�K��
        else
        {
            Debug.LogError("�������������̖̂��̂��w�肳��Ă��܂���");
        }
    }
}