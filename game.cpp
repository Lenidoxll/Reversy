#include "game.h"
#include <QKeyEvent>
#include <QDebug>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Extra Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Game::Menu operator++(Game::Menu &menu) {
    menu = Game::Menu(int(menu) + 1);
    if (menu == Game::Menu::END) {
        menu = Game::Menu(int(menu) - 1);
    }
    return menu;
}

Game::Menu operator--(Game::Menu &menu) {
    menu = Game::Menu(int(menu) - 1);
    if (menu == Game::Menu::START) {
        menu = Game::Menu(int(menu) + 1);
    }
    return menu;
}

Game::Settings operator++(Game::Settings &menu) {
    menu = Game::Settings(int(menu) + 1);
    if (menu == Game::Settings::END) {
        menu = Game::Settings(int(menu) - 1);
    }
    return menu;
}

Game::Settings operator--(Game::Settings &menu) {
    menu = Game::Settings(int(menu) - 1);
    if (menu == Game::Settings::START) {
        menu = Game::Settings(int(menu) + 1);
    }
    return menu;
}

Game::MenuSettings operator++(Game::MenuSettings &menu) {
    menu = Game::MenuSettings(int(menu) + 1);
    if (menu == Game::MenuSettings::END) {
        menu = Game::MenuSettings(int(menu) - 1);
    }
    return menu;
}

Game::MenuSettings operator--(Game::MenuSettings &menu) {
    menu = Game::MenuSettings(int(menu) - 1);
    if (menu == Game::MenuSettings::START) {
        menu = Game::MenuSettings(int(menu) + 1);
    }
    return menu;
}

int Game::menuStateToInt(const Game::Menu &Menu) {
    switch(Menu) {
    case Game::Menu::START:             return (int)Game::Menu::START;
    case Game::Menu::SETTINGS_PLAYERS:  return (int)Game::Menu::SETTINGS_PLAYERS;
    case Game::Menu::PLAY:              return (int)Game::Menu::PLAY;
    case Game::Menu::EXIT:              return (int)Game::Menu::EXIT;
    case Game::Menu::END:               return (int)Game::Menu::END;
    }
    return -1;
}

int Game::menuSettingsStateToInt(const Game::MenuSettings &Menu) {
    switch(Menu) {
    case Game::MenuSettings::START:     return (int)Game::MenuSettings::START;
    case Game::MenuSettings::PLAYER1:   return (int)Game::MenuSettings::PLAYER1;
    case Game::MenuSettings::PLAYER2:   return (int)Game::MenuSettings::PLAYER2;
    case Game::MenuSettings::BACK:      return (int)Game::MenuSettings::BACK;
    case Game::MenuSettings::END:       return (int)Game::MenuSettings::END;
    }
    return -1;
}

int Game::SettingsStateToInt(const Game::Settings &Menu) {
    switch(Menu) {
    case Game::Settings::START: return (int)Game::Settings::START;
    case Game::Settings::RACE:  return (int)Game::Settings::RACE;
    case Game::Settings::NAME:  return (int)Game::Settings::NAME;
    case Game::Settings::END:   return (int)Game::Settings::END;
    }
    return -1;
}

Game::State menuToState(const Game::Menu &menu) {
    switch (menu) {
    case Game::Menu::START:
    case Game::Menu::END:               return Game::State::MENU;
    case Game::Menu::SETTINGS_PLAYERS:  return Game::State::SETTINGS_PLAYERS;
    case Game::Menu::PLAY:              return Game::State::PLAY;
    case Game::Menu::EXIT:              return Game::State::EXIT;
    }
    return Game::State::MENU;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Game~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Game::Game(QWidget *parent) : QGLWidget(parent)
{

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setFixedSize(w, h);

    vMenu.push_back({Menu::PLAY,                "Play"});
    vMenu.push_back({Menu::SETTINGS_PLAYERS,    "Settings players"});
    vMenu.push_back({Menu::EXIT,                "Exit"});

    m.init(nameWhite.toStdString(), nameBlack.toStdString(), humanWhite, humanBlack);

    chips = new Chip*[8];
    for (int i = 0; i < 8; i++) {
        chips[i] = new Chip[8];
        for (int j = 0; j < 8; j++) {
            chips[i][j] = Chip::empty;
        }
    }
}

Game::~Game()
{
    for (int i = 0; i < 8; i++)
        delete[] chips[i];
    delete[] chips;
}

void Game::initializeGL()
{
    glOrtho(0, w, h, 0, 0, 1);  //инициализируем окно
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);    //подключаем текстурки

    dr.setGame(this);
}

