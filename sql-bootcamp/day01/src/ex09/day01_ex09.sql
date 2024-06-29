SELECT pi.name FROM pizzeria AS pi
WHERE pi.id NOT IN (SELECT DISTINCT pv.pizzeria_id FROM person_visits AS pv);

SELECT pi.name FROM pizzeria AS pi
WHERE NOT EXISTS(SELECT 1 FROM person_visits AS pv
WHERE pv.pizzeria_id = pi.id);
