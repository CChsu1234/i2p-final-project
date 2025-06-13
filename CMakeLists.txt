cmake_minimum_required(VERSION 3.27)
project(2025_I2P2_TowerDefense)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Resource)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2025_I2P2_TowerDefense

    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    Engine/LightShadow.cpp
    Engine/LightShadow.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    Engine/IObject3D.cpp
    Engine/IObject3D.hpp
    Engine/Triangle3D.cpp
    Engine/Triangle3D.hpp
    Engine/ModelView.cpp
    Engine/ModelView.hpp
    Engine/Transform.cpp
    Engine/Transform.hpp
    Engine/MouseKeyboard.cpp
    Engine/MouseKeyboard.hpp

    File/User.cpp
    File/User.hpp
  
    
    Scene/FinalStartScene.cpp
    Scene/FinalStartScene.hpp
    Scene/SettingsScene.cpp
    Scene/SettingsScene.hpp
    Scene/FinalScoreBoardScene.cpp
    Scene/FinalScoreBoardScene.hpp
    Scene/TestScene.cpp
    Scene/TestScene.hpp
    Scene/LoginScene.cpp
    Scene/LoginScene.hpp
    Scene/SurvivalScene.cpp
    Scene/SurvivalScene.hpp
    Scene/EndTwoScene.cpp
    Scene/EndTwoScene.hpp
    Scene/EndScene.cpp
    Scene/EndScene.hpp
    Scene/FinalSelectScene.cpp
    Scene/FinalSelectScene.hpp
    
    UI/Animation/CubeBackGround.cpp
    UI/Animation/CubeBackGround.hpp

    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp
    UI/Component/TextEditor.cpp
    UI/Component/TextEditor.hpp
    UI/Component/TestObject3D.cpp
    UI/Component/Testobject3D.hpp
    UI/Component/TestClick3D.cpp
    UI/Component/TestClick3D.hpp
    UI/Component/CrossHair.cpp
    UI/Component/CrossHair.hpp
    UI/Component/Userinfo.cpp
    UI/Component/UserInfo.hpp
    UI/Component/RotatingCube.cpp
    UI/Component/RotatingCube.hpp
    UI/Component/LineChart.cpp
    UI/Component/LineChart.hpp
 
    main.cpp
)

IF (WIN32)
    target_include_directories(2025_I2P2_TowerDefense PUBLIC C:/allegro/include)
    target_link_directories(2025_I2P2_TowerDefense PUBLIC C:/allegro/lib)
    target_compile_options(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2025_I2P2_TowerDefense liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2025_I2P2_TowerDefense PUBLIC lib)
    target_include_directories(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2025_I2P2_TowerDefense ${ALLEGRO5_LIBRARIES})
    target_link_directories(2025_I2P2_TowerDefense PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
ENDIF()
