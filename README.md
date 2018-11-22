## pecl-exifkit

`pecl-exifkit` attempts to expose the capabilities of libexif, this is currently a slow and early preview.

## Dependencies

`libexif` is required (and bundled). `libexif` is slightly modified in order to compile. Below is the changes made to make `libexif` compile:

 * The bundled library is version 2.5.2pre1
 * A `config.h` file is included in the root of the library folder
 * The inline keyword has been removed for the `exif_tag_table_count()` function
 * A warning about signedness has been fixed in `exif-entry.c`

## Support

This extension currently only supports Windows! \o/

## Installation

To compile this into your PHP installation, you need to compile PHP with `configure --enable-exifkit`. This extension can also be compiled as a shard extension like; `configure --enable-exifkit=shared`.

## API Reference

### Constants

 * `EXIFKIT_LIBVER`: The libexif version used to compile pecl/exifkit
 * `EXIFKIT_BYTEORDER_MOTOROLA`: Motorola byte order, see the `COMPUTED` section in the `exifkit_read_data()` function block below
 * `EXIFKIT_BYTEORDER_INTEL`: Intel byte order, see the `COMPUTED` section in the `exifkit_read_data()` function block below

### Functions

```
function exifkit_thumbnail(string $file) : string | bool
```

The `exifkit_thumbnail()` function works exactly like the `exif_thumbnail()` function, it returns a string with the thumbnail data and if an error should occur, it will return false. 

```
function exifkit_read_data(string $file [, bool $thumbnail = false ]) : array | bool
```

The `exifkit_read_data()` function reads all tags and returns them. Tags are returned in their respective sections. The following sections can be returned:

 * `IFD0`
 * `IFD1`
 * `EXIF`
 * `GPS`
 * `INTEROP`
 * `COMPUTED`
 * `THUMBNAIL` (Not implemented yet)
 * `MAKERNOTE` (Not implemented yet)

 The `COMPUTED` section contains computed information regarding the EXIF data found in the header. Currently the following can be returned in the `COMPUTED` section:

 * `ByteOrder`: The numeric byte order value. This value can be compared against `EXIFKIT_BYTEORDER_MOTOROLA` and `EXIFKIT_BYTEORDER_INTEL`.
 * `ByteOrderName`: The name of the byte order. This can either be `Motorola` or `Intel`

## Contributing

Should you find this extension interesting in anyway, you are welcome to contribute in anyway possible by submitting reports and pull requests.

## Copyright

 * `pecl-exifkit`: Copyright (c) 2017, Kalle Sommer Nielsen <kalle@php.net>
 * `libexif`: Copyright (c) 2001, Lutz Mueller <lutz@users.sourceforge.net>

## License

 * `pecl-exifkit` is licensed under the PHP License 3.01.

 * `libexif` is licensed under the GNU Lesser General Public License 2 (LGPL2).
