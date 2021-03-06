#ifndef SPC_ECHO_HHHH
#define SPC_ECHO_HHHH

#include <stdint.h>
//#include <SDL2/SDL_types.h>
//#include <SDL2/SDL_audio.h>

#ifndef AUDIO_U8
#define AUDIO_U8        0x0008  /**< Unsigned 8-bit samples */
#define AUDIO_S8        0x8008  /**< Signed 8-bit samples */
#define AUDIO_U16LSB    0x0010  /**< Unsigned 16-bit samples */
#define AUDIO_S16LSB    0x8010  /**< Signed 16-bit samples */
#define AUDIO_U16MSB    0x1010  /**< As above, but big-endian byte order */
#define AUDIO_S16MSB    0x9010  /**< As above, but big-endian byte order */
#define AUDIO_U16       AUDIO_U16LSB
#define AUDIO_S16       AUDIO_S16LSB
#define AUDIO_S32LSB    0x8020  /**< 32-bit integer samples */
#define AUDIO_S32MSB    0x9020  /**< As above, but big-endian byte order */
#define AUDIO_S32       AUDIO_S32LSB
#define AUDIO_F32LSB    0x8120  /**< 32-bit floating point samples */
#define AUDIO_F32MSB    0x9120  /**< As above, but big-endian byte order */
#define AUDIO_F32       AUDIO_F32LSB
#endif


struct SpcEcho;

extern SpcEcho *echoEffectInit(int rate, uint16_t format, int channels);
extern void echoEffectFree(SpcEcho *context);

enum EchoSetup
{
    ECHO_EON = 0,
    ECHO_EDL,
    ECHO_EFB,

    ECHO_MVOLL,
    ECHO_MVOLR,
    ECHO_EVOLL,
    ECHO_EVOLR,

    ECHO_FIR0,
    ECHO_FIR1,
    ECHO_FIR2,
    ECHO_FIR3,
    ECHO_FIR4,
    ECHO_FIR5,
    ECHO_FIR6,
    ECHO_FIR7
};

extern void spcEchoEffect(int chan, void *stream, int len, void *context);

extern void echoEffectResetFir(SpcEcho *out);
extern void echoEffectResetDefaults(SpcEcho *out);

extern void echoEffectSetReg(SpcEcho *out, EchoSetup key, int val);
extern int  echoEffectGetReg(SpcEcho *out, EchoSetup key);

#endif // SPC_ECHO_HHHH
