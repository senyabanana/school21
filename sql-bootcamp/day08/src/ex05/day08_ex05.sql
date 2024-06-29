--Session #1
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;
SELECT sum(rating) FROM pizzeria;
SELECT sum(rating) FROM pizzeria;
COMMIT;
SELECT sum(rating) FROM pizzeria;

--Session #2
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;
UPDATE pizzeria SET rating = 1 WHERE name = 'Pizza Hut';
COMMIT;
SELECT sum(rating) FROM pizzeria;