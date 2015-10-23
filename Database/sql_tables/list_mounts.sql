/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50622
Source Host           : 127.0.0.1:3306
Source Database       : Dev4

Target Server Type    : MYSQL
Target Server Version : 50622
File Encoding         : 65001

Date: 2015-02-20 02:29:39
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for list_mounts
-- ----------------------------
DROP TABLE IF EXISTS `list_mounts`;
CREATE TABLE `list_mounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `mountid` int(11) DEFAULT NULL,
  `mspeed` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=56 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of list_mounts
-- ----------------------------
INSERT INTO `list_mounts` VALUES ('43', 'Choropy (15)', '1', '1000');
INSERT INTO `list_mounts` VALUES ('44', 'Sabretooth (7)', '2', '1500');
INSERT INTO `list_mounts` VALUES ('45', 'Luna Wolf (7)', '3', '1500');
INSERT INTO `list_mounts` VALUES ('46', 'Moldie (7)', '4', '1250');
INSERT INTO `list_mounts` VALUES ('47', 'Moldie (5)', '5', '1250');
INSERT INTO `list_mounts` VALUES ('48', 'Krawfy (7)', '6', '1500');
INSERT INTO `list_mounts` VALUES ('49', 'Green Krawfy (7)', '7', '1500');
INSERT INTO `list_mounts` VALUES ('50', 'Sabertooth (30)', '8', '1500');
INSERT INTO `list_mounts` VALUES ('51', 'Luna Wolf (30)', '9', '1250');
INSERT INTO `list_mounts` VALUES ('52', 'Moldie (30)', '10', '1250');
INSERT INTO `list_mounts` VALUES ('53', 'Chicken (30)', '11', '1250');
INSERT INTO `list_mounts` VALUES ('54', 'Mammoth (30)', '12', '750');
INSERT INTO `list_mounts` VALUES ('55', 'Mammoth (30)', '13', '1250');
