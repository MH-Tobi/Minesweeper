#include "MainWindow.h"
#include "Field.h"
#include "TimingWorker.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QLineEdit>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QFormLayout>
#include <QThread>

#include <random>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    _rows(10),
    _columns(15),
    _sum_mines(25),
    _field_size(40),
    _fields_to_solve(_rows*_columns-_sum_mines),
    _fields_marked(0),
    _mouse_in_use(false),
    _available_mouses(3),
    _mine_hit(false),
    _current_time(0),
    _playfield(new QWidget(this))    
{
    _window_layout = new QVBoxLayout;
    _window_layout->setContentsMargins(5, 5, 5, 5);
    setWindowTitle("Minesweeper");
    createMenu();
    createStatisticWidget();

    _window_layout->setMenuBar(_menu_bar);
    _window_layout->addWidget(_statistic_widget);
    _window_layout->addWidget(_playfield);

    connect(this, &MainWindow::gameFinished, this, &MainWindow::createResult);

    NewGame();

    this->setLayout(_window_layout);
}

void MainWindow::createResult()
{
    if (_fields_to_solve == 0)
    {
        _button_game_status->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\smiling_face.png"));
        _button_game_status->setIconSize(QSize(_button_game_status->width()*3/4,_button_game_status->height()*3/4));
    
    }else if (_mine_hit)
    {
        _mine_hit = false;

        _button_game_status->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\sad_face.png"));
        _button_game_status->setIconSize(QSize(_button_game_status->width()*3/4,_button_game_status->height()*3/4));

        openAllMines();
    }
    
    emit stopTimer();
}


void MainWindow::startTimer()
{
    auto *thread = new QThread();
    auto *worker = new TimingWorker();

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &TimingWorker::doWork);
    connect(worker, &TimingWorker::timeIncreasedOneSecond, this, &MainWindow::increaseTimer);
    connect(worker, &TimingWorker::done, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(this, &MainWindow::stopTimer, worker, &TimingWorker::cancel);

    thread->start();
}

void MainWindow::increaseTimer()
{
    _current_time++;
    _edit_timer->setText(QString::number(_current_time));
}

void MainWindow::openAllMines()
{
    for (size_t i = 0; i < _sum_mines; i++)
    {
        _fields[_mines[i]]->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mine_blasted.png"));
        _fields[_mines[i]]->setIconSize(QSize(_fields[_mines[i]]->getFieldSize()*3/4,_fields[_mines[i]]->getFieldSize()*3/4));
    }
}

