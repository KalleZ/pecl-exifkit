--TEST--
exifkit_read_data() Test 1
--SKIPIF--
<?php
	if (!extension_loaded('exifkit')) {
		print('skip: exifkit extension not available');
	}
?>
--FILE--
<?php
var_dump(exifkit_read_data(__DIR__ . '/test-1.jpg'));
?>
--EXPECT--
array(4) {
  ["IFD0"]=>
  array(4) {
    ["Copyright"]=>
    string(66) "Photo (c) M.Boerger (Photographer) - Edited by M.Boerger. (Editor)"
    ["XResolution"]=>
    string(2) "72"
    ["YResolution"]=>
    string(2) "72"
    ["ResolutionUnit"]=>
    string(4) "Inch"
  }
  ["IFD1"]=>
  array(4) {
    ["Compression"]=>
    string(32) "Internal error (unknown value 0)"
    ["XResolution"]=>
    string(2) "72"
    ["YResolution"]=>
    string(2) "72"
    ["ResolutionUnit"]=>
    string(4) "Inch"
  }
  ["EXIF"]=>
  array(3) {
    ["ExifVersion"]=>
    string(16) "Exif Version 2.1"
    ["FlashPixVersion"]=>
    string(20) "FlashPix Version 1.0"
    ["ColorSpace"]=>
    string(12) "Uncalibrated"
  }
  ["COMPUTED"]=>
  array(2) {
    ["ByteOrder"]=>
    int(0)
    ["ByteOrderName"]=>
    string(8) "Motorola"
  }
}
