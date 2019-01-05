#ifndef DICTATION_H
#define DICTATION_H

#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include "getaudiothread.h"

#if _MSC_VER >= 1910
#pragma execution_character_set("utf-8")
#endif

const QString XIAOYAN = "xiaoyan";
const QString XIAOFENG = "xiaofeng";

class Dictation : public QWidget
{
    Q_OBJECT
public:
    explicit Dictation(QWidget *parent = nullptr);

    ~Dictation();

    void create_window_widgets();

private:
    /*组件*/
    QPushButton *btn_begin_dictate = nullptr;
    QPushButton *btn_import_text = nullptr;
    QRadioButton *btn_radio_vioce_man = nullptr;
    QRadioButton *btn_radio_vioce_woman = nullptr;
    QLabel *label_select_vioce = nullptr;
    QLabel *label_dictate_time_interval = nullptr;
    QComboBox *combo_box_dictate_time_interval = nullptr;
    QHBoxLayout *layout_h_left_select_vioce = nullptr;
    QHBoxLayout *layout_h_left_dictate_time_interval = nullptr;
    QVBoxLayout *layout_v_right = nullptr;
    QGridLayout *layout_h_main = nullptr;

    /*变量*/
    QString voice_name;
    QVector<QString> qstr_vector;
    bool is_import_text = false;

    /*获得音频的线程*/
    GetAudioThread *getaudio = nullptr;

    /*函数*/
    void set_voice();
    void stylize();

private slots:
    void slot_import_text();
    void slot_begin_dictate();
};

#endif // DICTATION_H