void MainWindow::createStatisticWidget()
{
    _statistic_widget = new QWidget(this);

    QGridLayout *statisticLayout = new QGridLayout(_statistic_widget);
    statisticLayout->setContentsMargins(5, 5, 5, 5);

    _edit_count_solved_fields = new QLineEdit();
    _button_game_status = new QPushButton();
    _edit_count_marked_fields = new QLineEdit();
    _button_mouse = new QPushButton();
    _edit_timer = new QLineEdit();

    _edit_count_solved_fields->setReadOnly(true);
    _edit_count_marked_fields->setReadOnly(true);
    _edit_timer->setReadOnly(true);

    _edit_count_solved_fields->setDisabled(true);
    _edit_count_marked_fields->setDisabled(true);
    _edit_timer->setDisabled(true);

    _edit_count_solved_fields->setFixedSize(QSize(80, 30));
    _button_game_status->setFixedSize(QSize(30, 30));
    _edit_count_marked_fields->setFixedSize(QSize(80, 30));
    _button_mouse->setFixedSize(QSize(30, 30));
    _edit_timer->setFixedSize(QSize(80, 30));

    _edit_count_solved_fields->setPlaceholderText("Solved Fields");
    _edit_count_marked_fields->setPlaceholderText("Marked Fields");
    _edit_timer->setPlaceholderText("Timer");

    _edit_count_solved_fields->setStyleSheet(
        "background-color: white;"
        "font-family: Lucida Handwriting;"
        "font-size: 16px;"
        "font-color: black;"
        "border-width: 1px;"
        "border-style: solid;"
        "border-color: lightgray;"
    );
    _edit_count_marked_fields->setStyleSheet(
        "background-color: white;"
        "font-family: Times New Roman;"
        "font-size: 16px;"
        "font-color: black;"
        "border-width: 1px;"
        "border-style: solid;"
        "border-color: lightgray;"
    );
    _edit_timer->setStyleSheet(
        "background-color: white;"
        "font-family: Times New Roman;"
        "font-size: 16px;"
        "font-color: black;"
        "border-width: 1px;"
        "border-style: solid;"
        "border-color: lightgray;"
    );

    QSpacerItem *spacerV1 = new QSpacerItem(1, 1, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
    statisticLayout->addItem(spacerV1, 0, 0, 1, 4);
    statisticLayout->addWidget(_edit_count_solved_fields, 0, 4, 1, 1);
    statisticLayout->addWidget(_button_game_status, 0, 5, 1, 1);
    statisticLayout->addWidget(_edit_count_marked_fields, 0, 6, 1, 1);
    statisticLayout->addItem(spacerV1, 0, 7, 1, 1);
    statisticLayout->addWidget(_button_mouse, 0, 8, 1, 1);
    statisticLayout->addWidget(_edit_timer, 0, 9, 1, 1);

    statisticLayout->setColumnStretch(0, 1);
    statisticLayout->setColumnStretch(7, 1);

    _button_game_status->setCheckable(false);

    _button_game_status->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\open.png"));
    _button_game_status->setIconSize(QSize(_button_game_status->width()*3/4,_button_game_status->height()*3/4));

    _button_mouse->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mouse_available.png"));
    _button_mouse->setIconSize(QSize(_button_mouse->width()*3/4,_button_mouse->height()*3/4));

    _statistic_widget->setFixedHeight(35);

    connect(_button_mouse, &QPushButton::clicked, this, &MainWindow::useMouse);
}

void MainWindow::useMouse()
{
    if (_mouses_used > 0)
    {
        if (_mouse_in_use)
        {
            _button_mouse->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mouse_available.png"));
            _button_mouse->setIconSize(QSize(_button_mouse->width()*3/4,_button_mouse->height()*3/4));
            _button_mouse->setDown(false);
            _mouse_in_use = false;
        }else{
            _button_mouse->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mouse_working.png"));
            _button_mouse->setIconSize(QSize(_button_mouse->width()*3/4,_button_mouse->height()*3/4));
            _button_mouse->setDown(true);
            _mouse_in_use = true;
        }
    }else{
        _button_mouse->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mouse_available.png"));
        _button_mouse->setIconSize(QSize(_button_mouse->width()*3/4,_button_mouse->height()*3/4));
        _button_mouse->setDown(false);
        _mouse_in_use = false;
        _button_mouse->setDisabled(true);
    }
}

void MainWindow::createMenu()
{
    _menu_bar = new QMenuBar;

    _app_menu = new QMenu("App", this);
    _info_menu = new QMenu("Info", this);

    _new_game_action = _app_menu->addAction("New");
    _settings_action = _app_menu->addAction("Settings");
    _quit_action = _app_menu->addAction("Quit");

    _qt_info_action = _info_menu->addAction("About Qt");
    _other_info_action = _info_menu->addAction("About Other");

    _menu_bar->addMenu(_app_menu);
    _menu_bar->addMenu(_info_menu);

    connect(_new_game_action, &QAction::triggered, this, &MainWindow::NewGame);
    connect(_settings_action, &QAction::triggered, this, &MainWindow::Settings);
    connect(_quit_action, &QAction::triggered, this, &MainWindow::Quit);
    connect(_qt_info_action, &QAction::triggered, this, &MainWindow::AboutQt);
    connect(_other_info_action, &QAction::triggered, this, &MainWindow::AboutOther);
}

void MainWindow::Quit()
{
    QApplication::instance()->quit();
}

void MainWindow::AboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::NewGame()
{
    if (_game_started)
    {
        emit gameFinished();
    }
    
    _playfield->resize(_field_size*_columns, _field_size*_rows);

    _button_game_status->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\open.png"));
    _button_game_status->setIconSize(QSize(_button_game_status->width()*3/4,_button_game_status->height()*3/4));

    _fields_to_solve = _rows*_columns-_sum_mines;
    _edit_count_solved_fields->setText(QString::number(_fields_to_solve));

    _fields_marked = 0;
    _edit_count_marked_fields->setText(QString::number(_fields_marked) + "/" + QString::number(_sum_mines));

    _current_time = 0;
    _edit_timer->setText(QString::number(_current_time));

    _button_mouse->setDisabled(false);
    _mouses_used=_available_mouses;
    _game_started=false;
    
    createFields();

    this->setFixedSize(_playfield->width()+10, _playfield->height()+85);
}

void MainWindow::createFields()
{
    for (QPushButton *field : _fields)
    {
        field->close();
    }
    
    _fields.clear();

    uint16_t k;
    uint16_t l;
    
    for (uint16_t i = 0; i < _rows*_columns; i++)
    {
        k = i/_columns;
        l = i % _columns;

        Field *field = new Field(i, _field_size, _playfield);
        _fields.append(field);
        
        field->QPushButton::setFixedSize(field->getFieldSize(), field->getFieldSize());
        field->QPushButton::move(l*field->getFieldSize(), k*field->getFieldSize());
        field->QPushButton::show();
        
        connect(field, &QPushButton::clicked, this, [this, field]{fieldClicked(field);});
        connect(field, &Field::rightClicked, this, [this, field]{fieldRightClicked(field);});

    }
}

void MainWindow::fieldRightClicked(Field *field)
{
    if (field->getFieldIsMarked())
    {
        _fields_marked++;
        _edit_count_marked_fields->setText(QString::number(_fields_marked) + "/" + QString::number(_sum_mines));

    }else if (field->getFieldIsQuestionable())
    {
        _fields_marked--;
        _edit_count_marked_fields->setText(QString::number(_fields_marked) + "/" + QString::number(_sum_mines));
    }
}

void MainWindow::fieldClicked(Field *field)
{
    if (!_game_started)
    {
        _game_started = true;
        startGame(field->getFieldID());

        startTimer();
    }

    if (_mouse_in_use)
    {
        if (!field->getFieldIsMarked())
        {
            _mouses_used--;
            useMouse();
            if (field->getFieldIsMine())
            {
                field->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\flag.png"));
                field->setIconSize(QSize(field->getFieldSize()*3/4,field->getFieldSize()*3/4));

                _fields_marked++;
                _edit_count_marked_fields->setText(QString::number(_fields_marked) + "/" + QString::number(_sum_mines));

            }else{
                _fields_to_solve--;
                _edit_count_solved_fields->setText(QString::number(_fields_to_solve));

                field->setText(QString::number(field->getFieldNearMines()));
                field->setFlat(true);
                field->setDisabled(true);

                if (field->getFieldNearMines() == 0)
                {
                    solveZeros(field->getFieldID());
                }
            }
        }
    }else{
        if (!(field->getFieldIsMarked() || field->getFieldIsQuestionable()))
        {
            if (field->getFieldIsMine())
            {
                field->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mine_blasted.png"));
                field->setIconSize(QSize(field->getFieldSize()*3/4,field->getFieldSize()*3/4));
                
                field->setFlat(true);
                field->setEnabled(false);

                _mine_hit = true;

                emit gameFinished();

            }else{
                _fields_to_solve--;
                _edit_count_solved_fields->setText(QString::number(_fields_to_solve));

                field->setText(QString::number(field->getFieldNearMines()));
                field->setFlat(true);
                field->setDisabled(true);

                if (field->getFieldNearMines() == 0)
                {
                    solveZeros(field->getFieldID());
                }
            }
        }
    }

    if (_fields_to_solve == 0)
    {
        emit gameFinished();
    }
}

void MainWindow::solveZeros(uint16_t fieldID)
{
    int16_t *nearFields = getNearFields(fieldID);

    for (size_t i = 0; i < 9; i++)
    {
        if (nearFields[i] != -1 && nearFields[i] != fieldID)
        {
            if (!_fields[nearFields[i]]->isFlat())
            {
                _fields[nearFields[i]]->click();
            }
        }
    }
    
    delete nearFields;
}

void MainWindow::startGame(uint16_t fieldID)
{    
    int16_t *unallowedFields = getNearFields(fieldID);

    //uint16_t _mines[_sum_mines] = {};
    _mines = new uint16_t[_sum_mines]{};

    uint16_t countMines = 0;
    uint16_t columnRange[2] = {};
    uint16_t rowRange[2] = {};

    uint16_t map[_rows][_columns] = {};
    uint16_t f = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> distrib(0, ((_rows*_columns)-1));

    while (f < _sum_mines)
    {
        uint16_t randomValue = distrib(gen);
        uint16_t k = randomValue/_columns;
        uint16_t l = randomValue % _columns;
        bool skip = false;

        for (uint16_t i = 0; i < 9; i++)
        {
            if (randomValue == unallowedFields[i])
            {
                skip = true;
            }
        }

        if (!skip)
        {
            if (f>0)
            {
                _mines[f] = randomValue;
                f++;
                map[k][l] = 9;
                for (uint16_t i = 0; i < f-1; i++)
                {
                    if (randomValue == _mines[i])
                    {
                        f--;
                    }
                }
            }else{
                _mines[f] = randomValue;
                f++;
                map[k][l] = 9;
            }
        }
    }

    for (uint16_t i = 0; i < _rows; i++)
    {
        for (uint16_t j = 0; j < _columns; j++)
        {
            if (i > 0 && i < (_rows-1))
            {
                rowRange[0] = i-1;
                rowRange[1] = i+1;
            }else if (i > 0)
            {
                rowRange[0] = i-1;
                rowRange[1] = i;
            }else{
                rowRange[0] = i;
                rowRange[1] = i+1;
            }

            if (j > 0 && j < (_columns-1))
            {
                columnRange[0] = j-1;
                columnRange[1] = j+1;
            }else if (j > 0)
            {
                columnRange[0] = j-1;
                columnRange[1] = j;
            }else{
                columnRange[0] = j;
                columnRange[1] = j+1;
            }

            countMines = 0;

            for (uint16_t m = rowRange[0]; m <= rowRange[1]; m++)
            {
                for (uint16_t n = columnRange[0]; n <= columnRange[1]; n++)
                {
                    if (map[m][n] == 9)
                    {
                        countMines++;
                    }
                }
            }
            
            if (map[i][j] != 9)
            {
                _fields[i*_columns+j]->setFieldNearMines(countMines);
                _fields[i*_columns+j]->setFieldIsMine(false);
            }else{
                _fields[i*_columns+j]->setFieldNearMines(9);
                _fields[i*_columns+j]->setFieldIsMine(true);
            }
        }
    }
    delete unallowedFields;
}

void MainWindow::Settings()
{
    _settings_widget = new QWidget;

    QLabel *labelNumberRows = new QLabel("Number Rows");
    QLabel *labelNumberColumns = new QLabel("Number Columns");
    QLabel *labelNumberMines = new QLabel("Number Mines");
    QLabel *labelFieldSize = new QLabel("Field Size");
    QLabel *labelAvailableMouses = new QLabel("Available Mouses");

    _edit_number_rows = new QLineEdit();
    _edit_number_columns = new QLineEdit();
    _edit_number_mines = new QLineEdit();
    _edit_field_size = new QLineEdit();
    _edit_available_mouses = new QLineEdit();

    resetSettings();

    //_edit_number_rows->setValidator(new QIntValidator(5, 100));
    //_edit_number_columns->setValidator(new QIntValidator(5, 100));
    //_edit_number_mines->setValidator(new QIntValidator(1, 100));
    //_edit_field_size->setValidator(new QIntValidator(1, 50));
    //_edit_available_mouses->setValidator(new QIntValidator(1, 5));

    QPushButton *buttonSet = new QPushButton("Set");
    QPushButton *buttonReset = new QPushButton("Reset");
    QPushButton *buttonCancel = new QPushButton("Cancel");

    QVBoxLayout *mainLayout = new QVBoxLayout(_settings_widget);

    QFormLayout *settingsLayout = new QFormLayout(_settings_widget);
    settingsLayout->addRow(labelNumberRows, _edit_number_rows);
    settingsLayout->addRow(labelNumberColumns, _edit_number_columns);
    settingsLayout->addRow(labelNumberMines, _edit_number_mines);
    settingsLayout->addRow(labelFieldSize, _edit_field_size);
    settingsLayout->addRow(labelAvailableMouses, _edit_available_mouses);
    
    QHBoxLayout *button_layout = new QHBoxLayout(_settings_widget);
    button_layout->addWidget(buttonSet);
    button_layout->addWidget(buttonReset);
    button_layout->addWidget(buttonCancel);

    mainLayout->addLayout(settingsLayout);
    mainLayout->addLayout(button_layout);

    connect(buttonSet, &QPushButton::clicked, this, &MainWindow::setSettings);
    connect(buttonReset, &QPushButton::clicked, this, &MainWindow::resetSettings);
    connect(buttonCancel, &QPushButton::clicked, this, &MainWindow::closeSettings);

    _settings_widget->show();
}

uint16_t MainWindow::getNumRows()         {return _rows;}
uint16_t MainWindow::getNumColumns()      {return _columns;}
uint16_t MainWindow::getNumMines()        {return _sum_mines;}
uint16_t MainWindow::getFieldSize()       {return _field_size;}
uint8_t  MainWindow::getAvailableMouses() {return _available_mouses;}


void MainWindow::setNumRows(uint16_t value)        {_rows = value;}
void MainWindow::setNumColumns(uint16_t value)     {_columns = value;}
void MainWindow::setNumMines(uint16_t value)       {_sum_mines = value;}
void MainWindow::setFieldSize(uint16_t value)      {_field_size = value;}
void MainWindow::setAvailableMouses(uint8_t value) {_available_mouses = value;}

void MainWindow::setSettings()
{
    setNumRows(_edit_number_rows->text().toInt());
    setNumColumns(_edit_number_columns->text().toInt());
    setNumMines(_edit_number_mines->text().toInt());
    setFieldSize(_edit_field_size->text().toInt());
    setAvailableMouses(_edit_available_mouses->text().toInt());

    _settings_widget->close();
}

void MainWindow::resetSettings()
{
    _edit_number_rows->setText(QString::number(getNumRows()));
    _edit_number_columns->setText(QString::number(getNumColumns()));
    _edit_number_mines->setText(QString::number(getNumMines()));
    _edit_field_size->setText(QString::number(getFieldSize()));
    _edit_available_mouses->setText(QString::number(getAvailableMouses()));
}

void MainWindow::closeSettings()
{
    _settings_widget->close();
}

int16_t* MainWindow::getNearFields(uint16_t fieldID)
{
    int16_t *nearFields = new int16_t[9]{-1,-1,-1,-1,-1,-1,-1,-1,-1};

    if (((fieldID/_columns) > 0) && ((fieldID/_columns) < _rows-1)) // if selected field is between the top and bottom row
    {
        if (((fieldID % _columns) > 0) && ((fieldID % _columns) < _columns-1))
        {
            // if selected field is between the top and bottom row and between the left and right column
            nearFields[0] = fieldID - _columns - 1;       // Top-Left
            nearFields[1] = fieldID - _columns;           // Top
            nearFields[2] = fieldID - _columns + 1;       // Top-Right
            nearFields[3] = fieldID - 1;                  // Left
            nearFields[4] = fieldID;                      // Field
            nearFields[5] = fieldID + 1;                  // Right
            nearFields[6] = fieldID + _columns - 1;       // Bottom-Left
            nearFields[7] = fieldID + _columns;           // Bottom
            nearFields[8] = fieldID + _columns + 1;       // Bottom-Right

        }else if ((fieldID % _columns) > 0)
        {
            // if selected field is between the top and bottom row and in the right column
            nearFields[0] = fieldID - _columns - 1;       // Top-Left
            nearFields[1] = fieldID - _columns;           // Top
            nearFields[2] = fieldID - 1;                  // Left
            nearFields[3] = fieldID;                      // Field
            nearFields[4] = fieldID + _columns - 1;       // Bottom-Left
            nearFields[5] = fieldID + _columns;           // Bottom

        }else{
            // if selected field is between the top and bottom row and in the left column
            nearFields[0] = fieldID - _columns;           // Top
            nearFields[1] = fieldID - _columns + 1;       // Top-Right
            nearFields[2] = fieldID;                      // Field
            nearFields[3] = fieldID + 1;                  // Right
            nearFields[4] = fieldID + _columns;           // Bottom
            nearFields[5] = fieldID + _columns + 1;       // Bottom-Right
        }
    }else if ((fieldID/_columns) > 0) // if selected field is in the bottom row
    {
        if (((fieldID % _columns) > 0) && ((fieldID % _columns) < _columns-1))
        {
            // if selected field is in the bottom row and between the left and right column
            nearFields[0] = fieldID - _columns - 1;       // Top-Left
            nearFields[1] = fieldID - _columns;           // Top
            nearFields[2] = fieldID - _columns + 1;       // Top-Right
            nearFields[3] = fieldID - 1;                  // Left
            nearFields[4] = fieldID;                      // Field
            nearFields[5] = fieldID + 1;                  // Right

        }else if ((fieldID % _columns) > 0)
        {
            // if selected field is in the bottom row and in the right column
            nearFields[0] = fieldID - _columns - 1;       // Top-Left
            nearFields[1] = fieldID - _columns;           // Top
            nearFields[2] = fieldID - 1;                  // Left
            nearFields[3] = fieldID;                      // Field

        }else{
            // if selected field is in the bottom row and in the left column
            nearFields[0] = fieldID - _columns;           // Top
            nearFields[1] = fieldID - _columns + 1;       // Top-Right
            nearFields[2] = fieldID;                      // Field
            nearFields[3] = fieldID + 1;                  // Right
        }
    }else{  // if selected field is in the top row
        if (((fieldID % _columns) > 0) && ((fieldID % _columns) < _columns-1))
        {
            // if selected field in the top row and between the left and right column
            nearFields[0] = fieldID - 1;                  // Left
            nearFields[1] = fieldID;                      // Field
            nearFields[2] = fieldID + 1;                  // Right
            nearFields[3] = fieldID + _columns - 1;       // Bottom-Left
            nearFields[4] = fieldID + _columns;           // Bottom
            nearFields[5] = fieldID + _columns + 1;       // Bottom-Right

        }else if ((fieldID % _columns) > 0)
        {
            // if selected field in the top row and in the right column
            nearFields[0] = fieldID - 1;                  // Left
            nearFields[1] = fieldID;                      // Field
            nearFields[2] = fieldID + _columns - 1;       // Bottom-Left
            nearFields[3] = fieldID + _columns;           // Bottom

        }else{
            // if selected field in the top row and in the left column
            nearFields[0] = fieldID;                      // Field
            nearFields[1] = fieldID + 1;                  // Right
            nearFields[2] = fieldID + _columns;           // Bottom
            nearFields[3] = fieldID + _columns + 1;       // Bottom-Right
        }
    }

    return nearFields;
}