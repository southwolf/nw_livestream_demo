#include "sdk/include/nlss_api.h"
#include <node.h>

namespace live
{

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;

bool initDeviceLiveStream(_HNLSSERVICE hNLSService, char *pVideoPath, char *pAudioPath)
{
    bool have_video_source = true;
    bool have_audio_source = true;
    ST_NLSS_PARAM stParam;

    Nlss_GetDefaultParam(hNLSService, &stParam);
    stParam.stVideoParam.iOutFps = 15;
    stParam.stVideoParam.enInType = EN_NLSS_VIDEOIN_CAMERA;
    stParam.stVideoParam.u.stInCamera.paDevicePath = pVideoPath;
    stParam.stVideoParam.u.stInCamera.enLvl = EN_NLSS_VIDEOQUALITY_MIDDLE;

    stParam.stAudioParam.iInSamplerate = 44100;
    stParam.stAudioParam.enInType = EN_NLSS_AUDIOIN_MIC;
    stParam.stAudioParam.paaudioDeviceName = pAudioPath;


    if (have_audio_source && have_video_source)
        stParam.enOutContent = EN_NLSS_OUTCONTENT_AV;//默认音视频设备都存在则推流音视频，当然，也可以设置成音频/视频，
    else if (have_audio_source && !have_video_source)
        stParam.enOutContent = EN_NLSS_OUTCONTENT_AUDIO;
    else if (have_video_source && !have_audio_source)
        stParam.enOutContent = EN_NLSS_OUTCONTENT_VIDEO;
    else if (!have_audio_source && !have_video_source)
    {
        return false;
    }

    stParam.paOutUrl = new char[1024];
    memset(stParam.paOutUrl, 0, 1024);
    strcpy(stParam.paOutUrl, "rtmp://pc40f45df.live.126.net/live/7dc6551e0bd3442b9317c59d113114ad?wsSecret=07e6b157a0d36e9ae019a248fa508d8e&wsTime=1488271949");

    if (NLSS_OK != Nlss_InitParam(hNLSService, &stParam))
    {
        delete[]stParam.paOutUrl;
        return false;
    }
    return true;
}

void   previewCB(ST_NLSS_VIDEO_SAMPLER *pstSampler)
{
    //可以进行预览画面显示
    return;
}

void statusCB(EN_NLSS_STATUS enStatus, EN_NLSS_ERRCODE enErrCode)
{
    //可以获取状态
    return;
}

void testSimpleCamera()
{
    int  m_iVideoDeviceNum = 0;
    int  m_iAudioDeviceNum = 0;
    ST_NLSS_INDEVICE_INF *m_pVideoDevices;
    ST_NLSS_INDEVICE_INF *m_pAudioDevices;
    Nlss_GetFreeDevicesNum(&m_iVideoDeviceNum, &m_iAudioDeviceNum);

    if (m_iVideoDeviceNum <= 0)
    {
        return;
    }
    else
    {
        m_pVideoDevices = new ST_NLSS_INDEVICE_INF[m_iVideoDeviceNum];
        for (int i = 0; i < m_iVideoDeviceNum; i++)
        {
            m_pVideoDevices[i].paPath = new char[1024];
            m_pVideoDevices[i].paFriendlyName = new char[1024];
        }
    }

    if (m_iAudioDeviceNum <= 0)
    {
        return;
    }
    else
    {
        m_pAudioDevices = new ST_NLSS_INDEVICE_INF[m_iAudioDeviceNum];

        for (int i = 0; i < m_iAudioDeviceNum; i++)
        {
            m_pAudioDevices[i].paPath = new char[1024];
            m_pAudioDevices[i].paFriendlyName = new char[1024];
        }
    }


    Nlss_GetFreeDeviceInf(m_pVideoDevices, m_pAudioDevices);

    _HNLSSERVICE hNLSService = NULL;
    Nlss_Create(NULL, &hNLSService);

    Nlss_SetVideoSamplerCB(hNLSService, previewCB);
    Nlss_SetStatusCB(hNLSService, statusCB);

    initDeviceLiveStream(hNLSService, (char *)m_pVideoDevices[0].paPath, (char *)m_pAudioDevices[0].paPath);

    Nlss_StartVideoCapture(hNLSService);
    Nlss_StartVideoPreview(hNLSService);
    Nlss_StartLiveStream(hNLSService);

    while(1) {
        
    }
    Nlss_StopLiveStream(hNLSService);
    Nlss_StopVideoPreview(hNLSService);
    Nlss_StopVideoCapture(hNLSService);

    Nlss_UninitParam(hNLSService);
    Nlss_Destroy(hNLSService);

}

void Method(const FunctionCallbackInfo<Value> &args)
{
    testSimpleCamera();
    Isolate *isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "World"));
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(live, init)

} // namespace live
