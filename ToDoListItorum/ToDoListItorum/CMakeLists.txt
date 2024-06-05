# CMakeList.txt: проект CMake для ToDoListItorum; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# !!!change directory Qt6, for example: QT6_DIR = C:\Qt\6.6.0\msvc2019_64\lib\cmake!!!
set(QT6_DIR_CMAKE "$ENV{QT6_PATH}")
set(CMAKE_PREFIX_PATH "${QT6_DIR_CMAKE}")

set(QT_PLUGINS_DIR ${QT6_DIR_CMAKE}/../../plugins)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Xml)
qt_add_resources("resource/icons.qrc" " resource/styled.qrc")
# Добавьте источник в исполняемый файл этого проекта.
add_executable (ToDoListItorum "main.cpp"  
"ToDoApp.cpp" 
"ToDoApp.h" 
"ListViewDelegate.h" 
"ListViewDelegate.cpp" 
"ListViewDelegatePrivate.h"   
"NotesListView.h" 
"NotesListView.cpp" 
"NotesListModel.h" 
"NotesListModel.cpp" 
"TaskPage.h" 
"TaskPage.cpp" 
"TaskListView.h" 
"TaskListView.cpp" 
"TaskListModel.h" 
"TaskListModel.cpp"   
"WriteXMLNote.h" 
"WriteXMLNote.cpp" 
"TaskNoteItem.h"
"resource/icons.qrc"
"resource/styled.qrc")



target_link_libraries(ToDoListItorum PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Xml)

add_custom_command(TARGET ToDoListItorum POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${QT_PLUGINS_DIR}/platforms
                   $<TARGET_FILE_DIR:ToDoListItorum>/platforms)
add_custom_command(TARGET ToDoListItorum POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Core> $<TARGET_FILE_DIR:ToDoListItorum>)
add_custom_command(TARGET ToDoListItorum POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Gui> $<TARGET_FILE_DIR:ToDoListItorum>)
add_custom_command(TARGET ToDoListItorum POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Widgets> $<TARGET_FILE_DIR:ToDoListItorum>)
add_custom_command(TARGET ToDoListItorum POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   $<TARGET_FILE:Qt6::Xml> $<TARGET_FILE_DIR:ToDoListItorum>)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ToDoListItorum PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
