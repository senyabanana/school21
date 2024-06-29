START TRANSACTION;

DELETE FROM person_order
WHERE order_date IN ('2022-02-25');

DELETE FROM menu
WHERE pizza_name IN ('greek pizza');