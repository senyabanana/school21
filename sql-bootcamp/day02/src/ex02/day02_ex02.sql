SELECT coalesce(p.name, '-') AS person_name,
pv.visit_date,
coalesce(pi.name, '-') AS pizzeria_name
FROM person AS p
FULL OUTER JOIN (SELECT * FROM person_visits AS pv
WHERE pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS pv
ON p.id = pv.person_id
FULL OUTER JOIN pizzeria AS pi
ON pv.pizzeria_id = pi.id
ORDER BY 1, 2, 3;