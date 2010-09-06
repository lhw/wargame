-- MySQL dump 10.13  Distrib 5.1.49, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: wargame
-- ------------------------------------------------------
-- Server version	5.1.49-1

--
-- Create Database
--
CREATE DATABASE wargame;

--
-- Table structure for table `system_data`
--

DROP TABLE IF EXISTS `system_data`;
CREATE TABLE `system_data` (
  `process` varchar(255) DEFAULT NULL,
  `data_table` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `system_data`
--

LOCK TABLES `system_data` WRITE;
INSERT INTO `system_data` VALUES ('wargame','6hwRlSuqcju6RXnR9Ap2oCcHKZkbWsW6G69P04Hygj'),('wargame','VwTAQyUKBba5BdcQLfi2lO9NC8zKFB6oRxJQl9LBua'),('wargame','SvFsKc76Xqu4pPRDITXkHIEglZL2ywtaKRPZJluPxU'),('wargame','86WLDX5SwgOuZKxza1VwF7jZR5vUqVtHDlryCg2Rsw'),('wargame','QHUteU6gaYK5zLn13Mj8A5NEg0HoxdoQNnkj58jrhg'),('wargame','ahDHZbLvDbt6pA1iirKagHhDT1zbcZP3Nw4WD1yar2'),('wargame','csoZoLDdwyluvxXXbUJhyBmTVhuq4KjgoGnt2LVcUD'),('wargame','EM9LKGVyJEi7BDINFB65fMZNFOOhtRZCg0GjZSP8tN'),('wargame','vqTrlKsI7iPMU8my3iRNLrh9cKCAcHYhQ8lsM1kIYs'),('wargame','h6kosWkk5513SieGXCLyAOivI1O2Y6N0xiwleA7Ao5'),('wargame','pVXqJYLHmTZ3LjLdSsFORXtoPoOgz5IQH6qvdfFu1k'),('wargame','foSfJYbjwfNITxoZ5Znls6FU5IqbWjxkYRKO8JTkEm'),('wargame','Ty0zek8hTdct9GZbh4w9ewgeEyahBjDdaEbXG5OwSQ'),('wargame','6m1kdJ6xcMWcuTvL3j953UcefBv9nFQcrKoKg9b2Fg'),('wargame','DkGT8W3l85OrNN75J2Y7IAMSmCzG9HtZdROjTqaGH2'),('wargame','AZkSPtEOpWWJu4jZdVREdh6QDYl6bfdPmaFR1xoOCa'),('wargame','uzOlIgpVNQuWG9wnh0ERuNSbaJeWd7XzhkZ1bj85La'),('wargame','lmllWXFI37OvwwJ1D1e4dhAqZdwbIKbwY8v2b2ha41'),('wargame','4dlar4Yh4eUwoliLeNh5cRl5Q57UBnYCsaTI5d9oOC'),('wargame','dRaXCNzwVHPbClToXO46q35gJCmR7SEPMJq4dDjE1A'),('wargame','894TGJobYAOnzGjZ90MP3NoCUPQInTUSaPsXwV9TBK'),('wargame','TudtOEGdNEngiaIvbmYn5mhg7jeqyPJgxGWNKwMKio'),('wargame','ThisIsThePasswordToAccessTheWargameViaSSH'),('wargame','WxEbC6p0WnIGCsQDB0OHdzvkZpCSNUPTm7tTeJzyPy'),('wargame','7C8gjb7UuL8XJgTx4DpgoXnystMm7heA2kVSZJaiaG'),('wargame','y85F9o4QCqXyEa4SgpfmeodH0i6jeEcFRlknOXfAkP'),('wargame','IBocVZ4HpCurFRvipn2zpkXecKP7dSiXHN3GeWwgQR'),('wargame','wL8tdJ1p4DWDJhZK1eAlosRpq3IJCYIwoW5KscwDFK'),('wargame','9JSSnhmsgccZHGUQCqlV6dRlCtgIQSr43coCYi2acE'),('wargame','HcJgV4hR5zrQZmjf4G2RhXUn0b7jH80zrAMwoO6jhS'),('wargame','toD2m63CUrn5KqV0l556g5pVUejsrsNwBDs7HmXQup'),('wargame','2tXdU13HzBwGcaU2qXa9lhlZJdUaSL86TY0ZfggPau'),('wargame','BwAAm2Fi9AZUmxxTnDuYhGebor7gsteAsKjUDa2174'),('wargame','e6UTt7pRcoDXX8vLd8IIQZ7yyfNcWE4xB5Acp95Ri0'),('wargame','UfA9paFdjuCI1gMU08c1a54WlVzfGsYaXDw0wBoSil'),('wargame','y4QHXrWD8AocRV8X1nnWeJcgZfOpxh03jExa9Sq63i'),('wargame','qLugCf6yYolAytprAvuoZA1l62NluaImnu7P9fuHnl'),('wargame','1YqZmxYB3wuWtLvCyBfNCkWlWun4pBiU3hn1tCnwA9'),('wargame','jjFrFKW4zQZxr8IY7rZmXkDY3A4Ood5mRixkN35zdv'),('wargame','9Ig9i2vFjm89dux8aMOvg6QdCCLSqi84tvOoEiEnq6'),('wargame','TFIikooSQixnoWZeHL9ZKWmJnZFwwcSINWfp99J0HQ'),('wargame','tb2h16wHalwnGCXuS6Q68trehNYwVX0aWC1LN2HpEB'),('wargame','KUQdYZzfNwX3ZyYdciHKP2y54O6aCsNzHm3CRwRyZV'),('wargame','nE6mUl9oe5mYK6vkfNWIYyBP6vHTesx4JfNqv0316q'),('wargame','lt1Oj8HBqJ5zReoMItnnnVfhTD49t7IcnEEn2I5xIs');
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `nick` varchar(24) NOT NULL DEFAULT '',
  PRIMARY KEY (`nick`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
INSERT INTO `users` VALUES ('lhw');
UNLOCK TABLES;


--
-- Create user privileges
--
GRANT SELECT ON wargame.* TO wargame@localhost IDENTIFIED BY "N1gVyFXKL8Q0bG4Rl1ySaoP";

-- Dump completed on 2010-09-06  0:27:52
