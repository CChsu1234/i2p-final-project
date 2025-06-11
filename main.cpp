// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.hpp"
#include "Scene/FinalStartScene.hpp"
#include "Scene/FinalSelectScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/ScoreBoardScene.hpp"
#include "Scene/FinalScoreBoardScene.hpp"
#include "Scene/RecordScene.hpp"
#include "Scene/TestScene.hpp"
#include "Scene/LoginScene.hpp"
#include "Scene/EndScene.hpp"
#include "File/Settings.hpp"

int main(int argc, char **argv) {

	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // DONE HACKATHON-2 (2/3): Register Scenes here
    game.AddNewScene("test", new TestScene());
    game.AddNewScene("stage-select", new StageSelectScene());
    game.AddNewScene("start", new StartScene());
    game.AddNewScene("settings", new SettingsScene());
    game.AddNewScene("scoreboard", new ScoreBoardScene());
    game.AddNewScene("finalscoreboard", new FinalScoreBoardScene());
    game.AddNewScene("login", new LoginScene());
    game.AddNewScene("record", new RecordScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
    game.AddNewScene("FinalEnd", new EndScene());
    game.AddNewScene("finalStart", new FinalStartScene());
    game.AddNewScene("finalSelect", new FinalSelectScene());

    // DONE HACKATHON-1 (1/1): Change the start scene
    Settings settings;
	game.Start("finalStart", 60, 1600, 832);

    settings.Save();
	return 0;
}
