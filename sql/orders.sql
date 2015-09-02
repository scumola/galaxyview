create table orders (
        turn     INTEGER PRIMARY KEY,
        sequence INTEGER,
	command  CHARACTER(1),
	arg1     CHARACTER VARYING(64),
	arg2     CHARACTER VARYING(64),
	arg3     CHARACTER VARYING(64),
	arg4     CHARACTER VARYING(64),
	arg5     CHARACTER VARYING(64),
	arg6     CHARACTER VARYING(64),
	comment  CHARACTER VARYING(255)
);

create index orders_turn on orders(turn);
create index orders_turn_sequence on orders(turn, sequence);

