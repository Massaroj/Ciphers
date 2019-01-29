import Data.Char
-- Variable list
-- n = number, s = string, c = char, os = observed frequencies,
-- es = expected frequencies, xs = list

--Table holding expected usage percentages of numbers
table :: [Float]
table = [8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4, 6.7,
         7.5,1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1]

--This turns a letter into a number
let2nat :: Char -> Int
let2nat c = (ord c) - (ord 'a')

--This turns a number into a letter
nat2let :: Int -> Char
nat2let n = (chr (97 + n))

--Using let2nat and nat2let
--This shifts a character over by a specific numbers
--It wraps around and only works on lowercase letters
shift :: Int -> Char -> Char
shift n c = if isLower c then nat2let (((let2nat c) + n) `mod` 26) else c

--This encodes a string by shifting each letter by n
encode :: Int -> String -> String
encode n s = [shift n c | c <- s]

--This decodes a string by shifting each letter back
decode :: Int -> String -> String
decode n s = [shift (-n) c | c <- s]

--This finds out how many lower case letters there are in the string
lowers :: String -> Int
lowers s = length[x | x <- s, isLower x]

--This counts the number of a certain letter in a string
count :: Char -> String -> Int
count c s = length[x | x <- s, x == c]

--This calculates a percent of two numbers
percent :: Int -> Int -> Float
percent x y = fromIntegral x / fromIntegral y * 100

--Using lowers, count, and percent
--This makes a frequency table for the given string
freqs :: String -> [Float]
freqs s = [percent (count x s)(lowers s) | x <- ['a'..'z']]

--This rotates n letters from the head to the tail of the string
rotate :: Int -> [a] -> [a]
rotate n s = (drop n s) ++ (take n s)

--This calculates the observed frequencies in respect to the expected frequencies
chisqr :: [Float] -> [Float] -> Float
chisqr os es = sum[((x-y)^2)/y | (x,y) <- zip os es]

--This finds the first position of the given value
position :: Eq a => a -> [a] -> Int
position x xs = head [b | (a,b) <- zip xs [0..(length xs - 1)], a == x]

--Helper function that calculates the chi square value of each rotation
--Used in crack function
helper s = [chisqr (freqs (decode x s)) table | x <- [0..25]]

--This tries to decode the string without the key
crack :: String -> String
crack s = decode (position (minimum (helper s)) (helper s)) s
