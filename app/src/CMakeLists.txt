set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)