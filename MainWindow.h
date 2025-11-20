#pragma once

#include <QWidget>

class Field;
class QPushButton;
class QMenuBar;
class QVBoxLayout;
class QLineEdit;
class QThread;
class TimingWorker;
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
        uint8_t  getAvailableMouses();
        void setNumRows(uint16_t value);
        void setNumColumns(uint16_t value);
        void setNumMines(uint16_t value);
        void setFieldSize(uint16_t value);
        void setAvailableMouses(uint8_t value);
        
        void setSettings();
        void resetSettings();
        void closeSettings();
        
    private:
        uint16_t _rows;
        uint16_t _columns;
        uint16_t _sum_mines;
        uint16_t _field_size;
        uint16_t _fields_to_solve;
        uint16_t _fields_marked;

        uint8_t _available_mouses;

        bool _mine_hit;

        uint16_t _current_time;

        uint16_t *_mines;

        uint8_t _mouses_used;
        bool _mouse_in_use;

        QVBoxLayout *_window_layout;
        
        void createMenu();
        void createStatisticWidget();
        void createFields();
        void startGame(uint16_t id);
        void solveZeros(uint16_t id);
        int16_t *getNearFields(uint16_t id);
        void openAllMines();

        void startTimer();

        bool _game_started;
        
        QThread *_thread;
        TimingWorker *_worker;

        QWidget *_playfield;
        QWidget *_settings_widget;
        QWidget *_statistic_widget;

        QMenuBar *_menu_bar;
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
        QLineEdit *_edit_available_mouses;

        QLineEdit *_edit_count_solved_fields;
        QPushButton *_button_game_status;
        QLineEdit *_edit_count_marked_fields;
        QPushButton *_button_mouse;
        QLineEdit *_edit_timer;
        
        QList<Field *> _fields;
        
    public slots:
        void fieldClicked(Field *field);
        void fieldRightClicked(Field *field);
        void useMouse();
        void createResult();
        void increaseTimer();

    signals:
        void gameFinished();
        void stopTimer();
};