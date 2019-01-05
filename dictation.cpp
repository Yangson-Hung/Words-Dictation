#include "dictation.h"
#include "tts.h"
#include "getaudiothread.h"
#include "warningbox.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtWinExtras>

Dictation::Dictation(QWidget *parent) : QWidget(parent)
{
    create_window_widgets();
    stylize();

    connect(btn_import_text,SIGNAL(clicked()),this,SLOT(slot_import_text()));
    connect(btn_begin_dictate,SIGNAL(clicked()),this,SLOT(slot_begin_dictate()));
}

Dictation::~Dictation()
{

}

void Dictation::create_window_widgets()
{
    /*创建布局*/
    layout_h_left_select_vioce = new QHBoxLayout();
    layout_h_left_dictate_time_interval = new QHBoxLayout();
    layout_v_right = new QVBoxLayout();
    layout_h_main = new QGridLayout(this);


    /*创建按钮*/
    btn_import_text = new QPushButton();
    btn_begin_dictate = new QPushButton();
    btn_radio_vioce_man = new QRadioButton();
    btn_radio_vioce_woman = new QRadioButton();


    btn_import_text->setText(tr("导入文本"));
    btn_begin_dictate->setText(tr("开始听写"));
    btn_radio_vioce_man->setText(tr("男"));
    btn_radio_vioce_woman->setText(tr("女"));

    btn_radio_vioce_woman->setChecked(true);


    /*创建标签*/
    label_select_vioce = new QLabel();
    label_dictate_time_interval = new QLabel();

    label_select_vioce->setText(tr("选择发音人"));
    label_dictate_time_interval->setText(tr("听写间隔时间"));

    /*创建下拉列表框*/
    combo_box_dictate_time_interval = new QComboBox();

    combo_box_dictate_time_interval->insertItem(0,tr("3s"));
    combo_box_dictate_time_interval->insertItem(1,tr("5s"));

    /*添加窗口部件*/

    /*左边部件*/
    layout_h_left_select_vioce->addWidget(label_select_vioce);
    layout_h_left_select_vioce->addWidget(btn_radio_vioce_woman);
    layout_h_left_select_vioce->addWidget(btn_radio_vioce_man);
    layout_h_left_dictate_time_interval->addWidget(label_dictate_time_interval);
    layout_h_left_dictate_time_interval->addWidget(combo_box_dictate_time_interval);

    /*右边部件*/
    layout_v_right->addWidget(btn_import_text);
    layout_v_right->addWidget(btn_begin_dictate);

    /*主布局添加子布局*/
    layout_h_main->addLayout(layout_h_left_select_vioce,0,0);
    layout_h_main->addLayout(layout_h_left_dictate_time_interval,1,0);
    layout_h_main->addLayout(layout_v_right,0,1,2,2);
}


void Dictation::set_voice()
{
    if (btn_radio_vioce_man->isChecked()) {
        voice_name = XIAOFENG;
    } else if (btn_radio_vioce_woman->isChecked()) {
        voice_name = XIAOYAN;
    }
}


void Dictation::stylize()
{
    if (QOperatingSystemVersion::current() < QOperatingSystemVersion::Windows8) {
        //在WIN7下实现窗口的毛玻璃效果
        if (QtWin::isCompositionEnabled()) {
            QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1); //玻璃效果
            setAttribute(Qt::WA_TranslucentBackground, true); //半透明背景
            setStyleSheet(QStringLiteral("dictation { background: transparent; }"));
        } else {
            QtWin::resetExtendedFrame(this);
            setAttribute(Qt::WA_TranslucentBackground, false);
            setStyleSheet(QStringLiteral("dictation { background: %1; }").arg(QtWin::realColorizationColor().name()));
        }
    }
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}


void Dictation::slot_import_text()
{
    /*获得文件名*/
    QString file_name = QFileDialog::getOpenFileName(this,tr("打开文件"),"/",tr("Text files (*.txt)"));
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
        /*当语音合成结束时，将线程结束*/
        if (getaudio->get_over()) {
            getaudio->terminate(); //终止线程
            getaudio->wait(); //等待线程阻塞
        }
    } else {
        /*未导入文本时提示*/
        WarningBox warning_box; //定义警告消息框
        warning_box.setWindowTitle(tr("提示")); //标题
        warning_box.addButton(tr("确定"),QMessageBox:: ActionRole); //添加按钮
        warning_box.setText(tr("请先导入文件！")); //设置文字提醒信息
        warning_box.exec(); //显示此警告消息狂
    }
}
