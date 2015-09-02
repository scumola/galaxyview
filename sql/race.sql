create table races (
	turn		INTEGER,
	id			INTEGER,	
	name		CHARACTER VARYING(64),
	drive		FLOAT,
	weapons		FLOAT,
	shields		FLOAT,
	cargo		FLOAT,
	posture		VARCHAR(12),
	
	PRIMARY KEY(turn, id)
);

create index races_index on races(id);
create index name_index on races(name);


