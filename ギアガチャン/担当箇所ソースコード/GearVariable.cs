using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GearVariable : MonoBehaviour
{//ギアのシーン内共有変数
    [HideInInspector]
    public bool MoveFlg;//全体で回転できるか;
    List<GameObject> movegear = new List<GameObject>();
    void Start()
    {//変数の初期化
        MoveFlg = false;
    }

    /// <summary>
    /// ギア回転処理
    /// </summary>
    public void Rote()
    {
        if (!MoveFlg)
        {//回転出来る
            foreach (var obj in movegear)
            {
                if (Search_BigGear())
                {//大きなギアがある
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage03);
                }
                else
                {//普通のギア
                    SoundDirectorScript.Instance.PlaySE(SoundDirectorScript.SEType.Engage02);
                }
                //回転処理
                var gearscript = obj.GetComponent<GearRote>();
                if(gearscript!=null)
                    gearscript.MoveRotation();

                //スライド移動処理
                var scaffoldscript = obj.GetComponent<ScaffoldMove>();
                if (scaffoldscript != null)
                    scaffoldscript.SlideMove();
            }
        }
        else
        {
            foreach (var obj in movegear)
            {//リセット処理
                var gearscript = obj.GetComponent<GearRote>();
                if(gearscript!=null)
                    gearscript.SetFlg();
            }
        }
        movegear.Clear();//リストを初期化する
        MoveFlg = false;//フラグを初期化する
    }

    public bool Search_BigGear()
    {
        //動いているギアのリストのギアの子オブジェクトのどれか一つに大きいギアがあるか探してその結果を返す
        foreach (var obj in movegear)
        {
            var child = obj.GetComponentsInChildren<Transform>();
            foreach (var chid in child)
            {
                if (chid.gameObject.tag == "BigGear")//タグの名前の決め、それを調べる
                {
                    return true;
                }
            }
        }
        return false;
    }

    /// <summary>
    /// MoveGear格納数関数
    /// </summary>
    /// <returns></returns>
    public int Search_GearNum()
    {
        return movegear.Count;
    }

    /// <summary>
    /// リストに追加する
    /// </summary>
    /// <param name="rote">追加するオブジェクト</param>
    public void SetListGear(GameObject rote)
    {
        movegear.Add(rote);
    }
}
