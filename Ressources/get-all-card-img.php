<?php

$jsonString = file_get_contents("./AllSets.json");
$jsonTab = json_decode($jsonString, true);

$baseUrl = 'http://wow.zamimg.com/images/hearthstone/cards/enus/original/#CardID#.png';
$baseImg = './Cards/#CardID#.png';

$i = 0;

foreach ($jsonTab as $key => $set) {
	foreach ($set as $card) {
		if ($card["collectible"] == false) {
			//continue;
		}
		$url = str_replace("#CardID#", $card["id"], $baseUrl);	
		$img = str_replace("#CardID#", $card["name"], $baseImg);

		$content = file_get_contents($url);
		if ($content != false) {
			file_put_contents($img, $content);
			$i++;
		}
	}
}

echo "Retrieved Cards : " . $i . PHP_EOL;