--TEST--
exifkit_read_data() Test 2
--SKIPIF--
<?php
	if (!extension_loaded('exifkit')) {
		print('skip: exifkit extension not available');
	}
?>
--FILE--
<?php
var_dump(exifkit_read_data(__DIR__ . '/test-2.jpg'));
?>
--EXPECT--
array(5) {
  ["IFD0"]=>
  array(7) {
    ["Orientation"]=>
    string(8) "Top-left"
    ["Model"]=>
    string(8) "SGH-i900"
    ["Make"]=>
    string(7) "SAMSUNG"
    ["Software"]=>
    string(11) "Mits Camera"
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
    string(16) "JPEG compression"
    ["XResolution"]=>
    string(2) "72"
    ["YResolution"]=>
    string(2) "72"
    ["ResolutionUnit"]=>
    string(4) "Inch"
  }
  ["EXIF"]=>
  array(20) {
    ["ExposureTime"]=>
    string(11) "1/1666 sec."
    ["ExifVersion"]=>
    string(16) "Exif Version 2.2"
    ["Contrast"]=>
    string(6) "Normal"
    ["Saturation"]=>
    string(6) "Normal"
    ["Sharpness"]=>
    string(6) "Normal"
    ["MeteringMode"]=>
    string(23) "Center-weighted average"
    ["ISOSpeedRatings"]=>
    string(2) "50"
    ["PixelXDimension"]=>
    string(4) "2560"
    ["PixelYDimension"]=>
    string(4) "1920"
    ["DateTimeOriginal"]=>
    string(19) "2009:11:19 12:16:43"
    ["DateTimeDigitized"]=>
    string(19) "2009:11:19 12:16:43"
    ["WhiteBalance"]=>
    string(18) "Auto white balance"
    ["Flash"]=>
    string(11) "Flash fired"
    ["FocalLength"]=>
    string(6) "4.5 mm"
    ["UserComment"]=>
    string(4) "ASCI"
    ["FNumber"]=>
    string(5) "f/2.8"
    ["CustomRendered"]=>
    string(14) "Normal process"
    ["DigitalZoomRatio"]=>
    string(3) "1.0"
    ["FlashPixVersion"]=>
    string(20) "FlashPix Version 1.0"
    ["ColorSpace"]=>
    string(12) "Uncalibrated"
  }
  ["GPS"]=>
  array(8) {
    ["GPSVersionID"]=>
    string(7) "1.0.0.0"
    ["GPSLatitudeRef"]=>
    string(1) "N"
    ["GPSLatitude"]=>
    string(24) "43.0000, 16.0000, 7.4765"
    ["GPSLongitudeRef"]=>
    string(1) "E"
    ["GPSLongitude"]=>
    string(25) "77.0000, 21.0000, 53.3843"
    ["GPSAltitudeRef"]=>
    string(9) "Sea level"
    ["GPSAltitude"]=>
    string(8) "1599.000"
    ["GPSMapDatum"]=>
    string(6) "WGS-84"
  }
  ["COMPUTED"]=>
  array(2) {
    ["ByteOrder"]=>
    int(1)
    ["ByteOrderName"]=>
    string(5) "Intel"
  }
}
