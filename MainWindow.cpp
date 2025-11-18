#include "MainWindow.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QApplication>
#include <QPushButton>
#include <random>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QSpacerItem>
#include "Field.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent), _rows(10), _columns(15), _sum_mines(25), _Playfield(new QWidget(this)), _field_size(40), _FieldsToSolve(_rows*_columns-_sum_mines)
{
    QVBoxLayout *_Windowlayout = new QVBoxLayout;
    _Windowlayout->setContentsMargins(5, 5, 5, 5);
    setWindowTitle("Minesweeper");
    createMenu();
    createStatisticWidget();

    _Windowlayout->setMenuBar(_MenuBar);
    _Windowlayout->addWidget(_StatisticWidget);
    _Windowlayout->addWidget(_Playfield);

    NewGame();

    this->setLayout(_Windowlayout);
}

void MainWindow::createStatisticWidget()
{
    _StatisticWidget = new QWidget(this);

    QGridLayout *_StatisticLayout = new QGridLayout(_StatisticWidget);
    _StatisticLayout->setContentsMargins(5, 5, 5, 5);

    _edit_count_solved_fields = new QLineEdit();
    _edit_game_status = new QLineEdit();
    _edit_count_marked_fields = new QLineEdit();
    _button_mouse = new QPushButton();
    _edit_timer = new QLineEdit();

    _edit_count_solved_fields->setReadOnly(true);
    _edit_game_status->setReadOnly(true);
    _edit_count_marked_fields->setReadOnly(true);
    _edit_timer->setReadOnly(true);

    _edit_count_solved_fields->setFixedSize(QSize(80, 30));
    _edit_game_status->setFixedSize(QSize(30, 30));
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
    _StatisticLayout->addItem(spacerV1, 0, 0, 1, 4);
    _StatisticLayout->addWidget(_edit_count_solved_fields, 0, 4, 1, 1);
    _StatisticLayout->addWidget(_edit_game_status, 0, 5, 1, 1);
    _StatisticLayout->addWidget(_edit_count_marked_fields, 0, 6, 1, 1);
    _StatisticLayout->addItem(spacerV1, 0, 7, 1, 1);
    _StatisticLayout->addWidget(_button_mouse, 0, 8, 1, 1);
    _StatisticLayout->addWidget(_edit_timer, 0, 9, 1, 1);

    _StatisticLayout->setColumnStretch(0, 1);
    _StatisticLayout->setColumnStretch(7, 1);

    _StatisticWidget->setFixedHeight(35);
}

void MainWindow::createMenu()
{
    _MenuBar = new QMenuBar;

    _app_menu = new QMenu("App", this);
    _info_menu = new QMenu("Info", this);

    _new_game_action = _app_menu->addAction("New");
    _settings_action = _app_menu->addAction("Settings");
    _quit_action = _app_menu->addAction("Quit");

    _qt_info_action = _info_menu->addAction("About Qt");
    _other_info_action = _info_menu->addAction("About Other");

    _MenuBar->addMenu(_app_menu);
    _MenuBar->addMenu(_info_menu);

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
    _Playfield->resize(_field_size*_columns, _field_size*_rows);

    _FieldsToSolve = _rows*_columns-_sum_mines;
    _edit_count_solved_fields->setText(QString::number(_FieldsToSolve));

    _GameStarted=false;
    
    createFields();

    this->setFixedSize(_Playfield->width()+10, _Playfield->height()+85);
}

void MainWindow::createFields()
{
    for (QPushButton *field : _Fields)
    {
        field->close();
    }
    
    _Fields.clear();

    uint16_t k;
    uint16_t l;
    
    for (uint16_t i = 0; i < _rows*_columns; i++)
    {
        k = i/_columns;
        l = i % _columns;

        Field *field = new Field(i, _field_size, _Playfield);
        _Fields.append(field);
        
        field->QPushButton::setFixedSize(field->getFieldSize(), field->getFieldSize());
        field->QPushButton::move(l*field->getFieldSize(), k*field->getFieldSize());
        field->QPushButton::show();
        
        connect(field, &QPushButton::clicked, this, [this, field]{fieldClicked(field);});
    }
}

