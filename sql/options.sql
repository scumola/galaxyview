create table options (
	turn    INTEGER,
    name	VARCHAR(80),
    value	VARCHAR(80)
);

create index options_turn on options(turn);
