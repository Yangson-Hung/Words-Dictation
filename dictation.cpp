#include "dictation.h"
#include "tts.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "getaudiothread.h"

Dictation::Dictation(QWidget *parent) : QWidget(parent)
{
    create_window_widgets();

    connect(btn_import_text,SIGNAL(clicked()),this,SLOT(slot_import_text()));
    connect(btn_begin_dictate,SIGNAL(clicked()),this,SLOT(slot_begin_dictate()));
}

Dictation::~Dictation()
{

}

void Dictation::create_window_widgets()
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

    btn_radio_vioce_woman->setChecked(true);


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
    layout_h_left_select_vioce->addWidget(btn_radio_vioce_woman);
    layout_h_left_select_vioce->addWidget(btn_radio_vioce_man);
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


void Dictation::set_voice()
{
    if (btn_radio_vioce_man->isChecked()) {
        voice_name = JOHN;
    } else if (btn_radio_vioce_woman->isChecked()) {
        voice_name = CATHERINE;
    }
}


void Dictation::slot_import_text()
{
    /*获得文件名*/
    QString file_name = QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("Text files (*.txt)"));
    /* 当未获得文件名时，不往下执行
     * 如果没有这个if判断，会在控制台出现
     * "QFSFileEngine::open: No file name specified"提示
    */
    if (file_name.isEmpty()) {
        return;
    }
    QFile file(file_name); //给“文件”设置文件名
    /*以只读方式打开*/
    if (file.open(QFile::ReadOnly)) {
        QTextStream text_stream_in(&file); //定义QTextStream的输入流
        /*当读取的不是最后一行时*/
        while (!text_stream_in.atEnd()) {
            qstr_vector.push_back(text_stream_in.readLine()); //将读取内容保存到QString容器中
        }
        is_import_text = true; //文件已经导入的标志
    }
}


void Dictation::slot_begin_dictate()
{
    /*导入文本后执行语音合成*/
    if (is_import_text) {
        set_voice(); //发音人选择
        getaudio = new GetAudioThread(qstr_vector,voice_name); //新建获得音频的线程
        getaudio->start(); //开启线程

//        /*当语音合成结束时，将线程结束*/
//        if (getaudio->get_over()) {
//            getaudio->terminate(); //终止线程
//            getaudio->wait(); //等待线程阻塞
//        }
    } else {
        /*未导入文本时提示*/
        QMessageBox::warning(this,tr("提示"),tr("请先导入文件"),tr("确定"));
    }
}
