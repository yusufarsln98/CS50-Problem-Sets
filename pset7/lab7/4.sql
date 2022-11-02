-- 4. sql, Write a SQL query to list the name of songs that have danceability,
-- energy and valence greater than 0.75.

SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 and valence > 0.75;