-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get description of crime from crime_scene_reports table to explore how
-- theft has been done.

SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28
AND street = "Humphrey Street";
-- | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today
-- | with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |

-- ----------------------------------------------------------------------------------------------------------------------
-- Results from the query:
-- 1. Theft took place at 10:15am
-- 2. Theft took place at Humphrey Street bakery.
-- 3. There was 3 witnesses at the scene. They are interviewed.


-- Get the name of witnesses and transcripts from interviews table.
SELECT name, transcript
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

-- All interview transcriptions:
-- | Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
-- | Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
-- | Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- | Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |

-- Clearly, Ruth, Eugene, and Raymond talk about a theft.
-- Lets take a look at the informations day give:
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--             If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot
--             in that time frame.                                                          |
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning,
--             before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--             In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |


--------- 1. Based on the information Ruth gave, let's take a look at bakery_security_logs ---------
-- Examine the exits from the parking lot from the bakery_security_logs up to 10 minutes after the theft occurred.

SELECT people.id, name, phone_number, passport_number, people.license_plate FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25
AND activity = "exit";

-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- +--------+---------+----------------+-----------------+---------------+


--------- 2. Based on information Eugene gave, let's take a look at atm_transactions ---------
--  See who withdrew the money on the day of the theft on Leggett Street on July 28.

SELECT people.id, name, phone_number, passport_number, license_plate FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28
AND atm_location = "Leggett Street";

-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- +--------+---------+----------------+-----------------+---------------+


--------- 3. Based on information Raymond gave, let's take a look at phone_calls. ---------
-- Take a glance at phone calls up to 1 minute from the day of the theft.

SELECT DISTINCT people.id, name, phone_number, passport_number, license_plate FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28
AND duration < 60;

-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       |
-- +--------+---------+----------------+-----------------+---------------+


--------- 4. Based on information Raymond gave, let's take a look at flights ---------
-- Make a list of the passengers of the earliest flight leaving the Fiftyville on 29 July.

SELECT people.id, name, phone_number, people.passport_number, license_plate FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE flights.id =
(
    SELECT id FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE "%Fiftyville%")
    AND year = 2021 AND month = 7 AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 953679 | Doris  | (066) 555-9701 | 7214083635      | M51FA04       |
-- | 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 651714 | Edward | (328) 555-1152 | 1540955065      | 130LD9Z       |
-- | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 395717 | Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
-- +--------+--------+----------------+-----------------+---------------+


----                                                            ----
------- Take the intersection of the datas and arrest thief! -------
----                                                            ----

SELECT people.id, name, phone_number, passport_number, people.license_plate FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25
AND activity = "exit"

INTERSECT

SELECT people.id, name, phone_number, passport_number, license_plate FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28
AND atm_location = "Leggett Street"

INTERSECT

SELECT DISTINCT people.id, name, phone_number, passport_number, license_plate FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28
AND duration < 60

INTERSECT

SELECT people.id, name, phone_number, people.passport_number, license_plate FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE flights.id =
(
    SELECT id FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE "%Fiftyville%")
    AND year = 2021 AND month = 7 AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- |￣￣￣￣￣￣￣|
-- |   Bruce     |
-- |_____________|
-- (\__/) ||
-- (•ㅅ•) ||
-- / 　 づ


-- The thief ESCAPED TO:

SELECT city FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id =
(
    SELECT id FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE "%Fiftyville%")
    AND year = 2021 AND month = 7 AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+

-- |￣￣￣￣￣￣￣￣￣￣￣|
-- |   New York City    |
-- |____________________|
-- (\__/) ||
-- (•ㅅ•) ||
-- / 　 づ

-- The ACCOMPLICE is:

SELECT DISTINCT people.id, name, phone_number, passport_number, license_plate FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28
AND duration < 60;

SELECT name FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28
AND duration < 60
AND caller = "(367) 555-5533";

-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+
-- +----------+

-- |￣￣￣￣￣￣￣|
-- |  Robin      |
-- |_____________|
-- (\__/) ||
-- (•ㅅ•) ||
-- / 　 づ