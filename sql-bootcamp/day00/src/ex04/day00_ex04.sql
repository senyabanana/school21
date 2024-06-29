SELECT name || ' (age:' || age || ',gender:' || '''' || gender
|| '''' || ',address:' || '''' || address || '''' || ')' person_information
FROM person
ORDER BY person_information;
