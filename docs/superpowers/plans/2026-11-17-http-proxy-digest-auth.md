# break_http: Digest authentication for the CONNECT proxy (2026-11-17)

Status: Done

## Goal
`break_http` sends proxy credentials only as Basic
(`docs/cross_engine/missing_capabilities.md` §15, "Digest/NTLM 等其他代理认证").
A proxy that only accepts Digest (RFC 7616) answers 407 and the tunnel
fails. This slice answers one Digest challenge.

## Design
- The first CONNECT is unchanged (Basic when credentials are set).
- When it is answered 407, credentials are set and a
  `Proxy-Authenticate: Digest ...` header carries an acceptable challenge,
  the client closes the connection, opens a new one to the proxy (same
  connect budget, same total I/O deadline) and sends CONNECT once more with
  `Proxy-Authorization: Digest ...` and no Basic header. Any answer to the
  second CONNECT is final: a second 407 is ERR_STATUS, there is no third
  attempt.
- Challenge parsing (header name and scheme case-insensitive; the first
  header whose value starts with `Digest ` and parses wins, others such as
  Basic are skipped):
  - auth-params `name=token` or `name="quoted"` separated by commas; a
    quoted value may use `\x` escapes but must not yield `"`, `\` or a
    control byte, and is at most 255 bytes. `realm` and `nonce` must be
    present, `nonce` non-empty. A duplicate known param, an empty name, a
    missing `=`, an unterminated quote, a trailing comma or two params
    without a comma reject the challenge.
  - `algorithm`: absent or `MD5` -> MD5, `SHA-256` -> SHA-256; anything else
    (`-sess`, SHA-512-256) is unsupported.
  - `qop`: absent -> RFC 2069 form; a list that contains `auth` -> qop=auth;
    a list without `auth` is unsupported. `userhash` other than `false` is
    unsupported. `opaque` is echoed. Other params are ignored.
  - An unsupported or malformed challenge is not answered: ERR_STATUS as
    before.
- Response: HA1 = H(user:realm:password), HA2 = H("CONNECT:" authority),
  with qop `H(HA1:nonce:00000001:cnonce:auth:HA2)`, without qop
  `H(HA1:nonce:HA2)`; lowercase hex. `cnonce` is 16 random bytes in hex
  (OpenSSL `RAND_bytes`). The user is quoted with `"` and `\` escaped; the
  password never leaves the client.

## Tests (TDD, `test_break_http`)
- MD5 + qop=auth + opaque: tunnel works; first CONNECT has Basic, second
  only Digest with every param, response equals the reference computation.
- SHA-256; the legacy form without qop; header name and scheme in other
  cases, a Basic header before the Digest one, an escaped plain character.
- Maximum sizes (255-byte user of quote characters, password, realm, nonce,
  opaque) fit.
- A second 407 is ERR_STATUS with no third connection.
- Refused challenges (no second connection, ERR_STATUS): unsupported
  algorithm or qop, missing realm or nonce, empty nonce, escaped quote,
  unterminated quote, duplicate param, missing comma, userhash=true,
  256-byte nonce, empty param name, Basic only, `DigestX`, a Digest
  challenge on a 403, a Digest challenge without credentials.

## Not done
NTLM, https proxies, keeping the 407 connection open.

## Result
- RED: 4 of 5 new tests failed; the unusable-challenge test passed on the
  old code, which never answers a challenge. GREEN: `test_break_http` 66/66.
- Mutation: 38 mutants, 8 survived the first round. Trimming trailing
  whitespace of the header value was redundant (the head parser already
  trims) and was removed. Cases for `Digestrealm=`, a missing `=`, an empty
  value, a 256-byte token, a qop list with spaces and empty credentials
  killed 6 more. The guard for a `\` at the very end of a quoted value
  survives: past the value the next byte is `\r`, which is rejected anyway,
  so the behaviour is the same; the guard stays for memory safety.
- Shadow check rc=0.

