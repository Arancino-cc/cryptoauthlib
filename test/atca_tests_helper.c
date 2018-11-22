/**
 * \file
 * \brief Unity tests for the cryptoauthlib Verify Command
 *
 * \copyright (c) 2017 Microchip Technology Inc. and its subsidiaries.
 *            You may use this software and any derivatives exclusively with
 *            Microchip products.
 *
 * \page License
 *
 * (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
 * software and any derivatives exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIPS TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
 * TERMS.
 */
#include <stdlib.h>
#include "atca_test.h"
#include "basic/atca_basic.h"
#include "atca_host.h"
#include "atca_tests.h"


#define ATCA_TESTS_HELPER_DEVICES   ( DEVICE_MASK(ATSHA204A) | DEVICE_MASK(ATECC108A) | DEVICE_MASK(ATECC508A) | DEVICE_MASK(ATECC608A) )

static const uint8_t atca_tests_helper_base64_vector_in0[] = "We were henceforth to be hurled along, the playthings of the fierce elements of the deep.       \n";
static const char atca_tests_helper_base64_vector_out0[] = "V2Ugd2VyZSBoZW5jZWZvcnRoIHRvIGJlIGh1cmxlZCBhbG9uZywgdGhlIHBsYXl0\r\n"
                                                           "aGluZ3Mgb2YgdGhlIGZpZXJjZSBlbGVtZW50cyBvZiB0aGUgZGVlcC4gICAgICAg\r\n"
                                                           "Cg==";

/* Vector of all possible uint8_t values */
static uint8_t atca_tests_helper_base64_vector_in1[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
};

static char atca_tests_helper_base64_vector_out1[] =
    "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4v\r\n"
    "MDEyMzQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5f\r\n"
    "YGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6P\r\n"
    "kJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/\r\n"
    "wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v\r\n"
    "8PHy8/T19vf4+fr7/P3+/w==";

static char atca_tests_helper_base64_vector_url1[] =
    "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4v"
    "MDEyMzQ1Njc4OTo7PD0-P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5f"
    "YGFiY2RlZmdoaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn-AgYKDhIWGh4iJiouMjY6P"
    "kJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmqq6ytrq-wsbKztLW2t7i5uru8vb6_"
    "wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t_g4eLj5OXm5-jp6uvs7e7v"
    "8PHy8_T19vf4-fr7_P3-_w";

/* Parameterized Encode Test */
static void atca_tests_helper_base64_encode(const uint8_t * pIn, size_t in_len,
                                            const char* pOut, size_t out_len, const uint8_t* rules, uint8_t dirty)
{
    ATCA_STATUS status;
    char encoded[512];
    size_t encodedLen;

    /* Check inputs */
    TEST_ASSERT(pIn);
    TEST_ASSERT(in_len);
    TEST_ASSERT(pOut);
    TEST_ASSERT(out_len);

    /* Set the buffer */
    memset(encoded, dirty ? 0xFF : 0, sizeof(encoded));

    /* Encode the input string */
    encodedLen = sizeof(encoded);
    status = atcab_base64encode_(pIn, in_len, encoded, &encodedLen, rules);
    TEST_ASSERT_EQUAL(ATCA_SUCCESS, status);

    /* Check the result is null terminated */
    TEST_ASSERT_FALSE(encoded[encodedLen]);

    /* Check the resulting sizes */
    TEST_ASSERT_EQUAL(out_len, encodedLen);

    /* Check that the buffer matches the expected */
    TEST_ASSERT_EQUAL_MEMORY(encoded, pOut, encodedLen);
}

