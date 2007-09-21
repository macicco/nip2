/* a managed gobject 
 */

/*

    Copyright (C) 1991-2003 The National Gallery

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 */

/*

    These files are distributed with VIPS - http://www.vips.ecs.soton.ac.uk

 */

#include "ip.h"

/* 
#define DEBUG
 */

static ManagedClass *parent_class = NULL;

static void
managedgobject_dispose( GObject *gobject )
{
	Managedgobject *managedgobject = MANAGEDGOBJECT( gobject );

#ifdef DEBUG
	printf( "managedgobject_dispose: " );
	iobject_print( IOBJECT( managedgobject ) );
#endif /*DEBUG*/

	IM_FREEF( g_object_unref, managedgobject->object );

	G_OBJECT_CLASS( parent_class )->dispose( gobject );
}

static void
managedgobject_info( iObject *iobject, BufInfo *buf )
{
	Managedgobject *managedgobject = MANAGEDGOBJECT( iobject );
	GObject *object = managedgobject->object;

	IOBJECT_CLASS( parent_class )->info( iobject, buf );

	if( object ) 
		buf_appendf( buf, "->object :: %s", 
			G_OBJECT_TYPE_NAME( object ) );
}

static void
managedgobject_class_init( ManagedgobjectClass *class )
{
	GObjectClass *gobject_class = G_OBJECT_CLASS( class );
	iObjectClass *iobject_class = IOBJECT_CLASS( class );

	parent_class = g_type_class_peek_parent( class );

	gobject_class->dispose = managedgobject_dispose;

	iobject_class->info = managedgobject_info;
}

static void
managedgobject_init( Managedgobject *managedgobject )
{
#ifdef DEBUG
	printf( "managedgobject_init: %p\n", managedgobject );
#endif /*DEBUG*/

	managedgobject->object = NULL;
}

GType
managedgobject_get_type( void )
{
	static GType type = 0;

	if( !type ) {
		static const GTypeInfo info = {
			sizeof( ManagedgobjectClass ),
			NULL,           /* base_init */
			NULL,           /* base_finalize */
			(GClassInitFunc) managedgobject_class_init,
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof( Managedgobject ),
			32,             /* n_preallocs */
			(GInstanceInitFunc) managedgobject_init,
		};

		type = g_type_register_static( TYPE_MANAGED, 
			"Managedgobject", &info, 0 );
	}

	return( type );
}

Managedgobject *
managedgobject_new( Heap *heap, GObject *object )
{
	Managedgobject *managedgobject = 
		g_object_new( TYPE_MANAGEDGOBJECT, NULL );

	managed_link_heap( MANAGED( managedgobject ), heap );
	managedgobject->object = object;
	g_object_ref( object );

	return( managedgobject );
}