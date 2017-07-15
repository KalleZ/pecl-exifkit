--TEST--
Byte order Test 1
--SKIPIF--
<?php
	if (!extension_loaded('exifkit')) {
		print('skip: exifkit extension not available');
	}
?>
--FILE--
<?php
$exif = exifkit_read_data(__DIR__ . '/test-1.jpg');

var_dump(defined('EXIFKIT_BYTEORDER_MOTOROLA'), EXIFKIT_BYTEORDER_MOTOROLA);
var_dump(defined('EXIFKIT_BYTEORDER_INTEL'), EXIFKIT_BYTEORDER_INTEL);

var_dump($exif['COMPUTED']['ByteOrder'] === EXIFKIT_BYTEORDER_MOTOROLA);
?>
--EXPECT--
bool(true)
int(0)
bool(true)
int(1)
bool(true)

