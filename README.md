# GuitarAssistantApp

Приложение для гитаристов: транспонирование аккордов, метроном, тюнер. Написано на C++ с использованием Qt5.

## Системные требования

- **Операционная система**: Linux
- **Компилятор**: g++ с поддержкой C++17
- **Qt**: версия 5.15 или выше (модули: core, widgets, multimedia, network)
- **GStreamer**: для воспроизведения звука метронома (плагины base, good, bad, ugly, libav)
- **Git** (для клонирования репозитория)

## Установка зависимостей

### 1. Qt5 и необходимые модули

Выполните в терминале:

```bash
sudo apt update
sudo apt install qtbase5-dev qtchooser qtbase5-dev-tools qttools5-dev-tools build-essential
sudo apt install qtmultimedia5-dev 
```

### 2. Плагины GStreamer для воспроизведения MP3

```bash
sudo apt install gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
                 gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly \
                 gstreamer1.0-libav libgstreamer1.0-0
sudo apt install libqt5multimedia5-plugins   # плагины Qt Multimedia
```

### 3. Дополнительно (опционально)

Если планируете работать в Visual Studio Code, установите расширения:

- C/C++ 
- Qt C++ 

## Сборка проекта

### Клонирование репозитория

```bash
git clone https://github.com/bahmatok/GuitarAssistantApp.git
cd GuitarAssistantApp
```

### Сборка через qmake и make

```bash
qmake GuitarAssistantApp.pro  
make -j$(nproc)
```

После успешной сборки появится исполняемый файл `GuitarAssistantApp`.

## Запуск

Просто выполните:

```bash
./GuitarAssistantApp
```

При первом запуске в папке с программой создастся файл `settings.txt` для хранения настроек (громкость, BPM, последние аккорды). Если файл пуст, программа сообщит об этом, но продолжит работу с настройками по умолчанию.

## Работа в Visual Studio Code

### Настройка IntelliSense для Qt

Создайте в корне проекта папку `.vscode` и файл `c_cpp_properties.json`:

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/x86_64-linux-gnu/qt5",
                "/usr/include/x86_64-linux-gnu/qt5/QtCore",
                "/usr/include/x86_64-linux-gnu/qt5/QtGui",
                "/usr/include/x86_64-linux-gnu/qt5/QtWidgets",
                "/usr/include/x86_64-linux-gnu/qt5/QtMultimedia"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```

### Задачи для сборки

Можно настроить tasks.json для автоматизации:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "qmake",
            "type": "shell",
            "command": "qmake",
            "args": ["GuitarAssistantApp.pro"],
            "group": "build",
            "problemMatcher": []
        },
        {
            "label": "make",
            "type": "shell",
            "command": "make",
            "args": [],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "dependsOn": ["qmake"],
            "problemMatcher": ["$gcc"]
        }
    ]
}
```

Теперь можно собирать проект через `Ctrl+Shift+B`.