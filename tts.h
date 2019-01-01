#ifndef TTS_H
#define TTS_H


/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
    char            riff[4];
    int             size_8;
    char            wave[4];
    char            fmt[4];
    int             fmt_size;

    short int       format_tag;
    short int       channels;
    int             samples_per_sec;
    int             avg_bytes_per_sec;
    short int       block_align;
    short int       bits_per_sample;

    char            data[4];
    int             data_size;
} wave_pcm_hdr;

int text_to_speech(const char* src_text, const char* des_path, const char* params);
void begin_tts(const char* text, const char* filename);






#endif // TTS_H
