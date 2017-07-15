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

#include <libexif/exif-data.h>
#include <libexif/exif-loader.h>

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_exifkit_thumbnail, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_exifkit_read_data, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, thumbnail)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ exifkit_functions[]
 */
const zend_function_entry exifkit_functions[] = {
	PHP_FE(exifkit_thumbnail,		arginfo_exifkit_thumbnail)
	PHP_FE(exifkit_read_data,		arginfo_exifkit_read_data)
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

/* {{{ ZEND_TSRMLS_CACHE_DEFINE
 */
#if defined(ZTS) && defined(COMPILE_DL_EXIFKIT)
ZEND_TSRMLS_CACHE_DEFINE()
#endif
/* }}} */

/* {{{ exifkit_module_entry
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

/* {{{ ZEND_GET_MODULE
 */
#ifdef COMPILE_DL_EXIFKIT
ZEND_GET_MODULE(exifkit)
#endif
/* }}} */

/* {{{ exifkit_ifd_table
*/
static const struct {
	ExifIfd ifd;
	const char *name;
} exifkit_ifd_table[] = {
	{ EXIFKIT_SECTION_IFD_0, "IFD0" }, 
	{ EXIFKIT_SECTION_IFD_1, "IFD1" }, 
	{ EXIFKIT_SECTION_EXIF, "EXIF" }, 
	{ EXIFKIT_SECTION_GPS, "GPS" }, 
	{ EXIFKIT_SECTION_INTEROP, "INTEROP" }, 
	/* { EXIFKIT_SECTION_THUMB, "THUMBNAIL" }, */
	/* { EXIFKIT_SECTION_MAKER, "MAKERNOTE" }, */
	{ EXIFKIT_SECTION_COMPUTED, "COMPUTED" },
	{ 0, NULL }
};
/* }}} */

/* {{{ exifkit_get_section_name
 */
static const char *exifkit_get_section_name(ExifIfd ifd)
{
	unsigned int i;

	for (i = 0; exifkit_ifd_table[i].name; i++) {
		if (exifkit_ifd_table[i].ifd == ifd) {
				return exifkit_ifd_table[i].name;
		}
	}

	return "";
}
 /* }}} */

/* {{{ exifkit_add_tag
 */
static void exifkit_add_section(zval *rv, const char *section, ExifContent *content)
{
	zval zv;
	unsigned int i;

	if (!content || !content->count) {
		return;
	}

	array_init(&zv);

	for (i = 0; i < content->count; i++) {
		char value[1024];
		ExifEntry *entry = content->entries[i];

		if (!entry) {
			continue;
		}

		add_assoc_string(&zv, exif_tag_get_name_in_ifd(entry->tag, exif_entry_get_ifd(entry)), exif_entry_get_value(entry, value, sizeof(value)));
	}

	if (zend_hash_num_elements(Z_ARRVAL(zv))) {
		add_assoc_zval(rv, section, &zv);
	}
}
/* }}} */

/* {{{ exifkit_add_computed_section
 */
static void exifkit_add_computed_section(zval *rv, ExifData *data)
{
	zval zv;
	ExifByteOrder byte_order = exif_data_get_byte_order(data);
	const char *byte_order_name = exif_byte_order_get_name(byte_order);

	array_init(&zv);

	add_assoc_long(&zv, "ByteOrder", byte_order);
	add_assoc_string(&zv, "ByteOrderName", (byte_order_name ? byte_order_name : "<Default>"));

	add_assoc_zval(rv, exifkit_get_section_name(EXIFKIT_SECTION_COMPUTED), &zv);
}
/* }}} */

/* {{{ PHP_FUNCTION(exifkit_thumbnail)
 */
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

		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ PHP_FUNCTION(exifkif_read_data)
 */
PHP_FUNCTION(exifkit_read_data)
{
	ExifData *data;
	char *file;
	size_t file_len;
	zend_bool thumbnail = TRUE;
	unsigned int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "p", &file, &file_len, &thumbnail) == FAILURE) {
		return;
	}


	/* TODO: Look at passing options to be in more compliance with ext/exif */

	data = exif_data_new_from_file(file);

	if (!data) {
		php_error_docref(NULL, E_WARNING, "Unable to load file");

		RETURN_FALSE;
	}

	array_init(return_value);

	for (i = 0; i < EXIF_IFD_COUNT; i++) {
		if (data->ifd[i] && data->ifd[i]->count) {
			exifkit_add_section(return_value, exifkit_get_section_name(i), data->ifd[i]);
		}
	}

	if (thumbnail && data->data) {
		/* TODO: Implement thumbnail section */
	}

	/* TODO: Implement MAKERNOTE section */

	exifkit_add_computed_section(return_value, data);

	exif_data_unref(data);

	if (!zend_hash_num_elements(Z_ARRVAL_P(return_value))) {
		RETURN_FALSE;
	}
}
/* }}}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 tw=78 fdm=marker
 * vim<600: sw=4 ts=4 tw=78
 */
