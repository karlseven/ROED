/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50622
Source Host           : 127.0.0.1:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50622
File Encoding         : 65001

Date: 2015-02-19 22:46:18
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for staff_list
-- ----------------------------
DROP TABLE IF EXISTS `staff_list`;
CREATE TABLE `staff_list` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `character_name` varchar(255) DEFAULT NULL,
  `position` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of staff_list
-- ----------------------------
INSERT INTO `staff_list` VALUES ('2', 'Diddy', 'Moderator');
INSERT INTO `staff_list` VALUES ('3', 'Fizzmo', 'Moderator');
INSERT INTO `staff_list` VALUES ('4', 'NiMi', 'Moderator');
INSERT INTO `staff_list` VALUES ('5', 'Andy', 'Moderator');
INSERT INTO `staff_list` VALUES ('6', 'EvilKenz', 'Artist');
INSERT INTO `staff_list` VALUES ('7', 'Meydan', 'Programmer');
INSERT INTO `staff_list` VALUES ('8', 'Kismetbecomes', 'Web Developer');
INSERT INTO `staff_list` VALUES ('9', 'Megumi', 'Client Developer');
INSERT INTO `staff_list` VALUES ('10', 'iGod', 'Client Developer');
INSERT INTO `staff_list` VALUES ('11', 'StreetDog', 'Client Developer');
INSERT INTO `staff_list` VALUES ('12', 'R3L0AD', 'Head Developer');
INSERT INTO `staff_list` VALUES ('13', 'Fallout', 'Co-Administrator');
INSERT INTO `staff_list` VALUES ('14', 'Matt', 'Administrator');