/* Parameterized Decode Test */
static void atca_tests_helper_base64_decode(const char * pIn, size_t in_len,
                                            const uint8_t* pOut, size_t out_len, const uint8_t* rules, uint8_t dirty)
{
    ATCA_STATUS status;
    uint8_t decoded[512];
    size_t decodedLen;

    /* Check inputs */
    TEST_ASSERT_NOT_NULL_MESSAGE(pIn, "pIn");
    TEST_ASSERT_MESSAGE(in_len, "in_len");
    TEST_ASSERT_NOT_NULL_MESSAGE(pOut, "pOut");
    TEST_ASSERT_MESSAGE(out_len, "out_len");

    /* Set the buffer */
    memset(decoded, dirty ? 0xFF : 0, sizeof(decoded));

    /* Encode the input string */
    decodedLen = sizeof(decoded);
    status = atcab_base64decode_(pIn, in_len, decoded, &decodedLen, rules);
    TEST_ASSERT_EQUAL(ATCA_SUCCESS, status);

    /* Check the resulting sizes */
    TEST_ASSERT_EQUAL(out_len, decodedLen);

    /* Check that the buffer matches the expected */
    TEST_ASSERT_EQUAL_MEMORY(decoded, pOut, decodedLen);
}

/* Parameterized Encode - Decode Test */
static void atca_tests_helper_base64_encode_decode(const uint8_t * pIn, size_t in_len, uint8_t dirty)
{
    ATCA_STATUS status;

    char encoded[512];
    uint8_t decoded[512];

    size_t encodedLen;
    size_t decodedLen;

    if (dirty)
    {
        memset(encoded, 0xFF, sizeof(encoded));
        memset(decoded, 0xFF, sizeof(decoded));
    }
    else
    {
        memset(encoded, 0, sizeof(encoded));
        memset(decoded, 0, sizeof(decoded));
    }

    /* Encode the input string */
    encodedLen = sizeof(encoded);
    status = atcab_base64encode(pIn, in_len, encoded, &encodedLen);
    TEST_ASSERT_EQUAL(ATCA_SUCCESS, status);

    /* Decode the result */
    decodedLen = sizeof(decoded);
    status = atcab_base64decode(encoded, encodedLen, decoded, &decodedLen);
    TEST_ASSERT_EQUAL(ATCA_SUCCESS, status);

    /* Check the resulting sizes */
    TEST_ASSERT_EQUAL(in_len, decodedLen);

    /* Check that the buffer is what we stared with */
    TEST_ASSERT_EQUAL_MEMORY(decoded, pIn, decodedLen);
}

TEST_GROUP(atca_helper);

TEST_SETUP(atca_helper)
{

}

TEST_TEAR_DOWN(atca_helper)
{

}

TEST(atca_helper, base64_encode)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in0;
    size_t in_len = sizeof(atca_tests_helper_base64_vector_in0) - 1;
    const char * out = atca_tests_helper_base64_vector_out0;
    size_t out_len = strlen(out);

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_default, false);
}

TEST(atca_helper, base64_encode_to_dirty_buffer)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in0;
    size_t in_len = sizeof(atca_tests_helper_base64_vector_in0) - 1;
    const char * out = atca_tests_helper_base64_vector_out0;
    size_t out_len = strlen(out);

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_default, true);
}

TEST(atca_helper, base64_decode)
{
    const char * in = atca_tests_helper_base64_vector_out0;
    size_t in_len = strlen(in);
    const uint8_t * out = atca_tests_helper_base64_vector_in0;
    size_t out_len = sizeof(atca_tests_helper_base64_vector_in0) - 1;

    atca_tests_helper_base64_decode(in, in_len, out, out_len,
                                    atcab_b64rules_default, false);
}

TEST(atca_helper, base64_decode_to_dirty_buffer)
{
    const char * in = atca_tests_helper_base64_vector_out0;
    size_t in_len = strlen(in);
    const uint8_t * out = atca_tests_helper_base64_vector_in0;
    size_t out_len = sizeof(atca_tests_helper_base64_vector_in0) - 1;

    atca_tests_helper_base64_decode(in, in_len, out, out_len,
                                    atcab_b64rules_default, true);
}

TEST(atca_helper, base64_encode_decode)
{
    const uint8_t * buf = atca_tests_helper_base64_vector_in1;
    size_t buf_len = sizeof(atca_tests_helper_base64_vector_in1);

    atca_tests_helper_base64_encode_decode(buf, buf_len, false);
}