void Game::resizeGL(int w, int h)
{
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glOrtho(0, w, h, 0, 0, 1);
}

void Game::paintGL()
{
    //очищаем экран
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglClearColor(Qt::darkCyan);
    processing();
    draw();
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    switch(state) {
    case State::MENU: {
        key_released_menu(e->key());
        break;
    } case State::PLAY: {
        key_released_play(e->key());
        break;
    } case State::SETTINGS_PLAYERS: {
        key_released_settings_players(e);
        break;
    } case State::EXIT: {
        break;
    }
    }
}

void Game::processing()
{
    switch(state) {
    case State::MENU: {
        break;
    } case State::PLAY: {
            whiteChips = 0;
            blackChips = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (m.getChip(i, j) == Chip::black)
                        blackChips++;
                    else if (m.getChip(i, j) == Chip::white)
                        whiteChips++;
                }
            }

        break;
    } case State::SETTINGS_PLAYERS: {
        if (shouldRestart) {
            m.restartGame(nameWhite.toStdString(), nameBlack.toStdString(), humanWhite, humanBlack);
            begin = true;
        }
        break;
    } case State::EXIT: {
        close();
        break;
    }
    }
}

void Game::draw()
{
    switch(state) {
    case State::MENU: {
        draw_menu();
        break;
    } case State::PLAY: {
        draw_play();
        break;
    } case State::SETTINGS_PLAYERS: {
        draw_settings_players();
        break;
    } case State::EXIT: {
        break;
    }
    }
}

void Game::draw_menu()
{
    static auto appW = w / 2.f;
    static auto appH = h / 3.f;

    static auto font = QFont("Sans", 25);
    static auto font_selected = QFont("Sans", 30);
    font_selected.setBold(true);

    auto x = appW - 170;
    auto y = appH;
    auto dy = 55.f;
    int end = vMenu.size();

    for (int i = 0; i < end; ++i) {
        if (i == menuStateToInt(currentMenu)) {
            qglColor(Qt::red);
            renderText(x, y, vMenu[i].second.c_str(), font_selected);
        } else {
            qglColor(Qt::white);
            renderText(x, y, vMenu[i].second.c_str(), font);
        }

        y += dy;
    }
}

void Game::draw_settings_players()
{
    dr.draw_settings_players(menuSettingsStateToInt(activeMenuSettings),
                             SettingsStateToInt(activeSetting), humanWhite, humanBlack,
                             nameWhite, nameBlack);
}

void Game::draw_play()
{
    qDebug() << "3. ilast = " << ilast << ", jlast = " << jlast << Qt::endl;
    if (!gameOver)
        dr.draw_play(8, icur, jcur, m.getChips(), ilast, jlast, activeBack,
                 whiteChips, blackChips, (isBlack) ? nameBlack : nameWhite, numMessage);
    else
        dr.draw_play(8, icur, jcur, m.getChips(), ilast, jlast, activeBack,
                 whiteChips, blackChips, (winner == Chip::black) ? nameBlack : nameWhite, numMessage);
}

