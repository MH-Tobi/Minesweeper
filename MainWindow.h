#pragma once

#include <QWidget>


class QPushButton;
class QMenu;
class QMenuBar;
class QAction;
class QHBoxLayout;
class QLineEdit;
class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        void NewGame();
        void Settings();
        void Quit();
        void AboutQt();
        void AboutOther(){};
        uint16_t getNumRows();
        uint16_t getNumColumns();
        uint16_t getNumMines();
        uint16_t getFieldSize();
        void setNumRows(uint16_t Value);
        void setNumColumns(uint16_t Value);
        void setNumMines(uint16_t Value);
        void setFieldSize(uint16_t Value);
        
        void setSettings();
        
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
        
        QLineEdit *_edit_number_rows;
        QLineEdit *_edit_number_columns;
        QLineEdit *_edit_number_mines;
        QLineEdit *_edit_field_size;

        QList<QPushButton *> _Fields;
        
        uint16_t _rows;
        uint16_t _columns;
        uint16_t _sum_mines;
        uint16_t _field_size;

        int FIELD_SIZE = 40;

    public slots:
        void fieldClicked(uint16_t field);

    signals:
};