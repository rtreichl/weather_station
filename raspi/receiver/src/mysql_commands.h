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

const std::string mysql_select_sensorsavgmaxmin = "SELECT * FROM `%s` WHERE `ADDRESS` = '%d' AND `DATE` = DATE(NOW());";

const std::string mysql_select_sensorsactavg = "SELECT * FROM `SensorsActAvg` WHERE `ADDRESS` = '%d' AND `AVGTIME` = '%d';";

const std::string mysql_colum_as_index = "ALTER TABLE `%s` ADD INDEX(`%s`);";

const std::string mysql_table_sensors_active =  "CREATE TABLE IF NOT EXISTS `SensorsActive` ( \
  `ID` TINYINT KEY AUTO_INCREMENT, \
  `NAME` varchar(20) COLLATE latin1_german1_ci NOT NULL COMMENT 'Name of Sensor', \
  `ADDRESS` TINYINT NOT NULL COMMENT 'Address from sensor', \
  `UPDATETED` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Last received data', \
  `STATUS` SMALLINT NOT NULL COMMENT 'Indicates last status', \
  `PROTOCOL` TINYINT NOT NULL COMMENT 'Used protocol by Sensor', \
  `MESSUREMENTS` BIGINT NOT NULL COMMENT 'Total number of received measurements', \
  `HISTORY` int(11) NOT NULL COMMENT 'Reference to history table', \
  `TOTAL` int(11) NOT NULL COMMENT 'Reference to total table' \
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_max_values  = "CREATE TABLE IF NOT EXISTS `SensorsMax` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` TINYINT NOT NULL COMMENT 'Address from sensor',\
  `DATE` date NULL COMMENT 'Date of day data', \
  `HDC1000_TEMP_MAX` decimal(5,2) NOT NULL COMMENT 'HDC1000 max temperature °C', \
  `HDC1000_HUMI_MAX` decimal(5,2) NOT NULL COMMENT 'HDC1000 max humidity in %', \
  `TMP102_TEMP_MAX` decimal(5,2) NOT NULL COMMENT 'TMP102 max temperature in °C', \
  `LPS25H_TEMP_MAX` decimal(5,2) NOT NULL COMMENT 'LPS25H max temperature in °C', \
  `LPS25H_PRESS_MAX` decimal(6,2) NOT NULL COMMENT 'LPS25H max pressure in hPa', \
  `SI1147_UV_MAX` decimal(4,2) NOT NULL COMMENT 'SI1147 max uv index', \
  `SI1147_VIS_MAX` decimal(8,2) NOT NULL COMMENT 'SI1147 max visible light in lux', \
  `SI1147_IR_MAX` decimal(8,2) NOT NULL COMMENT 'SI1147 max ir light in lux', \
  `VOLT_BAT_MAX` decimal(3,2) NOT NULL COMMENT 'Sensor max battery voltage in V', \
  `CHARGE_BAT_MAX` decimal(5,2) NOT NULL COMMENT 'Sensor max battery charge in %', \
  `RATE_BAT_MAX` decimal(4,2) NOT NULL COMMENT 'Sensor max battery charge rate in %/hr', \
  `VOLT_SOLAR_MAX` decimal(3,2) NOT NULL COMMENT 'Sensor max solar cell voltage in V', \
  `RSSI_MAX` decimal(4,1) NOT NULL COMMENT 'Sensor min rssi in dBm' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_min_values = "CREATE TABLE IF NOT EXISTS `SensorsMin` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` TINYINT NOT NULL COMMENT 'Address from sensor', \
  `DATE` date NULL COMMENT 'Date of day data', \
  `HDC1000_TEMP_MIN` decimal(5,2) NOT NULL COMMENT 'HDC1000 min temperature °C', \
  `HDC1000_HUMI_MIN` decimal(5,2) NOT NULL COMMENT 'HDC1000 min humidity in %', \
  `TMP102_TEMP_MIN` decimal(5,2) NOT NULL COMMENT 'TMP102 min temperature in °C', \
  `LPS25H_TEMP_MIN` decimal(5,2) NOT NULL COMMENT 'LPS25H min temperature in °C', \
  `LPS25H_PRESS_MIN` decimal(6,2) NOT NULL COMMENT 'LPS25H min pressure in hPa', \
  `SI1147_UV_MIN` decimal(4,2) NOT NULL COMMENT 'SI1147 min uv index', \
  `SI1147_VIS_MIN` decimal(8,2) NOT NULL COMMENT 'SI1147 min visible light in lux', \
  `SI1147_IR_MIN` decimal(8,2) NOT NULL COMMENT 'SI1147 min ir light in lux', \
  `VOLT_BAT_MIN` decimal(3,2) NOT NULL COMMENT 'Sensor min battery voltage in V', \
  `CHARGE_BAT_MIN` decimal(5,2) NOT NULL COMMENT 'Sensor min battery charge in %', \
  `RATE_BAT_MIN` decimal(4,2) NOT NULL COMMENT 'Sensor min battery charge rate in %/hr', \
  `VOLT_SOLAR_MIN` decimal(3,2) NOT NULL COMMENT 'Sensor min solar cell voltage in V', \
  `RSSI_MIN` decimal(4,1) NOT NULL COMMENT 'Sensor min rssi in dBm' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_avg_values = "CREATE TABLE IF NOT EXISTS `SensorsAvg` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` INT NOT NULL COMMENT 'Address from sensor', \
  `DATE` date NULL COMMENT 'Date of day data', \
  `SAMPLES` INT NULL COMMENT 'Samples of averaging', \
  `HDC1000_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'HDC1000 avg temperature °C', \
  `HDC1000_HUMI_AVG` decimal(5,2) NOT NULL COMMENT 'HDC1000 avg humidity in %', \
  `TMP102_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'TMP102 avg temperature in °C', \
  `LPS25H_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'LPS25H avg temperature in °C', \
  `LPS25H_PRESS_AVG` decimal(6,2) NOT NULL COMMENT 'LPS25H avg pressure in hPa', \
  `SI1147_UV_AVG` decimal(4,2) NOT NULL COMMENT 'SI1147 avg uv index', \
  `SI1147_VIS_AVG` decimal(8,2) NOT NULL COMMENT 'SI1147 avg visible light in lux', \
  `SI1147_IR_AVG` decimal(8,2) NOT NULL COMMENT 'SI1147 avg ir light in lux', \
  `VOLT_BAT_AVG` decimal(3,2) NOT NULL COMMENT 'Sensor avg battery voltage in V', \
  `CHARGE_BAT_AVG` decimal(5,2) NOT NULL COMMENT 'Sensor avg battery charge in %', \
  `RATE_BAT_AVG` decimal(4,2) NOT NULL COMMENT 'Sensor avg battery charge rate in %/hr', \
  `VOLT_SOLAR_AVG` decimal(3,2) NOT NULL COMMENT 'Sensor avg solar cell voltage in V', \
  `RSSI_AVG` decimal(4,1) NOT NULL COMMENT 'Sensor avg rssi in dBm' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_act_avg_values = "CREATE TABLE IF NOT EXISTS `SensorsActAvg` ( \
  `ID` INT KEY AUTO_INCREMENT, \
  `ADDRESS` INT NOT NULL COMMENT 'Address from sensor', \
  `AVGTIME` INT NULL COMMENT 'Time of averaging', \
  `SAMPLES` INT NULL COMMENT 'Samples of averaging', \
  `HDC1000_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'HDC1000 avg temperature °C', \
  `HDC1000_HUMI_AVG` decimal(5,2) NOT NULL COMMENT 'HDC1000 avg humidity in %', \
  `TMP102_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'TMP102 avg temperature in °C', \
  `LPS25H_TEMP_AVG` decimal(5,2) NOT NULL COMMENT 'LPS25H avg temperature in °C', \
  `LPS25H_PRESS_AVG` decimal(6,2) NOT NULL COMMENT 'LPS25H avg pressure in hPa', \
  `SI1147_UV_AVG` decimal(4,2) NOT NULL COMMENT 'SI1147 avg uv index', \
  `SI1147_VIS_AVG` decimal(8,2) NOT NULL COMMENT 'SI1147 avg visible light in lux', \
  `SI1147_IR_AVG` decimal(8,2) NOT NULL COMMENT 'SI1147 avg ir light in lux', \
  `VOLT_BAT_AVG` decimal(3,2) NOT NULL COMMENT 'Sensor avg battery voltage in V', \
  `CHARGE_BAT_AVG` decimal(5,2) NOT NULL COMMENT 'Sensor avg battery charge in %', \
  `RATE_BAT_AVG` decimal(4,2) NOT NULL COMMENT 'Sensor avg battery charge rate in %/hr', \
  `VOLT_SOLAR_AVG` decimal(3,2) NOT NULL COMMENT 'Sensor avg solar cell voltage in V', \
  `RSSI_AVG` decimal(4,1) NOT NULL COMMENT 'Sensor avg rssi in dBm' \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_table_protocol = "CREATE TABLE IF NOT EXISTS `%s` ( \
  `ID` BIGINT KEY AUTO_INCREMENT, \
  `DATE` date NULL COMMENT 'Date of received data', \
  `TIME` time NULL COMMENT 'Time of received data', \
  `HDC1000_TEMP` decimal(5,2) NOT NULL COMMENT 'HDC1000 temperature °C', \
  `HDC1000_HUMI` decimal(5,2) NOT NULL COMMENT 'HDC1000 humidity in %', \
  `TMP102_TEMP` decimal(5,2) NOT NULL COMMENT 'TMP102 temperature in °C', \
  `LPS25H_TEMP` decimal(5,2) NOT NULL COMMENT 'LPS25H temperature in °C', \
  `LPS25H_PRESS` decimal(6,2) NOT NULL COMMENT 'LPS25H pressure in hPa', \
  `SI1147_UV` decimal(4,2) NOT NULL COMMENT 'SI1147 uv index', \
  `SI1147_VIS` decimal(8,2) NOT NULL COMMENT 'SI1147 visible light in lux', \
  `SI1147_IR` decimal(8,2) NOT NULL COMMENT 'SI1147 ir light in lux', \
  `VOLT_BAT` decimal(3,2) NOT NULL COMMENT 'Sensor battery voltage in V', \
  `CHARGE_BAT` decimal(5,2) NOT NULL COMMENT 'Sensor battery charge in %', \
  `RATE_BAT` decimal(4,2) NOT NULL COMMENT 'Sensor battery charge rate in %/hr', \
  `VOLT_SOLAR` decimal(3,2) NOT NULL COMMENT 'Sensor solar cell voltage in V', \
  `RSSI` decimal(4,1) NOT NULL COMMENT 'Received signal strength in dBm', \
  `DATETIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP \
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;";

const std::string mysql_update_sensors_active = "UPDATE `SensorsActive` SET `STATUS` = '%d', `MESSUREMENTS` = `MESSUREMENTS` + '1' WHERE `ADDRESS` = '%d';";

const std::string mysql_update_sensorsmax = "UPDATE `SensorsMax` SET \
`HDC1000_TEMP_MAX`= IF(`HDC1000_TEMP_MAX` > %f,`HDC1000_TEMP_MAX`, %f), \
`HDC1000_HUMI_MAX`= IF(`HDC1000_HUMI_MAX` > %f,`HDC1000_HUMI_MAX`, %f), \
`TMP102_TEMP_MAX`= IF(`TMP102_TEMP_MAX` > %f,`TMP102_TEMP_MAX`, %f), \
`VOLT_BAT_MAX`= IF(`VOLT_BAT_MAX` > %f,`VOLT_BAT_MAX`, %f), \
`CHARGE_BAT_MAX`= IF(`CHARGE_BAT_MAX` > %f,`CHARGE_BAT_MAX`, %f), \
`RATE_BAT_MAX`= IF(`RATE_BAT_MAX` > %f,`RATE_BAT_MAX`, %f), \
`VOLT_SOLAR_MAX`= IF(`VOLT_SOLAR_MAX` > %f,`VOLT_SOLAR_MAX`, %f), \
`LPS25H_TEMP_MAX`= IF(`LPS25H_TEMP_MAX` > %f,`LPS25H_TEMP_MAX`, %f), \
`LPS25H_PRESS_MAX`= IF(`LPS25H_PRESS_MAX` > %f,`LPS25H_PRESS_MAX`, %f), \
`SI1147_UV_MAX`= IF(`SI1147_UV_MAX` > %f,`SI1147_UV_MAX`, %f), \
`SI1147_VIS_MAX`= IF(`SI1147_VIS_MAX` > %f,`SI1147_VIS_MAX`, %f), \
`SI1147_IR_MAX`= IF(`SI1147_IR_MAX` > %f,`SI1147_IR_MAX`, %f), \
`RSSI_MAX`= IF(`RSSI_MAX` < %f,`RSSI_MAX`, %f) \
WHERE `ADDRESS` = '%d' AND `DATE` = DATE(NOW()) LIMIT 1;";

const std::string mysql_update_sensorsmin = "UPDATE `SensorsMin` SET \
`HDC1000_TEMP_MIN`= IF(`HDC1000_TEMP_MIN` < %f,`HDC1000_TEMP_MIN`, %f), \
`HDC1000_HUMI_MIN`= IF(`HDC1000_HUMI_MIN` < %f,`HDC1000_HUMI_MIN`, %f), \
`TMP102_TEMP_MIN`= IF(`TMP102_TEMP_MIN` < %f,`TMP102_TEMP_MIN`, %f), \
`VOLT_BAT_MIN`= IF(`VOLT_BAT_MIN` < %f,`VOLT_BAT_MIN`, %f), \
`CHARGE_BAT_MIN`= IF(`CHARGE_BAT_MIN` < %f,`CHARGE_BAT_MIN`, %f), \
`RATE_BAT_MIN`= IF(`RATE_BAT_MIN` < %f,`RATE_BAT_MIN`, %f), \
`VOLT_SOLAR_MIN`= IF(`VOLT_SOLAR_MIN` < %f,`VOLT_SOLAR_MIN`, %f), \
`LPS25H_TEMP_MIN`= IF(`LPS25H_TEMP_MIN` < %f,`LPS25H_TEMP_MIN`, %f), \
`LPS25H_PRESS_MIN`= IF(`LPS25H_PRESS_MIN` < %f,`LPS25H_PRESS_MIN`, %f), \
`SI1147_UV_MIN`= IF(`SI1147_UV_MIN` < %f,`SI1147_UV_MIN`, %f), \
`SI1147_VIS_MIN`= IF(`SI1147_VIS_MIN` < %f,`SI1147_VIS_MIN`, %f), \
`SI1147_IR_MIN`= IF(`SI1147_IR_MIN` < %f,`SI1147_IR_MIN`, %f), \
`RSSI_MIN`= IF(`RSSI_MIN` < %f,`RSSI_MIN`, %f) \
WHERE `ADDRESS` = '%d' AND `DATE` = DATE(NOW()) LIMIT 1;";

const std::string mysql_update_sensors_act_avgs = "UPDATE `SensorsActAvg` SET \
`HDC1000_TEMP_AVG`= ((`HDC1000_TEMP_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`HDC1000_HUMI_AVG`= ((`HDC1000_HUMI_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`TMP102_TEMP_AVG`= ((`TMP102_TEMP_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`VOLT_BAT_AVG`= ((`VOLT_BAT_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`CHARGE_BAT_AVG`= ((`CHARGE_BAT_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`RATE_BAT_AVG`= ((`RATE_BAT_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`VOLT_SOLAR_AVG`= ((`VOLT_SOLAR_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`LPS25H_TEMP_AVG`= ((`LPS25H_TEMP_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`LPS25H_PRESS_AVG`= ((`LPS25H_PRESS_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`SI1147_UV_AVG`= ((`SI1147_UV_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`SI1147_VIS_AVG`= ((`SI1147_VIS_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`SI1147_IR_AVG`= ((`SI1147_IR_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`RSSI_AVG` = ((`RSSI_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`SAMPLES` = IF(`SAMPLES` < `AVGTIME`, `SAMPLES` + 1, `SAMPLES`) \
WHERE `ADDRESS` = '%d' AND `AVGTIME` = '%d' LIMIT 1;";

const std::string mysql_update_sensorsavg = "UPDATE `SensorsAvg` SET \
`HDC1000_TEMP_AVG`= ((`HDC1000_TEMP_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`HDC1000_HUMI_AVG`= ((`HDC1000_HUMI_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`TMP102_TEMP_AVG`= ((`TMP102_TEMP_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`VOLT_BAT_AVG`= ((`VOLT_BAT_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`CHARGE_BAT_AVG`= ((`CHARGE_BAT_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`RATE_BAT_AVG`= ((`RATE_BAT_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`VOLT_SOLAR_AVG`= ((`VOLT_SOLAR_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`LPS25H_TEMP_AVG`= ((`LPS25H_TEMP_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`LPS25H_PRESS_AVG`= ((`LPS25H_PRESS_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`SI1147_UV_AVG`= ((`SI1147_UV_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`SI1147_VIS_AVG`= ((`SI1147_VIS_AVG` * `SAMPLES`)  + %f) / (`SAMPLES` + 1), \
`SI1147_IR_AVG`= ((`SI1147_IR_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`RSSI_AVG` = ((`RSSI_AVG` * `SAMPLES`) + %f) / (`SAMPLES` + 1), \
`SAMPLES` = `SAMPLES` + 1 \
WHERE `ADDRESS` = '%d' AND `DATE` = DATE(NOW()) LIMIT 1;";

const std::string mysql_insert_sensors_active = "INSERT INTO `SensorsActive` \
		( `ID`, `NAME`, `ADDRESS`, `UPDATETED`, `STATUS`, `PROTOCOL`, `MESSUREMENTS`, `HISTORY`, `TOTAL`)\
		VALUES \
		('', '%s', '%d', CURRENT_TIMESTAMP, '0', '%d', '0', '0', '0');";

const std::string mysql_insert_protocol_data = "INSERT INTO `%s` \
		(`ID`, `DATE`, `TIME`, `HDC1000_TEMP`, `HDC1000_HUMI`, `TMP102_TEMP`, `VOLT_BAT`, `CHARGE_BAT`, `RATE_BAT`, `VOLT_SOLAR`, `LPS25H_TEMP`, `LPS25H_PRESS`, `SI1147_UV`, `SI1147_VIS`, `SI1147_IR`, `RSSI`, `DATETIME`) \
		VALUES \
		('', NOW(), NOW(), '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', CURRENT_TIMESTAMP)";

const std::string mysql_insert_sensorsavg = "INSERT INTO `SensorsAvg` \
(`ADDRESS`, `SAMPLES`, `DATE`, `HDC1000_TEMP_AVG`, `HDC1000_HUMI_AVG`, `TMP102_TEMP_AVG`, `VOLT_BAT_AVG`, `CHARGE_BAT_AVG`, `RATE_BAT_AVG`, `VOLT_SOLAR_AVG`, `LPS25H_TEMP_AVG`, `LPS25H_PRESS_AVG`, `SI1147_UV_AVG`, `SI1147_VIS_AVG`, `SI1147_IR_AVG`, `RSSI_AVG`) \
VALUES \
(%d, 1, NOW(), %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

const std::string mysql_insert_sensorsactavg = "INSERT INTO `SensorsActAvg` \
(`ADDRESS`, `AVGTIME`, `SAMPLES`, `HDC1000_TEMP_AVG`, `HDC1000_HUMI_AVG`, `TMP102_TEMP_AVG`, `VOLT_BAT_AVG`, `CHARGE_BAT_AVG`, `RATE_BAT_AVG`, `VOLT_SOLAR_AVG`, `LPS25H_TEMP_AVG`, `LPS25H_PRESS_AVG`, `SI1147_UV_AVG`, `SI1147_VIS_AVG`, `SI1147_IR_AVG`, `RSSI_AVG`) \
VALUES \
(%d, %d, 1, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

const std::string mysql_insert_sensorsmax = "INSERT INTO `SensorsMax` \
(`ADDRESS`, `DATE`, `HDC1000_TEMP_MAX`, `HDC1000_HUMI_MAX`, `TMP102_TEMP_MAX`, `VOLT_BAT_MAX`, `CHARGE_BAT_MAX`, `RATE_BAT_MAX`, `VOLT_SOLAR_MAX`, `LPS25H_TEMP_MAX`, `LPS25H_PRESS_MAX`, `SI1147_UV_MAX`, `SI1147_VIS_MAX`, `SI1147_IR_MAX`, `RSSI_MAX`) \
VALUES \
(%d, NOW(), %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

const std::string mysql_insert_sensorsmin = "INSERT INTO `SensorsMin` \
(`ADDRESS`, `DATE`, `HDC1000_TEMP_MIN`, `HDC1000_HUMI_MIN`, `TMP102_TEMP_MIN`, `VOLT_BAT_MIN`, `CHARGE_BAT_MIN`, `RATE_BAT_MIN`, `VOLT_SOLAR_MIN`, `LPS25H_TEMP_MIN`, `LPS25H_PRESS_MIN`, `SI1147_UV_MIN`, `SI1147_VIS_MIN`, `SI1147_IR_MIN`, `RSSI_MIN`) \
VALUES \
(%d, NOW(), %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);";

#endif /* MYSQL_COMMANDS_H_ */