void Game::key_released_menu(int key)
{
    switch (key) {
    case Qt::Key_Up: {
        --currentMenu;
        break;
    } case Qt::Key_Down: {
        ++currentMenu;
        break;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter: {
        state = menuToState(currentMenu);
        if (currentMenu == Menu::SETTINGS_PLAYERS)
            activeMenuSettings = MenuSettings::PLAYER1;
        break;
    }
    }

    updateGL();
}

void Game::key_released_settings_players(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Up: {
        if (!isChoosen)
            --activeMenuSettings;
        else
            if (activeMenuSettings != MenuSettings::BACK)
                --activeSetting;
        break;
    } case Qt::Key_Down: {
        if (!isChoosen)
            ++activeMenuSettings;
        else
            if (activeMenuSettings != MenuSettings::BACK)
                ++activeSetting;
        break;
    } case Qt::Key_Right: {
        if (isChoosen && activeSetting == Settings::RACE) {
            if (activeMenuSettings == MenuSettings::PLAYER1 && humanBlack) {
                humanWhite = false;
                shouldRestart = true;
            }
            else if (activeMenuSettings == MenuSettings::PLAYER2  && humanWhite) {
                humanBlack = false;
                shouldRestart = true;
            }
        }
        break;
    } case Qt::Key_Left: {
        if (isChoosen && activeSetting == Settings::RACE) {
            if (activeMenuSettings == MenuSettings::PLAYER1) {
                humanWhite = true;
                shouldRestart = true;
            }
            else if (activeMenuSettings == MenuSettings::PLAYER2) {
                humanBlack = true;
                shouldRestart = true;
            }
        }
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return: {
        if (activeMenuSettings != MenuSettings::BACK) {
            if (isChoosen) {
                if (activeMenuSettings == MenuSettings::PLAYER1 && activeSetting == Settings::NAME) {
                    inputNameWhite = (inputNameWhite) ? false : true;
                    dr.changeVisibleSettingsNamePlayer(inputNameWhite, 1);
                } else if (activeMenuSettings == MenuSettings::PLAYER2 && activeSetting == Settings::NAME) {
                    inputNameBlack = (inputNameBlack) ? false : true;
                    dr.changeVisibleSettingsNamePlayer(inputNameBlack, 2);
                } else {
                    isChoosen = false;
                    activeSetting = Settings::START;
                }
            } else {
                shouldRestart = true;
                isChoosen = true;
            }
        } else {
            isChoosen = false;
            activeSetting = Settings::START;
            activeMenuSettings = MenuSettings::START;
            inputNameWhite = false;
            inputNameBlack = false;
            state = State::MENU;
            break;
        }
        //inputNameBlack = (inputNameBlack) ? false : true;
        break;
    }
    case Qt::Key_Delete: {
        if (inputNameBlack){
            if (nameBlack.size() > 0)
                nameBlack.remove(nameBlack.size() - 1, 1);
        } else if (inputNameWhite) {
                if (nameWhite.size() > 0)
                    nameWhite.remove(nameWhite.size() - 1, 1);
        }
        break;
    }
    case Qt::Key_Escape: {
            isChoosen = false;
            activeSetting = Settings::START;
            activeMenuSettings = MenuSettings::START;
            inputNameWhite = false;
            inputNameBlack = false;
            state = State::MENU;
            shouldRestart = true;
            break;
        }
    default: {
        if (inputNameBlack && nameBlack.size() < 10)
            nameBlack += tr("%1").arg(e->text());
        else if (inputNameWhite && nameWhite.size() < 10)
            nameWhite += tr("%1").arg(e->text());
        break;
    }
    }
    updateGL();
}

void Game::key_released_play(int key)
{
    switch (key) {
    case Qt::Key_Up: {
        if (activeBack) {
            activeBack = false;
        } else if (icur > 0)
            icur--;
        break;
    } case Qt::Key_Down: {
        if (icur < 8 - 1)
            icur++;
        else if (icur == 7) {
            activeBack = true;
        }
        break;
    } case Qt::Key_Left: {
        if (jcur > 0)
            jcur--;
        break;
    } case Qt::Key_Right: {
        if (jcur < 8 - 1)
            jcur++;
        break;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter: {
        if (gameOver) {
            begin = true;
            numMessage = 0;
            m.restartGame(nameWhite.toStdString(), nameBlack.toStdString(), humanWhite, humanBlack);
            gameOver = false;
            break;
        }

        if (numMessage == 3 || numMessage == 4) {
            begin = true;
            numMessage = 0;
            m.restartGame(nameWhite.toStdString(), nameBlack.toStdString(), humanWhite, humanBlack);
            break;
        }

        if (activeBack) {
            activeBack = false;
            state = State::MENU;
            break;
        }
        ilast = icur;
        jlast = jcur;

        numMessage = m.makeMove(ilast, jlast);
        if (!m.isCurrentPlayerHuman()) {
            if ((m.getLast_i() != -1) && (m.getLast_j() != -1)) {
                ilast = m.getLast_i();
                jlast = m.getLast_j();
                icur = ilast;
                jcur = jlast;
            }
        }

        if (numMessage != 1)
            isBlack = (isBlack) ? false : true;

        gameOver = m.isOver();
        qDebug() << "2. ilast = " << ilast << ", jlast = " << jlast << Qt::endl;
        break;
    }
    }

    updateGL();
}
