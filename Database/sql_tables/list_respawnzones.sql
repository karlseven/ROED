/*
MySQL Data Transfer
Source Host: localhost
Source Database: osrose
Target Host: localhost
Target Database: osrose
Date: 7/18/2008 11:53:56 AM
*/
SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for list_respawnzones
-- ----------------------------
CREATE TABLE `list_respawnzones` (
`id` int(11) NOT NULL auto_increment,
`map` int(11) NOT NULL,
`x` float NOT NULL,
`y` float NOT NULL,
`radius` float NOT NULL default '10',
`type` int(11) NOT NULL default '2',
PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=286 DEFAULT CHARSET=latin1;
-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `list_respawnzones` VALUES (2, 1, 5240.72, 5189.85, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 1, 5210.47, 5136.67, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 1, 5277.17, 5499.94, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 1, 5275.68, 5427.39, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 2, 5655.32, 5238.22, 10, 1);
INSERT INTO `list_respawnzones` VALUES (4, 2, 5654.79, 5216.30, 10, 0);
INSERT INTO `list_respawnzones` VALUES (9, 2, 5334.14, 5177.97, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 2, 5517.67, 5448.76, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 3, 5177.97, 5008.88, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 3, 5184.00, 4999.62, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 4, 5084.54, 5021.58, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 4, 5096.12, 5021.34, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 5, 5155.11, 5105.19, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 5, 5201.83, 5498.40, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 5, 5200.79, 5059.89, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 6, 5155.11, 5105.19, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 6, 5201.83, 5498.40, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 6, 5200.79, 5059.89, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 7, 5742.59, 5095.05, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 7, 5742.29, 5094.52, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 8, 5525.87, 4546.56, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 8, 5520.16, 4558.11, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 11, 5512.24, 5027.03, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 11, 5016.03, 5360.19, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 11, 5380.43, 5427.36, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 11, 5428.77, 4982.24, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 11, 5000.67, 5045.25, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 12, 5512.24, 5027.03, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 12, 5016.03, 5360.19, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 12, 5380.43, 5427.36, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 12, 5428.77, 4982.24, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 12, 5000.67, 5045.25, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 13, 5512.24, 5027.03, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 13, 5016.03, 5360.19, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 13, 5380.43, 5427.36, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 13, 5428.77, 4982.24, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 13, 5000.67, 5045.25, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 19, 5196.10, 5182.86, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 19, 5212.27, 5184.06, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5397.82, 5510.88, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5140.36, 5492.47, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5131.70, 5385.95, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5346.65, 5006.12, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5509.02, 5224.88, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5254.93, 5058.17, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5175.88, 5070.37, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5513.37, 5228.58, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 21, 5310.11, 5510.94, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5151.15, 5285.68, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5483.22, 5380.17, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5344.34, 5393.28, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5642.27, 5172.71, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5742.59, 5095.05, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5068.36, 5423.69, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5514.31, 5154.20, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5303.76, 5106.87, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5742.29, 5094.52, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 22, 5530.07, 5216.46, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 23, 5036.32, 5085.89, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 23, 5348.23, 5061.66, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 23, 5345.55, 5056.65, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 23, 5480.84, 5502.46, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 24, 5527.76, 5246.70, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 24, 5525.30, 5376.16, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 24, 5027.82, 5099.68, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 24, 5526.01, 4944.91, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 25, 5379.49, 5184.52, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 25, 5515.46, 4899.35, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 25, 5490.36, 5359.51, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 25, 5265.90, 5555.69, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 25, 5179.41, 5086.81, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5283.77, 5161.85, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5063.09, 5494.25, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5251.59, 5554.70, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5443.63, 5293.25, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5685.06, 5104.05, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5291.23, 4893.05, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 26, 5053.08, 5034.35, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 27, 5179.07, 5411.13, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 27, 5221.27, 5328.82, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 27, 5623.88, 5187.46, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 27, 5582.24, 5460.38, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 28, 5196.53, 4906.26, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 28, 5527.71, 4812.22, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 28, 5148.43, 5225.29, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 28, 5541.16, 4816.40, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 28, 5570.47, 5174.68, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 29, 5091.54, 5150.00, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 29, 5091.16, 5141.70, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 31, 5520.00, 5455.00, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 31, 5429.84, 5509.55, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 32, 5517.44, 5409.57, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 32, 5253.55, 5416.94, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 33, 5606.58, 5464.56, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 33, 5695.31, 5269.66, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 36, 5098.63, 5233.40, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 36, 5110.04, 5233.01, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 37, 5098.63, 5233.40, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 37, 5110.04, 5233.01, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 38, 5072.83, 5346.01, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 38, 5060.95, 5337.62, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 39, 5070.40, 5353.36, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 39, 5063.80, 5343.57, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 40, 5180.85, 5210.49, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 40, 5189.88, 5211.03, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 41, 5062.03, 5201.67, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 41, 5232.10, 5292.51, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 41, 5113.63, 5246.86, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 42, 5311.87, 5150.83, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 42, 5319.54, 5150.52, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 43, 5097.29, 4970.94, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 43, 5098.07, 4978.57, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 43, 5534.98, 5295.78, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 43, 5544.38, 5294.84, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 43, 5055.35, 5159.86, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 44, 5356.59, 5043.46, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 44, 5361.43, 5034.55, 10, 0);
INSERT INTO `list_respawnzones` VALUES (5, 51, 5357.30, 5013.29, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 51, 5357.50, 5011.43, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 52, 6145.64, 5209.21, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 52, 6151.22, 5202.69, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5061.76, 5189.57, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5048.39, 5201.65, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5020.12, 4895.99, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5450.92, 5135.12, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5652.50, 5153.74, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5903.98, 5369.47, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 6163.34, 5358.23, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 6230.90, 4870.53, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 53, 5742.79, 4813.95, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 54, 5060.94, 4432.00, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 54, 5052.83, 4423.34, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 55, 5528.68, 4467.55, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 55, 5523.38, 4458.08, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 56, 5034.71, 4268.82, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 56, 5034.62, 4264.80, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 57, 5538.55, 5174.80, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 57, 5532.65, 5174.79, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 58, 5682.25, 4269.11, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 58, 5682.16, 4258.94, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 59, 5092.00, 5140.01, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 59, 5092.49, 5125.68, 10, 0);
INSERT INTO `list_respawnzones` VALUES (68, 61, 5435.24, 4569.69, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 61, 5429.73, 4573.14, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 62, 5837.58, 5173.35, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 62, 5850.91, 5166.71, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 63, 6079.18, 5197.36, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 63, 6089.52, 5193.01, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 64, 5038.56, 5311.87, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 64, 5049.29, 5317.46, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 65, 5510.47, 5390.22, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 66, 5997.55, 5255.15, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 66, 6005.04, 5244.78, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 71, 5199.99, 5236.79, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 72, 5124.31, 5308.19, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 72, 5116.80, 5308.77, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 73, 5243.53, 5201.21, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 73, 5243.97, 5208.54, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 74, 5168.69, 5249.56, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 74, 5170.47, 5245.72, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 75, 5275.96, 5324.33, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 75, 5283.02, 5330.68, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 76, 5468.91, 4976.84, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 76, 5465.06, 4969.49, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 77, 5073.31, 5244.58, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 77, 5073.25, 5245.41, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 78, 5609.27, 5158.66, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 78, 5614.16, 5154.37, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 78, 5191.06, 5047.64, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 79, 5350.17, 5202.84, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 79, 5356.38, 5205.71, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 79, 5029.43, 5160.54, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 80, 5009.05, 5408.81, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 80, 5251.39, 5152.01, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 80, 5246.55, 5408.78, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 80, 5062.92, 5192.62, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 81, 4946.63, 5298.20, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 82, 5098.72, 5345.22, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 130, 5190.00, 5140.00, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 130, 5210.00, 5140.00, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 131, 5197.28, 5184.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 131, 5201.24, 5184.08, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 132, 5197.28, 5184.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 132, 5201.24, 5184.08, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 133, 5197.28, 5184.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 133, 5201.24, 5184.08, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 134, 5197.28, 5184.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 134, 5201.24, 5184.08, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 135, 5197.28, 5184.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 135, 5201.24, 5184.08, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 138, 5084.42, 5040.36, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 138, 5083.76, 5040.37, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 139, 5084.42, 5040.36, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 139, 5083.76, 5040.37, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 143, 5020.03, 5250.60, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 143, 5019.90, 5250.60, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 144, 5020.03, 5250.60, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 144, 5019.90, 5250.60, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 148, 5200.17, 4772.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 148, 5200.17, 4772.39, 10, 0);
INSERT INTO `list_respawnzones` VALUES (0, 149, 5200.17, 4772.39, 10, 1);
INSERT INTO `list_respawnzones` VALUES (0, 149, 5200.17, 4772.39, 10, 0);
