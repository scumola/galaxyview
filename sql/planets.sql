create table planets (
	id			INTEGER PRIMARY KEY,
	x			FLOAT,
	y			FLOAT,
	status		VARCHAR(16)
);

create index planets_id on planets(id);


create table planets_turn (
	id			INTEGER NOT NULL,
	turn		INTEGER NOT NULL,
	source		CHARACTER(25),
	sourceid	CHARACTER(64),
	name		CHARACTER(25),
	owner		INTEGER,
	size		FLOAT,
	resources	FLOAT,	
	population	FLOAT,
	col			FLOAT,
	mat			FLOAT,
	cap			FLOAT,
	industry	FLOAT,
	posture		VARCHAR(12) NULL,
	
	PRIMARY KEY(id, turn)
);
		
create index planets_turn_id on planets_turn(id, turn);