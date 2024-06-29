CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
    IN pperson varchar DEFAULT 'Dmitriy',
    IN pprice numeric DEFAULT 500,
    IN pdate date DEFAULT '2022-01-08'
)
RETURNS TABLE(pizzeria_name varchar) AS
$$
BEGIN
    RETURN query
    SELECT pi.name FROM pizzeria AS pi
    INNER JOIN person_visits AS pv ON pi.id = pv.pizzeria_id
    INNER JOIN person AS p ON pv.person_id = p.id
    INNER JOIN menu AS m ON pi.id = m.pizzeria_id
    WHERE p.name = pperson AND m.price < pprice
    AND pv.visit_date = pdate;
END;
$$
LANGUAGE plpgsql;

SELECT * FROM fnc_person_visits_and_eats_on_date(pprice := 800);
SELECT * FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');