/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2015 Free Software Foundation, Inc.
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

#include <config.h>
#include <glib.h>
#include <glib/gi18n-lib.h>
#include "gth-trash-task.h"


struct _GthTrashTaskPrivate {
	GList *file_list;
};


G_DEFINE_TYPE (GthTrashTask, gth_trash_task, GTH_TYPE_TASK)


static void
gth_trash_task_finalize (GObject *object)
{
	GthTrashTask *self;

	self = GTH_TRASH_TASK (object);

	_g_object_list_unref (self->priv->file_list);

	G_OBJECT_CLASS (gth_trash_task_parent_class)->finalize (object);
}


static void
trash_ready_cb (GError   *error,
		gpointer  user_data)
{
	gth_task_completed (GTH_TASK (user_data), error);
}


static void
gth_trash_task_exec (GthTask *task)
{
	GthTrashTask *self;

	self = GTH_TRASH_TASK (task);

	gth_task_progress (task, _("Moving files to trash"), NULL, TRUE, 0.0);

	_g_trash_files_async (self->priv->file_list,
			      gth_task_get_cancellable (task),
			      trash_ready_cb,
			      self);
}


static void
gth_trash_task_class_init (GthTrashTaskClass *klass)
{
	GObjectClass *object_class;
	GthTaskClass *task_class;

	g_type_class_add_private (klass, sizeof (GthTrashTaskPrivate));

	object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = gth_trash_task_finalize;

	task_class = GTH_TASK_CLASS (klass);
	task_class->exec = gth_trash_task_exec;
}


static void
gth_trash_task_init (GthTrashTask *self)
{
	self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self, GTH_TYPE_TRASH_TASK, GthTrashTaskPrivate);
}


GthTask *
gth_trash_task_new (GList *file_list)
{
	GthTrashTask *self;

	self = GTH_TRASH_TASK (g_object_new (GTH_TYPE_TRASH_TASK, NULL));
	self->priv->file_list = _g_object_list_ref (file_list);

	return (GthTask *) self;
}