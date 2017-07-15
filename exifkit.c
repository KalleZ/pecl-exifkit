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
   | Authors: Kalle Sommer Nielsen <kalle@php.net>                        |
   +----------------------------------------------------------------------+
 */

/* $Id: $ */

#include "php.h"
#include "php_exifkit.h"
#include "ext/standard/info.h"

#include <libexif/exif-loader.h>

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_exifkit_thumbnail, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ exif_functions[]
 */
const zend_function_entry exifkit_functions[] = {
	PHP_FE(exifkit_thumbnail, arginfo_exifkit_thumbnail)
	PHP_FE_END
};
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(exifkit)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "EXIFKit Support", "enabled");
	php_info_print_table_row(2, "EXIFKit Version", PHP_EXIFKIT_VERSION);
	php_info_print_table_row(2, "Libexif Version", LIBEXIF_VERSION);
	php_info_print_table_end();
}
/* }}} */

#if defined(ZTS) && defined(COMPILE_DL_EXIFKIT)
ZEND_TSRMLS_CACHE_DEFINE()
#endif

/* {{{ exif_module_entry
 */
zend_module_entry exifkit_module_entry = {
	STANDARD_MODULE_HEADER,
	"exifkit",
	exifkit_functions,
	NULL, 
	NULL,
	NULL,
	NULL,
	PHP_MINFO(exifkit),
	PHP_EXIFKIT_VERSION,
	STANDARD_MODULE_PROPERTIES,
};
/* }}} */

#ifdef COMPILE_DL_EXIFKIT
ZEND_GET_MODULE(exifkit)
#endif

PHP_FUNCTION(exifkit_thumbnail)
{
	ExifLoader *loader;
	char *file;
	size_t file_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "p", &file, &file_len) == FAILURE) {
		return;
	}

	loader = exif_loader_new();

	if (loader) {
		ExifData *data;

		exif_loader_write_file(loader, file);

		data = exif_loader_get_data(loader);

		exif_loader_unref(loader);

		if (!data) {
			RETURN_FALSE;
		}

		RETVAL_STRINGL(data->data, data->size);

		exif_data_unref(data);
	} else {
		php_error_docref(NULL, E_WARNING, "Unable to load libexif");
	}
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 tw=78 fdm=marker
 * vim<600: sw=4 ts=4 tw=78
 */
