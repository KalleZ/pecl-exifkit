/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2017 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Marcus Boerger <helly@php.net>                              |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifndef HAVE_EXIFKIT_H
# define HAVE_EXIFKIT_H

# define PHP_EXIFKIT_VERSION "1.0.0 Alpha 1"

extern zend_module_entry exifkit_module_entry;
# define phpext_exifkit_ptr &exifkit_module_entry

# define EXIFKIT_SECTION_IFD_0			EXIF_IFD_0
# define EXIFKIT_SECTION_IFD_1			EXIF_IFD_1
# define EXIFKIT_SECTION_EXIF			EXIF_IFD_EXIF
# define EXIFKIT_SECTION_GPS			EXIF_IFD_GPS
# define EXIFKIT_SECTION_INTEROP		EXIF_IFD_INTEROPERABILITY
/* # define EXIFKIT_SECTION_THUMBNAIL		(1 << 5) */
/* # define EXIFKIT_SECTION_MAKER		(1 << 6) */
# define EXIFKIT_SECTION_COMPUTED		(1 << 7)

PHP_FUNCTION(exifkit_thumbnail);
PHP_FUNCTION(exifkit_read_data);

#endif
