#include "drawer.h"
#include <GL/gl.h>
#include <math.h>
#include <QWidget>
#include <QString>
#include <QObject>
#include <QDebug>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Another Function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void draw_circle(float l, bool black, bool last) {
    float x, y;
    float points = 40;
    float a = M_PI * 2 / points;
    glBegin(GL_TRIANGLE_FAN);
    if (black) glColor3f(0, 0, 0);
    else glColor3f(1.000, 0.980, 0.980);
    glVertex2f(0, 0);
    for (int i = -1; i < points; i++) {
        x = sin(a * i) * l;
        y = cos(a * i) * l;
        glVertex2f(x, y);
    }
    glEnd();

    if (last) {
    l = (l * 0.2) / 2.f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.420, 0.557, 0.137);
    glVertex2f(-l, l);
    glVertex2f(-l, -l);
    glVertex2f(l, -l);
    glVertex2f(l, l);
    glEnd();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Drawer~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
drawer::drawer()
{

}

void drawer::setGame(QGLWidget *_glw)
{
    game = _glw;
}

void drawer::draw_play(int size, int icur, int jcur, Chip** chips,
                       int ilast, int jlast, bool activeBack,
                       int whiteChips, int blackChips, QString name, int Message)
{

    draw_board(size, icur, jcur,whiteChips, blackChips, name, Message);
    if (Message == 3 || Message == 4 || Message == 5)
        return;
    draw_chips(size, chips, ilast, jlast);
    draw_back(activeBack);

}

void drawer::draw_settings_players(int numberMenuSettings, int selectSetting,
                                   bool isHumanWhite, bool isHumanBlack, QString name1, QString name2)
{
    draw_column_settings(1, isHumanWhite, name1,
                         (numberMenuSettings == 0) ? true : false,
                         (numberMenuSettings == 0) ? selectSetting : -1);

    draw_column_settings(2, isHumanBlack, name2,
                         (numberMenuSettings == 1) ? true : false,
                         (numberMenuSettings == 1) ? selectSetting : -1);
    draw_back((numberMenuSettings == 2) ? true : false);

}

void drawer::changeVisibleSettingsNamePlayer(bool value, int player)
{
    if (player == 1)
        visibleSettingsNamePlayerWhite = value;
    else if (player == 2)
        visibleSettingsNamePlayerBlack = value;
}

void drawer::draw_board(int size, int icur, int jcur,
                        int whiteChips, int blackChips, QString name, int Message)
{
    float bSize = ((game->geometry().width() > game->geometry().height()) ? game->geometry().height() : game->geometry().width()) - 80;
    static auto bHeight = bSize / size;

    game->qglColor(Qt::lightGray);

    float x{ (game->geometry().width() - bSize) / 2.f };
    float y{ (game->geometry().height() - bSize) / 2.f };

    float xcur[2], ycur[2];

    float texti, textj;
    glPushMatrix();
    glTranslatef(- 100, 0, 0);
    glLineWidth(5);
    glBegin(GL_LINES);
    for (int k = 0; k <= size; k++) {
        if (k == 1)
            textj = y + bHeight * k - bHeight / 2;
        glVertex2i(x, y + bHeight * k);
        glVertex2i(x + bSize, y + bHeight * k);
        if (k == icur)
            ycur[0] = (y + bHeight * k);
        else if (k - 1 == icur)
            ycur[1] = (y + bHeight * k);
    }
    for (int k = 0; k <= size; k++) {
        if (k == size)
            texti = x + bHeight * k - 85;
        glVertex2i(x + bHeight * k, y);
        glVertex2i(x + bHeight * k, y + bSize);
        if (k == jcur)
            xcur[0] = (x + bHeight * k);
        else if (k - 1 == jcur)
            xcur[1] = (x + bHeight * k);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.902, 0.902, 0.980, 0.3);
    glVertex2f(xcur[0], ycur[0]);
    glVertex2f(xcur[1], ycur[0]);
    glVertex2f(xcur[1], ycur[1]);
    glVertex2f(xcur[0], ycur[1]);
    glEnd();

    glPopMatrix();

    if (Message == 3 || Message == 4 || Message == 5)
        gameOver(whiteChips, blackChips, Message, name);
    else {
        glPushMatrix();
        glTranslatef(- 100, 0, 0);
        draw_text(texti, textj, bHeight, (game->geometry().width() - bSize) / 2.f + 100,
              whiteChips, blackChips, name, Message);
        glPopMatrix();

    }
}

