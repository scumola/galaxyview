create table bulletins (
	turn    INTEGER,
        sequence INTEGER,
        data     VARCHAR(80)
);

create index bulletins_turn_sequence on bulletins(turn, sequence);
