#include "sha.h"
#include <mbedtls/sha256.h>
#include <stdio.h>

int oefs_sha256(oefs_sha256_t* hash, const void* data, size_t size)
{
    int ret = -1;
    mbedtls_sha256_context ctx;

    if (hash)
        memset(hash, 0, sizeof(oefs_sha256_t));

    if (!hash || !data)
        goto done;

    mbedtls_sha256_init(&ctx);

    if (mbedtls_sha256_starts_ret(&ctx, 0) != 0)
        goto done;

    if (mbedtls_sha256_update_ret(&ctx, data, size) != 0)
        goto done;

    if (mbedtls_sha256_finish_ret(&ctx, hash->u.bytes) != 0)
        goto done;

    ret = 0;

done:
    return ret;
}

void oefs_sha256_dump(const oefs_sha256_t* hash)
{
    for (size_t i = 0; i < sizeof(oefs_sha256_t); i++)
    {
        uint8_t byte = hash->u.bytes[i];
        printf("%02x", byte);
    }

    printf("\n");
}

int oefs_sha256_v(oefs_sha256_t* hash, const oefs_vector_t* vector, size_t size)
{
    int ret = -1;
    mbedtls_sha256_context ctx;

    if (hash)
        memset(hash, 0, sizeof(oefs_sha256_t));

    if (!hash || !vector)
        goto done;

    mbedtls_sha256_init(&ctx);

    if (mbedtls_sha256_starts_ret(&ctx, 0) != 0)
        goto done;

    for (size_t i = 0; i < size; i++)
    {
        const oefs_vector_t* v = &vector[i];

        if (mbedtls_sha256_update_ret(&ctx, v->data, v->size) != 0)
            goto done;
    }

    if (mbedtls_sha256_finish_ret(&ctx, hash->u.bytes) != 0)
        goto done;

    ret = 0;

done:
    return ret;
}
