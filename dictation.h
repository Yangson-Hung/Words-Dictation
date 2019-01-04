#ifndef DICTATION_H
#define DICTATION_H

#include <QWidget>
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
    QPushButton *btn_begin_dictate;
    QPushButton *btn_import_text;
    QRadioButton *btn_radio_vioce_man;
    QRadioButton *btn_radio_vioce_woman;
    QLabel *label_select_vioce;
    QLabel *label_dictate_time_interval;
    QComboBox *combo_box_dictate_time_interval;
    QHBoxLayout *layout_h_left_select_vioce;
    QHBoxLayout *layout_h_left_dictate_time_interval;
    QVBoxLayout *layout_v_right;
    QGridLayout *layout_h_main;

    QString voice_name;
    QVector<QString> qstr_vector;
    GetAudioThread *getaudio;
    bool is_import_text = false;
    void set_voice();

private slots:
    void slot_import_text();

    void slot_begin_dictate();
};

#endif // DICTATION_H
