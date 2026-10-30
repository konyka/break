# TLS test fixtures

`break_test_cert.pem` and `break_test_key.pem` are a self-signed EC P-256
certificate (CN=localhost, subjectAltName=DNS:localhost, valid 2020-01-01 to
2049-12-31) used only by the `break_http`, update and crash end-to-end tests.
They are checked in so those tests do not depend on any other source tree.
The key protects nothing: it is public, never installed, and never loaded by a
shipped binary.

Regenerate with:

    openssl req -x509 -newkey ec -pkeyopt ec_paramgen_curve:prime256v1 \
        -keyout break_test_key.pem -out break_test_cert.pem -sha256 -nodes \
        -subj '/CN=localhost' -addext 'subjectAltName=DNS:localhost' \
        -not_before 20200101000000Z -not_after 20491231235959Z
