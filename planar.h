#ifndef	PLANAR_H
#define	PLANAR_H

#include "avxsynth.h"

extern const int plane[];

class	PlanarAccess
{
private:
	int	planeoffset[3];
	int (__stdcall PlanarAccess::*_GetPitch)(avxsynth::VideoFrame *frame, int i);
	const BYTE* (__stdcall PlanarAccess::*_GetReadPtr)(avxsynth::VideoFrame *frame, int i);
	BYTE* (__stdcall PlanarAccess::*_GetWritePtr)(avxsynth::VideoFrame *frame, int i);

	int __stdcall &YV12_GetPitch(avxsynth::VideoFrame *frame, int i);
	
	int __stdcall &YUY2_GetPitch(avxsynth::VideoFrame *frame, int i);

	const BYTE *__stdcall &YV12_GetReadPtr(avxsynth::VideoFrame *frame, int i);

	const BYTE *__stdcall &YUY2_GetReadPtr(avxsynth::VideoFrame *frame, int i);

	BYTE *__stdcall &YV12_GetWritePtr(avxsynth::VideoFrame *frame, int i);

	BYTE *__stdcall &YUY2_GetWritePtr(avxsynth::VideoFrame *frame, int i);

public:
	int	width[3];
	int	height[3];
	int	planes;

	inline int GetPitch(avxsynth::PVideoFrame &frame, int i)
	{
		return	(this->*_GetPitch)(frame.operator ->(), i);
	}

	inline const BYTE * GetReadPtr(avxsynth::PVideoFrame &frame, int i)
	{
		return	(this->*_GetReadPtr)(frame.operator ->(), i);
	}

	inline BYTE * GetWritePtr(avxsynth::PVideoFrame &frame, int i)
	{
		return	(this->*_GetWritePtr)(frame.operator ->(), i);
	}

	PlanarAccess(const avxsynth::VideoInfo &vi, bool planar = true);
};

// The two subsequent classes have nothing to do with PlanarAccess, but they provide an analogous
// service, namely to assure that the frames of the child have always the same pitch.
// Unfortunately only the original, not neccessary aligned frames are cached by Avisynth

class HomogeneousChild 
{
	avxsynth::PClip	child;
	int		planes;
	int		width[3], height[3];
	avxsynth::VideoInfo vi;

public:
	avxsynth::PVideoFrame __stdcall GetFrame(int n, avxsynth::IScriptEnvironment* env);
	void __stdcall GetAudio(void* buf, __int64 start, __int64 count, avxsynth::IScriptEnvironment* env) { child->GetAudio(buf, start, count, env); }
	const avxsynth::VideoInfo& __stdcall GetVideoInfo() { return vi; }
	bool __stdcall GetParity(int n) { return child->GetParity(n); }
	void __stdcall SetCacheHints(int cachehints,int frame_range) { child->SetCacheHints(cachehints, frame_range); } 
	int		pitch[3];
	HomogeneousChild* operator->() { return this; }
	HomogeneousChild(avxsynth::PClip _child, bool grey, avxsynth::IScriptEnvironment* env);
};


class HomogeneousVideoFilter : public avxsynth::IClip // Replacement for GenericVideoFilter
{
	HomogeneousChild child;
public:
	avxsynth::VideoInfo vi;
	HomogeneousVideoFilter(avxsynth::PClip _child, bool grey, avxsynth::IScriptEnvironment* env) : child(_child, grey, env) { vi = _child->GetVideoInfo(); }
	avxsynth::PVideoFrame __stdcall GetFrame(int n, avxsynth::IScriptEnvironment* env) { return child->GetFrame(n, env); }
	void __stdcall GetAudio(void* buf, __int64 start, __int64 count, avxsynth::IScriptEnvironment* env) { child->GetAudio(buf, start, count, env); }
	const avxsynth::VideoInfo& __stdcall GetVideoInfo() { return vi; }
	bool __stdcall GetParity(int n) { return child->GetParity(n); }
	void __stdcall SetCacheHints(int cachehints,int frame_range) { } ;  
};
#endif // PLANAR_H
