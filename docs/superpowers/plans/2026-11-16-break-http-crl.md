# break_http certificate revocation lists (2026-11-16)

## Goal
`break_http` checks the CA chain, host name, validity dates and optional
public-key pins, but not revocation: a leaf certificate the CA has revoked
still connects. `docs/design/update_transport.md` §4 lists CRL/OCSP as not
delivered. This slice adds CRL checking from a local file, in the same
explicit-trust style as `ca_file` (no network fetch of CRLs, no system
store).

## Design
- `BreakHttpConfig` gets `const char *crl_file` (PEM, one or more CRLs).
  NULL or "" keeps today's behavior exactly.
- When set, every CRL in the file is added to the context's X509 store and
  `X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL` is set, so OpenSSL
  checks every certificate of the verified chain (leaf and CAs) against a
  CRL from its issuer during the handshake:
  - a revoked certificate fails verification: `BHTTP_ERR_TLS`;
  - a certificate whose issuer has no CRL in the file fails as well
    (`X509_V_ERR_UNABLE_TO_GET_CRL`): a configured CRL file is a promise
    to cover the chain, so a gap is not silently accepted;
  - an expired CRL (`nextUpdate` in the past) or a CRL not signed by the
    issuer fails (OpenSSL's own checks).
- A CRL file that cannot be read or holds no CRL: `BHTTP_ERR_URL` before
  any socket, like a missing CA file.
- Plain loopback http ignores `crl_file` (as it ignores pins).
- Not done here: OCSP and OCSP stapling, CRL distribution-point fetching,
  delta CRLs.

## Tests (TDD, `test_break_http`)
The test generates a CA, a leaf signed by it for localhost, and CRLs
signed by the CA:
- control: an empty CRL from the CA (nothing revoked) connects;
- the leaf's serial in the CRL: `BHTTP_ERR_TLS`;
- a CRL file whose only CRL comes from another CA: `BHTTP_ERR_TLS`;
- an expired CRL: `BHTTP_ERR_TLS`;
- a missing CRL file, and a file with no CRL in it: `BHTTP_ERR_URL`
  without a connection;
- the revoked leaf over plain loopback http still works (ignored);
- no `crl_file`: the revoked leaf still connects (unchanged behavior);
- a root -> intermediate -> leaf chain: both CRLs present connects; the
  intermediate revoked by the root, a missing root CRL, or the leaf revoked
  by the intermediate are each `BHTTP_ERR_TLS`.

## Status
- RED: with only the config field added, the three revocation cases failed
  and the control passed (the generated PKI was sound).
- GREEN: `test_break_http` 48/48 (was 37 + 7 pin tests).
- Mutation: the first run had three survivors. Two were the return value
  of `X509_STORE_add_crl` (it fails only when out of memory, and a CRL
  that was not added already leaves the issuer without a CRL, which the
  chain check refuses), so the check was removed. The third showed the
  plan's "leaf only" scope was not tested either way; the chain is now
  checked in full (`X509_V_FLAG_CRL_CHECK_ALL`) and a three-level chain
  test pins it. Second run: 9 mutations, all killed.

