/*******************************************************************
 *
 *  Copyright 2005  David Turner, The FreeType Project (www.freetype.org)
 *  Copyright 2007  Trolltech ASA
 *
 *  This is part of HarfBuzz, an OpenType Layout engine library.
 *
 *  See the file name COPYING for licensing information.
 *
 ******************************************************************/
#ifndef HARFBUZZ_STREAM_H
#define HARFBUZZ_STREAM_H

#include <ft2build.h>
#include FT_FREETYPE_H

FT_BEGIN_HEADER

typedef struct HB_StreamRec_
{
    FT_Byte*             base;
    unsigned long        size;
    unsigned long        pos;
    
    FT_Byte*             cursor;
} HB_StreamRec, *HB_Stream;

FT_Error HB_open_stream(FT_Face face, FT_Tag tableTag, HB_Stream *stream);
void HB_close_stream(HB_Stream stream);


/* stream macros used by the OpenType parser */
#define  FILE_Pos()      stream->pos
#define  FILE_Seek(pos)  SET_ERR( _hb_ftglue_stream_seek( stream, pos ) )
#define  ACCESS_Frame(size)  SET_ERR( _hb_ftglue_stream_frame_enter( stream, size ) )
#define  FORGET_Frame()      _hb_ftglue_stream_frame_exit( stream )

#define  GET_Byte()      (*stream->cursor++)
#define  GET_Short()     (stream->cursor += 2, (FT_Short)( \
                              (*((stream->cursor)-2) << 8) |    \
                               *((stream->cursor)-1)             \
                              ))
#define  GET_Long()      (stream->cursor += 4, (FT_Long)( \
				(*((stream->cursor)-4) << 24) | \
				(*((stream->cursor)-3) << 16) | \
				(*((stream->cursor)-2) << 8) | \
				 *((stream->cursor)-1) \
			 ))


#define  GET_Char()      ((FT_Char)GET_Byte())
#define  GET_UShort()    ((FT_UShort)GET_Short())
#define  GET_ULong()     ((FT_ULong)GET_Long())
#define  GET_Tag4()      GET_ULong()

FT_Long _hb_ftglue_stream_pos( HB_Stream   stream );

FT_Error _hb_ftglue_stream_seek( HB_Stream   stream,
                    FT_Long     pos );

FT_Error _hb_ftglue_stream_frame_enter( HB_Stream   stream,
                           FT_ULong    size );

void _hb_ftglue_stream_frame_exit( HB_Stream  stream );

#endif
