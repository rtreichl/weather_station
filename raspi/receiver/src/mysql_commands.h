/*
 * mysql_tables.h
 *
 *  Created on: 13.01.2016
 *      Author: Richard Treichl
 */

#ifndef MYSQL_COMMANDS_H_
#define MYSQL_COMMANDS_H_

#include <string>

const std::string mysql_table_exists = "SELECT table_name \
FROM information_schema.tables \
WHERE table_schema = 'WeatherStation' \
AND table_name = '%s';";

const std::string mysql_colum_as_index = "ALTER TABLE `%s` ADD INDEX(`%s`);";

const std::string mysql_table_sensors_active =  "CREATE TABLE IF NOT EXISTS `SensorsActive` ( \
  `ID` TINYINT KEY AUTO_INCREMENT, \
  `NAME` varchar(20) COLLATE latin1_german1_ci NOT NULL COMMENT 'Name of Sensor', \
  `ADDRESS` TINYINT NOT NULL COMMENT 'Address from sensor', \
  `UPDATETED` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Last received data', \
  `STATUS` SMALLINT NOT NULL COMMENT 'Indicates last status', \
  `PROTOCOL` TINYINT NOT NULL COMMENT 'Used protocol by Sensor', \
  `MESSUREMENTS` BIGINT NOT NULL COMMENT 'Total number of received messurements', \
  `HISTORY` int(11) NOT NULL COMMENT 'Reference to history table', \
  `TOTAL` int(11) NOT NULL COMMENT 'Reference to total table' \
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_max_values  = "CREATE TABLE IF NOT EXISTS `SensorsMax` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` TINYINT NOT NULL COMMENT 'Address from sensor',\
  `DATE` date NULL COMMENT 'Date of day data', \
  `HDC1000_TEMP_MAX` decimal(5,2) NOT NULL COMMENT 'HDC1000 max temperatur °C', \
  `HDC1000_HUMI_MAX` decimal(5,2) NOT NULL COMMENT 'HDC1000 max humidity in %', \
  `TMP102_TEMP_MAX` decimal(5,2) NOT NULL COMMENT 'TMP102 max temperatur in °C', \
  `LPS25H_TEMP_MAX` decimal(5,2) NOT NULL COMMENT 'LPS25H max temperatur in °C', \
  `LPS25H_PRESS_MAX` decimal(6,2) NOT NULL COMMENT 'LPS25H max pressure in hPa', \
  `SI1147_UV_MAX` decimal(4,2) NOT NULL COMMENT 'SI1147 max uv index', \
  `SI1147_VIS_MAX` decimal(8,2) NOT NULL COMMENT 'SI1147 max visible light in lux', \
  `SI1147_IR_MAX` decimal(8,2) NOT NULL COMMENT 'SI1147 max ir light in lux', \
  `VOLT_BAT_MAX` decimal(3,2) NOT NULL COMMENT 'Sensor max batterie voltage in V', \
  `VOLT_SOLAR_MAX` decimal(3,2) NOT NULL COMMENT 'Sensor max solar cell voltage in V' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_min_values = "CREATE TABLE IF NOT EXISTS `SensorsMin` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` TINYINT NOT NULL COMMENT 'Address from sensor', \
  `DATE` date NULL COMMENT 'Date of day data', \
  `HDC1000_TEMP_MIN` decimal(5,2) NOT NULL COMMENT 'HDC1000 min temperatur °C', \
  `HDC1000_HUMI_MIN` decimal(5,2) NOT NULL COMMENT 'HDC1000 min humidity in %', \
  `TMP102_TEMP_MIN` decimal(5,2) NOT NULL COMMENT 'TMP102 min temperatur in °C', \
  `LPS25H_TEMP_MIN` decimal(5,2) NOT NULL COMMENT 'LPS25H min temperatur in °C', \
  `LPS25H_PRESS_MIN` decimal(6,2) NOT NULL COMMENT 'LPS25H min pressure in hPa', \
  `SI1147_UV_MIN` decimal(4,2) NOT NULL COMMENT 'SI1147 min uv index', \
  `SI1147_VIS_MIN` decimal(8,2) NOT NULL COMMENT 'SI1147 min visible light in lux', \
  `SI1147_IR_MIN` decimal(8,2) NOT NULL COMMENT 'SI1147 min ir light in lux', \
  `VOLT_BAT_MIN` decimal(3,2) NOT NULL COMMENT 'Sensor min batterie voltage in V', \
  `VOLT_SOLAR_MIN` decimal(3,2) NOT NULL COMMENT 'Sensor min solar cell voltage in V' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_avg_values = "CREATE TABLE IF NOT EXISTS `SensorsAvg` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` INT NOT NULL COMMENT 'Address from sensor', \
  `DATE` date NULL COMMENT 'Date of day data', \
  `HDC1000_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'HDC1000 avg temperatur °C', \
  `HDC1000_HUMI_AVG` decimal(5,2) NOT NULL COMMENT 'HDC1000 avg humidity in %', \
  `TMP102_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'TMP102 avg temperatur in °C', \
  `LPS25H_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'LPS25H avg temperatur in °C', \
  `LPS25H_PRESS_AVG` decimal(6,2) NOT NULL COMMENT 'LPS25H avg pressure in hPa', \
  `SI1147_UV_AVG` decimal(4,2) NOT NULL COMMENT 'SI1147 avg uv index', \
  `SI1147_VIS_AVG` decimal(8,2) NOT NULL COMMENT 'SI1147 avg visible light in lux', \
  `SI1147_IR_AVG` decimal(8,2) NOT NULL COMMENT 'SI1147 avg ir light in lux', \
  `VOLT_BAT_AVG` decimal(3,2) NOT NULL COMMENT 'Sensor avg batterie voltage in V', \
  `VOLT_SOLAR_AVG` decimal(3,2) NOT NULL COMMENT 'Sensor avg solar cell voltage in V' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_protocol_1 = "CREATE TABLE IF NOT EXISTS `%s` ( \
  `ID` BIGINT KEY AUTO_INCREMENT, \
  `DATE` date NULL COMMENT 'Date of received data', \
  `TIME` time NULL COMMENT 'Time of received data', \
  `HDC1000_TEMP` decimal(5,2) NOT NULL COMMENT 'HDC1000 temperatur °C', \
  `HDC1000_HUMI` decimal(5,2) NOT NULL COMMENT 'HDC1000 humidity in %', \
  `TMP102_TEMP` decimal(5,2) NOT NULL COMMENT 'TMP102 temperatur in °C', \
  `LPS25H_TEMP` decimal(5,2) NOT NULL COMMENT 'LPS25H temperatur in °C', \
  `LPS25H_PRESS` decimal(6,2) NOT NULL COMMENT 'LPS25H pressure in hPa', \
  `SI1147_UV` decimal(4,2) NOT NULL COMMENT 'SI1147 uv index', \
  `SI1147_VIS` decimal(8,2) NOT NULL COMMENT 'SI1147 visible light in lux', \
  `SI1147_IR` decimal(8,2) NOT NULL COMMENT 'SI1147 ir light in lux', \
  `VOLT_BAT` decimal(3,2) NOT NULL COMMENT 'Sensor batterie voltage in V', \
  `VOLT_SOLAR` decimal(3,2) NOT NULL COMMENT 'Sensor solar cell voltage in V', \
  `DATETIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_protocol_2 = "CREATE TABLE IF NOT EXISTS `%s` ( \
  `ID` BIGINT KEY AUTO_INCREMENT, \
  `DATE` date NULL COMMENT 'Date of received data', \
  `TIME` time NULL COMMENT 'Time of received data', \
  `HDC1000_TEMP` decimal(5,2) NOT NULL COMMENT 'HDC1000 temperatur °C', \
  `HDC1000_HUMI` decimal(5,2) NOT NULL COMMENT 'HDC1000 humidity in %', \
  `TMP102_TEMP` decimal(5,2) NOT NULL COMMENT 'TMP102 temperatur in °C', \
  `LPS25H_TEMP` decimal(5,2) NOT NULL COMMENT 'LPS25H temperatur in °C', \
  `LPS25H_PRESS` decimal(6,2) NOT NULL COMMENT 'LPS25H pressure in hPa', \
  `VOLT_BAT` decimal(3,2) NOT NULL COMMENT 'Sensor batterie voltage in V', \
  `VOLT_SOLAR` decimal(3,2) NOT NULL COMMENT 'Sensor solar cell voltage in V', \
  `DATETIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_protocol_3 = "CREATE TABLE IF NOT EXISTS `%s` ( \
  `ID` BIGINT KEY AUTO_INCREMENT, \
  `DATE` date NULL COMMENT 'Date of received data', \
  `TIME` time NULL COMMENT 'Time of received data', \
  `HDC1000_TEMP` decimal(5,2) NOT NULL COMMENT 'HDC1000 temperatur °C', \
  `HDC1000_HUMI` decimal(5,2) NOT NULL COMMENT 'HDC1000 humidity in %', \
  `TMP102_TEMP` decimal(5,2) NOT NULL COMMENT 'TMP102 temperatur in °C', \
  `SI1147_UV` decimal(4,2) NOT NULL COMMENT 'SI1147 uv index', \
  `SI1147_VIS` decimal(8,2) NOT NULL COMMENT 'SI1147 visible light in lux', \
  `SI1147_IR` decimal(8,2) NOT NULL COMMENT 'SI1147 ir light in lux', \
  `VOLT_BAT` decimal(3,2) NOT NULL COMMENT 'Sensor batterie voltage in V', \
  `VOLT_SOLAR` decimal(3,2) NOT NULL COMMENT 'Sensor solar cell voltage in V', \
  `DATETIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_protocol_4 = "CREATE TABLE IF NOT EXISTS `%s` ( \
  `ID` BIGINT KEY AUTO_INCREMENT, \
  `DATE` date NULL COMMENT 'Date of received data', \
  `TIME` time NULL COMMENT 'Time of received data', \
  `HDC1000_TEMP` decimal(5,2) NOT NULL COMMENT 'HDC1000 temperatur °C', \
  `HDC1000_HUMI` decimal(5,2) NOT NULL COMMENT 'HDC1000 humidity in %', \
  `TMP102_TEMP` decimal(5,2) NOT NULL COMMENT 'TMP102 temperatur in °C', \
  `VOLT_BAT` decimal(3,2) NOT NULL COMMENT 'Sensor batterie voltage in V', \
  `VOLT_SOLAR` decimal(3,2) NOT NULL COMMENT 'Sensor solar cell voltage in V', \
  `DATETIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_insert_sensors_active = "INSERT INTO `SensorsActive` \
		( `ID`, `NAME`, `ADDRESS`, `UPDATETED`, `STATUS`, `PROTOCOL`, `MESSUREMENTS`, `HISTORY`, `TOTAL`)\
		VALUES \
		('', '%s', '%d', CURRENT_TIMESTAMP, '0', '%d', '0', '0', '0');";

const std::string mysql_insert_protocol_1_data = "INSERT INTO `%s` \
		(`ID`, `DATE`, `TIME`, `HDC1000_TEMP`, `HDC1000_HUMI`, `TMP102_TEMP`, `LPS25H_TEMP`, `LPS25H_PRESS`, `SI1147_UV`, `SI1147_VIS`, `SI1147_IR`, `VOLT_BAT`, `VOLT_SOLAR`, `DATETIME`) \
		VALUES \
		('', NOW(), NOW(), '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', CURRENT_TIMESTAMP)";

const std::string mysql_update_sensors_active = "UPDATE `SensorsActive` SET `STATUS` = '%d', `MESSUREMENTS` = `MESSUREMENTS` + '1' WHERE `ADDRESS` = '%d';";

const std::string mysql_update_sensorsmax = "UPDATE `SensorsMax` SET \
`HDC1000_TEMP_MAX`= IF(`HDC1000_TEMP_MAX` > %f,`HDC1000_TEMP_MAX`, %f), \
`HDC1000_HUMI_MAX`= IF(`HDC1000_HUMI_MAX` > %f,`HDC1000_HUMI_MAX`, %f), \
`TMP102_TEMP_MAX`= IF(`TMP102_TEMP_MAX` > %f,`TMP102_TEMP_MAX`, %f), \
`LPS25H_TEMP_MAX`= IF(`LPS25H_TEMP_MAX` > %f,`LPS25H_TEMP_MAX`, %f), \
`LPS25H_PRESS_MAX`= IF(`LPS25H_PRESS_MAX` > %f,`LPS25H_PRESS_MAX`, %f), \
`SI1147_UV_MAX`= IF(`SI1147_UV_MAX` > %f,`SI1147_UV_MAX`, %f), \
`SI1147_VIS_MAX`= IF(`SI1147_VIS_MAX` > %f,`SI1147_VIS_MAX`, %f), \
`SI1147_IR_MAX`= IF(`SI1147_IR_MAX` > %f,`SI1147_IR_MAX`, %f), \
`VOLT_BAT_MAX`= IF(`VOLT_BAT_MAX` > %f,`VOLT_BAT_MAX`, %f), \
`VOLT_SOLAR_MAX`= IF(`VOLT_SOLAR_MAX` > %f,`VOLT_SOLAR_MAX`, %f) \
WHERE `ADDRESS` = '%d' LIMIT 1;";

const std::string mysql_update_sensorsmin = "UPDATE `SensorsMin` SET \
`HDC1000_TEMP_MIN`= IF(`HDC1000_TEMP_MIN` < %f,`HDC1000_TEMP_MIN`, %f), \
`HDC1000_HUMI_MIN`= IF(`HDC1000_HUMI_MIN` < %f,`HDC1000_HUMI_MIN`, %f), \
`TMP102_TEMP_MIN`= IF(`TMP102_TEMP_MIN` < %f,`TMP102_TEMP_MIN`, %f), \
`LPS25H_TEMP_MIN`= IF(`LPS25H_TEMP_MIN` < %f,`LPS25H_TEMP_MIN`, %f), \
`LPS25H_PRESS_MIN`= IF(`LPS25H_PRESS_MIN` < %f,`LPS25H_PRESS_MIN`, %f), \
`SI1147_UV_MIN`= IF(`SI1147_UV_MIN` < %f,`SI1147_UV_MIN`, %f), \
`SI1147_VIS_MIN`= IF(`SI1147_VIS_MIN` < %f,`SI1147_VIS_MIN`, %f), \
`SI1147_IR_MIN`= IF(`SI1147_IR_MIN` < %f,`SI1147_IR_MIN`, %f), \
`VOLT_BAT_MIN`= IF(`VOLT_BAT_MIN` < %f,`VOLT_BAT_MIN`, %f), \
`VOLT_SOLAR_MIN`= IF(`VOLT_SOLAR_MIN` < %f,`VOLT_SOLAR_MIN`, %f) \
WHERE `ADDRESS` = '%d' LIMIT 1;";

const std::string mysql_update_sensorsavg = "UPDATE `SensorsAvg` SET \
`HDC1000_TEMP_AVG`= (`HDC1000_TEMP_AVG` + %f) / 2, \
`HDC1000_HUMI_AVG`= (`HDC1000_HUMI_AVG`  + %f) / 2, \
`TMP102_TEMP_AVG`= (`TMP102_TEMP_AVG`  + %f) / 2, \
`LPS25H_TEMP_AVG`= (`LPS25H_TEMP_AVG`  + %f) / 2, \
`LPS25H_PRESS_AVG`= (`LPS25H_PRESS_AVG`  + %f) / 2, \
`SI1147_UV_AVG`= (`SI1147_UV_AVG`  + %f) / 2, \
`SI1147_VIS_AVG`= (`SI1147_VIS_AVG`  + %f) / 2, \
`SI1147_IR_AVG`= (`SI1147_IR_AVG`  + %f) / 2, \
`VOLT_BAT_AVG`= (`VOLT_BAT_AVG`  + %f) / 2, \
`VOLT_SOLAR_AVG`= (`VOLT_SOLAR_AVG`  + %f) / 2 \
WHERE `ADDRESS` = '%d' LIMIT 1;";

const std::string mysql_select_sensorsavgmaxmin = "SELECT * FROM `%s` WHERE `ADDRESS` = '%d' AND `DATE` = DATE(NOW());";

const std::string mysql_insert_sensorsavg = "INSERT INTO `SensorsAvg` \
(`ADDRESS`, `DATE`, `HDC1000_TEMP_AVG`, `HDC1000_HUMI_AVG`, `TMP102_TEMP_AVG`, `LPS25H_TEMP_AVG`, `LPS25H_PRESS_AVG`, `SI1147_UV_AVG`, `SI1147_VIS_AVG`, `SI1147_IR_AVG`, `VOLT_BAT_AVG`, `VOLT_SOLAR_AVG`) \
VALUES \
(%d, NOW(), %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

const std::string mysql_insert_sensorsmax = "INSERT INTO `SensorsMax` \
(`ADDRESS`, `DATE`, `HDC1000_TEMP_MAX`, `HDC1000_HUMI_MAX`, `TMP102_TEMP_MAX`, `LPS25H_TEMP_MAX`, `LPS25H_PRESS_MAX`, `SI1147_UV_MAX`, `SI1147_VIS_MAX`, `SI1147_IR_MAX`, `VOLT_BAT_MAX`, `VOLT_SOLAR_MAX`) \
VALUES \
(%d, NOW(), %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

const std::string mysql_insert_sensorsmin = "INSERT INTO `SensorsMin` \
(`ADDRESS`, `DATE`, `HDC1000_TEMP_MIN`, `HDC1000_HUMI_MIN`, `TMP102_TEMP_MIN`, `LPS25H_TEMP_MIN`, `LPS25H_PRESS_MIN`, `SI1147_UV_MIN`, `SI1147_VIS_MIN`, `SI1147_IR_MIN`, `VOLT_BAT_MIN`, `VOLT_SOLAR_MIN`) \
VALUES \
(%d, NOW(), %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

#endif /* MYSQL_COMMANDS_H_ */
