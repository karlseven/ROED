/*
MySQL Data Transfer
Source Host: localhost
Source Database: roseza
Target Host: localhost
Target Database: roseza
Date: 11/8/2012 7:57:41 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_golist
-- ----------------------------
CREATE TABLE `list_golist` (
  `id` int(11) NOT NULL auto_increment,
  `loc` int(11) NOT NULL,
  `mapname` varchar(50) character set utf8 NOT NULL,
  `lvlmin` int(11) NOT NULL default '0',
  `lvlmax` int(11) NOT NULL default '250',
  `map` int(11) NOT NULL,
  `locx` int(11) NOT NULL,
  `locy` int(11) NOT NULL,
  `isactive` int(11) NOT NULL,
  `description` varchar(50) character set utf8 default NULL,
  PRIMARY KEY  (`id`,`loc`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_golist` VALUES ('1', '1', 'Adventure Plains', '0', '250', '22', '5649', '5161', '1', null);
INSERT INTO `list_golist` VALUES ('2', '2', 'Canyon City of Zant', '0', '250', '1', '5240', '5192', '1', null);
INSERT INTO `list_golist` VALUES ('3', '3', 'Junon Polis', '0', '250', '2', '5514', '5247', '1', null);
INSERT INTO `list_golist` VALUES ('4', '4', 'Magic City of Eucar - Luna', '50', '250', '51', '5357', '5013', '1', null);
INSERT INTO `list_golist` VALUES ('5', '5', 'Xita Refuge - Eldeon', '120', '250', '61', '5434', '4569', '1', null);
INSERT INTO `list_golist` VALUES ('6', '6', 'Sikuku Underground Prison', '160', '250', '65', '5485', '5285', '1', null);
INSERT INTO `list_golist` VALUES ('7', '7', 'Desert City of Muris - Oro', '180', '250', '71', '5199', '5236', '1', null);
INSERT INTO `list_golist` VALUES ('8', '8', 'Junon Clan Field', '0', '250', '11', '5512', '5019', '1', null);
INSERT INTO `list_golist` VALUES ('9', '9', 'Training Grounds', '0', '250', '6', '5199', '5280', '1', null);
INSERT INTO `list_golist` VALUES ('10', '10', 'Lions Plains', '0', '250', '8', '5160', '5080', '1', null);
INSERT INTO `list_golist` VALUES ('11', '11', 'Desert of the Dead', '0', '250', '29', '5093', '5144', '1', null);
INSERT INTO `list_golist` VALUES ('12', '12', 'Luna Clan Field', '120', '250', '59', '5095', '5128', '1', null);
INSERT INTO `list_golist` VALUES ('13', '13', 'Crystal Defenders', '0', '250', '131', '5197', '5184', '1', null);
INSERT INTO `list_golist` VALUES ('14', '14', 'Cave of Ulverick', '0', '250', '138', '5084', '5040', '1', null);
INSERT INTO `list_golist` VALUES ('15', '15', 'Halls of Oblivion', '0', '250', '143', '5020', '5250', '1', null);
INSERT INTO `list_golist` VALUES ('16', '16', 'Sea of Dawn', '0', '250', '148', '5200', '4772', '1', null);
INSERT INTO `list_golist` VALUES ('17', '17', 'Old Title Map', '0', '250', '4', '5084', '5021', '1', null);
INSERT INTO `list_golist` VALUES ('18', '18', 'Sunshine Coast - Event', '0', '250', '37', '5098', '5233', '1', null);
INSERT INTO `list_golist` VALUES ('19', '19', 'Grand Ballroom', '0', '250', '40', '5184', '5211', '1', null);
INSERT INTO `list_golist` VALUES ('20', '20', 'Santa Planetoid', '0', '250', '38', '5074', '5342', '1', null);
