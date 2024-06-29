CREATE TABLE person_audit
( created timestamptz NOT NULL DEFAULT CURRENT_TIMESTAMP,
  type_event char(1) NOT NULL DEFAULT 'I',
  row_id bigint NOT NULL,
  name varchar,
  age integer,
  gender varchar,
  address varchar,
  constraint ch_type_event check(type_event IN('I','D','U'))
);

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit()
RETURNS TRIGGER AS
$$
BEGIN
    INSERT INTO person_audit(created, type_event, row_id, name, age, gender, address)
    VALUES(CURRENT_TIMESTAMP, 'I', new.id, new.name, new.age, new.gender, new.address);
    RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_person_insert_audit
    AFTER INSERT ON person
    FOR EACH ROW
    EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address)
VALUES (10,'Damir', 22, 'male', 'Irkutsk');

SELECT * FROM person_audit;