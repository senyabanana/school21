SELECT pf.name AS name FROM v_persons_female AS pf
UNION
SELECT pm.name AS name FROM v_persons_male AS pm
ORDER BY 1;