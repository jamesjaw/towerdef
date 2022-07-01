#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "StageSelectScene.hpp"

void StageSelectScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 1", "pirulen.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 2", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    //add setting button

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 330, halfH * 3 / 2 + 100, 400, 100);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Setting", "pirulen.ttf", 48, halfW + 530, halfH * 3 / 2+150, 0, 0, 0, 255, 0.5, 0.5));

    // TODO 1 (3/3): Move the sliderBGM, sliderSFX to the setting Scene and make sure the background music will be played
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void StageSelectScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void StageSelectScene::PlayOnClick(int stage) {
    //if stage == 3 mean click on setting button
    if(stage==3) Engine::GameEngine::GetInstance().ChangeScene("setting");
    else{
        PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
        scene->MapId = stage;
        Engine::GameEngine::GetInstance().ChangeScene("play");
    }
}

