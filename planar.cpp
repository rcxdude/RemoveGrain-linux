#define VC_EXTRALEAN 
#include "wrap_windows.h"
#include "planar.h"

#if	1
void	debug_printf(const char *format, ...);
#endif

using namespace avxsynth;

const	int		plane[3] = {PLANAR_Y, PLANAR_U, PLANAR_V};

int __stdcall PlanarAccess::YV12_GetPitch(VideoFrame *frame, int i)
{
	return	frame->GetPitch(plane[i]);
}
	
int __stdcall PlanarAccess::YUY2_GetPitch(VideoFrame *frame, int i)
{
	return	frame->GetPitch();	
}

const BYTE *__stdcall PlanarAccess::YV12_GetReadPtr(VideoFrame *frame, int i)
{
	return	frame->GetReadPtr(plane[i]);
}

const BYTE *__stdcall PlanarAccess::YUY2_GetReadPtr(VideoFrame *frame, int i)
{
	return	frame->GetReadPtr() + planeoffset[i];
}

BYTE *__stdcall PlanarAccess::YV12_GetWritePtr(VideoFrame *frame, int i)
{
	return	frame->GetWritePtr(plane[i]);
}

BYTE *__stdcall PlanarAccess::YUY2_GetWritePtr(VideoFrame *frame, int i)
{
	return	frame->GetWritePtr() + planeoffset[i];
}


PlanarAccess::PlanarAccess(const VideoInfo &vi, bool planar)
{
	_GetPitch = YUY2_GetPitch;
	_GetReadPtr = YUY2_GetReadPtr;
	_GetWritePtr = YUY2_GetWritePtr;
	width[1] = width[0] = vi.width;
	height[1] = height[0] = vi.height;
	if( vi.IsYUV() )
	{
		width[1] /= 2;
		if( vi.IsYV12() )
		{
			height[1] /= 2;
			_GetPitch = YV12_GetPitch;
			_GetReadPtr = YV12_GetReadPtr;
			_GetWritePtr = YV12_GetWritePtr;
		}
	}
	width[2] = width[1];
	height[2] = height[1];
	planeoffset[0] = 0;
	planeoffset[1] = width[0];
	planeoffset[2] = planeoffset[1] + width[1];
	planes = 2;

	if( planar + vi.IsYV12() == 0 ) 
	{
		planes = 0;
		width[0] = vi.RowSize();
	}
}

HomogeneousChild::HomogeneousChild(PClip _child, bool grey, IScriptEnvironment* env) : child(_child)
{
	vi = _child->GetVideoInfo();
	width[2] = width[1] = (width[0] = vi.width) / 2;
	height[2] = height[1] = (height[0] = vi.height) / 2;
	
	if( !vi.IsYV12() )
	{
		if( !grey ) width[0] = vi.RowSize();
		grey = true;
	}

	PVideoFrame nf = env->NewVideoFrame(vi);
	pitch[0] = nf->GetPitch();

	if( vi.IsYV12() )
	{
		pitch[1] = nf->GetPitch(PLANAR_U);
	}
	else
	{
		if( !grey ) width[0] = vi.RowSize();
		pitch[1] = pitch[0];
		grey = true;
	}
	planes = 2*(1-grey);
	pitch[2] = pitch[1];
}

PVideoFrame __stdcall HomogeneousChild::GetFrame(int n, IScriptEnvironment* env)
{
	PVideoFrame rf = child->GetFrame(n, env);
	if( rf->GetPitch() - pitch[0] == 0 ) return rf;
	PVideoFrame nf = env->NewVideoFrame(vi);
	int i = planes;
	do
	{
		int j = plane[i];
		env->BitBlt(nf->GetWritePtr(j), pitch[i], rf->GetReadPtr(j), rf->GetPitch(j), width[i], height[i]);
	} while( --i >= 0 );
	return nf;
}
