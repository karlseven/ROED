/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50622
Source Host           : 127.0.0.1:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50622
File Encoding         : 65001

Date: 2015-02-19 22:45:55
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for vote_counters
-- ----------------------------
DROP TABLE IF EXISTS `vote_counters`;
CREATE TABLE `vote_counters` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) DEFAULT NULL,
  `vote_link_id` int(11) DEFAULT NULL,
  `last_voted` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=211 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of vote_counters
-- ----------------------------
INSERT INTO `vote_counters` VALUES ('23', 'kismetbecomes', '1', '1418101755');
INSERT INTO `vote_counters` VALUES ('24', 'kismetbecomes', '2', '1418134402');
INSERT INTO `vote_counters` VALUES ('25', 'kismetbecomes', '3', '1418134776');
INSERT INTO `vote_counters` VALUES ('26', '', '0', '1419772764');
INSERT INTO `vote_counters` VALUES ('27', 'Matt12', '3', '1417738333');
INSERT INTO `vote_counters` VALUES ('28', 'Matt12', '2', '1417738455');
INSERT INTO `vote_counters` VALUES ('29', 'Matt12', '1', '1417738898');
INSERT INTO `vote_counters` VALUES ('30', 'cinecleric', '1', '1418388035');
INSERT INTO `vote_counters` VALUES ('31', 'cinecleric', '2', '1418388037');
INSERT INTO `vote_counters` VALUES ('32', 'cinecleric', '3', '1418388041');
INSERT INTO `vote_counters` VALUES ('33', 'diddytt128', '1', '1419005064');
INSERT INTO `vote_counters` VALUES ('34', 'diddytt128', '2', '1419005067');
INSERT INTO `vote_counters` VALUES ('35', 'diddytt128', '3', '1419005069');
INSERT INTO `vote_counters` VALUES ('36', 'cine', '1', '1418388120');
INSERT INTO `vote_counters` VALUES ('37', 'cine', '2', '1418388123');
INSERT INTO `vote_counters` VALUES ('38', 'cine', '3', '1418388126');
INSERT INTO `vote_counters` VALUES ('39', 'metaru', '1', '1418280581');
INSERT INTO `vote_counters` VALUES ('40', 'metaru', '2', '1418280586');
INSERT INTO `vote_counters` VALUES ('41', 'metaru', '3', '1418280591');
INSERT INTO `vote_counters` VALUES ('42', 'ervin112088', '1', '1419767076');
INSERT INTO `vote_counters` VALUES ('43', 'ervin112088', '2', '1419767078');
INSERT INTO `vote_counters` VALUES ('44', 'ervin112088', '3', '1419767079');
INSERT INTO `vote_counters` VALUES ('45', 'cineone', '1', '1418388196');
INSERT INTO `vote_counters` VALUES ('46', 'cineone', '2', '1418388200');
INSERT INTO `vote_counters` VALUES ('47', 'cineone', '3', '1418388202');
INSERT INTO `vote_counters` VALUES ('48', 'totat', '1', '1417839769');
INSERT INTO `vote_counters` VALUES ('49', 'totat', '2', '1417839767');
INSERT INTO `vote_counters` VALUES ('50', 'totat', '3', '1417839765');
INSERT INTO `vote_counters` VALUES ('51', 'krocker', '3', '1418716075');
INSERT INTO `vote_counters` VALUES ('52', 'krocker', '1', '1418716063');
INSERT INTO `vote_counters` VALUES ('53', 'krocker', '2', '1418716069');
INSERT INTO `vote_counters` VALUES ('54', 'darren11', '1', '1419773026');
INSERT INTO `vote_counters` VALUES ('55', 'darren11', '2', '1419773030');
INSERT INTO `vote_counters` VALUES ('56', 'darren11', '3', '1419773032');
INSERT INTO `vote_counters` VALUES ('57', 'slootss', '1', '1417948998');
INSERT INTO `vote_counters` VALUES ('58', 'slootss', '2', '1417949029');
INSERT INTO `vote_counters` VALUES ('59', 'slootss', '3', '1417949057');
INSERT INTO `vote_counters` VALUES ('60', 'itsmitmit', '1', '1417710858');
INSERT INTO `vote_counters` VALUES ('61', 'itsmitmit', '2', '1417710862');
INSERT INTO `vote_counters` VALUES ('62', 'itsmitmit', '3', '1417710864');
INSERT INTO `vote_counters` VALUES ('63', 'jelleb', '1', '1418980812');
INSERT INTO `vote_counters` VALUES ('64', 'jelleb', '2', '1418980852');
INSERT INTO `vote_counters` VALUES ('65', 'jelleb', '3', '1418980887');
INSERT INTO `vote_counters` VALUES ('66', 'joris', '1', '1417820691');
INSERT INTO `vote_counters` VALUES ('67', 'joris', '2', '1417820735');
INSERT INTO `vote_counters` VALUES ('68', 'joris', '3', '1417820761');
INSERT INTO `vote_counters` VALUES ('69', 'lulu', '1', '1419759307');
INSERT INTO `vote_counters` VALUES ('70', 'lulu', '2', '1419759343');
INSERT INTO `vote_counters` VALUES ('71', 'lulu', '3', '1419759361');
INSERT INTO `vote_counters` VALUES ('72', 'alxcleric', '1', '1417735644');
INSERT INTO `vote_counters` VALUES ('73', 'alxcleric', '2', '1417735656');
INSERT INTO `vote_counters` VALUES ('74', 'alxcleric', '3', '1417735668');
INSERT INTO `vote_counters` VALUES ('75', 'darren81192', '1', '1419773070');
INSERT INTO `vote_counters` VALUES ('76', 'darren81192', '2', '1419773072');
INSERT INTO `vote_counters` VALUES ('77', 'darren81192', '3', '1419773074');
INSERT INTO `vote_counters` VALUES ('78', 'darren', '1', '1419773091');
INSERT INTO `vote_counters` VALUES ('79', 'darren', '2', '1419773092');
INSERT INTO `vote_counters` VALUES ('80', 'darren', '3', '1419773094');
INSERT INTO `vote_counters` VALUES ('81', 'Gulden', '1', '1418637305');
INSERT INTO `vote_counters` VALUES ('82', 'Gulden', '2', '1418637344');
INSERT INTO `vote_counters` VALUES ('83', 'Gulden', '3', '1418637425');
INSERT INTO `vote_counters` VALUES ('84', '[ADMIN]Matt', '1', '1418250350');
INSERT INTO `vote_counters` VALUES ('85', '[ADMIN]Matt', '2', '1418250290');
INSERT INTO `vote_counters` VALUES ('86', '[ADMIN]Matt', '3', '1418249992');
INSERT INTO `vote_counters` VALUES ('87', 'Aluru666', '1', '1418799641');
INSERT INTO `vote_counters` VALUES ('88', 'Aluru666', '2', '1418799642');
INSERT INTO `vote_counters` VALUES ('89', 'Aluru666', '3', '1418799643');
INSERT INTO `vote_counters` VALUES ('90', 'rose', '1', '1418956031');
INSERT INTO `vote_counters` VALUES ('91', 'rose', '2', '1418956031');
INSERT INTO `vote_counters` VALUES ('92', 'rose', '3', '1418956035');
INSERT INTO `vote_counters` VALUES ('93', 'Mira', '2', '1418417951');
INSERT INTO `vote_counters` VALUES ('94', 'Mira', '1', '1418417908');
INSERT INTO `vote_counters` VALUES ('95', 'Mira', '3', '1418417995');
INSERT INTO `vote_counters` VALUES ('96', 'swayday', '1', '1419763517');
INSERT INTO `vote_counters` VALUES ('97', 'swayday', '2', '1419763519');
INSERT INTO `vote_counters` VALUES ('98', 'swayday', '3', '1419763522');
INSERT INTO `vote_counters` VALUES ('99', 'dialtone', '1', '1419482406');
INSERT INTO `vote_counters` VALUES ('100', 'dialtone', '2', '1419482532');
INSERT INTO `vote_counters` VALUES ('101', 'imsocute', '1', '1419579372');
INSERT INTO `vote_counters` VALUES ('102', 'imsocute', '2', '1419579377');
INSERT INTO `vote_counters` VALUES ('103', 'imsocute', '3', '1419579382');
INSERT INTO `vote_counters` VALUES ('104', 'imsocute143', '1', '1419579409');
INSERT INTO `vote_counters` VALUES ('105', 'imsocute143', '2', '1419579415');
INSERT INTO `vote_counters` VALUES ('106', 'imsocute143', '3', '1419579421');
INSERT INTO `vote_counters` VALUES ('107', 'ultrata', '1', '1418146617');
INSERT INTO `vote_counters` VALUES ('108', 'ultrata', '2', '1418146620');
INSERT INTO `vote_counters` VALUES ('109', 'ultrata', '3', '1418146623');
INSERT INTO `vote_counters` VALUES ('110', 'metaruu', '1', '1418236078');
INSERT INTO `vote_counters` VALUES ('111', 'metaruu', '2', '1418236081');
INSERT INTO `vote_counters` VALUES ('112', 'metaruu', '3', '1418236085');
INSERT INTO `vote_counters` VALUES ('113', 'metaruarti', '1', '1417890111');
INSERT INTO `vote_counters` VALUES ('114', 'metaruarti', '2', '1417890113');
INSERT INTO `vote_counters` VALUES ('115', 'metaruarti', '3', '1417890116');
INSERT INTO `vote_counters` VALUES ('116', 'zoro2010', '1', '1417890222');
INSERT INTO `vote_counters` VALUES ('117', 'zoro2010', '2', '1417890229');
INSERT INTO `vote_counters` VALUES ('118', 'zoro2010', '3', '1417890233');
INSERT INTO `vote_counters` VALUES ('119', 'Mushroom123', '1', '1419792406');
INSERT INTO `vote_counters` VALUES ('120', 'Mushroom123', '3', '1419792413');
INSERT INTO `vote_counters` VALUES ('121', 'Mushroom123', '2', '1419792413');
INSERT INTO `vote_counters` VALUES ('122', 'mags074', '2', '1418825076');
INSERT INTO `vote_counters` VALUES ('123', 'mags074', '3', '1418825218');
INSERT INTO `vote_counters` VALUES ('124', 'mags074', '1', '1418824933');
INSERT INTO `vote_counters` VALUES ('125', 'Crixus', '1', '1417945157');
INSERT INTO `vote_counters` VALUES ('126', 'Crixus', '2', '1417945175');
INSERT INTO `vote_counters` VALUES ('127', 'spartacus', '1', '1417945236');
INSERT INTO `vote_counters` VALUES ('128', 'MatzeGer', '1', '1417986847');
INSERT INTO `vote_counters` VALUES ('129', 'MatzeGer', '2', '1417986894');
INSERT INTO `vote_counters` VALUES ('130', 'MatzeGer', '3', '1417986898');
INSERT INTO `vote_counters` VALUES ('131', 'dialtone', '3', '1419482632');
INSERT INTO `vote_counters` VALUES ('132', 'york', '1', '1419438271');
INSERT INTO `vote_counters` VALUES ('133', 'york', '2', '1419438276');
INSERT INTO `vote_counters` VALUES ('134', 'york', '3', '1419438279');
INSERT INTO `vote_counters` VALUES ('135', 'meydan', '1', '1418026840');
INSERT INTO `vote_counters` VALUES ('136', 'meydan', '2', '1418026856');
INSERT INTO `vote_counters` VALUES ('137', 'meydan', '3', '1418026861');
INSERT INTO `vote_counters` VALUES ('138', 'Fatmilk', '1', '1418985637');
INSERT INTO `vote_counters` VALUES ('139', 'Fatmilk', '2', '1418985772');
INSERT INTO `vote_counters` VALUES ('140', 'Fatmilk', '3', '1418985775');
INSERT INTO `vote_counters` VALUES ('141', 'ELmER', '1', '1418123908');
INSERT INTO `vote_counters` VALUES ('142', 'ELmER', '2', '1418123997');
INSERT INTO `vote_counters` VALUES ('143', 'ELmER', '3', '1418124080');
INSERT INTO `vote_counters` VALUES ('144', 'fewmilk', '1', '1418129027');
INSERT INTO `vote_counters` VALUES ('145', 'fewmilk', '2', '1418129039');
INSERT INTO `vote_counters` VALUES ('146', 'fewmilk', '3', '1418129042');
INSERT INTO `vote_counters` VALUES ('147', 'jockeeng', '1', '1418151676');
INSERT INTO `vote_counters` VALUES ('148', 'fattmilk', '1', '1418172720');
INSERT INTO `vote_counters` VALUES ('149', 'fattmilk', '2', '1418172724');
INSERT INTO `vote_counters` VALUES ('150', 'fattmilk', '3', '1418172726');
INSERT INTO `vote_counters` VALUES ('151', 'majroo', '1', '1418234227');
INSERT INTO `vote_counters` VALUES ('152', 'ronexdee', '1', '1418250150');
INSERT INTO `vote_counters` VALUES ('153', 'ronexdee', '2', '1418250262');
INSERT INTO `vote_counters` VALUES ('154', 'ronexdee', '3', '1418250302');
INSERT INTO `vote_counters` VALUES ('155', 'Innovate', '1', '1418309205');
INSERT INTO `vote_counters` VALUES ('156', 'Innovate', '2', '1418309352');
INSERT INTO `vote_counters` VALUES ('157', 'Innovate', '3', '1418309401');
INSERT INTO `vote_counters` VALUES ('158', 'xArchurious', '1', '1418601976');
INSERT INTO `vote_counters` VALUES ('159', 'xArchurious', '2', '1418601997');
INSERT INTO `vote_counters` VALUES ('160', 'xArchurious', '3', '1418602019');
INSERT INTO `vote_counters` VALUES ('161', 'kamakazeeworm', '1', '1419800279');
INSERT INTO `vote_counters` VALUES ('162', 'kamakazeeworm', '2', '1419800289');
INSERT INTO `vote_counters` VALUES ('163', 'kamakazeeworm', '3', '1419800310');
INSERT INTO `vote_counters` VALUES ('164', 'Lincoln', '1', '1418908210');
INSERT INTO `vote_counters` VALUES ('165', 'Lincoln', '2', '1418908227');
INSERT INTO `vote_counters` VALUES ('166', 'Lincoln', '3', '1418908264');
INSERT INTO `vote_counters` VALUES ('167', 'xilliah', '1', '1419793652');
INSERT INTO `vote_counters` VALUES ('168', 'xilliah', '3', '1419793659');
INSERT INTO `vote_counters` VALUES ('169', 'xilliah', '2', '1419793656');
INSERT INTO `vote_counters` VALUES ('170', 'Rurouni', '1', '1419346725');
INSERT INTO `vote_counters` VALUES ('171', 'Rurouni', '2', '1419346730');
INSERT INTO `vote_counters` VALUES ('172', 'Rurouni', '3', '1419346742');
INSERT INTO `vote_counters` VALUES ('173', 'Morph', '1', '1419346627');
INSERT INTO `vote_counters` VALUES ('174', 'Morph', '2', '1419346637');
INSERT INTO `vote_counters` VALUES ('175', 'Morph', '3', '1419346663');
INSERT INTO `vote_counters` VALUES ('176', 'mycleric', '1', '1419346771');
INSERT INTO `vote_counters` VALUES ('177', 'mycleric', '2', '1419346811');
INSERT INTO `vote_counters` VALUES ('178', 'mycleric', '3', '1419346838');
INSERT INTO `vote_counters` VALUES ('179', 'meme', '1', '1419759221');
INSERT INTO `vote_counters` VALUES ('180', 'meme', '2', '1419759252');
INSERT INTO `vote_counters` VALUES ('181', 'meme', '3', '1419759273');
INSERT INTO `vote_counters` VALUES ('182', 'dougaa', '1', '1419241876');
INSERT INTO `vote_counters` VALUES ('183', 'kuhn9012', '1', '1419304778');
INSERT INTO `vote_counters` VALUES ('184', 'kuhn9012', '2', '1419304844');
INSERT INTO `vote_counters` VALUES ('185', 'kuhn9012', '3', '1419304869');
INSERT INTO `vote_counters` VALUES ('186', 'mead054', '1', '1419305068');
INSERT INTO `vote_counters` VALUES ('187', 'mead054', '2', '1419305136');
INSERT INTO `vote_counters` VALUES ('188', 'mead054', '3', '1419305173');
INSERT INTO `vote_counters` VALUES ('189', 'aika', '1', '1419595891');
INSERT INTO `vote_counters` VALUES ('190', 'aika', '3', '1419595903');
INSERT INTO `vote_counters` VALUES ('191', 'aika', '2', '1419595900');
INSERT INTO `vote_counters` VALUES ('192', 'anmeliax', '3', '1419555123');
INSERT INTO `vote_counters` VALUES ('193', 'anmeliax', '1', '1419556419');
INSERT INTO `vote_counters` VALUES ('194', 'anmeliax', '2', '1419556453');
INSERT INTO `vote_counters` VALUES ('195', 'unknown', '1', '1419580627');
INSERT INTO `vote_counters` VALUES ('196', 'unknown', '2', '1419580708');
INSERT INTO `vote_counters` VALUES ('197', 'unknown', '3', '1419580715');
INSERT INTO `vote_counters` VALUES ('198', 'grymmm', '2', '1419750116');
INSERT INTO `vote_counters` VALUES ('199', 'grymmm', '3', '1419750121');
INSERT INTO `vote_counters` VALUES ('200', 'grymmm', '1', '1419750131');
INSERT INTO `vote_counters` VALUES ('201', 'ocramocijom', '1', '1419770303');
INSERT INTO `vote_counters` VALUES ('202', 'ocramocijom', '2', '1419770303');
INSERT INTO `vote_counters` VALUES ('203', 'ocramocijom', '3', '1419770305');
INSERT INTO `vote_counters` VALUES ('204', 'ayhd', '1', '1419793009');
INSERT INTO `vote_counters` VALUES ('205', 'ayhd', '2', '1419793021');
INSERT INTO `vote_counters` VALUES ('206', 'ayhd', '3', '1419793026');
INSERT INTO `vote_counters` VALUES ('207', 'M477', '1', '1419798908');
INSERT INTO `vote_counters` VALUES ('208', 'M477', '2', '1419799001');
INSERT INTO `vote_counters` VALUES ('209', 'M477', '3', '1419799028');
INSERT INTO `vote_counters` VALUES ('210', 'kira1104098', '1', '1419804518');
