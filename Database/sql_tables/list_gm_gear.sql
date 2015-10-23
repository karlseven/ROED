/*
MySQL Data Transfer
Source Host: localhost
Source Database: roseza
Target Host: localhost
Target Database: roseza
Date: 11/8/2012 9:23:17 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_gm_gear
-- ----------------------------
CREATE TABLE `list_gm_gear` (
  `id` int(11) NOT NULL auto_increment,
  `itemnumber` int(11) NOT NULL,
  `itemtype` int(11) NOT NULL,
  `GEAR` varchar(4) NOT NULL,
  `isactive` int(11) NOT NULL default '1',
  `description` varchar(50) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_gm_gear` VALUES ('1', '151', '2', 'GM', '1', 'GM-Hat');
INSERT INTO `list_gm_gear` VALUES ('2', '151', '3', 'GM', '1', 'GM-Armor');
INSERT INTO `list_gm_gear` VALUES ('3', '151', '4', 'GM', '1', 'GM-Gloves');
INSERT INTO `list_gm_gear` VALUES ('4', '151', '5', 'GM', '1', 'GM-Shoes');
