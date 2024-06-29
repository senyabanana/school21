--Session #1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SELECT sum(rating) FROM pizzeria;
SELECT sum(rating) FROM pizzeria;
COMMIT;
SELECT sum(rating) FROM pizzeria;

--Session #2
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut';
COMMIT;
SELECT sum(rating) FROM pizzeria;