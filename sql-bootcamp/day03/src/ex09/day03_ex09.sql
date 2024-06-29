START TRANSACTION;

INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date)
VALUES((SELECT max(id) + 1 FROM person_visits),
(SELECT id FROM person WHERE name = 'Denis'),
(SELECT id FROM pizzeria WHERE name = 'Dominos'),
date('2022-02-05'));

INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date)
VALUES((SELECT max(id) + 1 FROM person_visits),
(SELECT id FROM person WHERE name = 'Irina'),
(SELECT id FROM pizzeria WHERE name = 'Dominos'),
date('2022-02-05'));