void MainWindow::fieldClicked(Field *field)
{
    if (!_GameStarted)
    {
        _GameStarted = true;
        startGame(field->getFieldID());
    }

    if (!(field->getFieldIsMarked() || field->getFieldIsQuestionable()))
    {
        if (field->getFieldIsMine())
        {
            field->setIcon(QIcon("D:\\Projekte\\Minesweeper\\icons\\mine_blasted.png"));
            field->setIconSize(QSize(field->getFieldSize()*3/4,field->getFieldSize()*3/4));

            field->setFlat(true);
            field->setEnabled(false);
        }else{
            _FieldsToSolve--;
            _edit_count_solved_fields->setText(QString::number(_FieldsToSolve));

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

void MainWindow::solveZeros(uint16_t Field_ID)
{
    int16_t *nearFields = getNearFields(Field_ID);

    for (size_t i = 0; i < 9; i++)
    {
        if (nearFields[i] != -1 && nearFields[i] != Field_ID)
        {
            if (!_Fields[nearFields[i]]->isFlat())
            {
                _Fields[nearFields[i]]->click();
            }
        }
    }
    
    delete nearFields;
}

void MainWindow::startGame(uint16_t id)
{    
    int16_t *unallowed_Fields = getNearFields(id);
    uint16_t Field_ID = id;

    uint16_t Mines[_sum_mines];

    uint16_t count_mines = 0;
    uint16_t column_range[2] = {0,0};
    uint16_t row_range[2] = {0,0};

    uint16_t Map[_rows][_columns];
    uint16_t f = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> distrib(0, ((_rows*_columns)-1));

    while (f < _sum_mines)
    {
        uint16_t Val = distrib(gen);
        uint16_t k = Val/_columns;
        uint16_t l = Val % _columns;
        bool skip = false;

        for (uint16_t i = 0; i < 9; i++)
        {
            if (Val == unallowed_Fields[i])
            {
                skip = true;
            }
        }

        if (!skip)
        {
            if (f>0)
            {
                Mines[f] = Val;
                f++;
                Map[k][l] = 9;
                for (uint16_t i = 0; i < f-1; i++)
                {
                    if (Val == Mines[i])
                    {
                        f--;
                    }
                }
            }else{
                Mines[f] = Val;
                f++;
                Map[k][l] = 9;
            }
        }
    }

    for (uint16_t i = 0; i < _rows; i++)
    {
        for (uint16_t j = 0; j < _columns; j++)
        {
            if (i > 0 && i < (_rows-1))
            {
                row_range[0] = i-1;
                row_range[1] = i+1;
            }else if (i > 0)
            {
                row_range[0] = i-1;
                row_range[1] = i;
            }else{
                row_range[0] = i;
                row_range[1] = i+1;
            }

            if (j > 0 && j < (_columns-1))
            {
                column_range[0] = j-1;
                column_range[1] = j+1;
            }else if (j > 0)
            {
                column_range[0] = j-1;
                column_range[1] = j;
            }else{
                column_range[0] = j;
                column_range[1] = j+1;
            }

            count_mines = 0;

            for (uint16_t m = row_range[0]; m <= row_range[1]; m++)
            {
                for (uint16_t n = column_range[0]; n <= column_range[1]; n++)
                {
                    if (Map[m][n] == 9)
                    {
                        count_mines++;
                    }
                }
            }
            
            if (Map[i][j] != 9)
            {
                _Fields[i*_columns+j]->setFieldNearMines(count_mines);
                _Fields[i*_columns+j]->setFieldIsMine(false);
            }else{
                _Fields[i*_columns+j]->setFieldNearMines(9);
                _Fields[i*_columns+j]->setFieldIsMine(true);
            }
        }
    }
    delete unallowed_Fields;
}

void MainWindow::Settings()
{
    _Settings_Window = new QWidget;

    QLabel *label_number_rows = new QLabel("Number Rows");
    QLabel *label_number_columns = new QLabel("Number Columns");
    QLabel *label_number_mines = new QLabel("Number Mines");
    QLabel *label_field_size = new QLabel("Field Size");

    _edit_number_rows = new QLineEdit();
    _edit_number_columns = new QLineEdit();
    _edit_number_mines = new QLineEdit();
    _edit_field_size = new QLineEdit();

    resetSettings();

    //_edit_number_rows->setValidator(new QIntValidator(5, 100));
    //_edit_number_columns->setValidator(new QIntValidator(5, 100));
    //_edit_number_mines->setValidator(new QIntValidator(1, 100));
    //_edit_field_size->setValidator(new QIntValidator(1, 50));

    QPushButton *button_set = new QPushButton("Set");
    QPushButton *button_reset = new QPushButton("Reset");
    QPushButton *button_cancel = new QPushButton("Cancel");

    QVBoxLayout *main_layout = new QVBoxLayout(_Settings_Window);

    QFormLayout *settings_layout = new QFormLayout(_Settings_Window);
    settings_layout->addRow(label_number_rows, _edit_number_rows);
    settings_layout->addRow(label_number_columns, _edit_number_columns);
    settings_layout->addRow(label_number_mines, _edit_number_mines);
    settings_layout->addRow(label_field_size, _edit_field_size);
    
    QHBoxLayout *button_layout = new QHBoxLayout(_Settings_Window);
    button_layout->addWidget(button_set);
    button_layout->addWidget(button_reset);
    button_layout->addWidget(button_cancel);

    main_layout->addLayout(settings_layout);
    main_layout->addLayout(button_layout);

    connect(button_set, &QPushButton::clicked, this, [this]{setSettings(); });
    connect(button_reset, &QPushButton::clicked, this, [this]{resetSettings(); });
    connect(button_cancel, &QPushButton::clicked, this, [this]{closeSettings(); });

    _Settings_Window->show();
}

uint16_t MainWindow::getNumRows()    {return _rows;}
uint16_t MainWindow::getNumColumns() {return _columns;}
uint16_t MainWindow::getNumMines()   {return _sum_mines;}
uint16_t MainWindow::getFieldSize()  {return _field_size;}

void MainWindow::setNumRows(uint16_t Value)    {_rows = Value;}
void MainWindow::setNumColumns(uint16_t Value) {_columns = Value;}
void MainWindow::setNumMines(uint16_t Value)   {_sum_mines = Value;}
void MainWindow::setFieldSize(uint16_t Value)  {_field_size = Value;}

void MainWindow::setSettings()
{
    setNumRows(_edit_number_rows->text().toInt());
    setNumColumns(_edit_number_columns->text().toInt());
    setNumMines(_edit_number_mines->text().toInt());
    setFieldSize(_edit_field_size->text().toInt());

    _Settings_Window->close();
}

void MainWindow::resetSettings()
{
    _edit_number_rows->setText(QString::number(getNumRows()));
    _edit_number_columns->setText(QString::number(getNumColumns()));
    _edit_number_mines->setText(QString::number(getNumMines()));
    _edit_field_size->setText(QString::number(getFieldSize()));
}

void MainWindow::closeSettings()
{
    _Settings_Window->close();
}

int16_t* MainWindow::getNearFields(uint16_t Field_ID)
{
    int16_t *near_Fields = new int16_t[9]{-1,-1,-1,-1,-1,-1,-1,-1,-1};


    if (((Field_ID/_columns) > 0) && ((Field_ID/_columns) < _rows-1)) // if selected field is between the top and bottom row
    {
        if (((Field_ID % _columns) > 0) && ((Field_ID % _columns) < _columns-1))
        {
            // if selected field is between the top and bottom row and between the left and right column
            near_Fields[0] = Field_ID - _columns - 1;       // Top-Left
            near_Fields[1] = Field_ID - _columns;           // Top
            near_Fields[2] = Field_ID - _columns + 1;       // Top-Right
            near_Fields[3] = Field_ID - 1;                  // Left
            near_Fields[4] = Field_ID;                      // Field
            near_Fields[5] = Field_ID + 1;                  // Right
            near_Fields[6] = Field_ID + _columns - 1;       // Bottom-Left
            near_Fields[7] = Field_ID + _columns;           // Bottom
            near_Fields[8] = Field_ID + _columns + 1;       // Bottom-Right

        }else if ((Field_ID % _columns) > 0)
        {
            // if selected field is between the top and bottom row and in the right column
            near_Fields[0] = Field_ID - _columns - 1;       // Top-Left
            near_Fields[1] = Field_ID - _columns;           // Top
            near_Fields[2] = Field_ID - 1;                  // Left
            near_Fields[3] = Field_ID;                      // Field
            near_Fields[4] = Field_ID + _columns - 1;       // Bottom-Left
            near_Fields[5] = Field_ID + _columns;           // Bottom

        }else{
            // if selected field is between the top and bottom row and in the left column
            near_Fields[0] = Field_ID - _columns;           // Top
            near_Fields[1] = Field_ID - _columns + 1;       // Top-Right
            near_Fields[2] = Field_ID;                      // Field
            near_Fields[3] = Field_ID + 1;                  // Right
            near_Fields[4] = Field_ID + _columns;           // Bottom
            near_Fields[5] = Field_ID + _columns + 1;       // Bottom-Right
        }
    }else if ((Field_ID/_columns) > 0) // if selected field is in the bottom row
    {
        if (((Field_ID % _columns) > 0) && ((Field_ID % _columns) < _columns-1))
        {
            // if selected field is in the bottom row and between the left and right column
            near_Fields[0] = Field_ID - _columns - 1;       // Top-Left
            near_Fields[1] = Field_ID - _columns;           // Top
            near_Fields[2] = Field_ID - _columns + 1;       // Top-Right
            near_Fields[3] = Field_ID - 1;                  // Left
            near_Fields[4] = Field_ID;                      // Field
            near_Fields[5] = Field_ID + 1;                  // Right

        }else if ((Field_ID % _columns) > 0)
        {
            // if selected field is in the bottom row and in the right column
            near_Fields[0] = Field_ID - _columns - 1;       // Top-Left
            near_Fields[1] = Field_ID - _columns;           // Top
            near_Fields[2] = Field_ID - 1;                  // Left
            near_Fields[3] = Field_ID;                      // Field

        }else{
            // if selected field is in the bottom row and in the left column
            near_Fields[0] = Field_ID - _columns;           // Top
            near_Fields[1] = Field_ID - _columns + 1;       // Top-Right
            near_Fields[2] = Field_ID;                      // Field
            near_Fields[3] = Field_ID + 1;                  // Right
        }
    }else{  // if selected field is in the top row
        if (((Field_ID % _columns) > 0) && ((Field_ID % _columns) < _columns-1))
        {
            // if selected field in the top row and between the left and right column
            near_Fields[0] = Field_ID - 1;                  // Left
            near_Fields[1] = Field_ID;                      // Field
            near_Fields[2] = Field_ID + 1;                  // Right
            near_Fields[3] = Field_ID + _columns - 1;       // Bottom-Left
            near_Fields[4] = Field_ID + _columns;           // Bottom
            near_Fields[5] = Field_ID + _columns + 1;       // Bottom-Right

        }else if ((Field_ID % _columns) > 0)
        {
            // if selected field in the top row and in the right column
            near_Fields[0] = Field_ID - 1;                  // Left
            near_Fields[1] = Field_ID;                      // Field
            near_Fields[2] = Field_ID + _columns - 1;       // Bottom-Left
            near_Fields[3] = Field_ID + _columns;           // Bottom

        }else{
            
            // if selected field in the top row and in the left column
            near_Fields[0] = Field_ID;                      // Field
            near_Fields[1] = Field_ID + 1;                  // Right
            near_Fields[2] = Field_ID + _columns;           // Bottom
            near_Fields[3] = Field_ID + _columns + 1;       // Bottom-Right
        }
    }

    return near_Fields;
}