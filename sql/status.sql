create table status (
	turn		INTEGER PRIMARY KEY,
	id              INTEGER,
	name		VARCHAR(70),
	password	VARCHAR(70),
	drive		FLOAT,
	weapons		FLOAT,
	shields		FLOAT,
	cargo		FLOAT,
	numplanets	INTEGER,
	population	INTEGER,
	industry	FLOAT,
	capital		FLOAT,
	material	FLOAT,
	colonists	FLOAT
);

create index status_index on status(turn);


