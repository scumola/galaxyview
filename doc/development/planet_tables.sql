create table planet_main (
   id        INTEGER PRIMARY KEY,
   x         FLOAT,
   y         FLOAT,
   size      FLOAT,
   resources FLOAT
);

create table planet_data (
   id            INTEGER,
   name          CHARACTER VARYING(255),
   turn          INTEGER,
   owner_id      INTEGER,
   last_owner_id INTEGER,
   producing     INTEGER,
   intel_src     INTEGER,
   population    FLOAT,
   industry      FLOAT,
   CAP           FLOAT,
   MAT           FLOAT,
   COL           FLOAT
);


create index planet_main_id on planet_main(id);
create index planet_data_id on planet_data(id);
create index planet_data_producing on planet_data(producing);
