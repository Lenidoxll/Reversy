#ifndef DRAWER_H
#define DRAWER_H

#include <QGLWidget>
#include "Chip.h"

struct drawer
{
public:
    drawer();

    void setGame(QGLWidget* _glw);
    void draw_play(int, int, int, Chip**, int, int, bool,
                   int, int, QString, int);
    void draw_settings_players(int numberMenuSettings, int selectSetting,
                               bool isHuman1, bool isHuman2,
                               QString name1, QString name2);
    void changeVisibleSettingsNamePlayer(bool, int);

private:
    void draw_board(int, int, int, int, int, QString, int);
    void gameOver(int, int, int, QString);
    void draw_text(float, float, float, float, int, int, QString, int);
    void draw_chips(int, Chip**, int, int);
    void draw_column_settings(int numberPlayer, bool isHuman, QString name,
                              bool isSelected, int selectSetting = -1);
    void draw_back(bool isSelected);

    QGLWidget* game = nullptr;
    bool visibleSettingsNamePlayerWhite = false;
    bool visibleSettingsNamePlayerBlack = false;

};

#endif // DRAWER_H
