add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}

        ${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/spaceship/Spaceship.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/spaceship/Spaceship.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerManager.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerSpaceship.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerSpaceship.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/player/Player.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/player/Player.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Shooter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Shooter.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/BulletShooter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/BulletShooter.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/ThreeWayShooter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/ThreeWayShooter.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/FrontalWiperShooter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/FrontalWiperShooter.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Bullet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Bullet.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/HealthComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/HealthComponent.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Explosion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/EnemySpaceship.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/EnemySpaceship.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/Vanguard.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/Vanguard.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/TwinBlade.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/TwinBlade.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/Hexagon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/Hexagon.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/UFO.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/UFO.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/VanguardStage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/VanguardStage.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/TwinBladeStage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/TwinBladeStage.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/HexagonStage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/HexagonStage.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/UFOStage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/UFOStage.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/level/GameLevelOne.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/level/GameLevelOne.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/reward/Reward.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/reward/Reward.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/GameplayHUD.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/GameplayHUD.cpp
    )

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
    add_custom_command (TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:${LIB_NAME}>
    $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

CopyLibDirToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
        TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_SRC_DIR}
        $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
        "Config.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)
