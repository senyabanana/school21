INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date)
VALUES((SELECT max(id) + 1 FROM person_visits),
(SELECT id FROM person WHERE name = 'Dmitriy'),
(SELECT pi.id FROM pizzeria AS pi INNER JOIN menu AS m ON pi.id = m.pizzeria_id
WHERE m.price <= 800 AND pi.name != 'Papa Johns' LIMIT 1),
'2022-01-08');

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;