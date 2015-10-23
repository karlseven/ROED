/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50622
Source Host           : 127.0.0.1:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50622
File Encoding         : 65001

Date: 2015-02-19 22:45:43
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for news
-- ----------------------------
DROP TABLE IF EXISTS `news`;
CREATE TABLE `news` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `author` varchar(255) DEFAULT NULL,
  `date` varchar(255) DEFAULT NULL,
  `type` varchar(255) DEFAULT NULL,
  `title` varchar(255) DEFAULT NULL,
  `content` longtext,
  `update` int(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of news
-- ----------------------------
INSERT INTO `news` VALUES ('31', 'Matt', '12/04/2014 12:06 AM', 'news', 'New Web Site', 'Thanks to Huely our web designer he has been cooking a stunning new RoseFateOnline website there will be alot of features added, but right now we just have the basics so if you see him in game make sure you say Hi.\r\n', '1');
INSERT INTO `news` VALUES ('32', 'kismetbecomes', '12/09/2014 8:19 AM', 'news', 'Website Updates and Progress', '<p style=\"text-align: justify;\">RoseFate players, it is my pleasure to announce the pre-release of this server\'s new website with a lot of facelifts and features. I\'m looking forward to contributing in best possible ways for the website to both attract players and to also accomodate the expectations and needs of RoseFate Online players. Mention that this is a Pre-release, here are what currently works and is accessible to RoseFate Players.</p>\r\n<p>&nbsp;</p>\r\n<p><strong>What currently works / is added / is updated:</strong></p>\r\n<ul>\r\n<li>Registration</li>\r\n<li>Login</li>\r\n<li>Player Information Display</li>\r\n<li>Voting Point System ( You may vote now and horde&nbsp;more points when vote mall is released. )</li>\r\n<li>Level Rankings</li>\r\n<li>Download Client Link</li>\r\n<li>Facebook ( Like the Page )</li>\r\n<li>Forums</li>\r\n<li>News</li>\r\n<li>Player Information Editor</li>\r\n<li>Community Links</li>\r\n<li>Server Status</li>\r\n</ul>\r\n<p><strong>What will be added soon:</strong></p>\r\n<ul>\r\n<li>Share-able News</li>\r\n<li>News Comments</li>\r\n<li>Media ( PrintScreens, Wallpapers per user )</li>\r\n<li>Vote Mall</li>\r\n<li>Item Mall</li>\r\n<li>Registration Captcha</li>\r\n<li>Registration Secret Question</li>\r\n<li>Player Password Recovery</li>\r\n<li>FAQ Section</li>\r\n<li>Image News Slideshow</li>\r\n</ul>\r\n<p>&nbsp;</p>\r\n<p><strong>Administrative Function Updates</strong>:</p>\r\n<ul>\r\n<li>Recoded the entire Add News, Edit News and Display News</li>\r\n<li>Added New Global Prompt Function instead of alert</li>\r\n</ul>', '1418134752');
