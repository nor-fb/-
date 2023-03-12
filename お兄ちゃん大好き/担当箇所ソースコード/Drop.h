#pragma once
#include"GameObject.h"
#include"Cannon.h"

/// <summary>
/// ドロップクラス
/// </summary>
class Drop :
    public GameObject
{
public:
    Drop() = default;
    ~Drop() = default;
    void Update();
    void Distance_Calculation(Float3,Float3);
protected:
    const float Specified_Frame = 60;
    Float3 Target_Distance;

    Float3 score_movedis;
    Float3 remaining_movedis;
    Float3 MoveSpeed;
    Float3 ChangeSize;
    bool Target_FlgX = false;
    bool Target_FlgY = false;
};

/// <summary>
/// 弾(ドロップ版)
/// </summary>
class DropBullet :
    public Drop
{
public:
    DropBullet();
    void Update();
    void Set_Model(std::string model) { this->model.emplace_back(model); }
    bool Get_Active(){ return Active; }
    bool Get_BulletCount()const { return CountBullet; }
    bool Get_HpHeal() { return Hpheal; }
    bool Get_HpHealType() { return HealType; }
    void Set_BulletCount() { CountBullet = false; Active = false; }
    void Set_BulletHeal() { Hpheal = false; HealType = false; }
    void Set_TYPE(eCANNON_TYPE type);
    void Set_Active(Float3 pos);
    void Set_Active(Float3 pos, bool hp);
    void Set_Active(bool flg) { Active = flg; }
    eCANNON_TYPE Get_TYPE() const { return Type; }
private:
    std::vector<std::string> model;
    eCANNON_TYPE Type;
    bool Active = false;
    bool HealType = false;
    bool Hpheal = false;
    bool CountBullet = false;
};

/// <summary>
/// スコア(ドロップ版)
/// </summary>
class MagicStone :
    public Drop
{
public:
    MagicStone();
    void Initialize();
    void Set_Active();
    void Set_Active(Float3 pos);
    void Set_Active(Float3 pos, Float3 dis);
    void Update();
    void Set_Model(std::string model) { mModelData.mSRV = model; }
    bool Get_Active() const { return Active; }
    bool Get_Count()const { return CountScore; }
    void Set_Count() { CountScore = false; }

private:
    float TimeCount;
    bool CountScore = false;
    bool Active = false;
    bool flg;
};


class Bomb :public Drop{
public:
    Bomb();
    void Initialize();
    void Update();
    void Set_Active(Float3 pos);//座標を決め、アクティブにする
    void Draw();
    void Set_Explosion(int num);
    bool Get_Active() { return Active; }
private:
    bool effect;
    bool Active;
    int BreakNumber;
    std::vector<std::string> TexDate;
    Animator anim[2];
    int animnum;
};