#ifndef GAME_H
#define GAME_H

#include <QGLWidget>
#include <QWidget>
#include <iostream>
#include <QLineEdit>
#include "drawer.h"
#include "Chip.h"
#include "Manager.h"

class Game : public QGLWidget
{
    Q_OBJECT

public:
    enum class State {
        MENU,
        SETTINGS_PLAYERS,
        PLAY,
        EXIT
    };

    enum class Menu {
        START = -1,
        PLAY,
        SETTINGS_PLAYERS,
        EXIT,
        END
    };

    enum class MenuSettings {
        START = -1,
        PLAYER1,    //white
        PLAYER2,    //black
        BACK,
        END
    };

    enum class Settings {
        START = -1,
        RACE,
        NAME,
        END
    };

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    int getVectorMenuSize() { return vMenu.size(); }
    int menuStateToInt(const Game::Menu &Menu);
    int menuSettingsStateToInt(const Game::MenuSettings &Menu);
    int SettingsStateToInt(const Game::Settings &Menu);
    Game::Menu getCurrentMenu() { return currentMenu; }
    QString getStringMenu(int i) { return vMenu[i].second.c_str(); }


    void initializeGL()                 override;
    void resizeGL(int, int)             override;
    void paintGL()                      override;

    void keyReleaseEvent(QKeyEvent *)   override;

private:
    void processing();
    void draw();

    void draw_menu();
    void draw_settings_players();
    void draw_play();

    void key_released_menu(int);
    void key_released_settings_players(QKeyEvent*);
    void key_released_play(int);

private:
    State state{State::MENU};
    Menu currentMenu = Menu::SETTINGS_PLAYERS;
    std::vector<std::pair<Menu, std::string>> vMenu;
    std::vector<std::pair<Settings, std::string>> vSettings;

    bool inputNameWhite = false, inputNameBlack = false;
    int w = 800, h = 600;

    drawer dr;

    Chip** chips;
    bool isBlack = true;
    int ilast, jlast, icur{0}, jcur{0};
    int whiteChips{0}, blackChips{0};
    int numMessage = 0;

    QString nameBlack{"Sasuke"}, nameWhite{"Naruto"};
    bool humanWhite = true, humanBlack = true;

    MenuSettings activeMenuSettings = MenuSettings::START;
    Settings activeSetting = Settings::START;
    bool isChoosen = false;

    bool activeBack = false;

    bool shouldRestart = false;
    bool begin = true;
    Manager m;
    Chip winner = Chip::empty;
    bool gameOver = false;;
};

#endif // GAME_H
