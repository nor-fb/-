#pragma once
#include "GameObject.h"
#include "SupervisionScene.h"
#include "StageSelect.h"
class Rogo :
    public SupervisionScene
{
public:
    Rogo();
    ~Rogo() {
        delete mTeamRogo;
        delete mBackGround;
    }
    void Initialize();
    void Update();
    void Draw();
    void Release();
private:
    Image* mTeamRogo;
    Image* mBackGround;
    std::vector<GameObject*>mRogoScene;
private:
    float Count;
};

