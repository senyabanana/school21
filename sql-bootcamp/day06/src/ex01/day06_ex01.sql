INSERT INTO person_discounts(id, person_id, pizzeria_id, discount)
SELECT row_number() over () AS id, person_id, pizzeria_id,
CASE
    WHEN count(*) = 1 THEN 10.5
    WHEN count(*) = 2 THEN 22
    ELSE 30
END AS discount
FROM person_order AS po
INNER JOIN menu AS m ON po.menu_id = m.id
GROUP BY person_id, pizzeria_id;