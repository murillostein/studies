--1
SELECT title FROM movies WHERE year = 2008

--2
SELECT birth FROM people WHERE name = "Emma Stone"

--3
SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC

 --4
 SELECT COUNT (*) FROM ratings WHERE rating = 10

 --5 
 SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE stars.movie_id IN (
            SELECT movie_id FROM stars
            Where stars.person_id = (
                SELECT id FROM people
                WHERE people.name = "Kevin Bacon" AND birth = 1958)
                            )
            )
 AND name != "Kevin Bacon"

 --6
 SELECT AVG(ratings.rating) FROM ratings JOIN movies ON movies.id = ratings.movie_id WHERE  movies.year = 2012

 --7
 SELECT ratings.rating , movies.title FROM ratings JOIN movies ON movies.id = ratings.movie_id WHERE movies.year = 2010 and ratings.rating != "\\N" ORDER BY ratings.rating DESC , movies.title ASC

 --8
 SELECT name FROM people JOIN stars ON people.id = stars.person_id WHERE stars.movie_id = (SELECT id FROM movies WHERE title ="Toy Story")

--9
SELECT people.name FROM people
WHERE id IN (
        SELECT person_id FROM stars
            WHERE movie_id IN (
            SELECT id FROM movies
            WHERE year = 2004
            )
    )
ORDER BY people.birth ASC

--10
SELECT name FROM people 
WHERE id IN (
            SELECT person_id FROM directors 
            WHERE movie_id IN (
                SELECT id FROM movieS 
                WHERE id IN (
                    SELECT movie_id FROM ratings 
                    WHERE rating >= 9
                )
            )
)

--11
SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON ratings.movie_id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5

--12
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name =  "Helena Bonham Carter"
INTERSECT
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name =  "Johnny Depp"

--13
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE stars.movie_id IN (
            SELECT movie_id FROM stars
            Where stars.person_id = (
                SELECT id FROM people
                WHERE people.name = "Kevin Bacon" AND birth = 1958)
                            )
            )
 AND name != "Kevin Bacon"

