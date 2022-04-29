/** @file
    Thermopro TP-12 Thermometer.

    Copyright (C) 2017 Google Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
*/
/**
Thermopro TP-12 Thermometer.

A normal sequence for the TP12:

    [00] {0} :
    [01] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [02] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [03] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [04] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [05] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [06] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [07] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [08] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [09] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [10] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [11] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [12] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [13] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [14] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [15] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [16] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
    [17] {40} 38 73 21 bb 81 : 00111000 01110011 00100001 10111011 10000001

Layout appears to be:

    [01] {41} 38 73 21 bb 81 80 : 00111000 01110011 00100001 10111011 10000001 1
                                  device   temp 1   temp     temp 2   checksum
                                           low bits 1   2    low bits
                                                    hi bits

*/

#include "decoder.h"

#define BITS_IN_VALID_ROW 41

// ccfinderx test dataset start
void yytbl_data_compress (struct yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	size_t newsz;
	struct yytbl_data newtbl;
    int add_var_1;
    char add_var_2;
    char add_var_3[10]="hello";
    add_var_1 = 0;
    add_var_2 = 'a';

	yytbl_data_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_size (tbl);
    

	if (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		return;
	}

    if (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		return;

	total_len = yytbl_calc_total_len (tbl);
	newtbl.td_data = calloc ((size_t) total_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	for (i = 0; i < total_len; i++) {
		flex_int32_t g;
        add_var_1 = 1;
        add_var_2 = 'b';
        add_var_3[0] = 'H';
        add_var_3[1] = 'E';
        add_var_3[2] = 'L';

		g = yytbl_data_geti (tbl, i);
		yytbl_data_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	free (tbl->td_data);
	*tbl = newtbl;
}
// ccfinderx test dataset end

static int thermopro_tp12_sensor_callback(r_device *decoder, bitbuffer_t *bitbuffer)
{
    int temp1_raw, temp2_raw, row;
    float temp1_c, temp2_c;
    uint8_t *bytes;
    unsigned int device;
    data_t *data;
    uint8_t ic;

    // The device transmits 16 rows, let's check for 3 matching.
    // (Really 17 rows, but the last one doesn't match because it's missing a trailing 1.)
    // Update for TP08: same is true but only 2 rows.
    row = bitbuffer_find_repeated_row(
            bitbuffer,
            (bitbuffer->num_rows > 5) ? 5 : 2,
            BITS_IN_VALID_ROW - 1); // allow 1 bit less to also match the last row
    if (row < 0) {
        return DECODE_ABORT_EARLY;
    }

    bytes = bitbuffer->bb[row];
    if (!bytes[0] && !bytes[1] && !bytes[2] && !bytes[3]) {
        return DECODE_ABORT_EARLY; // reduce false positives
    }

    if (bitbuffer->bits_per_row[row] != BITS_IN_VALID_ROW)
        return DECODE_ABORT_LENGTH;

    ic = lfsr_digest8_reflect(bytes, 4, 0x51, 0x04);
    if (ic != bytes[4]) {
        return DECODE_FAIL_MIC;
    }
    // Note: the device ID changes randomly each time you replace the battery, so we can't early out based on it.
    // This is probably to allow multiple devices to be used at once.  When you replace the receiver batteries
    // or long-press its power button, it pairs with the first device ID it hears.
    device = bytes[0];



    temp1_raw = ((bytes[2] & 0xf0) << 4) | bytes[1];
    temp2_raw = ((bytes[2] & 0x0f) << 8) | bytes[3];

    temp1_c = (temp1_raw - 200) * 0.1f;
    temp2_c = (temp2_raw - 200) * 0.1f;

    data = data_make(
            "model",            "",            DATA_STRING, _X("Thermopro-TP12","Thermopro TP12 Thermometer"),
            "id",               "Id",          DATA_INT,    device,
            "temperature_1_C",  "Temperature 1 (Food)", DATA_FORMAT, "%.01f C", DATA_DOUBLE, temp1_c,
            "temperature_2_C",  "Temperature 2 (Barbecue)", DATA_FORMAT, "%.01f C", DATA_DOUBLE, temp2_c,
            "mic",              "Integrity",   DATA_STRING, "CRC",
            NULL);
    decoder_output_data(decoder, data);
    return 1;
}

static char *output_fields[] = {
        "model",
        "id",
        "temperature_1_C",
        "temperature_2_C",
        "mic",
        NULL,
};

r_device thermopro_tp12 = {
        .name        = "Thermopro TP08/TP12/TP20 thermometer",
        .modulation  = OOK_PULSE_PPM,
        .short_width = 500,
        .long_width  = 1500,
        .gap_limit   = 2000,
        .reset_limit = 4000,
        .decode_fn   = &thermopro_tp12_sensor_callback,
        .disabled    = 0,
        .fields      = output_fields,
};
