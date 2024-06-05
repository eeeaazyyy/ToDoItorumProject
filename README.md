# **Сборка**
### **Этапы сборки**
1) **Настройка CMakeList.txt в папке ToDoListItorumProject\ToDoListItorum\ToDoListItorum**
   ```C++
   set(QT6_DIR_CMAKE "$ENV{QT6_PATH}")
   ```
   **Вместо** ```"$ENV{QT6_PATH}"``` **укажите путь к Qt\{version}\{build_system}\lib\cmake, например: ```set(QT6_DIR_CMAKE "C:\Qt\6.6.0\msvc2019_64\lib\cmake")```** 
2) **Сборка проекта**
   **перейти в папку проекта ```ToDoListItorumProject``` и прописать в командной строке следующее:** 
```cmd
cd ToDoListItorum
mkdir build
cmake ..
cmake --build .
```
