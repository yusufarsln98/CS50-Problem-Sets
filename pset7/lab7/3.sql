-- 3. sql, Write a SQL query to list the name of top 5 longest song in descending order of lenght.

SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;