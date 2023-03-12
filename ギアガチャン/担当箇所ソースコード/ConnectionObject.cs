using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConnectionObject : MonoBehaviour
{

    //�q�I�u�W�F�N�g�ő��ʓ��Ȃ̂�
    public bool Connection = false;
    public GameObject ParentObject;

    //�������e�I�u�W�F�N�g�ۂ�
    public bool ParentFlg = false;
    private List<GameObject> EdgeObject=new List<GameObject>();
    // Start is called before the first frame update

    private void Start()
    {
        if (Connection)
        {
            if (ParentObject != null)
            {
                var s = ParentObject.GetComponent<ConnectionObject>();
                if (s != null)
                    s.AddList(this.gameObject);
                else
                    Debug.LogError("GameObject:" + this.gameObject + "\nParentObject��ConnectionObject.cs�����Ă��܂���");
            }
            else
                Debug.LogError("Object:" + this.gameObject + "\n ParentObject��ݒ肵�Ă�������");
        }
        else if(ParentFlg)
        {
            EdgeObject.Add(this.gameObject);
        }
    }


    public GameObject GetListObject()
    {
        if (Connection)
        {
            //�e�I�u�W�F�N�g��Ԃ�
            return ParentObject;
        }
        else if (ParentFlg)
        {
            //������Ԃ�
            return this.gameObject;
        }
        return null;
    }


    public bool SearchListObject(GameObject obj)
    {
        if (obj != null)
        {
            foreach (var listobj in EdgeObject)
            {
                if (listobj == obj)
                    return true;
            }
        }

        return false;
    }


    public void AddList(GameObject obj)
    {
        EdgeObject.Add(obj);
    }
}
