CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
SELECT pi.name
FROM person_visits AS pv
INNER JOIN person AS p ON pv.person_id = p.id
INNER JOIN pizzeria AS pi ON pv.pizzeria_id = pi.id
INNER JOIN menu AS m ON pi.id = m.pizzeria_id
WHERE p.name = 'Dmitriy' AND pv.visit_date = '2022-01-08' AND m.price <= 800;
