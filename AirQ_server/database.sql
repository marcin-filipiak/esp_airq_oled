-- phpMyAdmin SQL Dump
-- version 5.2.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Oct 31, 2025 at 07:51 PM
-- Server version: 10.6.22-MariaDB-cll-lve
-- PHP Version: 8.2.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;


-- --------------------------------------------------------

--
-- Table structure for table `AirQ_flagman`
--

CREATE TABLE `AirQ_flagman` (
  `id_flagman` int(11) NOT NULL,
  `name_flagman` varchar(10) NOT NULL,
  `id_station` int(11) NOT NULL,
  `last_connection` datetime NOT NULL,
  `ip` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `AirQ_station`
--

CREATE TABLE `AirQ_station` (
  `id_station` int(11) NOT NULL,
  `name` varchar(50) NOT NULL,
  `id_aqicn` int(11) DEFAULT NULL,
  `id_gios` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `AirQ_flagman`
--
ALTER TABLE `AirQ_flagman`
  ADD PRIMARY KEY (`id_flagman`);

--
-- Indexes for table `AirQ_station`
--
ALTER TABLE `AirQ_station`
  ADD PRIMARY KEY (`id_station`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `AirQ_flagman`
--
ALTER TABLE `AirQ_flagman`
  MODIFY `id_flagman` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `AirQ_station`
--
ALTER TABLE `AirQ_station`
  MODIFY `id_station` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
