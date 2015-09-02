create table bookmarks (
	id	            CHARACTER(1),
	description		CHARACTER(64),
	app_width       INTEGER,
	app_height		INTEGER,
	app_x			INTEGER,
	app_y			INTEGER,
	split_width		INTEGER,
	split_height	INTEGER,
	map_zoom		INTEGER,
	map_ulx         INTEGER,
    map_uly			INTEGER,
	map_lrx			INTEGER,
	map_lry			INTEGER,
	PRIMARY KEY(id)
);
		
create index bookmark_name_id on bookmarks(id);