void drawer::gameOver(int whiteChips, int blackChips, int mes, QString name)
{
    float bSize = ((game->geometry().width() > game->geometry().height()) ? game->geometry().height() : game->geometry().width()) - 80;
    float x { (game->geometry().width() / 2.f) - (bSize / 2) };
    float y { (game->geometry().height() / 2.f) - (bSize / 4) };

    game->qglColor(Qt::red);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glVertex2f(x + bSize, y);
    glVertex2f(x + bSize, y + bSize / 2);
    glVertex2f(x,  y + bSize / 2);
    glEnd();

    float dy = bSize / 12;
    y =  y + bSize / 4 - 25 - dy /2;
    game->qglColor(Qt::white);
    int sizeFont = 25;
    QFont font = QFont("Sans", sizeFont);
    font.setBold(true);
    QString str;
    if (mes == 3 || mes == 5)
        str = QObject::tr("Победил %1!").arg(name);
    else if (mes == 4) {
        str = QObject::tr("Ничья!");
    }
    game->renderText(x + bSize / 2 - sizeFont * str.size() / 2, y, str, font);

    QString strWhite = QObject::tr("Белых: %1").arg(whiteChips);
    QString strBlack = QObject::tr("Чёрных: %1").arg(blackChips);
    font.setBold(false);
    game->renderText(x + bSize / 2 - sizeFont * str.size() / 2,
                     y + dy, strBlack, font);
    game->renderText(x + bSize / 2 - sizeFont * str.size() / 2,
                     y + dy * 2, strWhite, font);

}

void drawer::draw_text(float x, float y, float bSize, float width,
                       int whiteChips, int blackChips, QString name, int Message)
{
    QString mainStr1 = QObject::tr("Игрок %1,").arg(name);
    QString mainStr2 = QObject::tr("Ваш ход...");
    float sizeFont = width / mainStr1.size();
    QFont font = QFont("Sans", sizeFont);
    game->qglColor(Qt::white);
    game->renderText(x, y, mainStr1, font);
    float ylast = y + bSize * 7;
    y += bSize;
    game->renderText(x, y, mainStr2, font);

    if (Message == 2) {
        QString str = QObject::tr("Нет доступных ходов.");
        float asizeFont = width / str.size();
        font = QFont("Sans", asizeFont);
        game->qglColor(Qt::red);
        y += bSize;
        game->renderText(x, y, str, font);
    } else if (Message == 1) {
        QString str1 = QObject::tr("Неверный ход!");
        QString str2 = QObject::tr("Попробуйте ещё раз...");
        float asizeFont = width / str1.size();
        font = QFont("Sans", asizeFont);
        game->qglColor(Qt::red);
        y += bSize;
        game->renderText(x, y, str1, font);
        asizeFont = width / str2.size();
        font = QFont("Sans", asizeFont);
        game->qglColor(Qt::red);
        y += bSize;
        game->renderText(x, y, str2, font);
    }

    QString strWhite = QObject::tr("Белых: %1").arg(whiteChips);
    QString strBlack = QObject::tr("Чёрных: %1").arg(blackChips);
    sizeFont = width / strBlack.size();
    font = QFont("Sans", sizeFont);
    game->qglColor(Qt::white);
    game->renderText(x, ylast, strBlack, font);
    ylast -= bSize;
    game->renderText(x, ylast, strWhite, font);
}

