/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50622
Source Host           : 127.0.0.1:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50622
File Encoding         : 65001

Date: 2015-02-19 22:46:06
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for vote_links
-- ----------------------------
DROP TABLE IF EXISTS `vote_links`;
CREATE TABLE `vote_links` (
  `id` int(11) NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `vote_link` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of vote_links
-- ----------------------------
INSERT INTO `vote_links` VALUES ('1', 'Extreme Top 100', 'http://www.xtremetop100.com/in.php?site=1132353146');
INSERT INTO `vote_links` VALUES ('2', 'GTop 100', 'http://www.gtop100.com/topsites/Rose-Online/sitedetails/Rose-Fate-Online-87177?vote=1');
INSERT INTO `vote_links` VALUES ('3', 'Top of Games', 'http://topofgames.com/index.php?do=votes&id=77101');
