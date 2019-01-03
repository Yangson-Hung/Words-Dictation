#include "getaudiothread.h"
#include "tts.h"
#include "dictation.h"


GetAudioThread::GetAudioThread(QVector<QString> &in_qstr_vector, QString &in_voice_name)
{
    qstr_vector = in_qstr_vector;
    voice_name = in_voice_name;
}

void GetAudioThread::run()
{
    for (int i = 0; i < qstr_vector.size(); ++i) {
        begin_tts(qstr_vector[i],qstr_vector[i],voice_name);
    }
}
