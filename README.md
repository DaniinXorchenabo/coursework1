# Coursework 1

Представляет из себя консольное приложение с псевдографикой (`ascii`-символы).
Предназначено для рисования фигур по точкам.
Координаты фигур задаются в коде. 
Фигуры перемещаются и поворачиваются со случайной скоростью.
Пользователь может (если это поддерживает консоль) перетаскивать фигуру мышкой.
При наложении одной фигуры на другую происходит образование новой фигуры.

## Run

### Install dependencies

Для запуска приложения необходимо предварительно установить `Python >= 3.6`, добавить путь к интерпретатору `Python` в переменную среды `PATH`,
установить пакетный менеджер `pip` и выполнить установку зависимостей:

```bash
cd coursework1/production
pip install -r requirements.txt
```

### Run app

После чего можно запустить приложение

```bash
.../coursework1/production> main.exe
```

## Building

### Build app:

```bash
cd coursework1
builder.BAT
```

### Build DLL library:

*You need in python (and pip) installing*

```bash
cd coursework1/create_dll_lib
pip install -r requirements.txt
python dll_generator.py
```


