#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <conio.h>
#include <errno.h>

#include "tts/qtts.h"
#include "tts/msp_cmn.h"
#include "tts/msp_errors.h"
#include "tts.h"
#include <qt_windows.h>

static wave_pcm_hdr default_wav_hdr =
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
    FILE*        fp = nullptr;
    const char*  sessionID = nullptr;
    unsigned int audio_len = 0;
    wave_pcm_hdr wav_hdr = default_wav_hdr;
    int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

    if (nullptr == src_text || nullptr == des_path)
    {
        return ret;
    }
    fp = fopen(des_path, "wb");
    if (nullptr == fp)
    {
        return ret;
    }
    sessionID = QTTSSessionBegin(params, &ret);
    if (MSP_SUCCESS != ret)
    {
        fclose(fp);
        return ret;
    }
    ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), nullptr);
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
        if (nullptr != data)
        {
            fwrite(data, audio_len, 1, fp);
            wav_hdr.data_size += audio_len;
        }
        if (MSP_TTS_FLAG_DATA_END == synth_status)
            break;
        //Sleep(150);
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
    fp = nullptr;

    ret = QTTSSessionEnd(sessionID, "Normal");

    return ret;
}

void begin_tts(QString in_text, QString in_filename, QString in_voice_name)
{
    int         ret = MSP_SUCCESS;
    const char* login_params = "appid = 5c25c3f2, work_dir = .";//登录参数,appid与msc库绑定,请勿随意改动
    const QString file_format = ".wav";

    QByteArray text_ba = in_text.toLatin1();
    QByteArray filename_ba = (in_filename + file_format).toLatin1();

    const char* text = text_ba.data();
    const char* filename = filename_ba.data();

    /*
    * rdn:           合成音频数字发音方式
    * volume:        合成音频的音量
    * pitch:         合成音频的音调
    * speed:         合成音频对应的语速
    * voice_name:    合成发音人
    * sample_rate:   合成音频采样率
    * text_encoding: 合成文本编码格式
    *
    */
    QString params_head = "voice_name = ";
    QString params_tail = ", text_encoding = UTF8, sample_rate = 16000, speed = 50, volume = 100, pitch = 50, rdn = 2";
    QByteArray session_begin_params_ba = (params_head + in_voice_name + params_tail).toLatin1();
    const char* session_begin_params = session_begin_params_ba.data();

    ret = MSPLogin(nullptr, nullptr, login_params);
    if (MSP_SUCCESS != ret)
    {
        MSPLogout();
    }

    ret = text_to_speech(text, filename, session_begin_params);

    MSPLogout();

}
