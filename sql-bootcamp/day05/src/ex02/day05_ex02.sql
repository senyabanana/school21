SET enable_seqscan =off;
CREATE INDEX idx_person_name ON person(upper(name));
EXPLAIN ANALYZE
SELECT * FROM person
WHERE upper(name) = 'DENIS';