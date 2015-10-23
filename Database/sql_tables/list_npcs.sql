/*
Navicat MySQL Data Transfer

Source Server         : RoseFate
Source Server Version : 50536
Source Host           : localhost:3306
Source Database       : fate

Target Server Type    : MYSQL
Target Server Version : 50536
File Encoding         : 65001

Date: 2014-06-19 08:55:52
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `list_npcs`
-- ----------------------------
DROP TABLE IF EXISTS `list_npcs`;
CREATE TABLE `list_npcs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `type` int(11) NOT NULL,
  `map` int(11) NOT NULL,
  `dir` float NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `dialogid` int(11) NOT NULL DEFAULT '0',
  `eventid` int(11) NOT NULL DEFAULT '0',
  `tempdialogid` int(11) NOT NULL DEFAULT '0',
  `extra_param` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=311 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of list_npcs
-- ----------------------------
INSERT INTO `list_npcs` VALUES ('1', '[Livestock Farmer] Lampa', '1016', '1', '173.934', '5109.42', '5363.68', '116', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('2', '[Village Chief] Cornell', '1001', '1', '12.55', '5096.51', '5256.04', '101', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('3', '[Junon Order Co-Founder] Francis', '1003', '1', '157.957', '5080.3', '5066.28', '103', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('4', '[Righteous Crusader] Leonard', '1005', '1', '266.005', '5127.04', '5208.73', '105', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('5', '[Resident] Luth', '1015', '1', '270.003', '5130.61', '5154.58', '115', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('6', '[Event Info] Judy', '1201', '1', '162.011', '5261.88', '5212.97', '305', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('7', '[Monster Coin Trader] Dahved', '1492', '1', '0', '5245.1', '5164.56', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('8', '[Eccentric Inventor] Spero', '1011', '1', '0', '5273.1', '5267.12', '111', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('9', '[Weapon Seller] Raffle', '1008', '1', '3.008', '5213.73', '5260.83', '108', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('10', '[Armor Seller] Carrion', '1009', '1', '34.535', '5198.3', '5253.83', '109', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('11', '[Guide] Lena', '1014', '1', '333.435', '5272.68', '5079.04', '114', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('12', '[Ferrell Guild Staff] Crow', '1004', '1', '180.5', '5210.44', '5104.79', '104', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('13', '[Akram Kingdom Minister] Warren', '1002', '1', '181.501', '5132.56', '5078.95', '102', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('14', '[Cornell\'s Grandson] Cheney', '1018', '1', '22.043', '5435.3', '5492.26', '118', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('15', '[Designer] Keenu', '1010', '1', '238.556', '5319.51', '5151.29', '110', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('16', '[Ferrell Guild Staff] Ulysses', '1012', '1', '333.435', '5291.1', '5264.22', '112', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('17', '[Gypsy Merchant] Mina', '1007', '1', '307.514', '5308.01', '5241.04', '107', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('18', '[Arumic Merchant] Tryteh', '1006', '1', '298.187', '5316.27', '5212.11', '106', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('19', '[Keenu\'s Daughter] Arisa', '1020', '1', '275.985', '5428.17', '5082.68', '120', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('20', '[Tavern Owner] Sharlin', '1013', '1', '191.421', '5300.45', '5112.64', '113', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('21', '[Lena\'s Sister] Shirley', '1019', '1', '322.406', '5504.69', '5274.08', '119', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('22', 'NO NAME FOUND (NPC)', '3040', '2', '0', '4829.88', '4645.83', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('23', 'NO NAME FOUND (NPC)', '3041', '2', '0', '4832.84', '4645.52', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('24', 'NO NAME FOUND (NPC)', '1791', '2', '0', '4838.05', '4644.56', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('25', 'NO NAME FOUND (NPC)', '1792', '2', '0', '4841.91', '4644.57', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('26', 'NO NAME FOUND (NPC)', '1793', '2', '0', '4845.6', '4644.59', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('27', 'NO NAME FOUND (NPC)', '1794', '2', '0', '4849.58', '4644.48', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('28', 'NO NAME FOUND (NPC)', '1795', '2', '0', '4853.38', '4644.49', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('29', 'NO NAME FOUND (NPC)', '3042', '2', '0', '4835.08', '4645.67', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('30', '[Righteous Crusader] Gawain', '1090', '2', '84.016', '5334.58', '5353.91', '190', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('31', '[Righteous Crusader] Huffe', '1111', '2', '90', '5334.84', '5345.81', '211', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('32', '[Clan Manager] Burtland', '1115', '2', '19.295', '5290.6', '5267.6', '215', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('33', '[Honor Items] Henry', '2001', '2', '134.288', '5290.83', '5235.59', '233', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('34', '[Honor Weapons] William', '2002', '2', '277.961', '5345.67', '5265.91', '234', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('35', '[Honor Armors] Theodor', '2003', '2', '254.3', '5345.55', '5230.2', '235', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('36', '[Battlemaster] Esmee', '1990', '2', '88.001', '5285.04', '5252.55', '750', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('37', '[Founder of Junon Order] Raw', '1088', '2', '181.501', '5319.27', '5095.36', '188', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('38', '[Junon Order Elder] Gorthein', '1109', '2', '181.501', '5325.54', '5095.31', '209', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('39', '[Valor Materials] Mason', '2011', '2', '179.5', '5342.26', '5113.85', '236', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('40', '[Valor Weapons] Jason', '2012', '2', '180', '5306.26', '5112.41', '237', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('41', '[Valor Armors] Carson', '2013', '2', '180', '5297.27', '5112.72', '238', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('42', '[Guide] Eva', '1082', '2', '153.435', '5505.78', '5346.09', '182', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('43', '[Soldier] Odelo', '1116', '2', '0', '5507.31', '5397.4', '216', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('44', '[Soldier] Winters', '1117', '2', '0', '5522.99', '5397.75', '217', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('45', '[Mayor] Darren', '1081', '2', '178.499', '5514.48', '5238.2', '181', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('46', '[Event Info] Felice Fete', '1202', '2', '206.565', '5562', '5164.83', '306', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('47', '[Monster Coin Trader] Vedad', '1493', '2', '335.763', '5559.95', '5254.14', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('48', '[Akram Ambassador] Adalric', '1108', '2', '155.002', '5463.48', '5168.3', '226', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('49', '[Interplanetary Guide] Alphonso', '1118', '2', '178.499', '5520.56', '5063.66', '218', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('50', '[Historian] Jones', '1104', '2', '162.011', '5578.19', '4890.44', '204', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('51', '[Vicious Captain] Ruven', '1125', '2', '270', '5597.76', '4918.87', '220', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('52', '[Manager of Ferrell] Arothel', '1089', '2', '270', '5713.43', '5360.16', '189', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('53', '[Armor Merchant] Saki', '1094', '2', '258.129', '5721.8', '5290.79', '194', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('54', '[Ferrell Guild Staff] Charrs', '1110', '2', '270', '5713.38', '5368.71', '210', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('55', '[Gypsy Merchant] Bellia', '1092', '2', '217.594', '5725.11', '5199.04', '192', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('56', '[Weapon Merchant] Crune', '1093', '2', '335.763', '5728.67', '5224.89', '193', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('57', '[Designer] Lisa', '1095', '2', '220.893', '5729.06', '5136.33', '195', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('58', '[Ferrell Guild Merchant] Mildun', '1096', '2', '165.707', '5673.16', '5193.89', '196', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('59', '[Tavern Owner] Harin', '1097', '2', '90', '5681.79', '5131.11', '197', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('60', '[Premium Shop] Lyon', '1080', '2', '177.998', '5651.5', '5184.78', '1080', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('61', '[Arumic Merchant] Chelsie', '1091', '2', '211.693', '5723.96', '5087.24', '191', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('62', '[Ferrell Guild Staff] Kiroth', '1098', '2', '275.984', '5603.58', '5058.1', '198', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('63', '[Ferrell Guild Staff] Hayen', '1099', '2', '258.129', '5603.77', '5046.12', '199', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('64', '[Ferrell Guild Staff] Itz', '1100', '2', '270', '5603.69', '5034.52', '200', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('65', '[Arumic Researcher] Carasia', '1112', '2', '197.989', '5730.57', '5094.06', '212', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('66', '[Captain] Peg Leg', '3020', '2', '160.035', '5670.86', '4910.2', '232', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('67', '[Livestock Farmer] Sicru', '1107', '2', '187.631', '5818.02', '5487.59', '207', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('68', '[Ferrell Guild Staff] Rooen', '1513', '3', '0', '5104.48', '5019.71', '303', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('69', '[Akram Minister] Rodath', '1086', '5', '90', '5155.07', '5279.92', '186', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('70', '[Akram Minister] Mel', '1087', '5', '270', '5247.07', '5279.96', '187', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('71', '[Akram Minister] Gamp', '1084', '6', '271.999', '5248.14', '5279.2', '185', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('72', '[Akram Minister] Nell', '1085', '11', '84.016', '4953.37', '4992.35', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('73', '[Akram Minister] Nell', '1085', '11', '10.865', '4978.48', '5478.6', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('74', '[Akram Minister] Nell', '1085', '11', '337.957', '5455.57', '5478.99', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('75', '[Akram Minister] Nell', '1085', '11', '335.763', '5521.94', '5020.66', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('76', '[Akram Minister] Nell', '1085', '12', '84.016', '4953.37', '4992.35', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('77', '[Akram Minister] Nell', '1085', '12', '10.865', '4978.48', '5478.6', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('78', '[Akram Minister] Nell', '1085', '12', '337.957', '5455.57', '5478.99', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('79', '[Akram Minister] Nell', '1085', '12', '335.763', '5521.94', '5020.66', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('80', '[Akram Minister] Nell', '1085', '13', '84.016', '4953.37', '4992.35', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('81', '[Akram Minister] Nell', '1085', '13', '10.865', '4978.48', '5478.6', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('82', '[Akram Minister] Nell', '1085', '13', '337.957', '5455.57', '5478.99', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('83', '[Akram Minister] Nell', '1085', '13', '335.763', '5521.94', '5020.66', '184', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('84', '[Arumic Researcher] Lutis', '1051', '21', '160.035', '5118.14', '5374.91', '151', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('85', '[Cleric] Karitte', '1053', '21', '95.984', '5112.44', '5385.08', '153', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('86', '[Stranded Resident] Morgan', '1132', '21', '0', '5354.81', '5014.18', '154', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('87', '[Fruit Seller] Magdalena', '1135', '21', '353.933', '5513.39', '5248.06', '157', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('88', '[Resident] Rudolfo', '1134', '21', '173.415', '5501.85', '5211.11', '156', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('89', '[Livestock Farmer] Enu', '1133', '21', '24.237', '5496.56', '5248', '155', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('90', '[Smith] Rockwell', '1138', '21', '105.7', '5441.02', '5191.52', '158', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('91', '[Weapon Merchant] Dune', '1139', '21', '165.112', '5458.63', '5181.31', '159', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('92', '[Mountain Guide] Shannon', '1052', '21', '0', '5472.73', '5070.27', '152', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('93', 'Melendino', '1473', '22', '212.618', '5095.21', '5312.66', '16', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('94', '[Muse Trainer] Media', '1057', '22', '173.933', '5099.13', '5405.39', '59', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('95', '[Hawker Trainer] Connor', '1058', '22', '328.307', '5110.77', '5432.79', '60', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('96', '[Dealer Trainer] Titania', '1059', '22', '0', '5094.77', '5437.11', '61', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('97', '[Soldier Trainer] Murphy', '1056', '22', '40.893', '5054.37', '5439.15', '58', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('98', '[Pumpkin Farmer] Claude', '1060', '22', '95.984', '5126.59', '5280.7', '62', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('99', '[Boy by the Cart]Huey', '1021', '22', '323.451', '5355.05', '5401.97', '50', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('100', '[Path Guard] Bert', '1065', '22', '19.965', '5457.67', '5387.48', '63', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('101', '[Smith] Ronk', '1034', '22', '176.992', '5653.93', '5152.59', '53', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('102', '[Little Street Vendor] Pony', '1035', '22', '145.465', '5637.8', '5157.9', '54', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('103', '[Village Chief] Gray', '1038', '22', '90', '5627.19', '5172.31', '57', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('104', '[Ferrell Guild Staff] Seyon', '1036', '22', '23.492', '5632.37', '5194.24', '55', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('105', '[Old Man] Myad', '1041', '22', '270', '5669.22', '5180.15', '56', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('106', '[Akram Minister] Mairard', '1032', '22', '337.957', '5662.79', '5196.41', '52', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('107', '[Visitor Guide] Arua\'s Fairy', '1030', '22', '123.017', '5699.97', '5119.75', '51', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('108', '[Ferrell Guild Staff] Peron', '1511', '22', '352.369', '5828.29', '5205.66', '64', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('109', '[Novice Designer] Cassirin', '1040', '22', '340.035', '5896.42', '5148.75', '140', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('110', '[Breezy Hills Militia] Mercucio', '1067', '23', '311.684', '5080.09', '5194.14', '165', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('111', '[Ferrell Guild Staff] Belz', '1061', '23', '270', '5358.63', '5058.99', '161', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('112', '[Smith] Punwell', '1062', '23', '24.237', '5340.65', '5070.26', '162', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('113', '[Little Street Vendor] Mile', '1063', '23', '307.514', '5356.41', '5043.28', '163', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('114', '[Weapon Craftsman] Mairath', '1064', '23', '180', '5349.02', '5033.95', '164', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('115', '[Breezy Hills Militia] Rahl', '1070', '23', '24.237', '5469.98', '5507.27', '166', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('116', '[El Verloon Tour Guide] Franklin', '1140', '24', '159.355', '5024.51', '5092.78', '168', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('117', '[Tourist] Linda', '1145', '24', '0', '5120.16', '5500.81', '169', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('118', '[El Verloon Tourism Board] Caraan', '1074', '24', '0', '5383.02', '4918.3', '167', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('119', '[Tourist] Rick', '1146', '24', '200.645', '5531.21', '5370.05', '170', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('120', '[Archaeologist] Williams', '1075', '24', '0', '5473.2', '5137.21', '174', '0', '0', '2');
INSERT INTO `list_npcs` VALUES ('121', '[Ferrell Guild Merchant] Lina', '1071', '24', '293.031', '5567.26', '4927.03', '171', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('122', '[Gypsy Merchant] Methio', '1072', '24', '192.55', '5563.13', '4895.45', '172', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('123', '[Ikaness Staff] Orias', '1073', '24', '95.984', '5515.26', '4925.14', '173', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('124', '[Mountain Guide] Stephano', '1147', '25', '303.017', '5037.56', '5466.84', '175', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('125', '[Frightened Guard] Canterbury', '1148', '25', '193.124', '5087.44', '5249.22', '176', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('126', '[Ikaness Staff] Shroon', '1121', '25', '9.228', '5375.78', '5188.33', '221', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('127', '[Mountain Guide] Pein', '1122', '25', '307.514', '5503.22', '5350.93', '222', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('128', '[Gypsy Merchant] Edone', '1123', '25', '187.631', '5448.14', '4976.37', '223', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('129', '[Mountain Guide] Kay', '1131', '26', '22.043', '5669.16', '5105.24', '231', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('130', '[Ferrell Guild Merchant ] Bith', '1143', '27', '197.989', '5259.72', '5147.64', '243', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('131', '[Ferrell Guild Staff] Robin', '1512', '27', '264.016', '5239.23', '5040.74', '302', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('132', '[Resident] Hotch', '1144', '27', '189.228', '5384.23', '5180.1', '244', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('133', '[Righteous Crusader] Gallahad', '1141', '27', '178.499', '5345.2', '5047.71', '241', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('134', '[Akram Minister] Luce', '1142', '27', '101.871', '5320.52', '5081.27', '242', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('135', '[Gypsy Merchant] Tobar', '1130', '28', '118.187', '5587.22', '4732.54', '250', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('136', '[Shop Waitress] Betty', '1127', '28', '272', '5688.74', '4802.46', '247', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('137', '[Storage Keeper] Marcus', '1128', '28', '34.535', '5625.19', '4853.54', '248', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('138', '[Ferrell Guild Merchant] Med', '1151', '28', '345.707', '5686.58', '4902.11', '251', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('139', '[Blacksmith] Brock', '1129', '28', '182.002', '5667.78', '4701.27', '249', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('140', '[Dead Priest] Lantore', '1154', '29', '241.813', '5114.61', '5131.16', '254', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('141', '[Town Girl] Lithia', '1156', '29', '24.237', '5091.98', '5181.81', '256', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('142', '[Ghost] Harry', '1157', '29', '109.425', '5050.08', '5123.27', '257', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('143', '[Ranger] Paul', '1155', '29', '330.956', '5157.1', '5176.39', '255', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('144', '[Beach Resident] Judith', '1204', '36', '358.499', '5115.68', '5324.15', '308', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('145', '[Beach Resident] Judith', '1216', '37', '358.499', '5115.68', '5324.15', '308', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('146', '[Pick-A-Card] Alejandro', '1045', '37', '347.45', '5220.72', '5357.38', '92', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('147', '[Clown Throw] Mildred', '1044', '37', '0', '5246.65', '5366.65', '91', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('148', '[Junon RPS] Sherisse', '1043', '37', '0', '5259.34', '5367.26', '90', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('149', '[Digging for Treasure] Augustus', '1048', '37', '293.031', '5227.87', '5324.44', '95', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('150', '[Festival Manager] Lero', '1050', '37', '31.693', '5182.5', '5340.08', '97', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('151', '[Beach Resident] Casey Jean', '1210', '37', '16.102', '5256.56', '5304.59', '326', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('152', '[Scavenger Hunt] Pirelli', '1049', '37', '198.637', '5334.27', '5289.01', '96', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('153', '[Chicken Races] Hig', '1047', '37', '347.45', '5297.48', '5362.05', '94', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('154', '[Pie Crush] Tony', '1046', '37', '343.898', '5325.37', '5365.62', '93', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('155', '[Old Fisherman] Sal', '1066', '37', '197.351', '5298.5', '5045.7', '65', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('156', '[Event Info] Santa Claus', '1205', '38', '3.012', '5069.18', '5362.51', '309', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('157', '[Event Info] Loelsch', '1206', '38', '66.941', '5057.19', '5351.61', '310', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('158', '[Evil Reindeer] Bob', '1490', '38', '97.961', '5065.61', '5206.88', '318', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('159', '[Event Info] Lilly', '1164', '39', '30.79', '5054.89', '5347.89', '77', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('160', '[Festival Manager] Lero', '1055', '39', '0', '5072.25', '5363.08', '97', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('161', '[Cherry Berry Pie Crush] Anya', '1175', '39', '315.541', '5061.64', '5094.96', '76', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('162', '[Cherry Berry Pie Crush] Anya', '1177', '39', '14.293', '5133.83', '5360.16', '73', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('163', '[Snowmobile Races] Chilly', '1169', '39', '155.763', '5232.15', '5168.86', '82', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('164', '[Lunaris Bear Throw] Mighail', '1165', '39', '12.55', '5220.76', '5196.75', '78', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('165', '[Penguin Races] Penny', '1166', '39', '254.3', '5276.52', '5276.63', '79', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('166', '[Ice Fishing] Val', '1174', '39', '144.47', '5208.38', '5258.55', '75', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('167', '[Lunaris RPS] Evanna', '1168', '39', '340.035', '5298.56', '5206.56', '81', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('168', '[Snowplowing for Treasure] Magnus', '1167', '39', '243.497', '5303.99', '5171.08', '80', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('169', '[Cherry Berry Pie Crush] Anya', '1176', '39', '254.3', '5381.49', '5260.66', '72', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('170', '[Snow Valley Biathlon] Viktoria', '1170', '39', '243.497', '5393.62', '5044.77', '83', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('171', '[Cherry Berry Pie Crush] Anya', '1178', '39', '197.989', '5305.58', '5095.4', '74', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('172', '[Event Info] Lucille Fete', '1203', '40', '333.435', '5254.64', '5216.39', '307', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('173', '[Arua\'s Servant] Serenity', '1078', '41', '19.965', '5014.03', '5298.4', '266', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('174', '[Oblivion Temple] Room 1', '1771', '41', '0', '4969.53', '5427.82', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('175', '[Oblivion Temple] Room 2', '1772', '41', '0', '4973.5', '5427.39', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('176', '[Oblivion Temple] Room 3', '1773', '41', '0', '4977.33', '5427.88', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('177', '[Oblivion Temple] Room 4', '1774', '41', '0', '4981.46', '5427.93', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('178', '[Oblivion Temple] Room 5', '1775', '41', '0', '4969.81', '5422.09', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('179', '[Oblivion Temple] Room 6', '1776', '41', '0', '4974.24', '5421.48', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('180', '[Oblivion Temple] Room 7', '1777', '41', '0', '4978.03', '5421.83', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('181', '[Oblivion Temple] Room 8', '1778', '41', '0', '4981.5', '5421.61', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('182', '[Oblivion Temple] Room 9', '1779', '41', '0', '4969.99', '5416.66', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('183', '[Oblivion Temple] Room 10', '1780', '41', '0', '4974.77', '5415.91', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('184', '[Oblivion Temple] Room 11', '1781', '41', '0', '4978.62', '5416.18', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('185', '[Oblivion Temple] Room 12', '1782', '41', '0', '4981.52', '5416.73', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('186', '[Oblivion Temple] Room 13', '1783', '41', '0', '4970.05', '5412.56', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('187', '[Oblivion Temple] Room 14', '1784', '41', '0', '4974.47', '5412.82', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('188', '[Oblivion Temple] Room 15', '1785', '41', '0', '4978.37', '5412.36', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('189', '[Oblivion Temple] Room 16', '1786', '41', '0', '4981.47', '5412.39', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('190', '[Orlean Ambassador] Bond', '1077', '41', '180.5', '5071.9', '5258.5', '265', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('191', '[Hebarn\'s Vassal] Starburner', '1079', '41', '148.307', '5010.3', '5194.24', '267', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('192', '[Archaeologist] Jorgus', '1076', '41', '0', '5104.47', '5201.29', '264', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('193', '[Interplanetary Guide] Illiya', '1188', '51', '148.307', '5107.24', '4996.57', '288', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('194', '[Tavern Owner] Anzhelika', '1186', '51', '139.107', '5263.61', '5079.49', '286', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('195', '[Ferrell Guild Banker] Andre', '1180', '51', '0', '5414.86', '5114.41', '280', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('196', '[Arumic Merchant] Pabel', '1185', '51', '3.008', '5298.98', '5105.03', '285', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('197', '[Arumic Prophet] Olleck Basilasi', '1173', '51', '178.499', '5359.62', '5085.72', '273', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('198', '[Monster Coin Trader] Dedev', '1494', '51', '22.043', '5350.81', '5000.7', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('199', '[Battlemaster] Sappho', '1993', '51', '182.002', '5429.85', '5057.87', '750', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('200', '[Akram Ambassador] Eliot', '1172', '51', '157.957', '5285.69', '4940.95', '272', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('201', '[Eucar Judge] Ishtal', '1171', '51', '206.565', '5430.09', '4937.96', '271', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('202', '[Smith] Pavrick', '1181', '51', '335.763', '5440.45', '5103.41', '281', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('203', '[Ferrell Guild Staff] Sergei', '1184', '51', '258.129', '5450.88', '5077.06', '284', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('204', '[Gentleman Explorer] Toffee Coffington', '1182', '51', '212.618', '5655.85', '5210.83', '282', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('205', '[Gentleman Explorer] Nicholai Coffington', '1187', '52', '338.662', '6145.36', '5238.13', '287', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('206', '[Gentleman Explorer] Wilhelm Coffington', '1183', '53', '0', '6004.57', '5368.4', '283', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('207', '[Shamanist] Est', '1191', '54', '84.016', '5088.26', '4257.84', '291', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('208', '[Livestock Farmer] Kapeka', '1194', '55', '61.813', '5271.06', '4623.53', '294', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('209', '[Interplanetary Guide] Chacha', '1219', '61', '12.55', '5226.6', '4452.72', '319', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('210', '[Raknu Warrior] Toanu', '1229', '61', '180', '5434.62', '4671.5', '329', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('211', '[Raknu Warrior] Guanu', '1230', '61', '181.501', '5424.42', '4671.62', '330', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('212', '[Junon Order Elder] Oscar Patrick', '1214', '61', '157.957', '5371.18', '4546.51', '314', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('213', '[Righteous Crusader] Harold Evan', '1211', '61', '14.293', '5369.75', '4575.29', '311', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('214', '[Smith] Nel Eldora', '1223', '61', '14.293', '5395.55', '4614.05', '323', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('215', '[Akram Ambassador] Jacklyn Cooper', '1215', '61', '180', '5430', '4483.79', '315', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('216', '[Patrol Dog] Stephen', '1244', '61', '180', '5427.52', '4482.43', '317', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('217', '[Raknu Warrior] Jeffrey Lloyd', '1221', '61', '180', '5434.01', '4595.87', '321', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('218', '[Monster Coin Trader] Dyv\'d', '1495', '61', '39.765', '5382.18', '4611.8', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('219', '[Arumic Researcher] Catherine Clara', '1212', '61', '330.956', '5473.37', '4618.79', '312', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('220', '[Ferrell Guild Staff] Gilbert', '1213', '61', '217.594', '5474.35', '4513.74', '313', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('221', '[Storage Keeper] Dustin Leta', '1222', '61', '197.989', '5489.63', '4553.05', '322', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('222', '[Patrol Dog] Max', '1243', '61', '199.965', '5487.27', '4550.96', '316', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('223', '[Raknu Resident] Netty', '1237', '61', '328.307', '5494.83', '4593.46', '337', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('224', '[Battlemaster] Rubee', '1991', '61', '345.707', '5610.94', '4480.01', '750', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('225', '[Chef] Peppie', '1224', '61', '190.865', '5626.88', '4435.97', '324', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('226', '[Raknu Chief] Darka Khan', '1220', '61', '352.369', '5650.09', '4464.73', '320', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('227', '[Raknu Resident] Jerrita', '1236', '61', '303.017', '5657.17', '4455.98', '336', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('228', 'NO NAME FOUND (NPC)', '1271', '61', '12.55', '5630.54', '4429.22', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('229', '[Sikuku Warrior] Kilie', '1257', '62', '333.435', '5647.96', '5126.88', '356', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('230', '[Sikuku Resident] Martie', '1258', '62', '16.102', '5638.21', '5127.42', '357', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('231', '[Sikuku Resident] Carl', '1259', '62', '95.984', '5714.45', '5121.83', '358', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('232', '[Sikuku Resident] Parah', '1260', '62', '192.55', '5721.78', '5118.28', '359', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('233', '[Sikuku Chief] Namiel Char', '1252', '62', '220.893', '5896.76', '5129.8', '352', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('234', '[Cleric] Jude', '1251', '62', '330.956', '5851.77', '5209.4', '351', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('235', '[Bird] Hawker', '1253', '62', '220.893', '5901.42', '5130.73', '364', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('236', '[Sikuku Warrior] Seka', '1256', '62', '181.501', '5817.34', '5174', '355', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('237', '[Sikuku Resident] Shilma', '1261', '62', '330.956', '5854.29', '5225.03', '360', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('238', '[Sikuku Warrior] Wounded Soldier', '1262', '62', '206.565', '5864.97', '5211.14', '361', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('239', '[Sikuku Warrior] Wounded Soldier', '1263', '62', '350.772', '5862.55', '5218.48', '361', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('240', '[Critically Wounded] Nukie', '1266', '62', '202.043', '5858.96', '5208.03', '363', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('241', '[Sikuku Warrior] Yak', '1255', '62', '24.237', '5789.36', '5051.35', '354', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('242', '[Sikuku Warrior] Ruduck', '1254', '62', '22.043', '5779.49', '5040.41', '353', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('243', '[Smith] Kojo', '1247', '66', '352.369', '5545.17', '5190.61', '408', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('244', '[Arumic Researcher] Redford', '1265', '66', '44.459', '5587.14', '4807.23', '407', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('245', '[Cleric] Maria', '1248', '66', '135.541', '5668.65', '4861.56', '412', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('246', '[Mountain Guide] Bennett ', '1250', '66', '248.756', '5687.64', '4862.35', '413', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('247', '[Sikuku Tracker] Akuku', '1245', '66', '317.949', '5681.93', '4879.12', '410', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('248', 'NO NAME FOUND (NPC)', '1026', '66', '0', '5713.31', '4233.27', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('249', 'NO NAME FOUND (NPC)', '1027', '66', '0', '5713.16', '3918.96', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('250', '[Ruins Curator] Hope', '1249', '66', '180', '5900.05', '4341.24', '409', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('251', 'NO NAME FOUND (NPC)', '1024', '66', '0', '5868.43', '4225.89', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('252', 'NO NAME FOUND (NPC)', '1025', '66', '0', '5867.85', '3940.73', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('253', '[Ministry of Agriculture] Aquila', '2150', '71', '52.485', '5042.32', '5304.58', '431', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('254', '[Pharaoh Queen] Alana', '2121', '71', '0', '5199.98', '5399.09', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('255', '[Royal Vizier] Kaltet XIV', '2139', '71', '34.535', '5168.18', '5371.16', '433', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('256', '[Royal Vizier] Satet XIV', '2140', '71', '325.465', '5225.4', '5371.71', '445', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('257', '[Orlean Ambassador] Solara', '2141', '71', '60.166', '5170.97', '5309.67', '427', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('258', '[Manager of Ferrell] Ishmat', '2126', '71', '0', '5231.05', '5285.76', '417', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('259', '[Weapon Merchant] Huzam', '2122', '71', '0', '5129.25', '5289.15', '429', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('260', '[Armor Merchant] Azim', '2124', '71', '0', '5156.39', '5289.25', '428', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('261', '[Mechanic] Kreinto', '2128', '71', '150.956', '5272.06', '5290.73', '424', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('262', '[Mechanic\'s Dog] Chopper', '2151', '71', '351.841', '5273.3', '5272.75', '425', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('263', '[Hebarn\'s Vassal] Tama', '2157', '71', '226.997', '5218.91', '5310.57', '484', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('264', '[Hebarn\'s Vassal] Nysaa', '2158', '71', '320.235', '5213.26', '5349.05', '485', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('265', '[Hebarn\'s Vassal] Rexanne', '2159', '71', '31.693', '5210.63', '5349.96', '486', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('266', '[Hebarn\'s Vassal] Nonus', '2160', '71', '29.044', '5215.06', '5347.3', '487', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('267', '[Hebarn\'s Vassal] Onur', '2162', '71', '166.295', '5210.94', '5346.89', '489', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('268', '[Arua\'s Servant] Meryem', '2166', '71', '148.307', '5186.99', '5347.98', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('269', '[Arua\'s Servant] Miho', '2168', '71', '195.491', '5191.03', '5347.32', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('270', '[Arua\'s Servant] Goran', '2169', '71', '346.295', '5189.61', '5351.27', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('271', '[Arua\'s Servant] Lugus', '2170', '71', '133.003', '5200.29', '5317.75', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('272', '[Arua\'s Servant] Ohad', '2171', '71', '200.645', '5186.24', '5350.61', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('273', '[Hebarn\'s Vassal] Uros', '2161', '71', '0', '5201.08', '5302.63', '488', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('274', '[Arua\'s Servant] Henda', '2167', '71', '17.989', '5190.57', '5327', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('275', '[Invention] CG-3', '2120', '71', '344.509', '5279.4', '5284.65', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('276', '[Junon Order Elder] Hameed', '2133', '71', '90', '5186.94', '5155.04', '442', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('277', '[Ferrell Guild Staff] Kareem', '2136', '71', '88', '5181.34', '5132.4', '439', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('278', '[Event Guide] Jalilla', '2137', '71', '194.293', '5190.86', '5259.98', '432', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('279', '[Lojala Blackbear Leader] Tondro', '2138', '71', '293.031', '5270.76', '5187.31', '420', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('280', '[Smith] Mahyr', '2127', '71', '275.984', '5268.82', '5142.06', '438', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('281', '[Oro Bar Owner] Sahrazod', '2125', '71', '76.203', '5235.65', '5162.88', '434', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('282', '[Monster Coin Trader] Daih\'vyd', '1496', '71', '0', '5209', '5209.9', '0', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('283', '[Valor Quest Giver] Roen', '1497', '71', '342.011', '5215.88', '5139.86', '447', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('284', '[Battlemaster] Amber', '1992', '71', '93.995', '5127.36', '5192.5', '750', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('285', '[Ikaness Staff] Galiya', '2130', '71', '264.016', '5278.29', '5109.64', '416', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('286', '[Righteous Crusader] Rahnan', '2135', '71', '131.684', '5181.24', '5104.91', '437', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('287', '[Arumic Researcher] Fahimah', '2134', '71', '82.038', '5183.66', '5086.18', '443', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('288', '[Gypsy Merchant] Nadeem', '2131', '71', '1.501', '5229.51', '5078.33', '441', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('289', '[Livestock Farmer] Hafis', '2132', '71', '330.956', '5150.91', '5042.62', '415', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('290', '[Orlean Ambassador] Lynd', '2142', '71', '0', '5166.8', '5069.03', '426', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('291', '[Gunsmith] Rahd', '2123', '71', '252.423', '5203.26', '5051.36', '436', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('292', '[Stargazer] Nubo', '2129', '71', '351.841', '5299.85', '5434.61', '418', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('293', '[Interplanetary Guide] Nova', '2101', '73', '0', '5241.3', '5225.49', '453', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('294', '[Wandering Rifter] Nimbo', '2102', '73', '0', '5328.58', '5233.29', '454', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('295', '[Dread Captain] Bruise', '2103', '74', '22.043', '5090.25', '5293.49', '455', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('296', '[First Mate] Bighand Jack', '2104', '74', '0', '5164.95', '5256.5', '456', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('297', '[Astrophysicist] Dr. Ega', '2106', '74', '266.005', '5199.97', '5232.9', '458', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('298', '[Deckhand] Skully', '2105', '74', '335.763', '5215.69', '5239.55', '457', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('299', '[Lojala Blackbear Captain] Skualo', '2111', '80', '162.011', '5000.09', '5142.27', '469', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('300', '[Lojala Trader] Brizo', '2112', '80', '44.459', '5059.07', '5160.72', '470', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('301', '[Lojala Storage Keeper] Ventego', '2113', '80', '6.067', '4985.28', '5205.54', '471', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('302', '[Teleporter] Idiosel', '1119', '80', '207.374', '5025.32', '5153.08', '219', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('303', '[Lojala Smith] Ekblovo', '2114', '80', '52.486', '5040.65', '5211.01', '472', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('304', '[Fidelulo Blackbear Leader] Fulmo', '2115', '81', '214.535', '5552.8', '5016.1', '474', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('305', 'Hebarn Saboteur', '2188', '82', '29.044', '5029.99', '5282.74', '482', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('306', 'Arua Interrogator', '2189', '82', '37.594', '5032.01', '5287.5', '482', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('307', 'Hebarn Saboteur', '2153', '82', '0', '5195.37', '5392.48', '475', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('308', 'Arua Interrogator', '2154', '82', '0', '5198.64', '5392.5', '475', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('309', 'Arua Interrogator', '2193', '82', '72.423', '5298.15', '5151.66', '483', '0', '0', '0');
INSERT INTO `list_npcs` VALUES ('310', 'Hebarn Saboteur', '2192', '82', '44.459', '5299.03', '5154.51', '483', '0', '0', '0');
