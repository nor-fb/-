using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GearVariable : MonoBehaviour
{//�M�A�̃V�[�������L�ϐ�
    [HideInInspector]
    public bool MoveFlg;//�S�̂ŉ�]�ł��邩;
    List<GameObject> movegear = new List<GameObject>();
    void Start()
    {//�ϐ��̏�����
        MoveFlg = false;
    }

    /// <summary>
    /// �M�A��]����
    /// </summary>
    public void Rote()
    {
        if (!MoveFlg)
        {//��]�o����
            foreach (var obj in movegear)
            {
                if (Search_BigGear())
                {//�傫�ȃM�A������
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage03);
                }
                else
                {//���ʂ̃M�A
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage02);
                }
                //��]����
                var gearscript = obj.GetComponent<GearRote>();
                if(gearscript!=null)
                    gearscript.MoveRotation();

                //�X���C�h�ړ�����
                var scaffoldscript = obj.GetComponent<ScaffoldMove>();
                if (scaffoldscript != null)
                    scaffoldscript.SlideMove();
            }
        }
        else
        {
            foreach (var obj in movegear)
            {//���Z�b�g����
                var gearscript = obj.GetComponent<GearRote>();
                if(gearscript!=null)
                    gearscript.SetFlg();
            }
        }
        movegear.Clear();//���X�g������������
        MoveFlg = false;//�t���O������������
    }

    public bool Search_BigGear()
    {
        //�����Ă���M�A�̃��X�g�̃M�A�̎q�I�u�W�F�N�g�̂ǂꂩ��ɑ傫���M�A�����邩�T���Ă��̌��ʂ�Ԃ�
        foreach (var obj in movegear)
        {
            var child = obj.GetComponentsInChildren<Transform>();
            foreach (var chid in child)
            {
                if (chid.gameObject.tag == "BigGear")//�^�O�̖��O�̌��߁A����𒲂ׂ�
                {
                    return true;
                }
            }
        }
        return false;
    }

    /// <summary>
    /// MoveGear�i�[���֐�
    /// </summary>
    /// <returns></returns>
    public int Search_GearNum()
    {
        return movegear.Count;
    }

    /// <summary>
    /// ���X�g�ɒǉ�����
    /// </summary>
    /// <param name="rote">�ǉ�����I�u�W�F�N�g</param>
    public void SetListGear(GameObject rote)
    {
        movegear.Add(rote);
    }
}
