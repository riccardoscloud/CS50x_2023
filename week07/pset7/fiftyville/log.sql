-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Search for crimes on the 28/07/21
SELECT id FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
-- Reduce to crimes that happened on Humphrey Street
SELECT id FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Read description
SELECT id, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Search for the interview transcripts mentioned in the crime scene report
SELECT id, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- Search for bakery parking logs, thief leaving between 10.16 and 10.25
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26;
-- Search for withdrawals on Leggett Street on the day of the theft
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type LIKE '%withdraw%';
-- Linking the above withdrawals to people
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type LIKE '%withdraw%'));
-- Phone logs for calls on that day, less than a minute long
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- Combine Parking logs + ATM for reducing scope
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26 INTERSECT SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type LIKE '%withdraw%'));
-- Combine the above with call logs (2 possible thieves)
SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26 INTERSECT SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type LIKE '%withdraw%'))) INTERSECT SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- Search for first flight out of Fiftyville the day after
SELECT * FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;
-- List of passport numbers from above flight
SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);
-- Combining all the above information, this narrows down to the only possible thief
SELECT * FROM people WHERE phone_number IN (SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26 INTERSECT SELECT license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett Street%' AND transaction_type LIKE '%withdraw%'))) INTERSECT SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1));
-- Thief identity confirmed: BRUCE
-- Destination airport of the thief's flight
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);
-- Thief destination confirmed: NEW YORK CITY
-- Knowing that Bruce is the thief, we can use the call logs of the morning of the theft to point out to the incriminating call, therefore its receiver
SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));
-- Accomplice identity confirmed: ROBIN