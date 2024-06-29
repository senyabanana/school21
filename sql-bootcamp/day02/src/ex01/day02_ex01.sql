SELECT gs::date AS missing_date
FROM generate_series('2022-01-01', '2022-01-10', INTERVAL '1 day') AS gs
LEFT OUTER JOIN person_visits AS pv
ON gs::date = pv.visit_date AND (pv.person_id = 1 OR pv.person_id = 2)
WHERE pv.visit_date IS NULL
ORDER BY 1;
