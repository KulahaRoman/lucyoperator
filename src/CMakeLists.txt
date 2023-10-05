cmake_minimum_required(VERSION 3.15)

project(lucyoperator)

set(LUCYOPERATOR_SRC 
			# Main
			${PROJECT_NAME}/main.cpp

			# Operator
			${PROJECT_NAME}/modules/operator/operator.cpp
			${PROJECT_NAME}/modules/operator/runnableview.cpp
			${PROJECT_NAME}/modules/operator/maincontroller.cpp
			${PROJECT_NAME}/modules/operator/mainview.cpp
			${PROJECT_NAME}/modules/operator/mainwindow.cpp
			${PROJECT_NAME}/modules/operator/guiengine.cpp
			${PROJECT_NAME}/modules/operator/targetpanel.cpp
			${PROJECT_NAME}/modules/operator/targetshandler.cpp
			${PROJECT_NAME}/modules/operator/operatordispatcher.cpp
			${PROJECT_NAME}/modules/operator/models/servercredentials.cpp
			${PROJECT_NAME}/modules/operator/models/targetslist.cpp
)

if(WIN32) 
	set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/../rsrc/appicon.rc")
endif()

qt_add_resources(LUCYOPERATOR_SRC ../rsrc/images.qrc)

add_executable(${PROJECT_NAME} ${LUCYOPERATOR_SRC} ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE lucycore)
target_link_libraries(${PROJECT_NAME} PRIVATE lucynet)

target_compile_definitions(lucynet PRIVATE -DOPERATOR_MACHINE)
target_compile_definitions(${PROJECT_NAME} PRIVATE 
										-D_WIN32_WINNT=0x0601 
										-D_UNICODE 
										-DUNICODE 
										-D_CRT_SECURE_NO_WARNINGS
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS ${PROJECT_NAME} DESTINATION ${LUCYOPERATOR_INSTALL_BIN})