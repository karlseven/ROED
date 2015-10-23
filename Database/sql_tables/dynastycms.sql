/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50622
Source Host           : 127.0.0.1:3306
Source Database       : Revolution

Target Server Type    : MYSQL
Target Server Version : 50622
File Encoding         : 65001

Date: 2015-05-14 22:15:23
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for dynastycms
-- ----------------------------
DROP TABLE IF EXISTS `dynastycms`;
CREATE TABLE `dynastycms` (
  `title` varchar(100) DEFAULT NULL,
  `forums` varchar(100) DEFAULT NULL,
  `client` varchar(100) DEFAULT NULL,
  `patch` varchar(100) DEFAULT NULL,
  `exprate` varchar(100) DEFAULT NULL,
  `droprate` varchar(100) DEFAULT NULL,
  `zulyrate` varchar(100) DEFAULT NULL,
  `question` varchar(100) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of dynastycms
-- ----------------------------
INSERT INTO `dynastycms` VALUES ('RoseRevolution', 'http://s7.zetaboards.com/FurianRose/index/', null, null, '10', '10', '100', '7');
