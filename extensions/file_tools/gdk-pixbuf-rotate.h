/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2011 The Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GDK_PIXBUF_ROTATE_H
#define GDK_PIXBUF_ROTATE_H

#include <glib.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

void _gdk_pixbuf_rotate_get_cropping_parameters (GdkPixbuf *src_pixbuf,
					         double     angle,
					         double    *p1_plus_p2);

void _gdk_pixbuf_rotate_get_cropping_region (GdkPixbuf    *src_pixbuf,
					     double        angle,
					     double        p1,
					     double        p2,
					     GdkRectangle *region);

double _gdk_pixbuf_rotate_get_align_angle (gboolean vertical,
					   GdkPoint p1,
					   GdkPoint p2);

GdkPixbuf* _gdk_pixbuf_rotate (GdkPixbuf *src_pixbuf,
			       double     angle,
			       gboolean   high_quality);

G_END_DECLS

#endif /* GDK_PIXBUF_ROTATE_H */