/*****************************************************************************
 * ffplayer.c
 *****************************************************************************
 *
 * copyright (c) 2001 Fabrice Bellard
 * copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "ffplayer.h"

#include <stdbool.h>

static bool g_ffmpeg_global_inited = false;
static pthread_mutex_t g_avcodec_mutex;

void ijkff_global_init()
{
    if (g_ffmpeg_global_inited)
        return;

    pthread_mutex_init(&g_avcodec_mutex, NULL);

    av_register_all();
    avcodec_register_all();

    avformat_network_init();

    g_ffmpeg_global_inited = true;
}

void ijkff_global_uninit()
{
    if (!g_ffmpeg_global_inited)
        return;

    pthread_mutex_destroy(&g_avcodec_mutex);
    g_ffmpeg_global_inited = false;
}

void ijkff_avcodec_lock()
{
    if (!g_ffmpeg_global_inited)
        return;
    pthread_mutex_lock(&g_avcodec_mutex);
}

void ijkff_avcodec_unlock()
{
    if (!g_ffmpeg_global_inited)
        return;
    pthread_mutex_unlock(&g_avcodec_mutex);
}
