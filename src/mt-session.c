/*
 * Copyright © 2007 Gerd Kohlberger <lowfi@chello.at>
 *
 * This file is part of Mousetweaks.
 *
 * Mousetweaks is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mousetweaks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include <libgnomeui/gnome-client.h>

#include "mt-main.h"

static gint
session_save_yourself (GnomeClient *client,
		       gint phase,
		       GnomeSaveStyle save_style,
		       gint shutdown,
		       GnomeInteractStyle interact_style,
		       gint fast,
		       gpointer data)
{
    return TRUE;
}

static void
session_die (GnomeClient *client, gpointer data)
{
    spi_shutdown ();
}

void
mt_session_init (gint argc, gchar **argv)
{
    GnomeClient *client;

    client = gnome_master_client ();
    gnome_client_set_restart_command (client, argc, argv);
    gnome_client_set_restart_style (client, GNOME_RESTART_IF_RUNNING);

    g_signal_connect (G_OBJECT(client), "die",
		      G_CALLBACK(session_die), NULL);

    g_signal_connect (G_OBJECT(client), "save_yourself",
		      G_CALLBACK(session_save_yourself), NULL);
}
