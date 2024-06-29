START TRANSACTION;

INSERT INTO person_order(id, person_id, menu_id, order_date)
SELECT
generate_series((SELECT max(po.id) + 1 FROM person_order AS po),
(SELECT max(p.id) + max(po.id) FROM person AS p
INNER JOIN person_order AS po ON p.id = po.person_id)),
generate_series((SELECT min(p.id) FROM person AS p), (SELECT max(p.id) FROM person AS p)),
(SELECT id FROM menu WHERE pizza_name = 'greek pizza'),
date('2022-02-25');