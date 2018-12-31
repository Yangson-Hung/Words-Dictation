#include "dictation.h"

dictation::dictation(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(500,500);
    setWindowTitle(tr("单词听写"));
    setWindowIcon(QIcon(":/new/prefix1/ico.ico"));
    create_window_widget();
}

dictation::~dictation()
{

}

void dictation::create_window_widget()
{
    /*create layouts*/
    layout_h_left_select_vioce = new QHBoxLayout();
    layout_h_left_dictate_time_interval = new QHBoxLayout();
    layout_v_right = new QVBoxLayout();
    layout_h_main = new QGridLayout(this);


    /*create buttons*/
    btn_import_text = new QPushButton();
    btn_begin_dictate = new QPushButton();
    btn_radio_vioce_man = new QRadioButton();
    btn_radio_vioce_woman = new QRadioButton();

    btn_import_text->setText(tr("导入文本"));
    btn_begin_dictate->setText(tr("开始听写"));
    btn_radio_vioce_man->setText(tr("男"));
    btn_radio_vioce_woman->setText(tr("女"));


    /*create labels*/
    label_select_vioce = new QLabel();
    label_dictate_time_interval = new QLabel();

    label_select_vioce->setText(tr("选择发音人"));
    label_dictate_time_interval->setText(tr("听写间隔时间"));


    /*create comboBox*/
    combo_box_dictate_time_interval = new QComboBox();

    combo_box_dictate_time_interval->insertItem(0,tr("3s"));
    combo_box_dictate_time_interval->insertItem(1,tr("5s"));


    /*add widgets*/

    //left
    layout_h_left_select_vioce->addWidget(label_select_vioce);
    layout_h_left_select_vioce->addWidget(btn_radio_vioce_man);
    layout_h_left_select_vioce->addWidget(btn_radio_vioce_woman);
    layout_h_left_dictate_time_interval->addWidget(label_dictate_time_interval);
    layout_h_left_dictate_time_interval->addWidget(combo_box_dictate_time_interval);

    //right
    layout_v_right->addWidget(btn_import_text);
    layout_v_right->addWidget(btn_begin_dictate);

    //main
    layout_h_main->addLayout(layout_h_left_select_vioce,0,0);
    layout_h_main->addLayout(layout_h_left_dictate_time_interval,1,0);
    layout_h_main->addLayout(layout_v_right,0,1,2,2);
}
