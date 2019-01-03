#ifndef GETAUDIO_H
#define GETAUDIO_H

#include <QThread>
#include <QVector>

class GetAudioThread : public QThread
{
public:
    GetAudioThread(QVector<QString> &qstr_vector, QString &voice_name);

    bool get_over() const;

protected:
    void run();

private:
    QVector<QString> qstr_vector;
    QString voice_name;
    bool over = false;

};

#endif // GETAUDIO_H
