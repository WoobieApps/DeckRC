set(SOURCES
    main.cpp
    Logger.cpp
    InputMgr.cpp
    App.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${wxWidgets_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)