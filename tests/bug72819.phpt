--TEST--
Bug #72819 (EXIF thumbnails not read anymore)
--SKIPIF--
<?php
	if (!extension_loaded('exifkit')) {
		print('skip: exifkit extension not available');
	}
?>
--FILE--
<?php
var_dump(strlen(exifkit_thumbnail(__DIR__ . '/bug72819.jpg')));
?>
===DONE===
--EXPECT--
int(5448)
===DONE===
