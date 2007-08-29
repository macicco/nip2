/* base model for a client regions on an imageview
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

/*
#define DEBUG
 */

#include "ip.h"

static ClassmodelClass *parent_class = NULL;

static void
iregiongroup_dispose( GObject *gobject )
{
	iRegiongroup *iregiongroup;

#ifdef DEBUG
	printf( "iregiongroup_dispose\n" );
#endif /*DEBUG*/

	g_return_if_fail( gobject != NULL );
	g_return_if_fail( IS_IREGIONGROUP( gobject ) );

	iregiongroup = IREGIONGROUP( gobject );

	/* My instance destroy stuff.
	 */

	G_OBJECT_CLASS( parent_class )->dispose( gobject );
}

static void *
iregiongroup_update_model( Heapmodel *heapmodel )
{
#ifdef DEBUG
	printf( "iregiongroup_update_model: " );
	row_name_print( heapmodel->row );
	printf( "\n" );
#endif /*DEBUG*/

	if( HEAPMODEL_CLASS( parent_class )->update_model( heapmodel ) )
		return( heapmodel );

	/* Only display most-derived classes. Don't display "this".
	 */
	if( heapmodel->row->sym )
		model_set_display( MODEL( heapmodel ),
			!is_super( heapmodel->row->sym ) &&
			!is_this( heapmodel->row->sym ) );

	return( NULL );
}

static View *
iregiongroup_view_new( Model *model, View *parent )
{
	return( iregiongroupview_new() );
}

static void
iregiongroup_class_init( iRegiongroupClass *class )
{
	GObjectClass *gobject_class = (GObjectClass *) class;
	ModelClass *model_class = (ModelClass *) class;
	HeapmodelClass *heapmodel_class = (HeapmodelClass *) class;

	parent_class = g_type_class_peek_parent( class );

	/* Create signals.
	 */

	/* Init methods.
	 */
	gobject_class->dispose = iregiongroup_dispose;

	heapmodel_class->update_model = iregiongroup_update_model;

	model_class->view_new = iregiongroup_view_new;
}

static void
iregiongroup_init( iRegiongroup *iregiongroup )
{
	/* Display turned on in _update_model() above.
	 */
	MODEL( iregiongroup )->display = FALSE;
}

GType
iregiongroup_get_type( void )
{
	static GType type = 0;

	if( !type ) {
		static const GTypeInfo info = {
			sizeof( iRegiongroupClass ),
			NULL,           /* base_init */
			NULL,           /* base_finalize */
			(GClassInitFunc) iregiongroup_class_init,
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof( iRegiongroup ),
			32,             /* n_preallocs */
			(GInstanceInitFunc) iregiongroup_init,
		};

		type = g_type_register_static( TYPE_CLASSMODEL, 
			"iRegiongroup", &info, 0 );
	}

	return( type );
}

iRegiongroup *
iregiongroup_new( Classmodel *classmodel )
{
	iRegiongroup *iregiongroup;

	iregiongroup = IREGIONGROUP( g_object_new( TYPE_IREGIONGROUP, NULL ) );

	icontainer_child_add( ICONTAINER( classmodel ), 
		ICONTAINER( iregiongroup ), -1 );

#ifdef DEBUG
	printf( "iregiongroup_new: " );
	row_name_print( HEAPMODEL( classmodel )->row );
	printf( "\n" );
#endif /*DEBUG*/

	return( iregiongroup );
}
