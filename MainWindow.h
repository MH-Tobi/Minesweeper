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

    private:
        // Methods for building the application
        void createMenu();
        void createStatisticWidget();

        // Methods that do other things
        void quitApplication();
        void openInfoAboutQt();
        void openInfoAboutOther();

        // Methods for the Settings
        void openSettingsWindow();
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

        // Methods to prepare the Game
        void prepareNewGame();
        void createFields();

        // Methods for the Gameplay
        void startGame(uint16_t id);
        void solveZeros(uint16_t id);
        void openAllMines();
        void startTimer();
        
        // Helper Methods
        int16_t *getNearFields(uint16_t id);
        void setButtonIcon(QPushButton *button, QString icon);
        void setNearMinesText(Field *field);

        // Elements for the Gameplay
        uint16_t _rows;
        uint16_t _columns;
        uint16_t _sum_mines;
        uint16_t _field_size;
        uint16_t _fields_to_solve;
        uint16_t _fields_marked;
        uint8_t  _available_mouses;
        uint16_t _current_time;
        uint16_t *_mines;
        uint8_t  _mouses_used;
        bool _mine_hit;
        bool _mouse_in_use;
        bool _game_started;
        QList<Field *> _fields;

        // Common Elements of the Main-Window
        QVBoxLayout *_window_layout;
        QWidget     *_playfield;

        // Elements for the Menu
        QMenuBar *_menu_bar;
        QMenu    *_app_menu;
        QMenu    *_info_menu;
        QAction  *_new_game_action;
        QAction  *_settings_action;
        QAction  *_quit_action;
        QAction  *_qt_info_action;
        QAction  *_other_info_action;
        
        // Elements for the Settings-Window
        QWidget   *_settings_widget;
        QLineEdit *_edit_number_rows;
        QLineEdit *_edit_number_columns;
        QLineEdit *_edit_number_mines;
        QLineEdit *_edit_field_size;
        QLineEdit *_edit_available_mouses;

        // Elements for the Statistics-Layout
        QWidget     *_statistic_widget;
        QLineEdit   *_edit_count_solved_fields;
        QLineEdit   *_edit_count_marked_fields;
        QLineEdit   *_edit_timer;
        QPushButton *_button_game_status;
        QPushButton *_button_mouse;
        
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