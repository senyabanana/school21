(SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN person_visits AS pv
ON pi.id = pv.pizzeria_id
INNER JOIN person AS p
ON pv.person_id = p.id
WHERE p.gender = 'female'
EXCEPT ALL
SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN person_visits AS pv
ON pi.id = pv.pizzeria_id
INNER JOIN person AS p
ON pv.person_id = p.id
WHERE p.gender = 'male')
UNION ALL
(SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN person_visits AS pv
ON pi.id = pv.pizzeria_id
INNER JOIN person AS p
ON pv.person_id = p.id
WHERE p.gender = 'male'
EXCEPT ALL
SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN person_visits AS pv
ON pi.id = pv.pizzeria_id
INNER JOIN person AS p
ON pv.person_id = p.id
WHERE p.gender = 'female')
ORDER BY 1;