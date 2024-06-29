SELECT pi.name, pi.rating
FROM pizzeria pi
LEFT OUTER JOIN person_visits pv
ON pi.id = pv.pizzeria_id
WHERE pv.pizzeria_id is NULL;