// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/FinalStartScene.hpp"
#include "Scene/FinalSelectScene.hpp"
#include "Scene/SettingsScene.hpp"
#include "Scene/SurvivalScene.hpp"
#include "Scene/FinalScoreBoardScene.hpp"
#include "Scene/TestScene.hpp"
#include "Scene/LoginScene.hpp"
#include "Scene/EndScene.hpp"
#include "Scene/EndTwoScene.hpp"
#include "Scene/WaitScene.hpp"
#include "Scene/MultiPlayer.hpp"
// #include "File/Settings.hpp"

int main(int argc, char **argv) {
    if (enet_initialize() != 0) {
        std::cout << "An error occurred while initializing ENet." << std::endl;
    } else {
        std::cout << "initialize success!" << std::endl;
    }
    atexit(enet_deinitialize);

	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // DONE HACKATHON-2 (2/3): Register Scenes here
    /*
    game.AddNewScene("stage-select", new StageSelectScene());
    game.AddNewScene("start", new StartScene());
    game.AddNewScene("scoreboard", new ScoreBoardScene());
    game.AddNewScene("record", new RecordScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
    */
    
    game.AddNewScene("test", new TestScene());
    game.AddNewScene("settings", new SettingsScene());
    game.AddNewScene("finalscoreboard", new FinalScoreBoardScene());
    game.AddNewScene("login", new LoginScene());
    game.AddNewScene("FinalEnd", new EndScene());
    game.AddNewScene("finalStart", new FinalStartScene());
    game.AddNewScene("finalSelect", new FinalSelectScene());
    game.AddNewScene("survival", new SurvivalScene());
    game.AddNewScene("finalendtwo", new EndTwoScene());
    game.AddNewScene("multiplayer", new MultiPlayer());
    game.AddNewScene("wait", new WaitScene());

    // DONE HACKATHON-1 (1/1): Change the start scene
    // ettings settings;
	game.Start("wait", 60, 1600, 832);

	return 0;
}
