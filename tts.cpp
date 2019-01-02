#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <errno.h>

#include "tts/qtts.h"
#include "tts/msp_cmn.h"
#include "tts/msp_errors.h"
#include "tts.h"

wave_pcm_hdr default_wav_hdr =
{
    { 'R', 'I', 'F', 'F' },
    0,
    {'W', 'A', 'V', 'E'},
    {'f', 'm', 't', ' '},
    16,
    1,
    1,
    16000,
    32000,
    2,
    16,
    {'d', 'a', 't', 'a'},
    0
};

int text_to_speech(const char* src_text, const char* des_path, const char* params)
{
    int          ret = -1;
    FILE*        fp = NULL;
    const char*  sessionID = NULL;
    unsigned int audio_len = 0;
    wave_pcm_hdr wav_hdr = default_wav_hdr;
    int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

    if (NULL == src_text || NULL == des_path)
    {
        return ret;
    }
    fp = fopen(des_path, "wb");
    if (NULL == fp)
    {
        return ret;
    }
    sessionID = QTTSSessionBegin(params, &ret);
    if (MSP_SUCCESS != ret)
    {
        fclose(fp);
        return ret;
    }
    ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
    if (MSP_SUCCESS != ret)
    {
        QTTSSessionEnd(sessionID, "TextPutError");
        fclose(fp);
        return ret;
    }
    fwrite(&wav_hdr, sizeof(wav_hdr), 1, fp);
    while (1)
    {
        const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
        if (MSP_SUCCESS != ret)
            break;
        if (NULL != data)
        {
            fwrite(data, audio_len, 1, fp);
            wav_hdr.data_size += audio_len;
        }
        if (MSP_TTS_FLAG_DATA_END == synth_status)
            break;
    }
    if (MSP_SUCCESS != ret)
    {
        QTTSSessionEnd(sessionID, "AudioGetError");
        fclose(fp);
        return ret;
    }
    wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);

    fseek(fp, 4, 0);
    fwrite(&wav_hdr.size_8, sizeof(wav_hdr.size_8), 1, fp);
    fseek(fp, 40, 0);
    fwrite(&wav_hdr.data_size, sizeof(wav_hdr.data_size), 1, fp);
    fclose(fp);
    fp = NULL;

    ret = QTTSSessionEnd(sessionID, "Normal");

    return ret;
}

void begin_tts(const char* in_text, const char* in_filename, QString voice_name)
{
    int         ret = MSP_SUCCESS;

    QString params_head = "voice_name = ";
    QString params_tail = ", text_encoding = UTF8, sample_rate = 16000, speed = 30, volume = 100, pitch = 50, rdn = 2";
    QString tmp = params_head + voice_name + params_tail;
    QByteArray params_combined = tmp.toLatin1();

    const char* login_params = "appid = 5c25c3f2, work_dir = .";
    const char* session_begin_params = params_combined.data();
    const char* filename = in_filename;
    const char* text = in_text;

    ret = MSPLogin(NULL, NULL, login_params);
    if (MSP_SUCCESS != ret)
    {
        MSPLogout();
    }

    ret = text_to_speech(text, filename, session_begin_params);

    MSPLogout();

}
