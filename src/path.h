/* Declarations supporting search.c
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

/* List of directories we have seen this session. 
 */
extern GSList *path_session;

extern GSList *path_search_default;
extern GSList *path_start_default;
extern const char *path_tmp_default;

/* Type of path_map functions.
 */
typedef void *(*path_map_fn)( const char *, void *, void *, void * );

GSList *path_parse( const char *path );
char *path_unparse( GSList *path );
void path_free( GSList *path );
void *path_map_exact( GSList *path, 
	const char *patt, path_map_fn fn, void *a );
void *path_map( GSList *path, const char *patt, path_map_fn fn, void *a );
void *path_map_dir( const char *dir, const char *patt, 
	path_map_fn fn, void *a );
char *path_find_file( GSList *path, const char *patt );

void path_add_dir( const char *dir );
void path_add_file( const char *file );

void path_init( void );