void drawer::draw_chips(int size, Chip** chips, int ilast, int jlast)
{
    float bSize = ((game->geometry().width() > game->geometry().height()) ? game->geometry().height() : game->geometry().width()) - 80;
    static auto bHeight = bSize / size;

    //game->qglColor(Qt::lightGray);

    float x{ (game->geometry().width() - bSize) / 2.f  };
    float y{ (game->geometry().height() - bSize) / 2.f };

    qDebug() << "1. ilast = " << ilast << ", jlast = " << jlast << Qt::endl;
    glPushMatrix();
    glTranslatef(- 100, 0, 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (chips[i][j] != Chip::empty) {
                glPushMatrix();
                glTranslatef(x + bHeight * j + bHeight * 0.5, y + bHeight * i + bHeight * 0.5, 0);
                bool black = (chips[i][j] == Chip::black) ? true : false;
                bool last = ((i == ilast) && (j == jlast)) ? true : false;
                draw_circle((bHeight / 2)*0.86, black, last);
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}

void drawer::draw_column_settings(int numberPlayer, bool isHuman, QString name,
                                  bool isSelected, int selectSetting)
{
    float bSize = ((game->geometry().width() > game->geometry().height()) ? game->geometry().height() : game->geometry().width()) - 80;
    float x = bSize / 2  ;
    float y;
    if (numberPlayer == 1)
        y = bSize / 2 - bSize / 4 - ((game->geometry().height() - bSize) / 2.f);
    else
        y = bSize / 2 + ((game->geometry().height() - bSize) / 2.f);

    int sizeFont = (!isSelected) ? 25 : 30;

    QFont font = QFont("Sans", sizeFont);
    if (isSelected)
        font.setBold(true);
    else
        font.setBold(false);

    float dy = 50.f + sizeFont / 3;

//    static auto font_selected = QFont("Sans", 30);
//    font_selected.setBold(true);
    game->qglColor(Qt::white);
    QString namePlayer = (numberPlayer == 1) ? QObject::tr("белый") : QObject::tr("чёрный");
    game->renderText(x, y, QObject::tr("Игрок %1").arg(namePlayer), font);

    y += dy;

    if (selectSetting == 0) {
        game->qglColor(Qt::red);
        //font.setBold(true);
    }
    else {
        game->qglColor(Qt::white);
        //font.setBold(false);
    }
    QString typePlayer = (isHuman) ? QObject::tr("Человек >") : QObject::tr("< Компьютер");
    if (isHuman)
        game->renderText(x, y, QObject::tr("%1").arg(typePlayer), font);
    else
        game->renderText(x - sizeFont * 2, y, QObject::tr("%1").arg(typePlayer), font);

    y += dy;



    game->qglColor(Qt::white);
    font.setBold(false);
    game->renderText(x - sizeFont * 6, y, QObject::tr("Имя:  "), font);

    if (selectSetting == 1) {
        game->qglColor(Qt::red);
        //font.setBold(true);
    }
    else {
        game->qglColor(Qt::white);
        //font.setBold(false);
    }

    if ((numberPlayer == 1 && visibleSettingsNamePlayerWhite) ||
            (numberPlayer == 2 && visibleSettingsNamePlayerBlack)) {
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(0.902, 0.902, 0.980, 0.3);
        glVertex2f(x, y - dy * 0.8);
        glVertex2f(x, y + dy * 0.2);
        glVertex2f(x + bSize * 2 / 3, y + dy * 0.2);
        glVertex2f(x + bSize * 2 / 3, y - dy * 0.8);
        glEnd();
        game->renderText(x + sizeFont, y, QObject::tr("%1").arg(name), font);

    }
    else
        game->renderText(x, y, QObject::tr("%1").arg(name), font);

}

void drawer::draw_back(bool isSelected)
{
    float bSize = ((game->geometry().width() > game->geometry().height()) ? game->geometry().height() : game->geometry().width()) - 80;
    float x = game->geometry().width() / 2.f;
    float y =  game->geometry().height();

    int sizeFont = (!isSelected) ? 18 : 30;
    x -= sizeFont * 1.5;
    y -= sizeFont * 1 / 2;

    QFont font = QFont("Sans", sizeFont);

    game->qglColor(Qt::white);
    if (isSelected) {
        game->qglColor(Qt::red);
        font.setBold(true);
    }
    else
        font.setBold(false);

    game->renderText(x, y, QObject::tr("<<<"), font);
}

