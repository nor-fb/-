using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConnectionObject : MonoBehaviour
{

    //子オブジェクトで側面等なのか
    public bool Connection = false;
    public GameObject ParentObject;

    //自分が親オブジェクト否か
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
                    Debug.LogError("GameObject:" + this.gameObject + "\nParentObjectにConnectionObject.csがついていません");
            }
            else
                Debug.LogError("Object:" + this.gameObject + "\n ParentObjectを設定してください");
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
            //親オブジェクトを返す
            return ParentObject;
        }
        else if (ParentFlg)
        {
            //自分を返す
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
