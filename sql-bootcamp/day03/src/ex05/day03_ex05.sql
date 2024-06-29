SELECT DISTINCT pi.name AS pizzeria_name
FROM pizzeria AS pi
INNER JOIN person_visits AS pv
ON pi.id = pv.pizzeria_id
INNER JOIN person AS p
ON pv.person_id = p.id
INNER JOIN person_order AS po
ON p.id = po.person_id
WHERE p.name = 'Andrey' AND po.order_date <> pv.visit_date;
