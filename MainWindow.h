#pragma once

#include <QWidget>


class QPushButton;
class QMenu;
class QMenuBar;
class QAction;
class QHBoxLayout;
class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        void NewGame();
        void Settings(){};
        void Quit();
        void AboutQt();
        void AboutOther(){};

        

    private:
        QHBoxLayout *_Windowlayout;


        void createMenu();
        void createFields();
        void startGame(uint16_t field);

        bool _GameStarted;
        
        QWidget *_Playfield;

        QMenuBar *_MenuBar;
        QMenu *_app_menu;
        QAction *_new_game_action;
        QAction *_settings_action;
        QAction *_quit_action;
        
        QMenu *_info_menu;
        QAction *_qt_info_action;
        QAction *_other_info_action;
        

        QList<QPushButton *> _Fields;
        

        std::uint16_t _rows;
        std::uint16_t _columns;
        std::uint16_t _sum_mines;

        int FIELD_SIZE = 40;

    public slots:
        void fieldClicked(uint16_t field);
    signals:
};