TEST(atca_helper, base64_encode_decode_mod_3)
{
    const uint8_t * buf = atca_tests_helper_base64_vector_in1;
    size_t buf_len = 96;

    atca_tests_helper_base64_encode_decode(buf, buf_len, false);
}

TEST(atca_helper, base64_encode_decode_mod_3_minus_1)
{
    const uint8_t * buf = atca_tests_helper_base64_vector_in1;
    size_t buf_len = 96 - 1;

    atca_tests_helper_base64_encode_decode(buf, buf_len, true);
}

TEST(atca_helper, base64_encode_decode_mod_3_minus_2)
{
    const uint8_t * buf = atca_tests_helper_base64_vector_in1;
    size_t buf_len = 96 - 2;

    atca_tests_helper_base64_encode_decode(buf, buf_len, true);
}

TEST(atca_helper, base64_encode_decode_mod_3_minus_3)
{
    const uint8_t * buf = atca_tests_helper_base64_vector_in1;
    size_t buf_len = 96 - 3;

    atca_tests_helper_base64_encode_decode(buf, buf_len, true);
}

TEST(atca_helper, base64_encode_check_newline_32)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in0;
    size_t in_len = 24;
    const char * out = atca_tests_helper_base64_vector_out0;
    size_t out_len = 32;

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_default, true);
}

TEST(atca_helper, base64_encode_check_newline_64)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in0;
    size_t in_len = 48;
    const char * out = atca_tests_helper_base64_vector_out0;
    size_t out_len = 64;

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_default, true);
}

TEST(atca_helper, base64_encode_check_newline_96)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in0;
    size_t in_len = 72;
    const char * out = atca_tests_helper_base64_vector_out0;
    size_t out_len = 96 + 2;    /* 1x Newline added */

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_default, true);
}

TEST(atca_helper, base64_encode_check_newline_128)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in0;
    size_t in_len = 96;
    const char * out = atca_tests_helper_base64_vector_out0;
    size_t out_len = 128 + 2;   /* 1x Newline added */

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_default, true);
}

TEST(atca_helper, base64_url_encode)
{
    const uint8_t * in = atca_tests_helper_base64_vector_in1;
    size_t in_len = sizeof(atca_tests_helper_base64_vector_in1);
    const char * out = atca_tests_helper_base64_vector_url1;
    size_t out_len = strlen(atca_tests_helper_base64_vector_url1);

    atca_tests_helper_base64_encode(in, in_len, out, out_len,
                                    atcab_b64rules_urlsafe, true);
}

TEST(atca_helper, base64_url_decode)
{
    const char * in = atca_tests_helper_base64_vector_url1;
    size_t in_len = strlen(atca_tests_helper_base64_vector_url1);
    const uint8_t * out = atca_tests_helper_base64_vector_in1;
    size_t out_len = sizeof(atca_tests_helper_base64_vector_in1);

    atca_tests_helper_base64_decode(in, in_len, out, out_len,
                                    atcab_b64rules_urlsafe, true);
}

t_test_case_info helper_basic_test_info[] =
{
    { REGISTER_TEST_CASE(atca_helper, base64_encode),                      ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_to_dirty_buffer),      ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_decode),                      ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_decode_to_dirty_buffer),      ATCA_TESTS_HELPER_DEVICES },
                                                                                                     
    { REGISTER_TEST_CASE(atca_helper, base64_encode_decode),               ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_decode_mod_3),         ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_decode_mod_3_minus_1), ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_decode_mod_3_minus_2), ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_decode_mod_3_minus_3), ATCA_TESTS_HELPER_DEVICES },
                                                                                                     
    { REGISTER_TEST_CASE(atca_helper, base64_encode_check_newline_32),     ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_check_newline_64),     ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_check_newline_96),     ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_encode_check_newline_128),    ATCA_TESTS_HELPER_DEVICES },
                                                                                                     
    { REGISTER_TEST_CASE(atca_helper, base64_url_encode),                  ATCA_TESTS_HELPER_DEVICES },
    { REGISTER_TEST_CASE(atca_helper, base64_url_decode),                  ATCA_TESTS_HELPER_DEVICES },

    { (fp_test_case)NULL,             (uint8_t)0 },                        /* Array Termination element*/
};
